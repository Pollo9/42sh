/*
** sh_destroy.c for 42sh in /home/seblu/devel/c++/tiger
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Fri Apr  7 00:19:04 2006 Seblu
** Last update Sun May 21 15:29:07 2006 Seblu
*/

#include <stdlib.h>
#include "42sh.h"
#include "../var/var.h"
#include "../func/function.h"
#include "../history/history.h"
#include "../opt/opt.h"

#include "mem.h"

/*!
** Destroy 42SH structure.
**
** @param sh structure to destroy
** @note the sh = sh is needed if compile with -DNDEBUG since the assert will
** be suppressed.
*/
void			sh_destroy(struct s_42sh *sh)
{
  assert(sh);
  if (opt_isset("readline", sh->opt) && sh->history)
  {
    history_save(sh);
    history_delete(&sh->history);
  }
  var_delete(&sh->vars);
  func_clean(&sh->funcs);
  free(sh->opt);
  free(sh);
}
