/*
** builtin_exit.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Nov 12 16:48:50 2006 Seblu
** Last update Sun Nov 12 16:49:42 2006 Seblu
*/

#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "builtin.h"
#include "../main/42sh.h"

/*!
** Terminate program
**
** @param argv vector to argument
** @param shopt option structure of shell
**
** @return
*/
int	builtin_exit(char *argv[])
{
  long	i;
  char	*endptr;

  assert(argv && argv[0]);
  if (!argv[1])
  {
/*     if (isatty(fileno(stdin))) */
/*       printf("exit\n"); */
    i = sh->last_status;
    sh_destroy(sh);
    exit(i);
  }
  if (argv[2])
  {
    fprintf(stderr, "42sh : exit : too many arguments\n");
    fflush(stderr);
    return 1;
  }
  i = strtol(argv[1], &endptr, 10);
/*   if (isatty(fileno(stdin))) */
/*     printf("exit\n"); */
  if (*endptr)
    fprintf(stderr, "42sh: exit: %s: numeric argument required\n", argv[1]);
  sh_destroy(sh);
  exit((!*endptr) ? i : 255);
  return 1;
}
