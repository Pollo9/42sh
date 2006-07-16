/*
** sh_destroy.c for 42sh in /home/seblu/devel/c++/tiger
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Fri Apr  7 00:19:04 2006 Seblu
** Last update Sun Jul 16 20:30:02 2006 Seblu
*/

#include <stdlib.h>
#include <assert.h>
#include "shell.h"


/*!
** Destroy 42SH structure.
**
** @param sh structure to destroy
**
*/
void			shell_destroy(struct s_shell *sh)
{
  assert(sh);
/*   var_delete(&sh->vars); */
/*   func_clean(&sh->funcs); */
/*   free(sh->opt); */
  free(sh);
}
