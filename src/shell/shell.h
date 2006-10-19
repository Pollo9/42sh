/*
** shell.h for 42sh in /home/seblu/devel/c/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 16 20:03:53 2006 Seblu
** Last update Tue Oct 17 09:38:57 2006 seblu
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <errno.h>
# include <stdlib.h>
# include "../common/constant.h"
# include "../parser/alias.h"
# include "option.h"

typedef struct shell
{
/*   struct s_var		*vars; */
/*   struct s_func		*funcs; */
/*   struct s_history		*history; */
  s_aliases		*aliases;
  s_options		*options;
  char			*name;
  int			status;
} s_shell;

s_shell			*shell_init(const char *argv0);
void			shell_destroy(s_shell *sh);

const char		*get_prompt(e_prompt pty);

/*!
** Show a prompt on stderr is current shell is a plug on a tty
**
** @param pty prompt type (PS1, PS2, PS4)
*/
void			show_prompt(e_prompt pty);

extern s_shell		*shell;

#endif /* !SHELL_H_ */
