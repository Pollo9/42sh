/*
** builtin_set.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu May 11 09:32:30 2006 Seblu
** Last update Fri Nov 17 12:57:32 2006 seblu
*/

#include <stdio.h>
#include <assert.h>
#include "../shell/shell.h"

int	builtin_set(char *argv[])
{
  assert(argv);
  fprintf(stderr, "%s: set: not yet implemeted.\n", shell->name);
  argv = argv;
  return 1;
}
