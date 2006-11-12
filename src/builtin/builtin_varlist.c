/*
** builtin_varlist.c for 42sh in /goinfre/seblu/42sh/src/builtin
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Thu May 11 10:00:36 2006 Seblu
** Last update Sun May 21 18:40:43 2006 Seblu
*/

#include <assert.h>
#include "builtin.h"
#include "../var/var.h"
#include "../main/42sh.h"

int	builtin_varlist(char *argv[], struct s_42sh *sh)
{
   assert(sh);
   var_print(sh->vars);
   return 0;
   argv = argv;
   sh = sh;
}
