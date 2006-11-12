/*
** execution.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Mar 30 16:02:07 2006 Seblu
** Last update Sun Nov 12 16:41:42 2006 Seblu
*/

#ifndef EXEC_H_
# define EXEC_H_

# include <assert.h>
# include <stdio.h>
# include "../ast/ast.h"
# include "../shell/shell.h"

void		exec_node(s_ast_node *node);
void		exec_and(s_bin_node *node);
void		exec_or(s_bin_node *node);
void		exec_bang(s_bin_node *node);
void		exec_if(s_if_node *node);
void		exec_red(s_red_node *red);
void		exec_while(s_while_node *node);

/* FIXME */

/* void exec_for(struct s_for *node, struct s_42sh *sh); */
/* void exec_case(struct s_case *node, struct s_42sh *sh); */
/* void exec_funcdec(struct s_funcdec *node, struct s_42sh *sh); */

#endif
