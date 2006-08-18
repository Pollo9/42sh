/*
** ast_subshell.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Aug  3 03:03:31 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_subshell(ts_ast_node *child)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_SUBSHELL;
  node->body.child_subshell.lhs = child;
  node->body.child_subshell.rhs = NULL;
  return node;
}

void		ast_destruct_subshell(ts_ast_node *node)
{
  if (node->type != T_SUBSHELL) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_subshell.lhs);
  free(node);
}

