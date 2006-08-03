/*
** ast_sep.c for 42sh
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Aug  3 03:03:31 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

/*!
** Create a separtor ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
ts_ast_node	*ast_create_sep(ts_ast_node *lhs, ts_ast_node *rhs)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_SEP;
  node->body.child_sep.lhs = lhs;
  node->body.child_sep.rhs = rhs;
  return node;
}

/*!
** Destruct and separator node
**
** @param node node to destroy
*/
void		ast_destruct_sep(ts_ast_node *node)
{
  if (node->type != T_SEP) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_sep.lhs);
  ast_destruct(node->body.child_sep.rhs);
  free(node);
}

