/*
** parser.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:49:50 2006 Seblu
** Last update Fri Aug 25 15:17:29 2006 Seblu
*/

#include <setjmp.h>
#include "../ast/ast.h"

#ifndef PARSER_H_
# define PARSER_H_


// Define is parser or lexer is run for DEBBUGING
#define DEBUG_PARSER 1
#define DEBUG_LEXER 0

typedef enum		e_tokenid
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
  } te_tokenid;

typedef struct		s_token
{
  te_tokenid		id;
  const char		*str;
  size_t		len;
} ts_token;

typedef struct		s_lexer
{
  ts_token		token;
  FILE			*fs;
  char			eof;
  char			*buf;
  size_t		buf_size; //without \0
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

/*!
** Parse input as a here-document (describe is XSI)
**
** @param lexer current lexer
*/
void			lexer_heredocument(ts_lexer *lexer);

#endif
