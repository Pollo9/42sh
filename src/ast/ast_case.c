/*
** ast_for.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Mon Aug 28 23:57:38 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_case_create(char *word)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_CASE;
  node->body.child_case.word = word;
  node->body.child_case.items = NULL;
  return node;
}

void		ast_case_add_item(s_ast_node	*node,
				  char		**pattern,
				  s_ast_node	*exec)
{
  s_case_item	*item;
  s_case_item	**this;

  if (node->type != T_CASE)
    return;
  secmalloc(item, sizeof (s_case_item));
  item->pattern = pattern;
  item->exec = exec;
  item->next = NULL;
  for (this = &node->body.child_case.items; *this; *this = (*this)->next)
    ; //do nothing
  *this = item;
}

void		ast_case_destruct(s_ast_node *node)
{
  s_case_item	*this, *buf;

  if (node->type != T_CASE)
    return;
  free(node->body.child_case.word);
  for (this = node->body.child_case.items; this; this = buf) {
    for (register int i = 0; this->pattern[i]; ++i)
      free(this->pattern[i]);
    free(this->pattern);
    ast_destruct(this->exec);
    buf = this->next;
    free(this);
  }
  free(node);
}
