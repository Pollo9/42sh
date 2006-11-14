/*
** func.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 14:52:39 2006 seblu
** Last update Tue Nov 14 15:59:57 2006 seblu
*/

/*
** ============
** DECLARATIONS
** ============
*/

#include <string.h>
#include "func.h"
#include "../common/macro.h"

/*
** ===========
** DEFINITIONS
** ===========
*/

s_func		*func_init(void)
{
  s_func	*new;

  secmalloc(new, sizeof (s_func));
  new->count = 0;
  new->size = FUNC_DEFAULT_SIZE;
  secmalloc(new->table, new->size * sizeof (s_func_item));
  return new;
}
