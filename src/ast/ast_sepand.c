/*
** ast_sepand.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Aug 29 00:00:49 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_sepand_create(s_ast_node *lhs, s_ast_node *rhs)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_SEPAND;
  node->body.child_sepand.lhs = lhs;
  node->body.child_sepand.rhs = rhs;
  return node;
}

void		ast_sepand_destruct(s_ast_node *node)
{
  if (node->type != T_SEPAND)
    return;
  ast_destruct(node->body.child_sepand.lhs);
  ast_destruct(node->body.child_sepand.rhs);
  free(node);
}

