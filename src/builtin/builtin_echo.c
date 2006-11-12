/*
** builtin_echo.c for 42sh in /goinfre/seblu/builtins
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Tue Mar 14 20:57:07 2006 Seblu
** Last update Wed Apr 12 02:02:07 2006 Seblu
*/

#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "../main/42sh.h"
#include "../opt/opt.h"

#include "mem.h"

#define isoctale(x) (((x) >= '0' && (x) <= '7') ? 1 : 0)

static int builtin_echo_ext(const char *);
static void builtin_echo_ext2(const char **, int *);
static void print_hex(const char **);
static void print_oct(const char **);
static void getoption(char *argv[], int *argp, int *line, int *ext);
static int fisdigit(const int c);
static int fisxdigit(const int c);

/*!
** Echo show all element on her line
**
** @param argc number of argument given
** @param argv vector to argument
** @param shopt option structure of shell
**
** @return sucess status
*/
int		builtin_echo(char *argv[], struct s_42sh *sh)
{
  int		argp;
  int		ext = 0;
  int		line = 1;
  int		first;

  assert(argv && argv[0] && sh);
  ext = opt_isset("xpg_echo", sh->opt);
  for (getoption(argv, &argp, &line, &ext), first = argp; argv[argp]; ++argp)
  {
    if (first != argp)
      printf(" ");
    if (ext)
    {
      if (!builtin_echo_ext(argv[argp]))
	return fflush(stdout);
    }
    else
      printf("%s", argv[argp]);
  }
  if (line)
    printf("\n");
  return fflush(stdout);
}

/*!
** Retreinve command line option
**
** @param argv argument vector
** @param argp argument position
** @param line line flag
** @param ext extended flag
*/
static void	getoption(char *argv[], int *argp, int *line, int *ext)
{
  char		*carg;

  for (*argp = 1; (carg = argv[*argp]); ++*argp)
    if (*carg == '-')
      for (++carg; *carg; ++carg)
	if (*carg == 'e')
	  *ext = 1;
	else if (*carg == 'E')
	  *ext = 0;
	else if (*carg == 'n')
	  *line = 0;
	else
	  return;
    else
      return;
}

/*!
** Interpreter for special char
**
** @param msg
*/
static int	builtin_echo_ext(const char *msg)
{
  int		backed = 0;

  for (; *msg; ++msg)
    if (*msg == '\\' && !backed && (backed = 1))
      continue;
    else if (backed && *msg == 'a' && !(backed = 0))
      putchar('\a');
    else if (backed && *msg == 'b' && !(backed = 0))
      putchar('\b');
    else if (backed && *msg == 'c')
      return 0;
    else if (backed && *msg == 'e' && !(backed = 0))
      putchar(0x1b);
    else if (backed && *msg == 'f' && !(backed = 0))
      putchar('\f');
    else if (backed && *msg == 'n' && !(backed = 0))
      putchar('\n');
    else if (backed && *msg == 'r' && !(backed = 0))
      putchar('\r');
    else if (backed && *msg == 't' && !(backed = 0))
      putchar('\t');
    else
      builtin_echo_ext2(&msg, &backed);
  return 1;
}

/*!
** End of function builtin_echo_ext due to an stupid norme limitation.
**
** @param msg message to print
** @param backed if a backed char
*/
static void	builtin_echo_ext2(const char **msg, int *backed)
{
  if (*backed && **msg == '\\' && !(*backed = 0))
    putchar('\\');
  else if (*backed && **msg == 'v' && !(*backed = 0))
    putchar('\v');
  else if (*backed && fisdigit(**msg) && !(*backed = 0))
    print_oct(msg);
  else if (*backed && **msg == 'x' && !(*backed = 0) && (++*msg))
    print_hex(msg);
  else if (*backed && !(backed = 0))
    printf("\\%c", **msg);
  else
    putchar(**msg);
}

/*!
** Print hexa number on stdout a number
**
** @param msg message to print
** @param base base of the number
*/
static void	print_hex(const char **msg)
{
  char		buf[4];
  char		*end;
  long		n;
  unsigned char c;
  int		i;

  if (!fisxdigit(**msg))
    return;
  for (i = 0; fisxdigit(**msg) && i < 2; ++*msg, ++i)
    buf[i] = **msg;
  buf[i] = 0;
  --*msg;
  n = strtoul(buf, &end, 16);
  printf("%c", (c = n));
}

/*!
** Print oct number on stdout a number
**
** @param msg message to print
** @param base base of the number
*/
static void	print_oct(const char **msg)
{
  char		buf[5];
  char		*end;
  unsigned long	n;
  unsigned char c;
  int		i;
  int		max;

  if (!isoctale(**msg))
    return;
  max = (**msg == '0') ? 4 : 3;
  for (i = 0; isoctale(**msg) && i < max; ++*msg, ++i)
    buf[i] = **msg;
  buf[i] = 0;
  --*msg;
  n = strtoul(buf, &end, 8);
  printf("%c", (c = n));
}

/*!
** Function to say if c is a digit or not.
** It use macro isdigit, but due to epita coding style
** restriction about cast, it's impossible to call
** a macro wrote with int with char, because cast is forbidden
** and macro call, dont have the same right about parameter
** implicit cast (on netBSD)
**
** @param c character
**
** @return if \param c is a digit
*/
static int	fisdigit(const int c)
{
  return isdigit(c);
}

/*!
** Function to say if c is a digit or not.
** It use macro isdigit, but due to epita coding style
** restriction about cast, it's impossible to call
** a macro wrote with int with char, because cast is forbidden
** and macro call, dont have the same right about parameter
** implicit cast (on netBSD)
**
** @param c character
**
** @return if \param c is a hexa digit
*/
static int	fisxdigit(const int c)
{
  return isxdigit(c);
}
