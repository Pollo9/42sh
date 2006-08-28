/*
** ast_subshell.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Aug 29 00:07:12 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_subshell_create(s_ast_node *child)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_SUBSHELL;
  node->body.child_subshell.lhs = child;
  node->body.child_subshell.rhs = NULL;
  return node;
}

void		ast_subshell_destruct(s_ast_node *node)
{
  if (node->type != T_SUBSHELL)
    return;
  ast_destruct(node->body.child_subshell.lhs);
  free(node);
}

