/*
** builtin_doubledot.c for 42sh in /home/seblu/devel/c/towork/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Apr  8 18:02:31 2006 Seblu
** Last update Sun Apr  9 12:38:38 2006 SIGOURE Benoit
*/

#include <stddef.h>
#include "builtin.h"

#include "mem.h"

/*!
** Builtin double dot, allow you to cdup
**
** @param argv argv vector
** @param sh sh data
**
** @return builtin return success
*/
int		builtin_doubledot(char *argv[], struct s_42sh *sh)
{
  char		*argv2[3];

  argv2[0] = "cd";
  argv2[1] = "..";
  argv2[2] = NULL;
  return builtin_cd(argv2, sh);
  argv = argv;
}
