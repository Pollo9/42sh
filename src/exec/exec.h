/*
** execution.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Mar 30 16:02:07 2006 Seblu
** Last update Thu Nov 16 16:06:41 2006 seblu
*/

#ifndef EXEC_H_
# define EXEC_H_

# include <assert.h>
# include "../ast/ast.h"
# include "../shell/shell.h"

# define DEBUG_EXEC 0

void		exec_node(s_ast_node *node);

void		exec_cmd(s_cmd_node *cmd);
void		exec_and(s_bin_node *node);
void		exec_or(s_bin_node *node);
void		exec_bang(s_bin_node *node);
void		exec_if(s_if_node *node);
void		exec_red(s_red_node *red);
void		exec_while(s_while_node *node);
void		exec_sep(s_bin_node *node);
void		exec_sepand(s_bin_node *node);
void		exec_funcdec(s_funcdec_node *node);

#endif
