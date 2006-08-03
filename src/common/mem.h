/*
** mem.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 03:35:39 2006 Seblu
** Last update Sun Jul 30 03:42:49 2006 Seblu
*/

#ifndef MACRO_H_
# define MACRO_H_

#include <stdlib.h>

static const int MEM_ERROR = 42;

# define secmalloc(name, size) if (!(name = malloc(size))) exit(MEM_ERROR)
# define secrealloc(ret, name, size) if (!(ret = realloc(name, size))) exit(MEM_ERROR)
# define secstrdup(ret, str) if (!(ret = strdup(str))) exit(MEM_ERROR)

#endif
