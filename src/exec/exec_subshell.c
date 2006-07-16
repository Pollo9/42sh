/*
** exec_subshell.c for 42sh in /home/seblu/devel/c/42sh/src/execution
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Apr 15 08:54:51 2006 Seblu
** Last update Tue May 16 20:18:49 2006 Seblu
*/

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include "execution.h"

#include "mem.h"

void		in_subshell(struct s_subshell *node, struct s_42sh *sh);

/*!
** Execute a subshell
**
** @param node node to treat
** @param sh sh info
*/
void		exec_subshell(struct s_subshell *node, struct s_42sh *sh)
{
   pid_t	pid;
   int		status;

   assert(node && node->head && sh);
   if ((pid = fork()) == -1)
   {
      perror("42sh");
      sh->last_status = FORK_ERROR;
      return;
   }
   if (pid)
   {
      waitpid(pid, &status, 0);
      sh->last_status = WEXITSTATUS(status);
   }
   else
      exec_node(node->head, sh);
}
