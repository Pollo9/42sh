/*
** lexer.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:36:53 2006 Seblu
** Last update Wed Aug 23 18:05:56 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "../shell/shell.h"
#include "../readline/readline.h"
#include "../common/common.h"
#include "../common/mem.h"

/*
** Token recognition rationale:
** - Separator are chars which used to cut token but which are deleted.
** - Operators are chars which used to cut token and which are returned as token.
** - Keywords are chars which are collapsed by tokens and are reserved.
** - Others are chars considered like words.
*/

/*
** ============
** DECLARATIONS
** ============
*/

static ts_token operators[] =
  {
    {TOK_NEWLINE, "\n"},
    {TOK_AND, "&&"},
    {TOK_OR, "||"},
    {TOK_DSEMI, ";;"},
    {TOK_LESS, "<"},
    {TOK_GREAT, ">"},
    {TOK_DLESS, "<<"},
    {TOK_DGREAT, ">>"},
    {TOK_LESSAND, "<&"},
    {TOK_GREATAND, ">&"},
    {TOK_LESSGREAT, "<>"},
    {TOK_DLESSDASH, "<<-"},
    {TOK_CLOBBER, ">|"},
    {TOK_SEP, ";"},
    {TOK_SEPAND, "&"},
    {TOK_NONE, NULL}
  };

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

/*!
** Return a predicat about c is a quote
**
** @param c Must be a character
**
** @return true if c is a quote
*/
#define		is_quote(c) ((c) == '"' || (c) == '\'' || (c) == '`')

/*!
** Return a predicat about c is a separator
**
** @param c Must be a character
**
** @return true if c is a separator
*/
#define		is_sep(c) ((c) == ' ' || (c) == '\t' || (c) == '\v')

/*!
** Call readline while it's necessary to reconize a token.
**
** @param lex lexer struct
*/
static void	lexer_eat(ts_lexer *lex);

/*!
** Cut and reconize a token.
**
** @param lexer lexer struct
**
** @return 1, if someting is reconized, else 0
*/
static int	lexer_reconize(ts_lexer *lexer);

/*!
** Correctly set a token. In first, it call macro token_free to
** desallow memory if it's a word.
**
** @param token token to set
** @param id new token id
** @param s new token string
*/
static void	token_set(ts_token *token, te_tokenid id, const char *s);


/*
** ===========
** DEFINITIONS
** ===========
*/

ts_lexer	*lexer_init(FILE *fs)
{
  ts_lexer	*new;

  secmalloc(new, sizeof (ts_lexer));
  fflush(fs);
  new->fs = fs;
  new->buf = NULL;
  new->buf_size = new->buf_pos = 0;
  new->status = LEXER_READY;
  return new;
}

int		lexer_start(ts_lexer *lexer)
{
  if (lexer->status == LEXER_END)
    return 0;
  token_set(&lexer->token, TOK_NONE, NULL);
  if (lexer->buf) free(lexer->buf);
  lexer->buf = NULL;
  lexer->buf_size = lexer->buf_pos = 0;
  return 1;
}

ts_token	lexer_lookahead(ts_lexer *lexer)
{
  if (lexer->token.id == TOK_NONE)
    lexer_eat(lexer);
  return lexer->token;
}

ts_token	lexer_gettoken(ts_lexer *lexer)
{
  ts_token	buf;

  if (lexer->token.id == TOK_EOF)
    return lexer->token;
  if (lexer->token.id == TOK_NONE)
    lexer_eat(lexer);
  buf = lexer->token;
  lexer->token.id = TOK_NONE;
  lexer->token.str = NULL;
  return buf;
}

static void	token_set(ts_token *token, te_tokenid id, const char *s)
{
  token_free(*token);
  token->id = id;
  token->str = s;
}

static void	lexer_eat(ts_lexer *lexer)
{
  char		*lbuf, *lbuf2;

  //if line is void, start readding with good prompt
  if (lexer->buf_size == 0) {
    if ((lexer->buf = readline(get_prompt(TYPE_PS1))) == NULL) {
      token_set(&lexer->token, TOK_EOF, "EOF");
      lexer->status = LEXER_END;
      return;
    }
    lexer->buf_pos = 0;
    lexer->buf_size = strlen(lexer->buf);
  }
  //read line while a token will not be reconized
  while (!lexer_reconize(lexer)) {
    //change last \n by ;
    if (lexer->buf[lexer->buf_size - 1] == '\n')
      lexer->buf[lexer->buf_size - 1] = ';';
    if ((lbuf2 = readline(get_prompt(TYPE_PS2))) == NULL)
      lexer->status = LEXER_END;
    else {
      lbuf = lexer->buf;
      lexer->buf = strmerge(2, lbuf, lbuf2);
      lexer->buf_size = strlen(lexer->buf);
      free(lbuf), free(lbuf2);
    }
  }
}

/* static int	lexer_cutter(ts_lexer *lexer) */
/* { */
/*   const char	*buf = lexer->buf; */
/*   const size_t	buf_size = lexer->buf_size; */
/*   //  size_t	*buf_pos = &lexer->buf_pos; */
/*   size_t	token_start, token_pos; */
/*   int		end_found = 0; */
/*   char		backed = 0, quoted = 0, commented = 0; */

/*   token_start = token_pos = lexer->buf_pos; */

/* } */

static int	lexer_reconize(ts_lexer *lexer)
{
  const char	*buf = lexer->buf;
  const size_t	buf_size = lexer->buf_size;
  size_t	*buf_pos = &lexer->buf_pos;
  size_t	token_start, token_pos;
  int		end_found = 0;
  char		backed = 0, quoted = 0, commented = 0;

  //eat separators (" ",\t, \v) and comment
  for (; *buf_pos < buf_size; ++*buf_pos) {
    if (commented && buf[*buf_pos] == '#')
      ;
    else if (is_sep(buf[*buf_pos])) continue;
    else if (buf[*buf_pos] == '#') commented = 1;
    else break;
  }
  //eat comment
  while (*buf_pos < buf_size && buf[*buf_pos] == '#')
    while (*buf_pos < buf_size && buf[*buf_pos] == '\n')
      ++*buf_pos;
  //check if first chars is an operator
  for (register int i = 0; operators[i].id != TOK_NONE; ++i)
    if (!strncmp(buf + *buf_pos, operators[i].str, strlen(operators[i].str))) {
      *buf_pos +=  strlen(operators[i].str);
      token_set(&lexer->token, operators[i].id, operators[i].str);
      return 1;
  }
  // Rationale: Search end of token
  //cut a token
  token_start = token_pos = *buf_pos;
  for (; !end_found && token_pos < buf_size; ++token_pos) {
    if (backed) backed = 0;
    else if (commented && buf[token_pos] == '\n') commented = 0;
    else if (commented) continue;
    else if (buf[token_pos] == '#') commented = 1;
    else if (is_sep(buf[token_pos])) end_found = 1;
    else if (!quoted && is_quote(buf[token_pos]))  quoted = buf[token_pos];
    else if (quoted && buf[token_pos] == quoted)  quoted = 0;
    else if (!backed && buf[token_pos] == '\\') backed = 1;
    else for (register int i = 0; operators[i].id != TOK_NONE; ++i)
      if (!strncmp(buf + token_pos, operators[i].str, strlen(operators[i].str)))
	{ end_found = 1; break; }
    if (end_found) break;
  }
  if (!end_found) return 0;
  lexer->buf_pos = token_pos; //update real lexer buffer
  token_set(&lexer->token, TOK_CONTEXT,
	    strndup(buf + token_start, token_pos - token_start));
  return 1;
}

/* int			parser_reconition() */
/* { */
/*   //check if it's a registered keyword */
/*   for (register int i = 0; keywords[i].str; ++i) */
/*     if (!strncmp(keywords[i].str, buf + token_start, */
/* 		 token_pos - token_start)) { */
/*       token_set(&lexer->token, keywords[i].id, keywords[i].str); */
/* /\*       printf("reconized token: %d (%s)\n", keywords[i].id, keywords[i].str); *\/ */
/*       return 1; */
/*     } */
/*   return 0; */
/* } */
/*   //check if it's a IONUMBER token */
/*   if (isdigitstr(str)) */
/*     token_set(&lexer->token, TOK_NUMBER, str); */
