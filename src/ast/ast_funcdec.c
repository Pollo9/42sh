/*
** ast_funcdec.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Mon Aug 28 23:59:05 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_funcdec_create(char *name, s_ast_node *body)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_FUNCDEC;
  node->body.child_funcdec.name = name;
  node->body.child_funcdec.body = body;
  return node;
}

void		ast_funcdec_destruct(s_ast_node *node)
{
  if (node->type != T_FUNCDEC)
    return;
  free(node->body.child_funcdec.name);
  ast_destruct(node->body.child_funcdec.body);
  free(node);
}
