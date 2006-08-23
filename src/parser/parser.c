/*
** parser.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:56:07 2006 Seblu
** Last update Tue Aug 22 19:10:23 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include "parser.h"
#include "../common/mem.h"
#include "../shell/shell.h"
#include "../readline/readline.h"

/*
** ============
** DECLARATIONS
** ============
*/

/*
** Define is parser is run for DEBBUGING
*/
#define DEBUG_PARSER 1

static ts_ast_node	*regnode(ts_parser *parser, ts_ast_node *node);

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
static ts_ast_node	*parse_input(ts_parser *parser);

static ts_ast_node	*parse_list(ts_parser *parser);

static ts_ast_node	*parse_andor(ts_parser *parser);

static ts_ast_node	*parse_pipeline(ts_parser *parser);

static ts_ast_node	*parse_command(ts_parser *parser);

/*!
** Notify a parse error
**
** @param parser parser where error appear
** @param t token near of the error
*/
static void		parse_error(ts_parser *parser, ts_token t);

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

ts_parser		*parser_init(FILE *fs)
{
  ts_parser		*new;

  secmalloc(new, sizeof (ts_parser));
  new->lexer = lexer_init(fs);
  new->error = 0;
  new->regnodes = NULL;
  new->regsize = new->regpos = 0;
  return new;
}

static ts_ast_node	*regnode(ts_parser *parser, ts_ast_node *node)
{
  if (!node)
    return node;
  if (parser->regpos >= parser->regsize) {
    parser->regsize += 50;
    secrealloc(parser->regnodes, parser->regnodes,
	       parser->regsize * sizeof (ts_ast_node));
  }
  parser->regnodes[parser->regpos] = node;
  ++parser->regpos;
  return node;
}

static void		parse_error(ts_parser *parser, ts_token t)
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

ts_ast_node		*parse(ts_parser *parser)
{
  lexer_start(parser->lexer);
  parser->regpos = 0;
  parser->error = 0;
  // prevent of too big register ast size
  if (parser->regsize >= 200)
    secrealloc(parser->regnodes, parser->regnodes,
	       (parser->regsize = 50) * sizeof (ts_ast_node));
  if (setjmp(parser->stack))
    return NULL;
  //test lexer mode
  while (1)
    {
      ts_token tok;

      tok = lexer_gettoken(parser->lexer);
      if (tok.id == TOK_EOF)
	exit(42);
      if (tok.id == TOK_NEWLINE)
	lexer_start(parser->lexer);
      printf("Returned token: %d [%s]\n", tok.id, tok.str);
    }
  return parse_input(parser);
}

static ts_ast_node	*parse_input(ts_parser *parser)
{
  ts_token		token;
  ts_ast_node		*buf;

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

static ts_ast_node	*parse_list(ts_parser *parser)
{
  ts_token		token;
  ts_ast_node		*lhs;
  ts_ast_node		*rhs;

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

static ts_ast_node	*parse_andor(ts_parser *parser)
{
  ts_token		token;
  ts_ast_node		*lhs;
  ts_ast_node		*rhs;

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

static ts_ast_node	*parse_pipeline(ts_parser *parser)
{
  ts_token		token;
  ts_ast_node		*lhs;
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

static ts_ast_node	*parse_command(ts_parser *parser)
{
  ts_token		token;


  token = lexer_lookahead(parser->lexer);
  //if (token.id == TOK_WORD)
  return NULL;
}

/* static ts_ast_node	*parse_simplecommand(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_shellcommand(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_funcdec(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_cmdprefix(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_redirection(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_element(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_compound_list(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_rulefor(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_rulewhile(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_ruleuntil(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_rulecase(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_ruleif(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_elseclause(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_dogroup(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_caseclause(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_pattern(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */
