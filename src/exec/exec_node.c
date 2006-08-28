/*
** exec_node.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 14:51:09 2006 Seblu
** Last update Tue Aug 29 00:19:35 2006 Seblu
*/

#include "exec.h"

/*!
** Execute a node of ast by calling the good function
**
** @param node node to execute
** @param sh shell struct
*/
void		exec_node(s_ast_node *node)
{
  node = node;
}

/* { */
/*   if (node == NULL) */
/*     return; */
/*   else if (node->type == T_CMD) */
/*     exec_cmd(&node->data.node_cmd, sh); */
/*   else if (node->type == T_PIPE) */
/*     exec_pipe(&node->data.node_op, sh); */
/*   else if (node->type == T_LINE) */
/*     exec_line(&node->data.node_op, sh); */
/*   else if (node->type == T_SEP_AND) */
/*     exec_sepand(&node->data.node_op, sh); */
/*   else if (node->type == T_SEP_SEMICOMMA) */
/*     exec_sepsemicolon(&node->data.node_op, sh); */
/*   else if (node->type == T_IF) */
/*     exec_if(&node->data.node_if, sh); */
/*   else if (node->type == T_FOR) */
/*     exec_for(&node->data.node_for, sh); */
/*   else if (node->type == T_AND) */
/*     exec_and(&node->data.node_op, sh); */
/*   else if (node->type == T_OR) */
/*     exec_or(&node->data.node_op, sh); */
/*   else if (node->type == T_WHILE) */
/*     exec_while(&node->data.node_while, sh); */
/*   else if (node->type == T_UNTIL) */
/*     exec_until(&node->data.node_while, sh); */
/*   else if (node->type == T_BANG) */
/*     exec_bang(&node->data.node_op, sh); */
/*   else if (node->type == T_SUBSHELL) */
/*     exec_subshell(&node->data.node_subshell, sh); */
/*   else */
/*     assert(0); */
/* } */
