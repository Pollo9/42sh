/*
** exec_start.c for 42sh in /home/seblu
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 14:40:36 2006 Seblu
** Last update Fri May 19 17:57:30 2006 alexandre gerlic
*/

#include "execution.h"
#include "mem.h"

/*!
** Start AST execution
**
** @param sh sh struct to execute
*/
void		exec_start(struct s_42sh *sh)
{
  assert(sh && sh->ast);
  exec_node(sh->ast, sh);
  ast_destruct(sh->ast);
}
