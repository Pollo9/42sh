/*
** exec_if.c for 42sh in /home/seblu
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
** Execute if struct.
**
** @param node if struct
** @param sh sh data
*/
void exec_if(struct s_if *node, struct s_42sh *sh)
{
  assert(node && sh);
  exec_node(node->cond, sh);
  if (!sh->last_status)
    exec_node(node->if_then, sh);
  else
    exec_node(node->if_else, sh);
}
