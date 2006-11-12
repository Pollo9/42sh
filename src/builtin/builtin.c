/*
** builtin.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Apr 11 00:22:44 2006 Seblu
** Last update Sun Nov 12 16:47:59 2006 Seblu
*/

#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "builtin.h"
#include "../main/42sh.h"
#include "../ast/ast.h"
#include "../opt/opt.h"

#define BUILTIN_NUMBER 7
#define BUILTIN_BONUS_NUMBER 7

static const char *builtin_name[BUILTIN_NUMBER] =
  {
    "cd",
    "echo",
    "exit",
    "shopt",
    "source",
    "unset",
    "export"
  };

static const char *builtin_bonus_name[BUILTIN_BONUS_NUMBER] =
  {
    ".",
    "..",
    "set",
    "varlist",
    "funclist",
    "exec",
    "history"
  };

static const t_func_builtin builtin_function[BUILTIN_NUMBER] =
  {
    builtin_cd,
    builtin_echo,
    builtin_exit,
    builtin_shopt,
    builtin_source,
    builtin_unset,
    builtin_export
  };

static const t_func_builtin builtin_bonus_function[BUILTIN_BONUS_NUMBER] =
  {
    builtin_simpledot,
    builtin_doubledot,
    builtin_set,
    builtin_varlist,
    builtin_funclist,
    builtin_exec,
    builtin_history
  };

/*!
** test if a command is a builtin
**
** @param name The name of the command
** @return 1 if \a name is a builtin, else 0
*/
int		is_a_builtin(const char *name, struct s_42sh *sh)
{
  register int	i;

  for (i = 0; i < BUILTIN_NUMBER; ++i)
    if (!strcmp(name, builtin_name[i]))
      return 1;
  if (opt_isset("bonus", sh->opt))
    for (i = 0; i < BUILTIN_BONUS_NUMBER; ++i)
      if (!strcmp(name, builtin_bonus_name[i]))
	return 1;
  return 0;
}

/*!
** execute a shell builtin
**
** @param builtin_name The name of the builtin
** @param argv The builtin arguments, terminate by NULL, argv[0] = builtin_name
** @return The return value of the builtin
*/
int		exec_builtin(struct s_cmd *cmd, struct s_42sh *sh)
{
  register int	i;

  for (i = 0; i < BUILTIN_NUMBER; ++i)
    if (!strcmp(cmd->argv[0], builtin_name[i]))
      return builtin_function[i](cmd->argv, sh);
  if (opt_isset("bonus", sh->opt))
    for (i = 0; i < BUILTIN_BONUS_NUMBER; ++i)
      if (!strcmp(cmd->argv[0], builtin_bonus_name[i]))
	return builtin_bonus_function[i](cmd->argv, sh);
  return 0;
}
