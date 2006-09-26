/*
** ast_until.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Sep 26 17:44:32 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_until_create(s_ast_node *cond, s_ast_node *exec)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_UNTIL;
  node->body.child_until.cond = cond;
  node->body.child_until.exec = exec;
  return node;
}

void		ast_until_print(s_ast_node *node, FILE *fs, unsigned int *node_id)
{
  unsigned int	lhs_id, rhs_id, cur_id;

  if (node->type != T_UNTIL)
    return;
  fprintf(fs, "%u [label = \"until\"];\n", cur_id = *node_id);
  lhs_id = ++*node_id;
  ast_print_node(node->body.child_until.cond, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
  rhs_id = *node_id;
  ast_print_node(node->body.child_until.exec, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, rhs_id);
}

void		ast_until_destruct(s_ast_node *node)
{
  if (node->type != T_UNTIL)
    return;
  ast_destruct(node->body.child_until.cond);
  ast_destruct(node->body.child_until.exec);
  free(node);
}
