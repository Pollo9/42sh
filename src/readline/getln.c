/*
** getln.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 01:25:01 2006 Seblu
** Last update Thu Aug  3 11:44:30 2006 Seblu
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "readline.h"

/*!
** Secure layer over strlen
**
** @param s the string
**
** @return lenght of the string
*/
static size_t         sstrlen(const char *s)
{
  if (s == NULL)
    return 0;
  return strlen(s);
}

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


/*
** Memory allocation of getln buffer
*/
struct s_getln          *getln_open(const int fd)
{
  struct s_getln        *new_buf;

  if ((new_buf = malloc(sizeof (struct s_getln))) == NULL)
    exit(1);
  new_buf->fd = fd;
  new_buf->size = 0;
  new_buf->offset = 0;
  return new_buf;
}

/*
** Free a getln struct
*/
void            getln_close(struct s_getln *buf, const int closefd)
{
  if (closefd)
    close(buf->fd);
  free(buf);
}

/*
** Get next line in a file
** Return NULL when nothing to read
*/
char            *getln(struct s_getln *buf)
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
