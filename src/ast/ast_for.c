/*
** ast_for.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Mon Aug 28 23:58:56 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_for_create(char		*varname,
				char		**values, 
				s_ast_node	*exec)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_FOR;
  node->body.child_for.varname = varname;
  node->body.child_for.values = values;
  node->body.child_for.exec = exec;
  return node;
}

void		ast_for_destruct(s_ast_node *node)
{
  if (node->type != T_FOR)
    return;
  free(node->body.child_for.varname);
  for (register int i = 0; node->body.child_for.values[i]; ++i)
    free(node->body.child_for.values[i]);
  free(node->body.child_for.values);
  ast_destruct(node->body.child_for.exec);
  free(node);
}
