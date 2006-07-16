/*
** main.c for 42sh in /home/seblu/devel/c/42sh/src/execution
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Mon Apr 10 23:57:28 2006 Seblu
** Last update Sun Jul 16 20:26:30 2006 Seblu
*/

#include <stdio.h>

/*
** Global shell structure
*/
struct s_shell *shell = NULL;

/*!
** Program entry point
**
** @param argc Argument count
** @param argv Argument vector
**
** @return return program value
*/

#include "shell.h"

int		main(int argc, char *argv[])
{
  int		ret;

  /* shell initialization */
  shell = shell_init();
  /* parse arg line */
  argc = argc;
  argv = argv;
  //open_parse(argc, argv, shell);
  /*   if (shell->ast) */
  /*      exec_start(shell); */
  ret = shell->last_status;
  shell_destroy(shell);
  return ret;
}
