/*
** ast_sep.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Wed Aug 30 00:36:03 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_sep_create(s_ast_node *lhs, s_ast_node *rhs)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_SEP;
  node->body.child_sep.lhs = lhs;
  node->body.child_sep.rhs = rhs;
  return node;
}

void		ast_sep_destruct(s_ast_node *node)
{
  if (node->type != T_SEP)
    return;
  ast_destruct(node->body.child_sep.lhs);
  ast_destruct(node->body.child_sep.rhs);
  free(node);
}

