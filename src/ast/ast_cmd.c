/*
** ast_cmd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Fri Aug 18 22:13:51 2006 Seblu
** Last update Mon Sep 25 04:19:18 2006 Seblu
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

void		ast_cmd_add_prefix(s_ast_node *node, char *assignment_word)
{
  if (node->type != T_CMD)
    return;
  size_t	size = 0;
  if (node->body.child_cmd.prefix)
    while (node->body.child_cmd.prefix[size])
      ++size;
  secrealloc(node->body.child_cmd.prefix, node->body.child_cmd.prefix,
	     (++size + 1) * sizeof (char *));
  node->body.child_cmd.prefix[size - 1] = assignment_word;
  node->body.child_cmd.prefix[size] = NULL;
}

void		ast_cmd_add_argv(s_ast_node *node, char *argv)
{
  if (node->type != T_CMD)
    return;
  size_t	size = 0;
  if (node->body.child_cmd.argv)
    while (node->body.child_cmd.argv[size])
      ++size;
  secrealloc(node->body.child_cmd.argv, node->body.child_cmd.argv,
	     (++size + 1) * sizeof (char *));
  node->body.child_cmd.argv[size - 1] = argv;
  node->body.child_cmd.argv[size] = NULL;
}

void		ast_cmd_print(s_ast_node *node, FILE *fs, unsigned int *node_id)
{
  unsigned	cur_id = *node_id;

  if (node->type != T_CMD)
    return;
  fprintf(fs, "%u [label = \"Command\"];\n", *node_id);
  //prefix
  char **prefix = node->body.child_cmd.prefix;
  if (prefix && prefix[0]) {
    ++*node_id;
    fprintf(fs, "%u [label = \"", *node_id);
    for (int i = 0; prefix && prefix[i]; ++i) {
      fprintf(fs, "prefix[%d]:", i);
      size_t last = 0, p = 0;
      for (; prefix[i][p]; ++p)
	if (prefix[i][p] == '"')
	  fprintf(fs, "%.*s\\", p - last, prefix[i] + last), last = p;
      fprintf(fs, "%*s", p - last, prefix[i] + last), last = p;
      fprintf(fs, "\\n");
    }
    fprintf(fs, "\"];\n");
    fprintf(fs, "%u -> %u\n", cur_id, *node_id);
  }
  //arguments
  char **argv = node->body.child_cmd.argv;
  if (argv && argv[0]) {
    ++*node_id;
    fprintf(fs, "%u [label = \"", *node_id);
    for (int i = 0; argv && argv[i]; ++i) {
      fprintf(fs, "argv[%d]:", i);
      size_t last = 0, p = 0;
      for (; argv[i][p]; ++p)
	if (argv[i][p] == '"')
	  fprintf(fs, "%.*s\\", p - last, argv[i] + last), last = p;
      fprintf(fs, "%*s", p - last, argv[i] + last), last = p;
      fprintf(fs, "\\n");
    }
    fprintf(fs, "\"];\n");
    fprintf(fs, "%u -> %u\n", cur_id, *node_id);
  }
  //redirs
  if (node->body.child_cmd.redirs) {
    int i = 0;
    ++*node_id;
    fprintf(fs, "%u [label = \"", *node_id);
    for (s_redir *this = node->body.child_cmd.redirs; this; this = this->next, ++i) {
      fprintf(fs, "redirs[%d]: fd=%d, type=%d, word=", i, this->fd, this->type);
      size_t last = 0, p = 0;
      for (; this->word[p]; ++p)
	if (this->word[p] == '"')
	  fprintf(fs, "%.*s\\", p - last, this->word + last), last = p;
      fprintf(fs, "%*s", p - last, this->word + last), last = p;
      fprintf(fs, "\\n");
    }
    fprintf(fs, "\"];\n");
    fprintf(fs, "%u -> %u\n", cur_id, *node_id);
  }
}

void		ast_cmd_destruct(s_ast_node *node)
{
  s_redir	*this, *buf;

  if (node->type != T_CMD)
    return;
  if (node->body.child_cmd.argv) {
    for (register int i = 0; node->body.child_cmd.argv[i]; ++i)
      free(node->body.child_cmd.argv[i]);
    free(node->body.child_cmd.argv);
  }
  if (node->body.child_cmd.prefix) {
    for (register int i = 0; node->body.child_cmd.prefix[i]; ++i)
      free(node->body.child_cmd.prefix[i]);
    free(node->body.child_cmd.prefix);
  }
  for (this = node->body.child_cmd.redirs; this; this = buf) {
    free(this->word);
    buf = this->next;
    free(this);
  }
  free(node);
}
