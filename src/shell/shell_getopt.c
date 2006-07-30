/*
** shell_getopt.c
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 02:24:42 2006 Seblu
** Last update Sun Jul 30 02:53:05 2006 Seblu
*/

#include <stdio.h>
#include "shell.h"

void	shell_getopt(int argc, char *argv[])
{
  if (argc == 1)
    return;
  for (int i = 1; i < argc; ++i)
    {
      printf("Argument %d: %s\n", argc, argv[i]);
    }
}
