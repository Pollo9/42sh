/*
** ast_sep.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Fri Aug 25 03:46:42 2006 Seblu
*/

#include "ast.h"

ts_ast_node	*ast_sep_create(ts_ast_node *lhs, ts_ast_node *rhs)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_SEP;
  node->body.child_sep.lhs = lhs;
  node->body.child_sep.rhs = rhs;
  return node;
}

void		ast_sep_destruct(ts_ast_node *node)
{
  if (node->type != T_SEP) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_sep.lhs);
  ast_destruct(node->body.child_sep.rhs);
  free(node);
}

