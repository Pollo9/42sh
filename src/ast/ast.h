/*
** ast.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:40:03 2006 Seblu
** Last update Fri Aug 18 15:56:25 2006 Seblu
*/

#ifndef AST_H_
# define AST_H_

# include <sys/types.h>
# include <errno.h>
# include <stdlib.h>
# include <assert.h>

typedef struct s_ast  ts_ast_node;

/*
** If ast node
*/
typedef struct s_if_node
{
  ts_ast_node		*cond;
  ts_ast_node		*cond_true;
  ts_ast_node		*cond_false;
} ts_if_node;

/*
** For ast node
*/
typedef struct s_for_node
{
  char			*varname;
  char			**values;
  ts_ast_node		*exec;
} ts_for_node;

/*
** Case item (not an ast node)
*/
typedef struct s_case_item ts_case_item;
struct s_case_item
{
  char			**pattern;
  ts_ast_node		*list;
  ts_case_item		*next;
};

/*
** Case ast node
*/
typedef struct s_case_node
{
  char			*word;
  ts_case_item		*items;
} ts_case_node;

/*
** While ast node
*/
typedef struct s_while_node
{
  ts_ast_node		*cond;
  ts_ast_node		*exec;
} ts_while_node;

/*
** Enumerate different type of redirection
*/
typedef enum e_redir_type
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
  } te_redir_type;

/*
** Redirection ast node
*/
typedef struct s_redir_node
{
  te_redir_type		type;
  int			fd;
  char			*string;
} ts_redir_node;

/*
** Command ast node
*/
typedef struct s_cmd_node
{
  char			**argv;
  ts_redir_node		**redirs;
  char			**prefix;
} ts_cmd_node;

/*
** Binary ast node
** Generic type, it's a contener !
** T_PIPE, T_SEP_* , T_AND, T_OR : binary operator
** T_BANG : unary operator but ts_bin_op with right pointer is always NULL
*/
typedef struct s_bin_node
{
  ts_ast_node		*lhs;
  ts_ast_node		*rhs;
} ts_bin_node;

/*
** Funcdec node
*/
typedef struct s_funcdec_node
{
  char			*name;
  ts_ast_node		*body;
} ts_funcdec_node;

/*
** Enumerate all node type
*/
typedef enum e_node_type
  {
    T_IF,
    T_FOR,
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
    T_CASE,
  } te_node_type;

/*
** This is a type for a node item
*/
typedef union u_node_item
{
  ts_if_node		child_if;
  ts_for_node		child_for;
  ts_case_node		child_case; //todo
  ts_while_node		child_while;
  ts_while_node		child_until;
  ts_cmd_node		child_cmd; //todo
  ts_bin_node		child_and;
  ts_bin_node		child_or;
  ts_bin_node		child_subshell;
  ts_funcdec_node	child_funcdec;
  ts_bin_node		child_bang;
  ts_bin_node		child_pipe;
  ts_bin_node		child_sep;
  ts_bin_node		child_sepand;
} tu_node_item;

/*
** Generic ast node type
*/
struct s_ast
{
  te_node_type		type;
  tu_node_item		body;
};

/*!
** Destroy node and all its childs
**
** @param ast mother node to destroy
**
*/
void		ast_destruct(ts_ast_node *ast);

/*!
** Create an if ast node
**
** @param cond if condition
** @param cond_true tree if condition is true
** @param cond_false tree if condition is false
**
** @return the node
*/
ts_ast_node	*ast_create_if(ts_ast_node *cond,
			       ts_ast_node *cond_true,
			       ts_ast_node *cond_false);

/*!
** Destruct an if ast node
**
** @param node node to destroy
*/
void		ast_destruct_if(ts_ast_node *node);

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
ts_ast_node	*ast_create_for(char		*varname,
				char		**values, 
				ts_ast_node	*exec);

/*!
** Destruct a for ast node
**
** @param node node to destroy
*/
void		ast_destruct_for(ts_ast_node *node);

/*!
** Create a while ast node
**
** @param cond poursuit condition
** @param exec tree to execute if cond is true
**
** @return the node
*/
ts_ast_node	*ast_create_while(ts_ast_node *cond, ts_ast_node *exec);

/*!
** Destruct a while ast node
**
** @param node node to destroy
*/
void		ast_destruct_while(ts_ast_node *node);

/*!
** Create a until ast node
**
** @param cond poursuit condition
** @param exec tree to execute if cond is false
**
** @return the node
*/
ts_ast_node	*ast_create_until(ts_ast_node *cond, ts_ast_node *exec);

/*!
** Destruct a until ast node
**
** @param node node to destroy
*/
void		ast_destruct_until(ts_ast_node *node);

/*!
** Create an and (&&) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
ts_ast_node	*ast_create_and(ts_ast_node *lhs, ts_ast_node *rhs);

/*!
** Destruct an and (&&) node
**
** @param node node to destroy
*/
void		ast_destruct_and(ts_ast_node *node);

/*!
** Create an or (||) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
ts_ast_node	*ast_create_or(ts_ast_node *lhs, ts_ast_node *rhs);

/*!
** Destruct an or (||) node
**
** @param node node to destroy
*/
void		ast_destruct_or(ts_ast_node *node);

/*!
** Create a subshell ($()) ast node
**
** @param child subshell tree
**
** @return the node
*/
ts_ast_node	*ast_create_subshell(ts_ast_node *child);

/*!
** Destruct a subshell ($()) node
**
** @param node node to destroy
*/
void		ast_destruct_subshell(ts_ast_node *node);

/*!
** Create a funcdec (function declaration) ast node
**
** @param name function name
** @param body function body
**
** @return the node
*/
ts_ast_node	*ast_create_funcdec(char *name, ts_ast_node *body);

/*!
** Destruct a funcdec ast node
**
** @param node node to destroy
*/
void		ast_destruct_funcdec(ts_ast_node *node);

/*!
** Create a bang (!) ast node
**
** @param child under bang tree
**
** @return the node
*/
ts_ast_node	*ast_create_bang(ts_ast_node *child);

/*!
** Destruct a bang (!) node
**
** @param node node to destroy
*/
void		ast_destruct_bang(ts_ast_node *node);

/*!
** Create a pipe (|) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
ts_ast_node	*ast_create_pipe(ts_ast_node *lhs, ts_ast_node *rhs);

/*!
** Destruct a pipe (|) node
**
** @param node node to destroy
*/
void		ast_destruct_pipe(ts_ast_node *node);

/*!
** Create a separtor (;) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
ts_ast_node	*ast_create_sep(ts_ast_node *lhs, ts_ast_node *rhs);

/*!
** Destruct a sep (;) node
**
** @param node node to destroy
*/
void		ast_destruct_sep(ts_ast_node *node);

/*!
** Create a sepand (&) ast node
**
** @param lhs left child
** @param rhs right child
**
** @return the node
*/
ts_ast_node	*ast_create_sepand(ts_ast_node *lhs, ts_ast_node *rhs);

/*!
** Destruct a sepand (&) node
**
** @param node node to destroy
*/
void		ast_destruct_sep(ts_ast_node *node);

#endif /* !AST_H_ */
