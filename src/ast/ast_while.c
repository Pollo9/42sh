/*
** ast_while.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Aug 29 00:01:57 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_while_create(s_ast_node *cond, s_ast_node *exec)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_WHILE;
  node->body.child_while.cond = cond;
  node->body.child_while.exec = exec;
  return node;
}

void		ast_while_destruct(s_ast_node *node)
{
  if (node->type != T_WHILE)
    return;
  ast_destruct(node->body.child_while.cond);
  ast_destruct(node->body.child_while.exec);
  free(node);
}
