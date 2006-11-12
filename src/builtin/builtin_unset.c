/*
** builtin_unset.c for 42sh in /goinfre/seblu/42sh/src/builtin
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Thu May 11 09:36:06 2006 Seblu
** Last update Thu May 11 10:19:36 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "builtin.h"
#include "../var/var.h"
#include "../func/function.h"
#include "../main/42sh.h"

int		builtin_unset(char *argv[], struct s_42sh *sh)
{
   int		f = 0;
   int		v = 1;
   int		i;

   assert(argv && sh);
   for (i = 0; argv[i]; ++i)
      if (!strcmp(argv[i], "-v"))
	 v = 1;
      else if (!strcmp(argv[i], "-v"))
	 f = 1;
   for (i = 0; argv[i]; ++i)
      if (argv[i][0] == '-')
	 continue;
      else
      {
	 if (v)
	    var_unset(sh->vars, argv[i]);
	 if (f)
	    func_del(argv[i], &sh->funcs);
      }
   return 0;
}
