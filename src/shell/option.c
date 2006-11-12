/*
** opt_shopt.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Mar 21 19:00:38 2006 Seblu
** Last update Sun Nov 12 20:11:40 2006 Seblu
*/

/*
** ============
** DECLARATIONS
** ============
*/

#include <string.h>
#include "option.h"
#include "../shell/shell.h"
#include "../common/macro.h"

static const char *opts_table[NBR_OPTION] =
  {
    "xpg_echo",
    "dotglob",
    "extglob",
    "nocaseglob",
    "nullglob",
    "expand_aliases",
    "ast_print",
  };

/*
** ===========
** DEFINITIONS
** ===========
*/

s_options	*option_init(void)
{
  s_options	*new;

  secmalloc(new, sizeof (s_options));
  new->command = NULL;
  //FIXME: item is uninitialized! Do it here
  return new;
}

int		option_set(s_options *shopt, const char *name)
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

int		option_unset(s_options *shopt, const char *name)
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

int		option_isset(const s_options *shopt, const char *name)
{
  register int	i;

  for (i = 0; opts_table[i]; ++i)
    if (!strcmp(name, opts_table[i]))
      return shopt->item[i];
  return -1;
}

const char	**opt_get()
{
  return opts_table;
}
