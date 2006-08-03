/*
** parser.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:49:50 2006 Seblu
** Last update Thu Aug  3 12:28:14 2006 Seblu
*/

#include <stdio.h>
#include "../ast/ast.h"

#ifndef PARSER_H_
# define PARSER_H_

# define TOK_AND 1
# define TOK_OR 2
# define TOK_DSEMI 3
# define TOK_DLESS 4
# define TOK_DGREAT 5
# define TOK_LESSAND 6
# define TOK_GREATAND 7
# define TOK_LESSGREAT 8
# define TOK_DLESSDASH 9
# define TOK_CLOBBER 10
# define TOK_IF 11
# define TOK_THEN 12
# define TOK_ELSE 13
# define TOK_FI 14
# define TOK_ELIF 15
# define TOK_DO 16
# define TOK_DONE 17
# define TOK_CASE 18
# define TOK_ESAC 19
# define TOK_WHILE 20
# define TOK_UNTIL 21
# define TOK_FOR 22
# define TOK_IN 23
# define TOK_LBRACE 24
# define TOK_RBRACE 25
# define TOK_BANG 26
# define TOK_NEWLINE 27
# define TOK_SEP 28
# define TOK_SEPAND 29
# define TOK_EOF 30
# define TOK_NONE 31

typedef int t_token;

typedef struct s_token
{
  t_token id;
  const char *str;
} ts_token;


typedef enum e_parse_status
  {
    PARSE_OK,
    PARSE_ERROR,
    PARSE_END
  } te_parse_status;

typedef struct		s_parser
{
  te_parse_status	status;
  ts_token		current;
  FILE			*fs;
  char			*buf;
  size_t		buf_size;
  size_t		buf_pos;
} ts_parser;

/*!
** Parser initialization
**
** @param fs file stream to read
**
** @return the new struct
*/
ts_parser		*parser_init(FILE *fs);


/*!
** Notify a parse error
**
** @param parser parser where error appear
** @param t token near of the error
*/
void			parse_error(ts_parser *parser, ts_token t);

/*!
** Do a parse pass
**
** @param parser the parser where we do this parse
**
** @return ast_to_execute
*/
ts_ast_node		*parse(ts_parser *parser);

/*!
** Set (or reset) the lexer
**
** @param parser lexer to reset
*/
void			lexer_reset(ts_parser *parser);

/*!
** Return the current token
**
** @return the current token
*/
ts_token		lexer_get(ts_parser *lex);

/*!
** Eat a token (miam miam)
*/
void			lexer_eat(ts_parser *lex);

/*!
** Return a token string. Transform a t_token into string
**
** @param t token id to transform
**
** @return token string representation
*/
const char		*get_token_string(t_token t);

#endif
