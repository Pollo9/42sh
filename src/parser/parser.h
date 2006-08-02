/*
** parser.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:49:50 2006 Seblu
** Last update Wed Aug  2 17:47:18 2006 Seblu
*/

#include <stdio.h>
#include "../ast/ast.h"

#ifndef PARSER_H_
# define PARSER_H_

ts_ast_node	*parse(FILE* fs);

#endif
