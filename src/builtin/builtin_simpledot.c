/*
** builtin_simpledot.c for 42sh in /home/seblu/devel/c/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue May 16 19:59:03 2006 Seblu
** Last update Tue May 16 20:10:11 2006 Seblu
*/

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "builtin.h"

#include "mem.h"

/*!
** Builtin simple dot, equivalent to source
**
** @param argv argv vector
** @param sh sh data
**
** @return builtin return success
*/
int		builtin_simpledot(char *argv[], struct s_42sh *sh)
{
  assert(argv && sh);
  free(argv[0]);
  argv[0] = strdup("source");
  return builtin_source(argv, sh);
}
