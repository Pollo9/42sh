#SUBDIRS=
bin_PROGRAMS=42sh

#42sh_LDADD  = parser/libparse.a ../check/leaktrack/libmem.a evalexpr/libevalexpr.a


42sh_SOURCES=	ast/ast.h			\
		ast/ast_destruct.c		\
		ast/ast_sep.c			\
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
