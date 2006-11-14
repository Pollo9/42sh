/*
** func.h for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 14:52:22 2006 seblu
** Last update Tue Nov 14 15:59:32 2006 seblu
*/

#ifndef FUNC_H_
# define FUNC_H_

# include <assert.h>
# include <stdlib.h>
# include "../ast/ast.h"

enum { FUNC_DEFAULT_SIZE = 5 };

typedef struct	func_item
{
  char		*name;
  s_ast_node	*body;
} s_func_item;

typedef struct	func
{
  s_func_item	*table;
  size_t	count;
  size_t	size;
} s_func;

/*!
** Init a function structure.
**
** @return a malloced func structure
*/
s_func		*func_init(void);

/* int		func_add(char *, struct s_ast *, struct s_func **); */
/* int		func_del(const char *, struct s_func **); */
/* int		func_exec(const char *, struct s_42sh *); */
/* void		func_clean(struct s_func **); */
/* struct s_ast 	*func_get(const char *, struct s_func **); */

#endif
