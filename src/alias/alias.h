/*
** alias.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug 23 00:32:09 2006 Seblu
** Last update Wed Aug 23 18:44:52 2006 Seblu
*/

#ifndef ALIAS_H_
# define ALIAS_H_

# include <stddef.h>

typedef struct s_alias
{
  char		*name;
  char		*value;
} ts_alias;

typedef struct s_aliases
{
  size_t	size;
  size_t	pos;
  ts_alias	**db;
} ts_aliases;

/*!
** Create a new aliases database
**
** @return new alias database
*/
ts_aliases	*alias_init(void);

/*!
** Add an alias into an alias database
**
** @param aliases alias database
** @param name new alias name
** @param value new alias value
*/
void		alias_add(ts_aliases *aliases, const char *name, const char *value);

/*!
** Remove an alias into an alias database
**
** @param aliases alias database
** @param name alias name to remove
**
** @return true, if alias was found in database, else false
*/
int		alias_remove(ts_aliases *aliases, const char *name);

#endif
