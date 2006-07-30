/*
** main.c for 42sh in /home/seblu/devel/c/42sh/src/execution
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Mon Apr 10 23:57:28 2006 Seblu
** Last update Sun Jul 30 03:15:49 2006 Seblu
*/

#include <stdio.h>
#include "shell.h"

/*
** Global shell structure
*/
ts_shell *shell = NULL;

/*!
** Program entry point
**
** @param argc Argument count
** @param argv Argument vector
**
** @return return program value
*/
int		main(int argc, char *argv[])
{
  int		ret;

  /* shell initialization */
  shell = shell_init();
  /* parse arg line */
  opt_parser(argc, argv, shell->opt);
  //open_parse(argc, argv, shell);
  /*   if (shell->ast) */
  /*      exec_start(shell); */
  ret = shell->last_status;
  shell_destroy(shell);
  return ret;
}
