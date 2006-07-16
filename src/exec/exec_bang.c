/*
** exec_bang.c for 42sh in /home/seblu
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
** Execution a BANG node
**
** @param node node to treat
** @param sh sh data
*/
void		exec_bang(struct s_op *node, struct s_42sh *sh)
{
  assert(node && sh && !node->left);
  exec_node(node->left, sh);
  sh->last_status = !sh->last_status;
}
