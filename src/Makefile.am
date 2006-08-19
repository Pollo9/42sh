#SUBDIRS=
bin_PROGRAMS=42sh

#42sh_LDADD  = parser/libparse.a ../check/leaktrack/libmem.a evalexpr/libevalexpr.a


42sh_SOURCES=	ast/ast.h			\
		ast/ast_and.c			\
		ast/ast_bang.c			\
		ast/ast_case.c			\
		ast/ast_cmd.c			\
		ast/ast_destruct.c		\
		ast/ast_for.c			\
		ast/ast_funcdec.c		\
		ast/ast_if.c			\
		ast/ast_or.c			\
		ast/ast_pipe.c			\
		ast/ast_sep.c			\
		ast/ast_sepand.c		\
		ast/ast_subshell.c		\
		ast/ast_until.c			\
		ast/ast_while.c			\
		common/common.h			\
		common/mem.h			\
		common/strmerge.c		\
		common/strvmerge.c		\
		common/strndup.c		\
		common/basename.c		\
		exec/exec.h			\
		exec/exec_ast.c			\
		opt/opt.h			\
		opt/opt.c			\
		opt/opt_init.c			\
		opt/opt_parser.c		\
		parser/parser.h			\
		parser/parser.c			\
		parser/lexer.c			\
		readline/readline.h		\
		readline/readline.c		\
		readline/getln.c		\
		shell/shell.h			\
		shell/shell_entry.c		\
		shell/shell_init.c		\
		shell/shell_destroy.c		\
		shell/shell_prompt.c

CLEANFILES= *~ '\#*'
