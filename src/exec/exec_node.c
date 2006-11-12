/*
** exec_node.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 14:51:09 2006 Seblu
** Last update Sun Nov 12 16:43:18 2006 Seblu
*/

#include "exec.h"

void		exec_node(s_ast_node *node)
{
  assert(node);
  switch (node->type) {
  case T_SEP: break;
  case T_SEPAND: break;
  case T_CMD: break;
  case T_RED: exec_red(&node->body.child_red); break;
  case T_PIPE: break;
  case T_AND: exec_and(&node->body.child_and); break;
  case T_OR: exec_or(&node->body.child_or); break;
  case T_IF: exec_if(&node->body.child_if); break;
  case T_WHILE: exec_while(&node->body.child_while); break;
  case T_BANG: exec_bang(&node->body.child_bang); break;
  case T_SUBSHELL: break;
  case T_FUNCDEC: break;
  case T_CASE: break;
  default: assert(0);
  }
}
