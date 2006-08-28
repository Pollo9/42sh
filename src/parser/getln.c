/*
** getln.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 01:25:01 2006 Seblu
** Last update Mon Aug 28 22:55:18 2006 Seblu
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../common/macro.h"
#include "getln.h"

/*!
** Secure layer over strlen
**
** @param s the string
**
** @return lenght of the string
*/
#define sstrlen(s) ((s) == NULL ? 0 : strlen(s))

/*
** Append a string to the buffer string
*/
static void     buf_str(char **str, char *append, unsigned n)
{
  unsigned      ln;
  unsigned      i;
  unsigned      j;

  ln = sstrlen(*str);
  if ((*str = realloc(*str, (ln + n + 1) * sizeof (char))) == NULL)
    exit(1);
  for (i = ln, j = 0; i < ln + n; i++, j++)
    (*str)[i] = append[j];
  (*str)[ln + n] = 0;
}

s_getln		*getln_open(int fd)
{
  s_getln		*new_buf;

  secmalloc(new_buf, sizeof (s_getln));
  new_buf->fd = fd;
  new_buf->size = 0;
  new_buf->offset = 0;
  return new_buf;
}

void            getln_close(s_getln *buf, int closefd)
{
  if (closefd)
    close(buf->fd);
  free(buf);
}

char            *getln(s_getln *buf)
{
  char          *string = NULL;
  int           i;

  do
  {
    for (i = buf->offset; i < buf->size; i++)
      {
        if (buf->data[i] == '\n')
          {
            buf_str(&string, buf->data + buf->offset, i - buf->offset + 1);
            buf->offset = i + 1;
            return string;
          }
      }
    if (buf->size - buf->offset > 0)
      buf_str(&string, buf->data + buf->offset, buf->size - buf->offset);
    buf->offset = 0;
    buf->size = read(buf->fd, buf->data, GETLN_BUF_SIZE);
    if (buf->size < 0)
      buf->size = 0;
  }
  while (buf->size > 0);
  return string;
}
