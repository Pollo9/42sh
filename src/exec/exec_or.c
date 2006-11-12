/*
** exec_and.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Sun Nov 12 13:40:45 2006 seblu
*/

#include "exec.h"

void		exec_or(s_bin_node *node)
{
  assert(node);
  exec_node(node->lhs);
  //FIXME: error with chained "or" and "and"
  if (shell->status)
    exec_node(node->rhs);
}
