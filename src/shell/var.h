/*
** var.h for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 13:54:14 2006 seblu
** Last update Wed Nov 15 10:36:09 2006 seblu
*/

#ifndef VAR_H_
# define VAR_H_

# include <stddef.h>

enum { VAR_DEFAULT_SIZE = 25 };

typedef struct	var_item
{
  char		*value;
  char		*name;
} s_var_item;

/*!
** The variable structure
**  - table: The table of variables
**  - count: The number of variables
**  - size: The size of the table (mem alloced)
*/
typedef struct	var
{
  s_var_item	*table;
  size_t	count;
  size_t	size;
} s_var;

/*!
** Create a malloced variable structure
**
** @return new variable structure
*/
s_var		*var_init(void);

/*!
** Get a variable in a var struct
**
** @param var variable struct
** @param name variable name
**
** @return value of the variable, NULL if not exist
*/
const char	*var_get(const s_var *var, const char *name);


void		var_set(s_var	*var,
			char	*name,
			char	*value,
			int	overwrite);

/*!
** Print all variables on standard output
**
** @param var var struct
*/
void		var_print(const s_var *var);


#endif /* ! VAR_H_ */
