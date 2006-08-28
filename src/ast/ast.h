/*
** ast.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:40:03 2006 Seblu
** Last update Tue Aug 29 00:35:06 2006 Seblu
*/

#ifndef AST_H_
# define AST_H_

# include "../common/macro.h"

typedef struct ast_node  s_ast_node;

/*
** If ast node
*/
typedef struct if_node
{
  s_ast_node		*cond;
  s_ast_node		*cond_true;
  s_ast_node		*cond_false;
} s_if_node;

/*
** For ast node
*/
typedef struct for_node
{
  char			*varname;
  char			**values;
  s_ast_node		*exec;
} s_for_node;

/*
** Case item (not an ast node)
*/
typedef struct case_item s_case_item;
struct case_item
{
  char			**pattern;
  s_ast_node		*exec;
  s_case_item		*next;
};

/*
** Case ast node
*/
typedef struct case_node
{
  char			*word;
  s_case_item		*items;
} s_case_node;

/*
** While ast node
*/
typedef struct while_node
{
  s_ast_node		*cond;
  s_ast_node		*exec;
} s_while_node;

/*
** Enumerate different type of redirection
*/
typedef enum redir_type
  {
    R_LESS,		/*  <   */
    R_LESSAND,		/*  <&  */
    R_GREAT,		/*  >   */
    R_GREATAND,		/*  >&  */
    R_DGREAT,		/*  >>  */
    R_LESSGREAT,	/*  <>  */
    R_CLOBBER,		/*  >|  */
    R_DLESS,		/*  <<  */
    R_DLESSDASH		/*  <<- */
  } e_redir_type;

/*
** Redirection ast node
*/
typedef struct redir s_redir;
struct redir
{
  e_redir_type		type;
  int			fd;
  char			*word;
  s_redir		*next;
};

/*
** Command ast node
*/
typedef struct cmd_node
{
  char			**argv;
  s_redir		*redirs;
  char			**prefix;
} s_cmd_node;

/*
** Binary ast node
** Generic node, it's a contener !
** T_PIPE, T_SEP* , T_AND, T_OR : binary operator
** T_BANG : unary operator but ts_bin_op with right pointer is always NULL
*/
typedef struct bin_node
{
  s_ast_node		*lhs;
  s_ast_node		*rhs;
} s_bin_node;

/*
** Funcdec node
*/
typedef struct funcdec_node
{
  char			*name;
  s_ast_node		*body;
} s_funcdec_node;

/*
** Enumerate all node type
*/
typedef enum node_type
  {
    T_IF,
    T_FOR,
    T_CASE,
    T_WHILE,
    T_UNTIL,
    T_CMD,
    T_AND,
    T_OR,
    T_SUBSHELL,
    T_FUNCDEC,
    T_BANG,
    T_PIPE,
    T_SEPAND,
    T_SEP,
  } e_node_type;

/*
** This is a type for a node item
*/
typedef union node_item
{
  s_if_node		child_if;
  s_for_node		child_for;
  s_case_node		child_case;
  s_while_node		child_while;
  s_while_node		child_until;
  s_cmd_node		child_cmd;
  s_bin_node		child_and;
  s_bin_node		child_or;
  s_bin_node		child_subshell;
  s_funcdec_node	child_funcdec;
  s_bin_node		child_bang;
  s_bin_node		child_pipe;
  s_bin_node		child_sep;
  s_bin_node		child_sepand;
} u_node_item;

/*
** Generic ast node type
*/
struct ast_node
{
  e_node_type		type;
  u_node_item		body;
};

/*!
** Destroy node and all its childs
**
** @param ast mother node to destroy
**
*/
void		ast_destruct(s_ast_node *ast);

/*!
** Create an if ast node
**
** @param cond if condition
** @param cond_true tree if condition is true
** @param cond_false tree if condition is false
**
** @return the node
*/
s_ast_node	*ast_if_create(s_ast_node *cond,
			       s_ast_node *cond_true,
			       s_ast_node *cond_false);

/*!
** Destruct an if ast node
**
** @param node node to destroy
*/
void		ast_if_destruct(s_ast_node *node);

/*!
** Create a for ast node
**
** @param varname variable name
** @param values word list that var @value varname will take.
** @warning values is a NULL termined list of string
** @param exec tree to execute with @value varname correctly set
**
** @return the node
*/
s_ast_node	*ast_for_create(char		*varname,
				char		**values,
				s_ast_node	*exec);

/*!
** Destruct a for ast node
**
** @param node node to destroy
*/
void		ast_for_destruct(s_ast_node *node);

/*!
** Create a case ast node
**
** @param word reference word
**
** @return the node
*/
s_ast_node	*ast_case_create(char *word);

/*!
** Add a case item into a case node. An item is counpound of a set of word
** which match with reference word an case node and the corresponding
**
** @param node node where item will be added
** @param pattern list of word that can match to reference
** @param exec exec corresponding with match
*/
void		ast_case_add_item(s_ast_node	*node,
				  char		**pattern,
				  s_ast_node	*exec);

/*!
** Destruct a case ast node
**
** @param node node to destroy
*/
void		ast_case_destruct(s_ast_node *node);

/*!
** Create a while ast node
**
** @param cond poursuit condition
** @param exec tree to execute if cond is true
**
** @return the node
*/
s_ast_node	*ast_while_create(s_ast_node *cond, s_ast_node *exec);

/*!
** Destruct a while ast node
**
** @param node node to destroy
*/
void		ast_while_destruct(s_ast_node *node);

/*!
** Create a until ast node
**
** @param cond poursuit condition
** @param exec tree to execute if cond is false
**
** @return the node
*/
s_ast_node	*ast_until_create(s_ast_node *cond, s_ast_node *exec);

/*!
** Destruct a until ast node
**
** @param node node to destroy
*/
void		ast_until_destruct(s_ast_node *node);

/*!
** Create a cmd ast node
**
** @return the node
*/
s_ast_node	*ast_cmd_create(void);

/*!
** Add a redirection to a cmd node
**
** @param node node where add
** @param type type of redirection
** @param fd fd parameter of redirection
** @param word file or word parameter of redirection
*/
void		ast_cmd_add_redir(s_ast_node		*node,
				  e_redir_type		type,
				  int			fd,
				  char			*word);

/*!
** Destruct a cmd node
**
** @param node node to destroy
*/
void		ast_cmd_destruct(s_ast_node *node);

/*!
** Create an and (&&) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_and_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Destruct an and (&&) node
**
** @param node node to destroy
*/
void		ast_and_destruct(s_ast_node *node);

/*!
** Create an or (||) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_or_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Destruct an or (||) node
**
** @param node node to destroy
*/
void		ast_or_destruct(s_ast_node *node);

/*!
** Create a subshell ($()) ast node
**
** @param child subshell tree
**
** @return the node
*/
s_ast_node	*ast_subshell_create(s_ast_node *child);

/*!
** Destruct a subshell ($()) node
**
** @param node node to destroy
*/
void		ast_subshell_destruct(s_ast_node *node);

/*!
** Create a funcdec (function declaration) ast node
**
** @param name function name
** @param body function body
**
** @return the node
*/
s_ast_node	*ast_fundec_create(char *name, s_ast_node *body);

/*!
** Destruct a funcdec ast node
**
** @param node node to destroy
*/
void		ast_funcdec_destruct(s_ast_node *node);

/*!
** Create a bang (!) ast node
**
** @param child under bang tree
**
** @return the node
*/
s_ast_node	*ast_bang_create(s_ast_node *child);

/*!
** Destruct a bang (!) node
**
** @param node node to destroy
*/
void		ast_bang_destruct(s_ast_node *node);

/*!
** Create a pipe (|) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_pipe_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Destruct a pipe (|) node
**
** @param node node to destroy
*/
void		ast_pipe_destruct(s_ast_node *node);

/*!
** Create a separtor (;) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_sep_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Destruct a sep (;) node
**
** @param node node to destroy
*/
void		ast_sep_destruct(s_ast_node *node);

/*!
** Create a sepand (&) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
s_ast_node	*ast_sepand_create(s_ast_node *lhs, s_ast_node *rhs);

/*!
** Destruct a sepand (&) node
**
** @param node node to destroy
*/
void		ast_sepand_destruct(s_ast_node *node);

#endif /* !AST_H_ */
