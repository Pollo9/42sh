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
#include <ctype.h>
#include "parser.h"
#include "../shell/shell.h"
#include "../readline/readline.h"
#include "../common/common.h"

#define is_quote(c) ((c) == '"' || (c) == '\'' || (c) == '`')
#define is_sep(c) ((c) == ' ' || (c) == '\t' || (c) == '\v')

static int	lexer_reconize(ts_parser *parser);

/*!
** Set the current token for a parser
**
** @param p the parser
** @param t new token id
** @param s new token str
**
** @return token string representation
*/
static void	set_current_token(ts_parser *p, te_tokenid t, const char *s);

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
  set_current_token(parser, TOK_BEGIN, "begin");
  if (parser->buf != NULL)
    free(parser->buf);
  parser->buf = NULL;
  parser->buf_size = parser->buf_pos = 0;
}

const char	*get_token_string(te_tokenid t)
{
  for (register int i = 0; tokens[i].str; ++i)
    if (tokens[i].id == t)
      return tokens[i].str;
  return NULL;
}

ts_token	lexer_get(ts_parser *parser)
{
  if (parser->current.id == TOK_BEGIN)
    lexer_eat(parser);
  return parser->current;
}

void		lexer_eat(ts_parser *parser)
{
  char		*lbuf, *lbuf2;

  // return EOF (the last), if file is ended
  if (parser->status == PARSE_END)
    return;
  //if line is void, start readding
  if (parser->buf_size == 0) {
    if ((parser->buf = readline(get_prompt(TYPE_PS1))) == NULL) {
      set_current_token(parser, TOK_EOF, "eof");
      parser->status = PARSE_END;
      return;
    }
    parser->buf_pos = 0;
    parser->buf_size = strlen(parser->buf);
  }
  //read line while a token will not be reconized
  while (!lexer_reconize(parser)) {
    if ((lbuf2 = readline(get_prompt(TYPE_PS2))) == NULL) {
      set_current_token(parser, TOK_EOF, "eof");
      parser->status = PARSE_END;
      return;
    }
    lbuf = parser->buf;
    parser->buf = strmerge(2, lbuf, lbuf2);
    parser->buf_size = strlen(parser->buf);
    free(lbuf), free(lbuf2);
  }
}

static void	set_current_token(ts_parser *p, te_tokenid t, const char *s)
{
  if (p->current.id == TOK_WORD)
    free((char*)p->current.str);
  p->current.id = t;
  p->current.str = s;
}

static int	lexer_reconize(ts_parser *parser)
{
  const char	*buf = parser->buf;
  const size_t	buf_size = parser->buf_size;
  size_t	*buf_pos = &parser->buf_pos;
  size_t	token_start;
  size_t	token_pos;
  int		end_found = 0;
  char		backed = 0;
  char		quoted = 0;

  //eat spaces (" ",\t, \v)
  while (*buf_pos < buf_size &&
	 is_sep(buf[*buf_pos]))
    ++*buf_pos;
  //check for leading \n token
  if (buf[*buf_pos] == '\n') {
    ++*buf_pos;
    set_current_token(parser, TOK_NEWLINE, "\n");
    return 1;
  }
  //cut a token
  token_start = token_pos = *buf_pos;
  for (; !end_found && token_pos < buf_size; ++token_pos)
    if (backed)
      backed = 0;
    else if (!quoted && (buf[token_pos] == '\n' || is_sep(buf[token_pos])))
      { end_found = 1; break; }
    else if (!quoted && is_quote(buf[token_pos]))
      quoted = buf[token_pos];
    else if (quoted && buf[token_pos] == quoted)
      quoted = 0;
    else if (!backed && buf[token_pos] == '\\')
      backed = 1;
  if (!end_found) return 0;
  parser->buf_pos = token_pos;
  printf("cutted token: '%s'\n", 
	 strndup(buf + token_start, token_pos - token_start));
  //check if it's a registered keyword
  for (register int i = 0; tokens[i].str; ++i)
    if (!strncmp(tokens[i].str, buf + token_start,
		 token_pos - token_start)) {
      set_current_token(parser, tokens[i].id, tokens[i].str);
      printf("reconized token: %d (%s)\n", tokens[i].id, tokens[i].str);
      return 1;
    }
  //althought this token is a word
  set_current_token(parser, TOK_WORD, 
		    strndup(buf + token_start, token_pos - token_start));
  printf("reconized token (WORD): %d (%s)\n",
	 parser->current.id, parser->current.str);
  return 1;
}
