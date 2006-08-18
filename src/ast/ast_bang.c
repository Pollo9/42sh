/*
** ast_bang.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Fri Aug 18 15:57:05 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_bang(ts_ast_node *child)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_BANG;
  node->body.child_bang.lhs = child;
  node->body.child_bang.rhs = NULL;
  return node;
}

void		ast_destruct_bang(ts_ast_node *node)
{
  if (node->type != T_BANG) {
    ast_destruct(node);
    return;
  }
  ast_destruct(node->body.child_bang.lhs);
  free(node);
}

