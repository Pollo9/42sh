/*
** opt_shopt.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Mar 21 19:00:38 2006 Seblu
** Last update Sun Jul 30 03:41:36 2006 Seblu
*/

#include <string.h>
#include "../shell/shell.h"
#include "opt.h"

static const char *opts_table[NBR_OPT] =
  {
    "xpg_echo",
    "dotglob",
    "extglob",
    "nocaseglob",
    "nullglob",
    "expand_aliases",
  };

/*!
** Set a shell option
**
** @param name name of the option to set
** @param shopt structure to apply
**
** @return 0 on failure, else 1
*/
int		opt_set(const char *name, ts_opt *shopt)
{
  register int	i;

  for (i = 0; opts_table[i]; ++i)
    if (!strcmp(name, opts_table[i]))
    {
      shopt->item[i] = 1;
      return 1;
    }
  return 0;
}

/*!
** Unset a shell option
**
** @param name name of the option to unset
** @param shopt structure to apply
**
** @return 0 on failure, else 1
*/
int		opt_unset(const char *name, ts_opt *shopt)
{
  register int	i;

  for (i = 0; opts_table[i]; ++i)
    if (!strcmp(name, opts_table[i]))
    {
      shopt->item[i] = 0;
      return 1;
    }
  return 0;
}


/*!
** Tell if an option is set. if option nane is not set return -1
**
** @param name name to find
** @param shopt structure where find
**
** @return 0 if unset, 1 if set and -1 if not exist
*/
int		opt_isset(const char *name, const ts_opt *shopt)
{
  register int	i;

  for (i = 0; opts_table[i]; ++i)
    if (!strcmp(name, opts_table[i]))
      return shopt->item[i];
  return -1;
}

/*!
** Return a list of know opt
**
** @return list of opt
*/
const char	**opt_get()
{
  return opts_table;
}
