/*
** execution.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Mar 30 16:02:07 2006 Seblu
** Last update Thu Aug  3 01:20:18 2006 Seblu
*/

#ifndef EXEC_H_
# define EXEC_H_

# include <assert.h>
# include <stdio.h>
# include "../ast/ast.h"

void exec_ast(ts_ast_node *node);

/* void exec_node(struct s_ast *node, struct s_42sh *sh); */
/* void exec_list(struct s_list *node, struct s_42sh *sh); */
/* void exec_if(struct s_if *node, struct s_42sh *sh); */
/* void exec_while(struct s_while *node, struct s_42sh *sh); */
/* void exec_until(struct s_while *node, struct s_42sh *sh); */
/* void exec_and(struct s_op *node, struct s_42sh *sh); */
/* void exec_or(struct s_op *node, struct s_42sh *sh); */
/* void exec_cmd(struct s_cmd *node, struct s_42sh *sh); */
/* void exec_pipe(struct s_op *node, struct s_42sh *sh); */
/* void exec_bang(struct s_op *node, struct s_42sh *sh); */
/* void exec_sepand(struct s_op *node, struct s_42sh *sh); */
/* void exec_sepsemicolon(struct s_op *node, struct s_42sh *sh); */
/* void exec_line(struct s_op *node, struct s_42sh *sh); */
/* void exec_subshell(struct s_subshell *node, struct s_42sh *sh); */

/* /\* FIXME *\/ */

/* void exec_for(struct s_for *node, struct s_42sh *sh); */
/* void exec_case(struct s_case *node, struct s_42sh *sh); */
/* void exec_funcdec(struct s_funcdec *node, struct s_42sh *sh); */

#endif
