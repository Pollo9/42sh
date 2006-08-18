/*
** ast_and.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Aug  3 03:03:31 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_and(ts_ast_node *lhs, ts_ast_node *rhs)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_AND;
  node->body.child_and.lhs = lhs;
  node->body.child_and.rhs = rhs;
  return node;
}

void		ast_destruct_and(ts_ast_node *node)
{
  if (node->type != T_AND) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_and.lhs);
  ast_destruct(node->body.child_and.rhs);
  free(node);
}
