/*
** ast_until.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Fri Aug 25 03:48:15 2006 Seblu
*/

#include "ast.h"

ts_ast_node	*ast_until_create(ts_ast_node *cond, ts_ast_node *exec)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_UNTIL;
  node->body.child_until.cond = cond;
  node->body.child_until.exec = exec;
  return node;
}

void		ast_until_destruct(ts_ast_node *node)
{
  if (node->type != T_UNTIL) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_until.cond);
  ast_destruct(node->body.child_until.exec);
  free(node);
}
