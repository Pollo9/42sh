/*
** parser.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:56:07 2006 Seblu
** Last update Mon Sep 25 04:44:08 2006 Seblu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include <assert.h>
#include "parser.h"
#include "../common/macro.h"
#include "../shell/shell.h"
#include "getline.h"

/*
** ============
** DECLARATIONS
** ============
*/

enum {
  FD_MAX = 32765
};

static s_token keywords[] =
  {
    {TOK_IF, "if", 2},
    {TOK_THEN, "then", 4},
    {TOK_ELSE, "else", 4},
    {TOK_FI, "fi", 2},
    {TOK_ELIF, "elif", 4},
    {TOK_DO, "do", 2},
    {TOK_DONE, "done", 4},
    {TOK_CASE, "case", 4},
    {TOK_ESAC, "esac", 4},
    {TOK_WHILE, "while", 5},
    {TOK_UNTIL, "until", 5},
    {TOK_FOR, "for", 3},
    {TOK_IN, "in", 2},
    {TOK_LBRACE, "{", 1},
    {TOK_RBRACE, "}", 1},
    {TOK_BANG, "!", 1},
    {TOK_NONE, NULL, 0}
  };

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
static int		parse_prefix(s_parser *parser, s_ast_node *cmd);
static int		parse_element(s_parser *parser, s_ast_node *cmd);
static s_ast_node	*parse_simplecommand(s_parser *parser);
static void		parse_redirection(s_parser *parser, s_ast_node *cmd);
static s_ast_node	*parse_shellcommand(s_parser *parser);
static s_ast_node	*parse_rulefor(s_parser *parser);
static s_ast_node	*parse_rulewhile(s_parser *parser);
static s_ast_node	*parse_ruleuntil(s_parser *parser);
static s_ast_node	*parse_ruleif(s_parser *parser);
static s_ast_node	*parse_rulecase(s_parser *parser);

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

/* static int		is_keyword(s_token t) */
/* { */
/*   for (int i = 0; keywords[i].id != TOK_NONE; ++i) */
/*     if (!strncmp(t.str, keywords[i].str, keywords[i].len)) { */
/*       t.id = keywords[i].id; */
/*       return 1; */
/*     } */
/*   return 0; */
/* } */

static int		is_assignment(const s_token t)
{
  return strchr(t.str, '=') == NULL ? 0 : 1;
}

static void		recon(s_token *t)
{
  //check for keywords
  for (int i = 0; keywords[i].id != TOK_NONE; ++i)
    if (!strncmp(t->str, keywords[i].str, keywords[i].len)) {
      t->id = keywords[i].id;
    }
  //check
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
  if (token.id != TOK_EOF && token.id != TOK_NEWLINE)
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
  recon(&token);
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

  debugmsg("parse_command");
  token = lexer_lookahead(parser->lexer);
  recon(&token);
  if (token.id == TOK_FOR || token.id == TOK_WHILE || token.id == TOK_UNTIL ||
      token.id == TOK_CASE || token.id == TOK_IF ||
      !strcmp(token.str, "{") || !strcmp(token.str, "("))
    return parse_shellcommand(parser);
  // probleme de choix avec function pour l'instant ya pas  defonction !
  else if (token.id == TOK_WORD) {
    return parse_simplecommand(parser);
  }
  else
    parse_error(parser, token);
  return NULL;
}

static int		parse_element(s_parser *parser, s_ast_node *cmd)
{
  s_token		token;
  int			found = 0;

  debugmsg("parse_element");
  for (;;) {
    token = lexer_lookahead(parser->lexer);
    if (token.id >= TOK_DLESSDASH && token.id <= TOK_IONUMBER) {
      parse_redirection(parser, cmd);
      ++found;
    }
    else if (token.id == TOK_WORD) {
      ast_cmd_add_argv(cmd, lexer_gettoken(parser->lexer).str);
      ++found;
    }
    else
      break;
  }
  return found;
}

static int		parse_prefix(s_parser *parser, s_ast_node *cmd)
{
  s_token		token;
  int			found = 0;

  debugmsg("parse_prefix");
  for (;;) {
    token = lexer_lookahead(parser->lexer);
    if (token.id >= TOK_DLESSDASH && token.id <= TOK_IONUMBER) {
      parse_redirection(parser, cmd);
      ++found;
    }
    else if (is_assignment(token)) {
      ast_cmd_add_prefix(cmd, lexer_gettoken(parser->lexer).str);
      ++found;
    }
    else
      break;
  }
  return found;
}

static s_ast_node	*parse_simplecommand(s_parser *parser)
{
  s_ast_node		*cmd;
  int			found = 0;

  debugmsg("parse_simplecommand");
  cmd = regnode(parser, ast_cmd_create());
  found += parse_prefix(parser, cmd);
  found += parse_element(parser, cmd);
  if (!found)
    parse_error(parser, lexer_lookahead(parser->lexer));
  return cmd;
}

static s_ast_node	*parse_shellcommand(s_parser *parser)
{
  s_token		token;

  debugmsg("parse_shellcommand");
  token = lexer_lookahead(parser->lexer);
  switch (token.id) {
  case TOK_IF:		parse_ruleif(parser); break;
  case TOK_FOR:		parse_rulefor(parser); break;
  case TOK_WHILE:	parse_rulewhile(parser); break;
  case TOK_UNTIL:	parse_ruleuntil(parser); break;
  case TOK_CASE:	parse_rulecase(parser); break;
  case TOK_WORD:
    //gerer le cas de { et de (
    assert(0);
    break;
  default:
    parse_error(parser, token);
  }

  return NULL;
}

/* static s_ast_node	*parse_funcdec(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

static void		parse_redirection(s_parser *parser, s_ast_node *cmd)
{
  s_token		token;
  long int		fd;
  e_redir_type		redtype;

  debugmsg("parse_redirection");
  //retrieve redirection fd if exist
  if ((token = lexer_lookahead(parser->lexer)).id == TOK_IONUMBER) {
    lexer_gettoken(parser->lexer);
    errno = 0;
    fd = strtol(token.str, NULL, 10);
    if (errno || fd < 0 || fd > FD_MAX)
      parse_error(parser, token);
  }
  //retrieve redirection type
  token = lexer_gettoken(parser->lexer);
  switch (token.id) {
  case TOK_GREAT: redtype = R_GREAT; break;
  case TOK_DGREAT: redtype = R_DLESS; break;
  case TOK_DLESSDASH: redtype = R_DLESSDASH; break;
  case TOK_DLESS: redtype = R_DLESS; break;
  case TOK_LESSGREAT: redtype = R_LESSGREAT; break;
  case TOK_LESSAND: redtype = R_LESSAND; break;
  case TOK_LESS: redtype = R_LESS; break;
  case TOK_CLOBBER: redtype = R_CLOBBER; break;
  case TOK_GREATAND: redtype = R_GREATAND; break;
  default:
    parse_error(parser, token);
  }
  //retrieve redirection word
  token = lexer_gettoken(parser->lexer);
  if (token.id == TOK_WORD)
    ast_cmd_add_redir(cmd, redtype, fd, token.str);
  else
    parse_error(parser, token);
}

/* static s_ast_node	*parse_compound_list(s_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

static s_ast_node	*parse_rulefor(s_parser *parser)
{
  parser=parser;
  return NULL;
}

static s_ast_node	*parse_rulewhile(s_parser *parser)
{
  parser=parser;
  return NULL;
}

static s_ast_node	*parse_ruleuntil(s_parser *parser)
{
  parser=parser;
  return NULL;
}

static s_ast_node	*parse_rulecase(s_parser *parser)
{
  parser=parser;
  return NULL;
}

static s_ast_node	*parse_ruleif(s_parser *parser)
{
  parser=parser;
  return NULL;
}

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
