/*
** parser.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:49:50 2006 Seblu
** Last update Tue Aug 29 00:24:16 2006 Seblu
*/

#include <setjmp.h>
#include "../ast/ast.h"

#ifndef PARSER_H_
# define PARSER_H_

# include "getln.h"

// Define is parser or lexer is run for DEBBUGING
#define DEBUG_PARSER 1
#define DEBUG_LEXER 0

typedef enum		tokenid
  {
    //token free-context recognition (lexer time)
    TOK_NONE,
    TOK_NEWLINE,	// \n
    TOK_EOF,		// EOF
    TOK_AND,		// &&
    TOK_SEPAND,		// &
    TOK_OR,		// ||
    TOK_PIPE,		// |
    TOK_DSEMI,		// ;;
    TOK_SEP,		// ;
    TOK_DLESSDASH,	// <<-
    TOK_DLESS,		// <<
    TOK_LESSGREAT,	// <>
    TOK_LESSAND,	// <&
    TOK_LESS,		// <
    TOK_DGREAT,		// >>
    TOK_GREATAND,	// >&
    TOK_CLOBBER,	// >|
    TOK_GREAT,		// >
    TOK_WORD,		// all others
    //token context-sensitive recognition (parser time)
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
    TOK_NUMBER,
    TOK_ASSIGNMENT,
    TOK_BANG
  } e_tokenid;

typedef struct		token
{
  e_tokenid		id;
  const char		*str;
  size_t		len;
} s_token;

typedef struct		lexer
{
  s_token		token;
  FILE			*fs;
  char			eof;
  char			*buf;
  size_t		buf_size; //without \0
  size_t		buf_pos;
  s_getln		*stream;
} s_lexer;

typedef struct		parser
{
  int			error;
  s_lexer		*lexer;
  jmp_buf		stack;
  s_ast_node		**regnodes;
  size_t		regsize;
  size_t		regpos;
} s_parser;

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
s_parser		*parser_init(int fd);

/*!
** Do a parse pass
**
** @param parser the parser where we do this parse
**
** @return ast_to_execute
*/
s_ast_node		*parse(s_parser *parser);

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
s_lexer			*lexer_init(int fd);

/*!
** Start a new lexical recognition
** This must be call by parser before each parse start
** This function is necessarity to correctly show the prompt
**
** @param lexer lexer to set in starting block
**
** @return return if lexer is ready to start or not
*/
int			lexer_start(s_lexer *lexer);

/*!
** Return the next token and destroy it
** @warning The token MUST be freed !
**
** @param lexer lexer structure
**
** @return the next token
*/
s_token			lexer_gettoken(s_lexer *lexer);

/*!
** Return the next token without destruction of it.
** @warning The token string MUST NOT be freed !
**
** @param lexer lexer structure
**
** @return the look ahead token
*/
s_token			lexer_lookahead(s_lexer *lexer);

/*!
** Parse input as a here-document (describe is XSI)
**
** @param lexer current lexer
*/
s_token			lexer_getheredoc(s_lexer *lexer, const char *delim);

#endif
