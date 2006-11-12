/*
** builtin_cd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Apr 11 00:23:47 2006 Seblu
** Last update Sun Nov 12 19:55:57 2006 Seblu
*/

#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../main/42sh.h"
#include "builtin.h"
#include "../var/var.h"

static int cd_var(struct s_42sh *sh, const char *name);
static int cd_minus(struct s_42sh *sh);
static int secure_chdir(const char *path);

/*!
** Builtin cd.
** @param argv The tab of args: terminated by NULL, argv[0] = "cd"
** @param sh The 42sh structure
*/
int	builtin_cd(char **argv)
{
  assert(sh && argv && argv[0]);

  if (!argv[1])
    return cd_var(sh, "HOME");
  if (!strcmp("-", argv[1]))
    return cd_minus(sh);
  return secure_chdir(argv[1]);
}

/*!
** Change directory to home directory
**
** @param sh shell env
** @param name env var
**
** @return exit status
*/
static int	cd_var(struct s_42sh *sh, const char *name)
{
  const char	*new_dir;

  if (!(new_dir = var_get(sh->vars, name)))
  {
    fprintf(stderr, "42sh: cd: %s not set\n", name);
    return 1;
  }
  return secure_chdir(new_dir);
}

/*!
** Return in previous directory
**
** @param sh shell info
**
** @return return status
*/
static int	cd_minus(struct s_42sh *sh)
{
  if (cd_var(sh, "OLDPWD"))
    return 1;
  return 0;
}

/*!
** Change of directory and on error, print good error.
**
** @param path new path
**
** @return error status with error code (0 is good)
*/
static int	secure_chdir(const char *path)
{
  const char	*errormsg = "";
  char		*tmp;

  errno = 0;
  if (chdir(path))
  {
    if (errno == ENOENT)
      errormsg = "No such file or directory";
    else if (errno == EACCES)
      errormsg = "Permission denied";
    else if (errno == ENAMETOOLONG)
      errormsg = "File name too long";
    else if (errno == ENOTDIR)
      errormsg = "Not a directory";
    else if (errno == ELOOP)
      errormsg = "Too many levels of symbolic links";
    else
      assert(0);
    fprintf(stderr, "42sh: cd %s: %s\n", path, errormsg);
    return 1;
  }
  if ((tmp = getenv("PWD")))
    var_setenv("OLDPWD", tmp, !0);
  var_setenv("PWD", (tmp = var_getcwd()), !0);
  free(tmp);
  return 0;
}
