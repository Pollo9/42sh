/*
** parser.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:56:07 2006 Seblu
** Last update Tue Aug 29 02:28:28 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include "parser.h"
#include "../common/macro.h"
#include "../shell/shell.h"
#include "getline.h"

/*
** ============
** DECLARATIONS
** ============
*/


/* static ts_token keywords[] = */
/*   { */
/*     {TOK_IF, "if"}, */
/*     {TOK_THEN, "then"}, */
/*     {TOK_ELSE, "else"}, */
/*     {TOK_FI, "fi"}, */
/*     {TOK_ELIF, "elif"}, */
/*     {TOK_DO, "do"}, */
/*     {TOK_DONE, "done"}, */
/*     {TOK_CASE, "case"}, */
/*     {TOK_ESAC, "esac"}, */
/*     {TOK_WHILE, "while"}, */
/*     {TOK_UNTIL, "until"}, */
/*     {TOK_FOR, "for"}, */
/*     {TOK_IN, "in"}, */
/*     {TOK_LBRACE, "{"}, */
/*     {TOK_RBRACE, "}"}, */
/*     {TOK_BANG, "!"}, */
/*     {TOK_NONE, NULL} */
/*   }; */


static s_ast_node	*regnode(s_parser *parser, s_ast_node *node);

/*!
** Parse an input, following the Grammar rule input
** input:       list '\n'
**		list EOF
**		| '\n'
**		| EOF
**
** @param parser parser struct
**
** @return parent ast node, for execution
*/
static s_ast_node	*parse_input(s_parser *parser);

static s_ast_node	*parse_list(s_parser *parser);

static s_ast_node	*parse_andor(s_parser *parser);

static s_ast_node	*parse_pipeline(s_parser *parser);

static s_ast_node	*parse_command(s_parser *parser);

/*!
** Notify a parse error
**
** @param parser parser where error appear
** @param t token near of the error
*/
static void		parse_error(s_parser *parser, s_token t);

#if DEBUG_PARSER==1
# define debugmsg(msg) fprintf(stderr, "debug: %s\n", (msg))
#else
# define debugmsg(msg)
#endif

/*
** ===========
** DEFINITIONS
** ===========
*/

s_parser		*parser_init(int fd)
{
  s_parser		*new;

  secmalloc(new, sizeof (s_parser));
  new->lexer = lexer_init(fd);
  new->error = 0;
  new->regnodes = NULL;
  new->regsize = new->regpos = 0;
  return new;
}

static s_ast_node	*regnode(s_parser *parser, s_ast_node *node)
{
  if (!node)
    return node;
  if (parser->regpos >= parser->regsize) {
    parser->regsize += 50;
    secrealloc(parser->regnodes, parser->regnodes,
	       parser->regsize * sizeof (s_ast_node));
  }
  parser->regnodes[parser->regpos] = node;
  ++parser->regpos;
  return node;
}

static void		parse_error(s_parser *parser, s_token t)
{
  debugmsg("parse_error");
  fprintf(stderr, "%s: syntax error near unexpected token `%s'\n",
	  shell->name, t.str);
  parser->error = 1;
  shell->status = ERROR_PARSE;
  if (parser->regnodes)
    for (register int i = 0; parser->regnodes[i]; ++i)
      ast_destruct(parser->regnodes[i]);
  longjmp(parser->stack, 1);
}

s_ast_node		*parse(s_parser *parser)
{
  parser->regpos = 0;
  parser->error = 0;
  // prevent of too big register ast size
  if (parser->regsize >= 200)
    secrealloc(parser->regnodes, parser->regnodes,
	       (parser->regsize = 50) * sizeof (s_ast_node));
  if (setjmp(parser->stack))
    return NULL;
  show_prompt(PROMPT_PS1);
#if DEBUG_LEXER == 1
  //test lexer mode
  while (1)
    {
      s_token tok = lexer_gettoken(parser->lexer);
      if (tok.id == TOK_EOF)
	exit(69);
      printf("Returned token: %d [%s]\n", tok.id,
	     (*tok.str == '\n') ? "\\n" : tok.str);
      if (tok.id == TOK_NEWLINE)
	show_prompt(PROMPT_PS1);
    }
#endif
  return parse_input(parser);
}

static s_ast_node	*parse_input(s_parser *parser)
{
  s_token		token;
  s_ast_node		*buf;

  debugmsg("parse_input");
  token = lexer_lookahead(parser->lexer);
  if (token.id == TOK_EOF)
    return NULL;
  if (token.id == TOK_NEWLINE) {
    token = lexer_gettoken(parser->lexer);
    return NULL;
  }
  buf = parse_list(parser);
  token = lexer_gettoken(parser->lexer);
  if (token.id != TOK_EOF || token.id != TOK_NEWLINE)
    parse_error(parser, token);
  return buf;
}

static s_ast_node	*parse_list(s_parser *parser)
{
  s_token		token;
  s_ast_node		*lhs;
  s_ast_node		*rhs;

  debugmsg("parse_list");
  lhs = parse_andor(parser);
  token = lexer_lookahead(parser->lexer);
  if (token.id == TOK_SEP || token.id == TOK_SEPAND) {
    lexer_gettoken(parser->lexer);
    rhs = parse_list(parser);
    if (token.id == TOK_SEP)
      return regnode(parser, ast_sep_create(lhs, rhs));
    else
      return regnode(parser, ast_sepand_create(lhs, rhs));
  }
  return lhs;
}

static s_ast_node	*parse_andor(s_parser *parser)
{
  s_token		token;
  s_ast_node		*lhs;
  s_ast_node		*rhs;

  debugmsg("parse_andor");
  lhs = parse_pipeline(parser);
  token = lexer_lookahead(parser->lexer);
  if (token.id == TOK_AND || token.id == TOK_OR) {
    lexer_gettoken(parser->lexer);
    rhs = parse_andor(parser);
    if (token.id == TOK_AND)
      return regnode(parser, ast_and_create(lhs, rhs));
    else
      return regnode(parser, ast_or_create(lhs, rhs));
  }
  return lhs;
}

static s_ast_node	*parse_pipeline(s_parser *parser)
{
  s_token		token;
  s_ast_node		*lhs;
  int			banged = 0;

  debugmsg("parse_pipeline");
  token = lexer_lookahead(parser->lexer);
  if (token.id == TOK_BANG) {
    lexer_gettoken(parser->lexer);
    banged = 1;
  }
  lhs = parse_command(parser);
  return lhs;
}

static s_ast_node	*parse_command(s_parser *parser)
{
  s_token		token;


  token = lexer_lookahead(parser->lexer);
  //if (token.id == TOK_WORD)
  return NULL;
}

/* static s_ast_node	*parse_simplecommand(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_shellcommand(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_funcdec(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_cmdprefix(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_redirection(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_element(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_compound_list(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_rulefor(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_rulewhile(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_ruleuntil(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_rulecase(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_ruleif(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_elseclause(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_dogroup(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_caseclause(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static s_ast_node	*parse_pattern(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */
