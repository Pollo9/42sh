/*
** ast_or.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Mon Aug 28 23:59:55 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_or_create(s_ast_node *lhs, s_ast_node *rhs)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_OR;
  node->body.child_or.lhs = lhs;
  node->body.child_or.rhs = rhs;
  return node;
}

void		ast_or_destruct(s_ast_node *node)
{
  if (node->type != T_OR)
    return;
  ast_destruct(node->body.child_or.lhs);
  ast_destruct(node->body.child_or.rhs);
  free(node);
}

