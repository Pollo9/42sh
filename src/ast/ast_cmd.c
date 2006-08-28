/*
** ast_cmd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Fri Aug 18 22:13:51 2006 Seblu
** Last update Mon Aug 28 23:56:46 2006 Seblu
*/

#include "ast.h"

s_ast_node	*ast_cmd_create(void)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_CMD;
  node->body.child_cmd.argv = NULL;
  node->body.child_cmd.prefix = NULL;
  node->body.child_cmd.redirs = NULL;
  return node;
}

void		ast_cmd_add_redir(s_ast_node		*node,
				  e_redir_type		type,
				  int			fd,
				  char			*word)
{
  s_redir	*red;
  s_redir	**this;

  if (node->type != T_CMD)
    return;
  secmalloc(red, sizeof (s_redir));
  red->type = type;
  red->fd = fd;
  red->word = word;
  red->next = NULL;
  for (this = &node->body.child_cmd.redirs; *this; *this = (*this)->next)
    ; //do nothing
  *this = red;
}

void		ast_cmd_destruct(s_ast_node *node)
{
  s_redir	*this, *buf;

  if (node->type != T_CMD)
    return;
  for (register int i = 0; node->body.child_cmd.argv[i]; ++i)
    free(node->body.child_cmd.argv[i]);
  for (register int i = 0; node->body.child_cmd.prefix[i]; ++i)
    free(node->body.child_cmd.prefix[i]);
  free(node->body.child_cmd.argv);
  free(node->body.child_cmd.prefix);
  for (this = node->body.child_cmd.redirs; this; this = buf) {
    free(this->word);
    buf = this->next;
    free(this);
  }
  free(node);
}
