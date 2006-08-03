/*
** opt_init.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 03:33:09 2006 Seblu
** Last update Thu Aug  3 02:45:51 2006 Seblu
*/

#include "opt.h"
#include "../common/mem.h"

/*!
** Create a new option structure
**
** @return A new option structure
*/
ts_opt		*opt_init(void)
{
  ts_opt	*new;

  secmalloc(new, sizeof (ts_opt));
  new->command = NULL;
  return new;
}
