/*
** builtin.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Apr 11 00:22:44 2006 Seblu
** Last update Sun Nov 12 19:56:53 2006 Seblu
*/

#include <string.h>
#include "builtin.h"

enum { BUILTIN_COUNT = 7 };

typedef int (*f_builtin)(char *argv[]);

struct builtin_table
{
  const char *name;
  f_builtin func;
};

static struct builtin_table builtin_table[BUILTIN_COUNT] =
  {
    {"cd", NULL}, //builtin_cd},
    {"echo", NULL}, //builtin_echo},
    {"exit", builtin_exit},
    {"shopt", NULL}, //builtin_shopt},
    {"source", NULL}, //builtin_source},
    {"unset", NULL}, //builtin_unset},
    {"export", NULL}, //builtin_export}
  };

int		is_a_builtin(const char *name)
{
  register int	i;

  for (i = 0; i < BUILTIN_COUNT; ++i)
    if (!strcmp(name, builtin_table[i].name))
      return 1;
  return 0;
}

int		exec_builtin(s_cmd_node *cmd)
{
  register int	i;

  for (i = 0; i < BUILTIN_COUNT; ++i)
    if (!strcmp(cmd->argv[0], builtin_table[i].name))
      return builtin_table[i].func(cmd->argv);
  return 0;
}
