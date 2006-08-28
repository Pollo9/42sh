/*
** macro.h for 42sh
**
** Made by Seblu
** Login   <seblu@seblu.net>
**
** Started on  Fri Aug 25 03:32:54 2006 Seblu
** Last update Fri Aug 25 03:42:43 2006 Seblu
*/

#ifndef MACRO_H_
# define MACRO_H_

# include <unistd.h>
# include <stdlib.h>
# include "constant.h"

# define secmalloc(name, size) if (!(name = malloc(size))) exit(ERROR_MEM)
# define secrealloc(ret, name, size) if (!(ret = realloc(name, size))) exit(ERROR_MEM)
# define secstrdup(ret, str) if (!(ret = strdup(str))) exit(ERROR_MEM)

# define isinteractive() (isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))

#endif
