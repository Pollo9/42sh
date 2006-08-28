/*
** alias.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug 23 00:39:17 2006 Seblu
** Last update Mon Aug 28 23:08:31 2006 Seblu
*/

#include <string.h>
#include "alias.h"
#include "../common/macro.h"

static size_t step = 5;

s_aliases	*alias_init(void)
{
  s_aliases	*new;

  secmalloc(new, sizeof (s_aliases));
  new->size = step;
  new->pos = 0;
  new->db = NULL;
  return new;
}

void		alias_add(s_aliases *aliases, const char *name, const char *value)
{
  s_alias	*new;
  int		freeplace = 0;
  size_t	index;

  //check if already exist and if free place exist
  for (register int i = 0; aliases && aliases->db[i]; ++i)
    if (!strcmp(aliases->db[i]->name, name)) {
      free(aliases->db[i]->value);
      aliases->db[i]->value = strdup(value);
      return;
    }
    else if (!freeplace && *aliases->db[i]->name == 0)
      index = i;
  //if a place is free, fill it
  if (freeplace) {
    aliases->db[index]->name = strdup(name);
    aliases->db[index]->value = strdup(value);
    return;
  }
  //create a new one
  secmalloc(new, sizeof (s_alias));
  new->name = strdup(name);
  new->value = strdup(value);
  //add a new alias if not find
  if (aliases->pos >= aliases->size) {
    aliases->size += step;
    secrealloc(aliases->db, aliases->db, aliases->size * sizeof (s_alias));
  }
  aliases->db[aliases->pos] = new;
  ++aliases->pos;
}

int		alias_remove(s_aliases *aliases, const char *name)
{
  //find alias index
  for (register int i = 0; aliases && aliases->db[i]; ++i)
    if (!strcmp(aliases->db[i]->name, name)) {
      free(aliases->db[i]->name);
      free(aliases->db[i]->value);
      aliases->db[i]->name = "";
      return 1;
    }
  return 0;
}
