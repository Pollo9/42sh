/*
** ast_funcdec.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Fri Aug 18 15:55:42 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_create_funcdec(char *name, ts_ast_node *body)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_FUNCDEC;
  node->body.child_funcdec.name = name;
  node->body.child_funcdec.body = body;
  return node;
}

void		ast_destruct_funcdec(ts_ast_node *node)
{
  if (node->type != T_FUNCDEC) {
    ast_destruct(node);
    return;
  }
  free(node->body.child_funcdec.name);
  ast_destruct(node->body.child_funcdec.body);
  free(node);
}
