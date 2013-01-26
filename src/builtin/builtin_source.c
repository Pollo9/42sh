/*
** builtin_source.c for 42sh in /goinfre/42sh/src
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Sun Apr  9 04:40:11 2006 Seblu
** Last update Sun May 21 18:35:59 2006 Seblu
*/

#include <stdio.h>
#include <assert.h>
#include "builtin.h"
#include "../main/42sh.h"
#include "../execution/execution.h"

#include "mem.h"

static int		builtin_source_error(int err);

int			builtin_source(char *argv[], struct s_42sh *sh)
{
   FILE			*fd;
   int			yyparse();
   void			scan_switch_buffer(FILE *fd);
   int			scanerr = 0;
   int			parseerr = 0;
   struct s_42sh	tempsh;

   assert(argv && sh);
   if (!argv[1])
      return builtin_source_error(2);
   else if (!(fd = fopen(argv[1], "r")))
      return builtin_source_error(1);
   /* FIXME: call gerlic */
   scan_switch_buffer(fd);
   parseerr = yyparse("source: ", &scanerr, &tempsh);
   if (scanerr)
      return builtin_source_error(SCAN_ERROR);
   if (parseerr)
      return builtin_source_error(PARSE_ERROR);
   fclose(fd);
   scan_switch_buffer(NULL);
   exec_start(&tempsh);
   /* FIXME: ast destruction */
   return tempsh.last_status;
   sh = sh;
}

static int		builtin_source_error(int err)
{
   if (err == 1)
      perror("42sh: source");
   else if (err == 2)
      fprintf(stderr, "42sh: source: filename argument required\n");
   return 1;
}
