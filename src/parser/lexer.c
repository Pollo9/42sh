/*
** lexer.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:36:53 2006 Seblu
** Last update Sat Aug 19 01:41:32 2006 Seblu
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

static void	lexer_eat(ts_parser *lex);

static ts_token	token_create(te_tokenid id, const char *string);

static void	token_set(ts_token *token, te_tokenid id, const char *s);

ts_token operators[] =
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
    {TOK_SEP, ";"},
    {TOK_SEPAND, "&"},
    {TOK_NEWLINE, "\n"},
    {0, NULL}
  };

ts_token keywords[] =
  {
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
    {0, NULL}
  };

void		lexer_reset(ts_parser *parser)
{
  token_set(&parser->token, TOK_NONE, NULL);
  if (parser->buf) free(parser->buf);
  parser->buf = NULL;
  parser->buf_size = parser->buf_pos = 0;
}

ts_token	lexer_lookahead(ts_parser *parser)
{
  if (parser->status != PARSE_OK)
    return token_create(TOK_ERR, NULL);
  if (parser->token.id == TOK_NONE)
    lexer_eat(parser);
  return parser->token;
}

ts_token	lexer_gettoken(ts_parser *parser)
{
  ts_token	buf;

  if (parser->status != PARSE_OK)
    return token_create(TOK_ERR, NULL);
  if (parser->token.id == TOK_NONE)
    lexer_eat(parser);
  buf = parser->token;
  parser->token = token_create(TOK_NONE, NULL);
  return buf;
}

static ts_token	token_create(te_tokenid id, const char *string)
{
  ts_token	new = { id, string };

  return new;
}

static void	token_set(ts_token *token, te_tokenid id, const char *s)
{
  if (token->id == TOK_WORD && token->str)
    free((char*) token->str);
  token->id = id;
  token->str = s;
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
      token_set(&parser->token, TOK_EOF, "eof");
      parser->status = PARSE_END;
      return;
    }
    parser->buf_pos = 0;
    parser->buf_size = strlen(parser->buf);
  }
  //read line while a token will not be reconized
  while (!lexer_reconize(parser)) {
    if ((lbuf2 = readline(get_prompt(TYPE_PS2))) == NULL) {
      token_set(&parser->token, TOK_EOF, "eof");
      parser->status = PARSE_END;
      return;
    }
    lbuf = parser->buf;
    parser->buf = strmerge(2, lbuf, lbuf2);
    parser->buf_size = strlen(parser->buf);
    free(lbuf), free(lbuf2);
  }
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
    token_set(&parser->token, TOK_NEWLINE, "\n");
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
  for (register int i = 0; keywords[i].str; ++i)
    if (!strncmp(keywords[i].str, buf + token_start,
		 token_pos - token_start)) {
      token_set(&parser->token, keywords[i].id, keywords[i].str);
      printf("reconized token: %d (%s)\n", keywords[i].id, keywords[i].str);
      return 1;
    }
  //althought this token is a word
  token_set(&parser->token, TOK_WORD,
		    strndup(buf + token_start, token_pos - token_start));
  printf("reconized token (WORD): %d (%s)\n",
	 parser->token.id, parser->token.str);
  return 1;
}

