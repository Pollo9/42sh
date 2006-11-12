/*
** builtin_shopt.c for 42sh in /goinfre/seblu/42sh/src
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Wed Mar 22 16:27:35 2006 Seblu
** Last update Tue Apr 11 00:24:22 2006 Seblu
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "builtin.h"
#include "../main/42sh.h"
#include "../opt/opt.h"

#include "mem.h"

static void	getoption(char *argv[], int *argp, int opts[2]);
static int	mutator_opt(char *argv[], int *argp, int opts[2], struct s_42sh *sh);
static int	show_opt(char *argv[], int *argp, int opts[2], struct s_42sh *sh);
static int	show_all_opt(int quiet, struct s_42sh *sh);

/*!
** This builtin change local setting of the shell
** opts[0] == set or unset
** opts[1] == quiet mode
**
** @param argv argument vector
** @param sh shell data
**
** @return success status
*/
int		builtin_shopt(char *argv[], struct s_42sh *sh)
{
  int		opts[2];
  int		argp = 1;

  assert(argv && argv[0] && sh);
  opts[0] = -1;
  opts[1] = 0;
  getoption(argv, &argp, opts);
  if (opts[0] == -1 && !argv[argp])
    return show_all_opt(opts[1], sh);
  else if (opts[0] == -1 && argv[argp])
    return show_opt(argv, &argp, opts, sh);
  else
    return mutator_opt(argv, &argp, opts, sh);
}

/*!
** Retreinve command line option
**
** @param argv argument vector
** @param argp argument position
** @param line line flag
** @param ext extended flag
*/
static void	getoption(char *argv[], int *argp, int opts[2])
{
  for (; argv[*argp]; ++*argp)
    if (!strcmp("-s", argv[*argp]))
      opts[0] = 1;
    else if (!strcmp("-u", argv[*argp]))
      opts[0] = 0;
    else if (!strcmp("-q", argv[*argp]))
      opts[1] = 1;
    else
      break;
}

/*!
** Sun or unset an option
**
** @param argv arg vector
** @param argp cur pos
** @param opts argline opts
** @param sh struct info
**
** @return builtin status
*/
static int	mutator_opt(char		*argv[],
			    int			*argp,
			    int			opts[2],
			    struct s_42sh	*sh)
{
  int		ret = 0;

  for (; argv[*argp]; ++*argp)
  {
    if (opt_isset(argv[*argp], sh->opt) == -1)
    {
      fprintf(stderr, "42sh: shopt: %s: invalid shell option name\n",
	      argv[*argp]);
      ret = 1;
      continue;
    }
    if (opts[0])
      opt_set(argv[*argp], sh->opt);
    else
      opt_unset(argv[*argp], sh->opt);
  }
  return ret;
}

/*!
** Show info about shell opts
**
** @param argv arg vector
** @param argp cur pos
** @param opts argline opts
** @param sh struct info
**
** @return builtin status
*/
static int	show_opt(char			*argv[],
			 int			*argp,
			 int			opts[2],
			 struct s_42sh		*sh)
{
  int		ret = 0;
  int		isset = 0;

  for (; argv[*argp]; ++*argp)
  {
    if ((isset = opt_isset(argv[*argp], sh->opt)) == -1)
    {
      fprintf(stderr, "42sh: shopt: %s: invalid shell option name\n",
	      argv[*argp]);
      ret = 1;
      continue;
    }
    if (!opts[1])
      printf("%-15s %s\n", argv[*argp], (isset) ? "yes" : "no");
    else if (!isset)
      ret = 1;
  }
  return ret;
}

/*!
** Show all options
**
** @param quiet silent showing
**
** @return return status
*/
static int	show_all_opt(int quiet, struct s_42sh *sh)
{
  const char	**opts;
  register int	i;

  if (quiet)
    return 0;
  opts = opt_get();
  for (i = 0; opts[i]; ++i)
    printf("%-15s %s\n", opts[i], (opt_isset(opts[i], sh->opt)) ? "yes" : "no");
  return 0;
}
