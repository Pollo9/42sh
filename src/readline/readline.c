/*
** readline.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 01:13:56 2006 Seblu
** Last update Fri Aug 25 07:52:48 2006 Seblu
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "readline.h"

struct s_getln getln_stdin;

char	*readline(const char *prompt)
{
  if (prompt && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
    write(STDERR_FILENO, prompt, strlen(prompt));
  return getln(&getln_stdin);
}
