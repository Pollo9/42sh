/*
** ast_or.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Aug  3 03:03:31 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_or(ts_ast_node *lhs, ts_ast_node *rhs)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_OR;
  node->body.child_or.lhs = lhs;
  node->body.child_or.rhs = rhs;
  return node;
}

void		ast_destruct_or(ts_ast_node *node)
{
  if (node->type != T_OR) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_or.lhs);
  ast_destruct(node->body.child_or.rhs);
  free(node);
}

