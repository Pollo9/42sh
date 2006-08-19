/*
** parser.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:49:50 2006 Seblu
** Last update Sat Aug 19 01:35:31 2006 Seblu
*/

#include <stdio.h>
#include "../ast/ast.h"

#ifndef PARSER_H_
# define PARSER_H_

typedef enum e_token
  {
    TOK_AND,
    TOK_OR,
    TOK_DSEMI,
    TOK_DLESS,
    TOK_DGREAT,
    TOK_LESSAND,
    TOK_GREATAND,
    TOK_LESSGREAT,
    TOK_DLESSDASH,
    TOK_CLOBBER,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_FI,
    TOK_ELIF,
    TOK_DO,
    TOK_DONE,
    TOK_CASE,
    TOK_ESAC,
    TOK_WHILE,
    TOK_UNTIL,
    TOK_FOR,
    TOK_IN,
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_BANG,
    TOK_NEWLINE,
    TOK_SEP,
    TOK_SEPAND,
    TOK_WORD,
    TOK_EOF,
    TOK_BEGIN,
    TOK_NONE,
    TOK_ERR
  } te_tokenid;

typedef struct s_token
{
  te_tokenid id;
  const char *str;
} ts_token;

typedef enum e_parser_status
  {
    PARSE_OK,
    PARSE_ERROR,
    PARSE_END
  } te_parser_status;

typedef struct		s_parser
{
  te_parser_status	status;
  ts_token		token;
  FILE			*fs;
  char			*buf;
  size_t		buf_size;
  size_t		buf_pos;
  size_t		tok_start;
} ts_parser;

/*
** ==============
** FILE: parser.c
** ==============
*/

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

/*
** =============
** FILE: lexer.c
** =============
*/

/*!
** Set (or reset) the lexer
** This must be call by parser before each parse start
** This function is necessarity to correctly show the prompt
**
** @param parser lexer to reset
*/
void			lexer_reset(ts_parser *parser);

/*!
** Return the next token and destroy it
** @warning The token MUST be freed !
**
** @param parser parser/lexer structure
**
** @return the next token
*/
ts_token		lexer_gettoken(ts_parser *parser);

/*!
** Return the next token without destruction of it.
** @warning The token string MUST NOT be freed !
**
** @param parser parser/lexer structure
**
** @return the look ahead token
*/
ts_token		lexer_lookahead(ts_parser *parser);

#endif
