/*
** exec_and.c for 42sh in /home/seblu
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Sun Apr  9 12:04:03 2006 SIGOURE Benoit
*/

#include "execution.h"

#include "mem.h"

/*!
** Execution an AND node
**
** @param node node to treat
** @param sh sh data
*/
void		exec_and(struct s_op *node, struct s_42sh *sh)
{
  assert(node && sh);
  exec_node(node->left, sh);
  if (!sh->last_status)
    exec_node(node->right, sh);
}
