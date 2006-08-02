/*
** readline.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 01:06:25 2006 Seblu
** Last update Wed Aug  2 17:57:38 2006 Seblu
*/

#ifndef READLINE_H_
# define READLINE_H_

# define GETLN_BUF_SIZE 1024

struct          s_getln
{
  int           fd;
  char          data[GETLN_BUF_SIZE];
  unsigned      offset;
  int           size;
};

char		*readline(const char *prompt);
char            *getln(struct s_getln *buf);
void            getln_close(struct s_getln *buf, const int closefd);
struct s_getln  *getln_open(const int fd);

#endif
