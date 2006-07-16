/*
** exec_until.c for 42sh in /home/seblu
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
** Execute a node while a condition is verified
**
** @param node fucking node
** @param sh fucking sh structure
*/
void		exec_until(struct s_while *node, struct s_42sh *sh)
{
  assert(node && sh);
  for (exec_node(node->cond, sh); sh->last_status; exec_node(node->cond, sh))
    exec_node(node->exec, sh);
}
