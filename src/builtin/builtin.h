/*
** builtin.h for 42sh in /home/seblu/svn/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Nov 12 16:46:24 2006 Seblu
** Last update Sun Nov 12 16:47:03 2006 Seblu
*/

#ifndef BUILTIN_H_
# define BUILTIN_H_

struct s_42sh;
struct s_cmd;

typedef int (*t_func_builtin)(char *argv[], struct s_42sh *sh);

int	is_a_builtin(const char *name, struct s_42sh *sh);
int	exec_builtin(struct s_cmd *cmd, struct s_42sh *sh);

/*
** Regular builtin
*/
int	builtin_cd(char *argv[], struct s_42sh *sh);
int	builtin_echo(char *argv[], struct s_42sh *sh);
int	builtin_shopt(char *argv[], struct s_42sh *sh);
int	builtin_exit(char *argv[], struct s_42sh *sh);
int	builtin_source(char *argv[], struct s_42sh *sh);
int	builtin_unset(char *argv[], struct s_42sh *sh);
int	builtin_export(char *argv[], struct s_42sh *sh);

/*
** Bonus builtin
*/
int	builtin_simpledot(char *argv[], struct s_42sh *sh);
int	builtin_doubledot(char *argv[], struct s_42sh *sh);
int	builtin_set(char *argv[], struct s_42sh *sh);
int	builtin_varlist(char *argv[], struct s_42sh *sh);
int	builtin_funclist(char *argv[], struct s_42sh *sh);
int	builtin_exec(char *argv[], struct s_42sh *sh);
int	builtin_history(char *argv[], struct s_42sh *sh);

#endif /* ! BUILTIN_H_ */
