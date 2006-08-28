/*
** ast_bang.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Mon Aug 28 23:57:20 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_bang_create(s_ast_node *child)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_BANG;
  node->body.child_bang.lhs = child;
  node->body.child_bang.rhs = NULL;
  return node;
}

void		ast_bang_destruct(s_ast_node *node)
{
  if (node->type != T_BANG)
    return;
  ast_destruct(node->body.child_bang.lhs);
  free(node);
}

