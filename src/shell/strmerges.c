/*
** strmerges.c for 42sh in /home/seblu/devel/c/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue May 16 21:23:02 2006 Seblu
** Last update Tue May 16 21:27:30 2006 Seblu
*/

#include <stdarg.h>
#include <string.h>
#include "42sh.h"

/*!
** Merge strings
**
** @param n number of string to merge
** @param s1 First string to merge
**
** @return malloced string merged
** @warning the returned string must be freed by the caller
*/
char            *strmerges(int n, const char *s1, ...)
{
  va_list       param;
  char          *new = NULL;
  char          *tmp;
  int           i;
  size_t        l_new;
  size_t        l_tmp;

  va_start(param, s1);
  l_new = strlen(s1);
  secmalloc(new, (l_new + 1) * sizeof (char));
  strcpy(new, s1);
  for (i = 1; i < n; i++)
    {
      tmp = va_arg(param, char *);
      l_tmp = strlen(tmp);
      l_new += l_tmp;
      secrealloc(new, new, (l_new + 1) * sizeof (char));
      strcpy(new + l_new - l_tmp, tmp);
    }
  va_end(param);
  return new;
}