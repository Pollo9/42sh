/*
** shell.h for 42sh in /home/seblu/devel/c/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 16 20:03:53 2006 Seblu
** Last update Sun Jul 16 20:18:23 2006 Seblu
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <errno.h>
# include <stdlib.h>

# define SCAN_ERROR 1
# define PARSE_ERROR 2
# define MEM_ERROR 42
# define FORK_ERROR 128
# define RED_ERROR 1

# define secmalloc(name, size) if (!(name = malloc(size))) exit(MEM_ERROR)
# define secrealloc(ret, name, size) if (!(ret = realloc(name, size))) exit(MEM_ERROR)
# define secstrdup(ret, str) if (!(ret = strdup(str))) exit(MEM_ERROR)



struct			s_shell
{
/*   struct s_ast		*ast; */
/*   struct s_var		*vars; */
/*   struct s_func		*funcs; */
/*   struct s_opt		*opt; */
/*   struct s_history	*history; */
  int			last_status;
};

struct s_shell		*shell_init(void);
void			shell_destroy(struct s_shell *sh);
char			*strmerges(int n, const char *s1, ...);

#endif /* !SHELL_H_ */
