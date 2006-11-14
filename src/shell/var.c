/*
** var.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 13:55:46 2006 seblu
** Last update Tue Nov 14 16:25:06 2006 seblu
*/

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "var.h"
#include "../common/macro.h"
#include "../common/function.h"

s_var		*var_init(void)
{
  s_var		*var;

  secmalloc(var, sizeof (s_var));
  var->count = 0;
  var->size = VAR_DEFAULT_SIZE;
  secmalloc(var->table, var->size * sizeof (s_var_item));
  return var;
}

const char	*var_get(const s_var *var, const char *name)
{
  const char	*res;

  assert(name && var);
  if ((res = getenv(name)))
    return res;
  for (size_t i = 0; i < var->count; ++i) {
    if (!(var->table[i].name))
      continue;
    if (!strcmp(var->table[i].name, name))
      return var->table[i].value;
  }
  return NULL;
}

void		var_set(s_var	*var,
			char	*name,
			char	*value,
			int	env,
			int	overwrite)
{
  assert(0); var = var; name = value; env = overwrite;
/*  size_t		i; */
/*  int		pos = -1; */

/*   if (getenv(name)) { */
/*     setenv2(name, value, overwrite); */
/*     return; */
/*   } */
/*   for (i = 0; i < var->count; ++i) */
/*   { */
/*     if (!(var->table[i].name)) */
/*       pos = i; */
/*     else */
/*       if (!strcmp(var->table[i].name, name)) */
/* 	break; */
/*   } */
/*   if (i < var->count) */
/*     set_exist_var(var, value, overwrite, i); */
/*   else */
/*     if (pos != -1) */
/*       set_non_exist_var(var, value, name, pos); */
/*     else */
/*       add_var(var, name, value); */
}

int		var_unset(s_var *var, const char *name)
{
  assert(var && name);
/*   if (getenv(name)) { */
/*     var_unsetenv(name); */
/*     return 0; */
/*   } */
/*   for (i = 0; i < var->len_var; ++i) */
/*   { */
/*     if (!(var->tab_var[i].name)) */
/*       continue; */
/*     if (!strcmp(var->tab_var[i].name, name)) */
/*     { */
/*       free(var->tab_var[i].name); */
/*       free(var->tab_var[i].value); */
/*       var->tab_var[i].name = NULL; */
/*       var->tab_var[i].value = NULL; */
/*       return 0; */
/*     } */
/*   } */
  return 1;
}

/* static void		add_var(struct s_var	*var, */
/* 				const char	*name, */
/* 				const char	*value) */
/* { */
/*   struct s_local_var	*new_buff; */

/*   if (var->len_var >= var->size) */
/*   { */
/*     var->size += 50; */
/*     secrealloc(new_buff, var->tab_var, sizeof (struct s_local_var) * var->size); */
/*     free(var->tab_var); */
/*     var->tab_var = new_buff; */
/*   } */
/*   secstrdup(var->tab_var[var->len_var].name, name); */
/*   secstrdup(var->tab_var[var->len_var].value, value); */
/*   ++var->len_var; */
/* } */

/* static void		set_exist_var(struct s_var	*var, */
/* 				      const char	*value, */
/* 				      char		perm, */
/* 				      unsigned int	i) */
/* { */
/*   if (!perm) */
/*     return; */
/*   free(var->tab_var[i].value); */
/*   secstrdup(var->tab_var[i].value, value); */
/* } */

/* static void		set_non_exist_var(struct s_var	*var, */
/* 					  const char	*value, */
/* 					  const char	*name, */
/* 					  unsigned int	i) */
/* { */
/*   secstrdup(var->tab_var[i].name, name); */
/*   secstrdup(var->tab_var[i].value, value); */
/* } */

void		var_print(const s_var *var)
{
  for (size_t i = 0; i < var->count; ++i) {
    if (!(var->table[i].name))
      continue;
    printf("%s=%s\n", var->table[i].name, var->table[i].value);
  }
}
