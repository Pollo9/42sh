/*
** shell_init.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 16 20:11:09 2006 Seblu
** Last update Thu Aug  3 05:28:33 2006 Seblu
*/

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "shell.h"
#include "../opt/opt.h"
#include "../common/mem.h"
#include "../common/common.h"


/* static int		pwd_isgood(); */
/* static void		set_default_option(struct s_opt *); */

/*!
** Create shell structure
**
** @return the new shell structure
*/
ts_shell		*shell_init(const char *argv0)
{
  ts_shell		*new;

  secmalloc(new, sizeof (ts_shell));
/*   new->vars = NULL; */
/*   new->funcs = NULL; */
/*   new->history = NULL; */
  new->opt = opt_init();
/*   if (!pwd_isgood()) */
/*   { */
/*      var_setenv("PWD", (tmp = var_getcwd()), 1); */
/*      free(tmp); */
/*   } */
/*   var_unsetenv("OLDPWD"); */
  new->name = basename(argv0);
  new->status = 0;
  return new;
}

/*!
** Default sh option
**
*/
/* static void		set_default_option(struct s_opt *opt) */
/* { */
/*   opt_unset("xpg_echo", opt); */
/*   opt_unset("dotglob", opt); */
/*   opt_unset("extglob", opt); */
/*   opt_unset("nocaseglob", opt); */
/*   opt_unset("expand_aliases", opt); */
/*   opt_unset("bonus", opt); */
/*   opt_unset("readline", opt); */
/* } */

/*!
** Check if pwd, if set on the current directory
**
** @return bool satus
*/
/* static int		pwd_isgood() */
/* { */
/*    char			*pwd; */
/*    struct stat		s_pwd; */
/*    ino_t		ino_pwd; */

/*    pwd = getenv("PWD"); */
/*    if (stat(pwd, &s_pwd) == -1) */
/*       return 0; */
/*    ino_pwd = s_pwd.st_ino; */
/*    pwd = var_getcwd(); */
/*    if (stat(pwd, &s_pwd) == -1) */
/*    { */
/*       perror("42sh"); */
/*       exit(1); */
/*    } */
/*    free(pwd); */
/*    return ino_pwd == s_pwd.st_ino; */
/* } */
