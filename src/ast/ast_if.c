/*
** ast_if.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Aug  3 03:03:31 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_if(ts_ast_node *cond,
			       ts_ast_node *cond_true,
			       ts_ast_node *cond_false)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_IF;
  node->body.child_if.cond = cond;
  node->body.child_if.cond_true = cond_true;
  node->body.child_if.cond_false = cond_false;
  return node;
}

void		ast_destruct_if(ts_ast_node *node)
{
  if (node->type != T_IF) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_if.cond);
  ast_destruct(node->body.child_if.cond_true);
  ast_destruct(node->body.child_if.cond_false);
  free(node);
}
