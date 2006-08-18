/*
** ast_for.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Fri Aug 18 15:55:00 2006 Seblu
*/

#include "../common/mem.h"
#include "ast.h"

ts_ast_node	*ast_case_create(char *word)
{
  ts_ast_node	*node;

  secmalloc(node, sizeof (ts_ast_node));
  node->type = T_CASE;
  node->body.child_case.word = word;
  node->body.child_case.items = NULL;
  return node;
}

void		ast_case_add_item(ts_ast_node	*node,
				  char		**pattern,
				  ts_ast_node	*list)
{
/*   ts_case_item	*item; */

/*   secmalloc(item, sizeof (ts_case_item)); */
/*   item->pattern = pattern; */
/*   item->list = list; */
  node = node;
  pattern = pattern;
  list = list;
/*   for (ts_case_item **this = &node->items; */
/*        *this; */
/*        *this = (*this)->next) */
/*     ; //do nothing */
/*   *this = item; */
}

void		ast_case_destruct(ts_ast_node *node)
{
  node = node;
/*   ts_case_item	*this, *buf; */

/*   if (node->type != T_CASE) { */
/*     ast_destruct(node); */
/*     return; */
/*   } */
/*   free(node->body.child_case.word); */
/* /\*   for (ts_case_item *this = node->items; *\/ */
/* /\*        this; *\/ */
/* /\*        this = this->next) *\/ */
/* /\*   for (register int i = 0; node->body.child_case.items[i]; ++i) { *\/ */
/*     //fixme for multiple pattern */
/*     free(node->body.child_case.items[i].pattern); */
/*     ast_destruct(node->body.child_case.items[i].list); */
/*   } */
/*   free(node->body.child_case.items); */
/*   free(node); */
}
