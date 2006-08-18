/*
** ast_until.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Aug  3 03:03:31 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_until(ts_ast_node *cond, ts_ast_node *exec)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_UNTIL;
  node->body.child_until.cond = cond;
  node->body.child_until.exec = exec;
  return node;
}

void		ast_destruct_until(ts_ast_node *node)
{
  if (node->type != T_UNTIL) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_until.cond);
  ast_destruct(node->body.child_until.exec);
  free(node);
}
