/*
** ast_while.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Aug  3 03:03:31 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_while(ts_ast_node *cond, ts_ast_node *exec)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_WHILE;
  node->body.child_while.cond = cond;
  node->body.child_while.exec = exec;
  return node;
}

void		ast_destruct_while(ts_ast_node *node)
{
  if (node->type != T_WHILE) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_while.cond);
  ast_destruct(node->body.child_while.exec);
  free(node);
}
