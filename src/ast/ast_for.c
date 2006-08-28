/*
** ast_for.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Fri Aug 25 03:45:55 2006 Seblu
*/

#include "ast.h"

ts_ast_node	*ast_for_create(char		*varname,
				char		**values, 
				ts_ast_node	*exec)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_FOR;
  node->body.child_for.varname = varname;
  node->body.child_for.values = values;
  node->body.child_for.exec = exec;
  return node;
}

void		ast_for_destruct(ts_ast_node *node)
{
  if (node->type != T_FOR) {
    ast_destruct(node);
    return;
  }
  free(node->body.child_for.varname);
  for (register int i = 0; node->body.child_for.values[i]; ++i)
    free(node->body.child_for.values[i]);
  free(node->body.child_for.values);
  ast_destruct(node->body.child_for.exec);
  free(node);
}
