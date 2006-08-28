/*
** getln.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 01:06:25 2006 Seblu
** Last update Mon Aug 28 22:56:28 2006 Seblu
*/

#ifndef GETLN_H_
# define GETLN_H_

# define GETLN_BUF_SIZE 1024

typedef struct	getln
{
  int           fd;
  char          data[GETLN_BUF_SIZE];
  unsigned      offset;
  int           size;
} s_getln;

/*!
** Read a line from fd. This read is bufferised !
**
** @param buf struct getln
**
** @return malloced readded line
*/
char            *getln(s_getln *buf);

/*!
** Correctly close an getln struct and if @arg closefd is true
** close the fd of getln struct
**
** @param buf structure getln to close
** @param closefd if true (!0), close fd of getln struct
*/
void            getln_close(s_getln *buf, int closefd);

/*!
** Create a getln struct associed with @arg fd
**
** @param fd fd associed with struct
**
** @return new struct
*/
s_getln		*getln_open(int fd);

#endif
