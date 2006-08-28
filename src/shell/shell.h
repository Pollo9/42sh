/*
** shell.h for 42sh in /home/seblu/devel/c/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 16 20:03:53 2006 Seblu
** Last update Fri Aug 25 07:45:07 2006 Seblu
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <errno.h>
# include <stdlib.h>
# include "../common/constant.h"
# include "../alias/alias.h"
# include "../option/option.h"

typedef struct s_shell
{
/*   struct s_var		*vars; */
/*   struct s_func		*funcs; */
/*   struct s_history		*history; */
  ts_aliases		*aliases;
  ts_options		*options;
  char			*name;
  int			status;
} ts_shell;

ts_shell		*shell_init(const char *argv0);
void			shell_destroy(ts_shell *sh);

const char		*get_prompt(te_prompt pty);

/*!
** Show a prompt on stderr is current shell is a plug on a tty
**
** @param pty prompt type (PS1, PS2, PS4)
*/
void			show_prompt(te_prompt pty);

extern ts_shell		*shell;

#endif /* !SHELL_H_ */
