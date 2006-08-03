/*
** lexer.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:36:53 2006 Seblu
** Last update Thu Aug  3 12:39:34 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "../shell/shell.h"
#include "../readline/readline.h"

int		lexer_reconize(ts_parser *parser);

ts_token tokens[] =
  {
    {TOK_AND, "&&"},
    {TOK_OR, "||"},
    {TOK_DSEMI, ";;"},
    {TOK_DLESS, "<<"},
    {TOK_DGREAT, ">>"},
    {TOK_LESSAND, "<&"},
    {TOK_GREATAND, ">&"},
    {TOK_LESSGREAT, "<>"},
    {TOK_DLESSDASH, "<<-"},
    {TOK_CLOBBER, ">|"},
    {TOK_IF, "if"},
    {TOK_THEN, "then"},
    {TOK_ELSE, "else"},
    {TOK_FI, "fi"},
    {TOK_ELIF, "elif"},
    {TOK_DO, "do"},
    {TOK_DONE, "done"},
    {TOK_CASE, "case"},
    {TOK_ESAC, "esac"},
    {TOK_WHILE, "while"},
    {TOK_UNTIL, "until"},
    {TOK_FOR, "for"},
    {TOK_IN, "in"},
    {TOK_LBRACE, "{"},
    {TOK_RBRACE, "}"},
    {TOK_BANG, "!"},
    {TOK_SEP, ";"},
    {TOK_SEPAND, "&"},
    {TOK_NEWLINE, "\n"},
    {0,0}
  };

void		lexer_reset(ts_parser *parser)
{
  parser->current.id = TOK_NONE;
  parser->current.str = "none";
  if (parser->buf != NULL)
    free(parser->buf);
  parser->buf = NULL;
  parser->buf_size = 0;
  parser->buf_pos = 0;
}

const char	*get_token_string(t_token t)
{
  for (register int i = 0; tokens[i].str; ++i)
    if (tokens[i].id == t)
      return tokens[i].str;
  return "unknow";
}

ts_token	lexer_get(ts_parser *parser)
{
  if (parser->current.id == TOK_NONE)
    lexer_eat(parser);
  return parser->current;
}

void		lexer_eat(ts_parser *parser)
{
  if (parser->status == PARSE_END)
    return;
  if (parser->buf_size == 0) {
    if ((parser->buf = readline(get_prompt(TYPE_PS1))) == NULL) {
      parser->current.id = TOK_EOF;
      parser->status = PARSE_END;
      return;
    }
    parser->buf_pos = 0;
    parser->buf_size = strlen(parser->buf);
  }
  if (parser->buf_size > 0 &&
      parser->buf_size != parser->buf_pos) {
    if (lexer_reconize(parser))
      return;
  }
  do
    if ((parser->buf = readline(get_prompt(TYPE_PS2))) == NULL) {
      parser->current.id = TOK_EOF;
      parser->status = PARSE_END;
    }
  while (lexer_reconize(parser));
}

int		lexer_reconize(ts_parser *parser)
{
  size_t	n;

  for (register int i = 0; tokens[i].str; ++i)
    if (!strncmp(tokens[i].str, parser->buf + parser->buf_pos,
		n = strlen(tokens[i].str))) {
      parser->current = tokens[i];
      parser->buf_pos += n;
      printf("reconized %d\n", tokens[i].id);
      return 1;
    }
  parser->current.id = TOK_NONE;
  parser->current.str = "none";
  return 0;
}
