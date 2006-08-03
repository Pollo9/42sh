/*
** shell.h for 42sh in /home/seblu/devel/c/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 16 20:03:53 2006 Seblu
** Last update Thu Aug  3 07:01:26 2006 Seblu
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <errno.h>
# include <stdlib.h>
# include "../opt/opt.h"

static const int ERROR_PARSE = 258;
static const int ERROR_FORK = 128;
static const int ERROR_REDIR = 1;

typedef enum e_prompt_type {
  TYPE_PS1 = 1,
  TYPE_PS2 = 2,
  TYPE_PS4 = 4
} te_prompt_type;

typedef struct s_shell
{
/*   struct s_var		*vars; */
/*   struct s_func		*funcs; */
/*   struct s_history	*history; */
  ts_opt		*opt;
  char			*name;
  int			status;
} ts_shell;

ts_shell		*shell_init(const char *argv0);
void			shell_destroy(ts_shell *sh);

const char		*get_prompt(te_prompt_type pty);

ts_shell		*shell;

#endif /* !SHELL_H_ */
