/*
** ast_and.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Mon Aug 28 23:57:05 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_and_create(s_ast_node *lhs, s_ast_node *rhs)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_AND;
  node->body.child_and.lhs = lhs;
  node->body.child_and.rhs = rhs;
  return node;
}

void		ast_and_destruct(s_ast_node *node)
{
  if (node->type != T_AND)
    return;
  ast_destruct(node->body.child_and.lhs);
  ast_destruct(node->body.child_and.rhs);
  free(node);
}
