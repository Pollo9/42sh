#SUBDIRS=
bin_PROGRAMS=42sh

#42sh_LDADD  = parser/libparse.a ../check/leaktrack/libmem.a evalexpr/libevalexpr.a


42sh_SOURCES=	ast/ast.h			\
		common/common.h			\
		common/macro.h			\
		common/strmerge.c		\
		common/strvmerge.c		\
		lexer/lexer.h			\
		opt/opt.h			\
		opt/opt.c			\
		opt/opt_init.c			\
		opt/opt_parser.c		\
		parser/parser.h			\
		parser/parser.c			\
		readline/readline.h		\
		readline/readline.c		\
		readline/getln.c		\
		shell/shell.h			\
		shell/shell_entry.c		\
		shell/shell_init.c		\
		shell/shell_destroy.c		\
		shell/shell_prompt.c

CLEANFILES= *~ '\#*'
