/*
** parser.c for 42sh in /home/seblu/svn/42sh/src/parser
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:56:07 2006 Seblu
** Last update Wed Aug  2 17:47:01 2006 Seblu
*/

#include "parser.h"

/*!
** Parse a File stream, and return the ast
**
** @param fs file stream to parse
**
** @return ast from the file stream
*/
ts_ast_node	*parse(FILE* fs)
{
  int		fd;

  fd = fileno(fs);
  return NULL;
}
