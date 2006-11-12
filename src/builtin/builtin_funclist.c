/*
** builtin_funclist.c for 42sh in /goinfre/seblu/42sh/src/builtin
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Thu May 11 10:00:36 2006 Seblu
** Last update Sun May 21 18:40:33 2006 Seblu
*/

#include <assert.h>
#include <stdio.h>
#include "builtin.h"
#include "../func/function.h"
#include "../main/42sh.h"

int	builtin_funclist(char *argv[], struct s_42sh *sh)
{
   assert(sh);
   /* FIXME
   func_print(sh->funcs);
   */
   printf("Not yet implemented !\n");
   return 0;
   argv = argv;
   sh = sh;
}
