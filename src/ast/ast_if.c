/*
** ast_if.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Mon Aug 28 23:59:17 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_if_create(s_ast_node *cond,
			       s_ast_node *cond_true,
			       s_ast_node *cond_false)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_IF;
  node->body.child_if.cond = cond;
  node->body.child_if.cond_true = cond_true;
  node->body.child_if.cond_false = cond_false;
  return node;
}

void		ast_if_destruct(s_ast_node *node)
{
  if (node->type != T_IF)
    return;
  ast_destruct(node->body.child_if.cond);
  ast_destruct(node->body.child_if.cond_true);
  ast_destruct(node->body.child_if.cond_false);
  free(node);
}
