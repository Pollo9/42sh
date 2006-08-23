/*
** parser.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:49:50 2006 Seblu
** Last update Wed Aug 23 02:33:38 2006 Seblu
*/

#include <setjmp.h>
#include "../ast/ast.h"

#ifndef PARSER_H_
# define PARSER_H_

typedef enum		e_token
  {
    //token free-context recognition
    TOK_NONE,
    TOK_NEWLINE,
    TOK_NUMBER,
    TOK_EOF,
    TOK_AND,
    TOK_OR,
    TOK_DSEMI,
    TOK_LESS,
    TOK_GREAT,
    TOK_DLESS,
    TOK_DGREAT,
    TOK_LESSAND,
    TOK_GREATAND,
    TOK_LESSGREAT,
    TOK_DLESSDASH,
    TOK_CLOBBER,
    TOK_CONTEXT,
    TOK_WORD,
    //token context-sensitive recognition
    TOK_ASSIGNMENT,
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
    TOK_SEP,
    TOK_SEPAND,
  } te_tokenid;

typedef struct		s_token
{
  te_tokenid id;
  const char *str;
} ts_token;

typedef enum		e_lexer_status
  {
    LEXER_READY = 1,
    LEXER_END = 2,
  } te_lexer_status;

typedef struct		s_lexer
{
  te_lexer_status	status;
  ts_token		token;
  FILE			*fs;
  char			*buf;
  size_t		buf_size;
  size_t		buf_pos;
} ts_lexer;

typedef struct		s_parser
{
  int			error;
  ts_lexer		*lexer;
  jmp_buf		stack;
  ts_ast_node		**regnodes;
  size_t		regsize;
  size_t		regpos;
} ts_parser;


/*!
** Free the string of a token if is a word (dynamically allocated)
**
** @param token a token struct type (not a pointer)
*/
#define token_free(token) if ((token).id == TOK_WORD && (token).str) \
 free((char*)(token).str)

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
** Lexer initialization
**
** @param fs file stream to read
**
** @return the new struct
*/
ts_lexer		*lexer_init(FILE *fs);

/*!
** Start a new lexical recognition
** This must be call by parser before each parse start
** This function is necessarity to correctly show the prompt
**
** @param lexer lexer to set in starting block
**
** @return return if lexer is ready to start or not
*/
int			lexer_start(ts_lexer *lexer);

/*!
** Return the next token and destroy it
** @warning The token MUST be freed !
**
** @param lexer lexer structure
**
** @return the next token
*/
ts_token		lexer_gettoken(ts_lexer *lexer);

/*!
** Return the next token without destruction of it.
** @warning The token string MUST NOT be freed !
**
** @param lexer lexer structure
**
** @return the look ahead token
*/
ts_token		lexer_lookahead(ts_lexer *lexer);

#endif
