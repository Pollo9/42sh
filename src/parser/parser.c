/*
** parser.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:56:07 2006 Seblu
** Last update Thu Aug  3 12:30:15 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "parser.h"
#include "../common/mem.h"
#include "../shell/shell.h"
#include "../readline/readline.h"

/*
** Declaration
*/

/*!
** Parse a line
**
** @param parser
**
** @return
*/
static ts_ast_node	*parse_input(ts_parser *parser);


static ts_ast_node	*parse_list(ts_parser *parser);

static ts_ast_node	*parse_andor(ts_parser *parser);

/*
** Implemantation
*/

ts_parser		*parser_init(FILE *fs)
{
  ts_parser		*new;

  secmalloc(new, sizeof (ts_parser));
  fflush(fs);
  new->fs = fs;
  lexer_reset(new);
  return new;
}

void			parse_error(ts_parser *parser, ts_token t)
{
  printf("%s: syntax error near unexpected token `%s'\n",
	 shell->name, t.str);
  parser->status = PARSE_ERROR;
  shell->status = ERROR_PARSE;
}

ts_ast_node		*parse(ts_parser *parser)
{
  lexer_reset(parser);
  parser->status = PARSE_OK;
  return parse_input(parser);
}

static ts_ast_node	*parse_input(ts_parser *parser)
{
  ts_token cur_token;
  ts_ast_node *buf;

  lexer_eat(parser);
  cur_token = lexer_get(parser);
  if (cur_token.id == TOK_EOF) {
    parser->status = PARSE_END;
    return NULL;
  }
  if (cur_token.id == TOK_NEWLINE)
    return ast_create_sep(NULL, NULL);
  buf = parse_list(parser);
  cur_token = lexer_get(parser);
  if (cur_token.id != TOK_EOF || cur_token.id != TOK_NEWLINE)
    parse_error(parser, cur_token);
  return buf;
}

static ts_ast_node	*parse_list(ts_parser *parser)
{
  ts_token next_token;
  ts_ast_node *buf;

  parse_andor(parser);
  lexer_eat(parser);
  next_token = lexer_get(parser);
  if (next_token.id != TOK_SEP && next_token.id != TOK_SEPAND) {
    parse_error(parser, next_token);
    return buf;
  }
  return NULL;
}

static ts_ast_node	*parse_andor(ts_parser *parser)
{
  parser=parser;
  return NULL;
}

/* static ts_ast_node	*parse_pipeline(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

/* static ts_ast_node	*parse_command(ts_parser *parser) */
/* { */
/*   parser=parser; */
/*   return NULL; */
/* } */

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
