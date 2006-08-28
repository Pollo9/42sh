/*
** ast_while.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Fri Aug 25 03:48:21 2006 Seblu
*/

#include "ast.h"

ts_ast_node	*ast_while_create(ts_ast_node *cond, ts_ast_node *exec)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_WHILE;
  node->body.child_while.cond = cond;
  node->body.child_while.exec = exec;
  return node;
}

void		ast_while_destruct(ts_ast_node *node)
{
  if (node->type != T_WHILE) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_while.cond);
  ast_destruct(node->body.child_while.exec);
  free(node);
}
