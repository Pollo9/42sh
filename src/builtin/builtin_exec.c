/*
** builtin_exec.c for 42sh in /goinfre/seblu/42sh/src/builtin
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Thu May 11 10:00:36 2006 Seblu
** Last update Sun May 21 18:42:29 2006 Seblu
*/

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include "builtin.h"
#include "../main/42sh.h"

/*!
** Replace current process by which is given in arg
**
** @param argv arg vector
** @param sh shell struct
**
** @return success status
*/
int	builtin_exec(char *argv[], struct s_42sh *sh)
{
   assert(sh && argv);
   if (!argv[1])
      return 0;
   if (execvp(argv[1], argv + 1) == -1)
   {
      perror("42sh: exec");
      return 127;
   }
   return 0;
   argv = argv;
   sh = sh;
}
