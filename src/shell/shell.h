/*
** shell.h for 42sh in /home/seblu/devel/c/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 16 20:03:53 2006 Seblu
** Last update Sun Jul 30 03:42:43 2006 Seblu
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <errno.h>
# include <stdlib.h>
# include "../opt/opt.h"

static const int SCAN_ERROR = 1;
static const int PARSE_ERROR = 2;
static const int FORK_ERROR = 128;
static const int RED_ERROR = 1;


typedef struct
{
/*   struct s_ast		*ast; */
/*   struct s_var		*vars; */
/*   struct s_func		*funcs; */
/*   struct s_history	*history; */
  ts_opt		*opt;
  int			last_status;
} ts_shell;

ts_shell		*shell_init(void);
void			shell_destroy(ts_shell *sh);

ts_shell *shell;

#endif /* !SHELL_H_ */
