/*
** ast.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:40:03 2006 Seblu
** Last update Wed Aug  2 17:54:14 2006 Seblu
*/

#ifndef AST_H_
# define AST_H_

# include <sys/types.h>
# include <errno.h>
# include <stdlib.h>
# include <assert.h>

struct s_ast;
typedef struct s_ast  ts_ast_node;

/*
** If ast node
*/
typedef struct
{
  ts_ast_node		*cond;
  ts_ast_node		*cond_true;
  ts_ast_node		*cond_false;
} ts_if_node;

/*
** For ast node
*/
typedef struct
{
  char			*name;
  ts_ast_node		*values;
  ts_ast_node		*exec;
} ts_for_node;

/*
** Case ast node
*/
typedef struct
{
  char			*word;
  //FIXME
  struct s_case_item	**items;
} ts_case_node;

/*
** While ast node
*/
typedef struct
{
  ts_ast_node		*cond;
  ts_ast_node		*exec;
} ts_while_node;

/*
** Enumerate different type of redirection
*/
typedef enum
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
typedef struct
{
  te_redir_type		type;
  int			fd;
  char			*string;
} ts_redir_node;

/*
** Command ast node
*/
typedef struct
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
typedef struct
{
  ts_ast_node		*left;
  ts_ast_node		*right;
} ts_bin_node;

/*
** Subshell ast node
*/
typedef struct
{
  ts_ast_node		*head;
} ts_subshell_node;

/*
** Funcdec node
*/
typedef struct
{
  char			*name;
  ts_ast_node		*body;
} ts_funcdec_node;

/*
** Enumerate all node type
*/
typedef enum
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
    T_SEP_AND,
    T_SEP_SEMICOMMA,
    T_CASE,

    T_CASE_LIST,
    T_LIST,
    T_CL,
    T_CASE_ITEM,
    T_ITEM,
    T_LINE,
    T_WL,
    T_END
  } te_node_type;

/*
** This is a type for a node item
*/
typedef union
{
  ts_if_node		node_if;
  ts_for_node		node_for;
  ts_case_node		node_case;
  ts_while_node		node_while;
  ts_while_node		node_until;
  ts_cmd_node		node_cmd;
  ts_bin_node		node_and;
  ts_bin_node		node_or;
  ts_subshell_node	node_subshell;
  ts_funcdec_node	node_funcdec;
  ts_bin_node		node_bang;
  ts_bin_node		node_pipe;
  ts_bin_node		node_sep_semicomma;
  ts_bin_node		node_sep_and;


/*   ts_case_item	node_case_item; */
/*   ts_wordlist	node_wl; */
/*   ts_case_list	node_case_list; */
} tu_node_item;

/*
** Generic ast node type
*/
struct s_ast
{
  te_node_type		type;
  tu_node_item		node;
};





/* /\** */
/* ** structure wordlist ex : for var in wordlist do */
/* ** word : word */
/* ** next : next word finally Sexy NULL */
/* *\/ */
/* struct			s_wordlist */
/* { */
/*   char			*word; */
/*   struct s_wordlist	*next; */
/* }; */

/* struct			s_case_item */
/* { */
/*   char			**patterns; */
/*   int			allocated; */
/*   int			pos; */
/* }; */

/* struct			s_item */
/* { */
/*   struct s_wordlist	*pl; */
/*   struct s_ast		*cmd_list; */
/* }; */



/* /\** */
/* ** temporary structure */
/* ** which contains prefix and */
/* ** suffix command informations */
/* ** argv word or assigment words terminated by NULL */
/* ** redirs redirection pointer */
/* ** pos position in argv array */
/* ** nb_arg_alloc positions allocated */
/* *\/ */
/* struct			s_cmd_opt */
/* { */
/*   char			**argv; */
/*   struct s_redir	*redirs; */
/*   int			pos; */
/*   int			nb_arg_alloc; */
/* }; */
/* /\** */
/* ** create temporary structure */
/* ** in order to get prefix and */
/* ** suffix informations */
/* *\/ */
/* struct s_cmd_opt	*tmp_create_cmdopt(struct s_cmd_opt    	*opt, */
/* 					   struct s_redir      	*redir, */
/* 					   char			*arg); */
/* /\** */
/* ** add redirection to temporary */
/* ** structure s_redir */
/* *\/ */
/* struct s_redir          *tmp_add_redir(struct s_redir *base, struct s_redir *nelt); */
/* /\** */
/* ** create temporary structure s_redir */
/* *\/ */
/* struct s_redir          *tmp_create_redir(enum e_redir      type, */
/* 					  char              *filename, */
/* 					  int               fd, */
/* 					  struct s_redir    *redir); */
/* /\* */
/* ** PLEASE NOTE */
/* ** Every time, any argument given so this functions must be on the heap, */
/* ** they are not copied. Don't forget to dup string, for function create_cmd, */
/* ** function add_redir and function create_for */
/* *\/ */

/* /\*! */
/* ** Create an and node */
/* ** */
/* ** @param lhs left hand side */
/* ** @param rhs right hand side */
/* ** */
/* ** @return new ast node */
/* *\/ */
/* struct s_ast		*ast_create_and(struct s_ast *lhs, struct s_ast *rhs); */
/* /\*! */
/* ** Create an or node */
/* ** */
/* ** @param lhs left hand side */
/* ** @param rhs right hand side */
/* ** */
/* ** @return new ast node */
/* *\/ */
/* struct s_ast		*ast_create_or(struct s_ast *lhs, struct s_ast *rhs); */
/* struct s_ast		*ast_create_case_clause(char		*word, */
/* 						struct s_ast	*case_list); */
/* struct s_ast		*ast_create_if(struct s_ast *cond, */
/* 				       struct s_ast *positive, */
/* 				       struct s_ast *negative); */
/* struct s_ast		*ast_create_funcdec(char *name, struct s_ast *body); */
/* struct s_ast		*ast_create_subshell(struct s_ast *cmd); */
/* struct s_ast		*ast_create_for(char		*varname, */
/* 					struct s_ast	*value, */
/* 					struct s_ast	*exec); */
/* /\** */
/* ** create cmd node */
/* *\/ */
/* struct s_ast		*ast_create_cmd(struct s_cmd_opt     	*prefix, */
/* 					 char		       	*cmd, */
/* 					 struct s_cmd_opt     	*suffix); */

/* /\* struct s_ast		*ast_create_list(struct s_ast **item); *\/ */
/* struct s_ast		*ast_create_until(struct s_ast *cond, */
/* 					  struct s_ast *exec); */
/* struct s_ast		*ast_create_while(struct s_ast *cond, */
/* 					  struct s_ast *exec); */
/* /\** */
/* ** create pipe node */
/* *\/ */
/* struct s_ast		*ast_create_pipe(struct s_ast		*cmd1, */
/* 					 struct s_ast		*cmd2); */
/* /\** */
/* ** create shell structure */
/* *\/ */
/* struct s_42sh		*ast_create_ast(struct s_42sh	*shell, */
/* 					struct s_ast   	*ast); */

/* struct s_ast		*ast_create_patterns(char *word, struct s_ast *case_item); */
/* struct s_ast		*ast_create_case_list(struct s_ast	*item, */
/* 					      struct s_ast	*case_list); */
/* struct s_ast      	*ast_create_wordlist(struct s_ast	*wl, */
/* 					     char		*w); */
/* /\** */
/* ** change ast type : PIPE -> BANG_PIPE and CMD -> BANG_CMD */
/* *\/ */
/* struct s_ast		*ast_create_bang(struct s_ast *ast); */
/* struct s_ast		*ast_create_sep_op(struct s_ast		*cmd1, */
/* 					   enum e_type		sep_op, */
/* 					   struct s_ast		*cmd2); */

/* /\* void			ast_destruct_list(struct s_ast *node); *\/ */
/* void			ast_destruct_cmd(struct s_ast *node); */
/* void			ast_destruct_pipe(struct s_ast *node); */
/* void			ast_destruct_redir(struct s_redir *red); */

/* /\* void			ast_print(struct s_ast *ast); *\/ */
/* void			ast_destruct_sep_op(struct s_ast *node); */
/* void			ast_destruct_for(struct s_ast *node); */
/* void			ast_destruct_until(struct s_ast *node); */
/* void			ast_destruct_while(struct s_ast *node); */
/* void			ast_destruct_if(struct s_ast *node); */
/* void			ast_destruct(struct s_ast *node); */
/* void			ast_destruct_bang(struct s_ast *node); */
/* void			ast_destruct_wordlist(struct s_ast *node); */
/* void			ast_destruct_case(struct s_ast *node); */
/* /\*! */
/* ** Destruct an and node */
/* ** */
/* ** @param node head of node to destruct */
/* *\/ */
/* void			ast_destruct_and(struct s_ast *node); */
/* /\*! */
/* ** Destruct an or node */
/* ** */
/* ** @param node head of node to destruct */
/* *\/ */
/* void			ast_destruct_or(struct s_ast *node); */
/* void			ast_destruct_subshell(struct s_ast *node); */

#endif /* !AST_H_ */
