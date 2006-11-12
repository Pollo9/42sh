/*
** builtin_history.c for  in /home/joel/42sh
**
** Made by joel
** Login   <joel@epita.fr>
**
** Started on  Wed May 17 12:28:30 2006 joel
** Last update Sun May 21 18:44:31 2006 Seblu
*/

#include <assert.h>
#include <stdio.h>
#include "../main/42sh.h"
#include "../history/history.h"
#include "builtin.h"


/*!
** Builtin history.
** @param argv The tab of args: terminated by NULL, argv[0] = "cd"
** @param sh The 42sh structure
*/
int			builtin_history(char **argv, struct s_42sh *sh)
{
  struct s_my_dlist	*list;
  char			*elem;
  int			count = 1;

  assert(sh && argv && argv[0]);
  if (!sh->history->list)
    return 0;
  for (list = sh->history->list; list->next != NULL; list = list->next)
    ;
  for (; list; list = list->prev, ++count)
    fprintf(stdout, "    %i  %s\n", count, elem = list->elem);
  return 0;
  argv = argv;
}
