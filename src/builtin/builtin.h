/*
** builtin.h for 42sh in /home/seblu/svn/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Nov 12 16:46:24 2006 Seblu
** Last update Sun Nov 12 19:55:03 2006 Seblu
*/

#ifndef BUILTIN_H_
# define BUILTIN_H_

# include <assert.h>
# include "../ast/ast.h"
# include "../shell/shell.h"

int	is_a_builtin(const char *name);
int	exec_builtin(s_cmd_node *cmd);

int	builtin_cd(char *argv[]);
int	builtin_echo(char *argv[]);
int	builtin_shopt(char *argv[]);
int	builtin_exit(char *argv[]);
int	builtin_source(char *argv[]);
int	builtin_unset(char *argv[]);
int	builtin_export(char *argv[]);

/*
** Bonus builtin
*/
/* int	builtin_simpledot(char *argv[], struct s_42sh *sh); */
/* int	builtin_doubledot(char *argv[], struct s_42sh *sh); */
/* int	builtin_set(char *argv[], struct s_42sh *sh); */
/* int	builtin_varlist(char *argv[], struct s_42sh *sh); */
/* int	builtin_funclist(char *argv[], struct s_42sh *sh); */
/* int	builtin_exec(char *argv[], struct s_42sh *sh); */
/* int	builtin_history(char *argv[], struct s_42sh *sh); */

#endif /* ! BUILTIN_H_ */
