bin_PROGRAMS=42sh

42sh_SOURCES=	src/ast/ast.h				\
		src/ast/ast_and.c			\
		src/ast/ast_bang.c			\
		src/ast/ast_case.c			\
		src/ast/ast_cmd.c			\
		src/ast/ast_destruct.c			\
		src/ast/ast_for.c			\
		src/ast/ast_funcdec.c			\
		src/ast/ast_if.c			\
		src/ast/ast_or.c			\
		src/ast/ast_pipe.c			\
		src/ast/ast_print.c			\
		src/ast/ast_red.c			\
		src/ast/ast_sep.c			\
		src/ast/ast_sepand.c			\
		src/ast/ast_subshell.c			\
		src/ast/ast_while.c			\
		src/builtin/builtin.h			\
		src/builtin/builtin.c			\
		src/builtin/builtin_exit.c		\
		src/common/basename.c			\
		src/common/common.h			\
		src/common/constant.h			\
		src/common/isdigitstr.c			\
		src/common/macro.h			\
		src/common/strmerge.c			\
		src/common/strvectoradd.c		\
		src/common/strvmerge.c			\
		src/common/strndup.c			\
		src/exec/exec.h				\
		src/exec/exec_and.c			\
		src/exec/exec_bang.c			\
		src/exec/exec_node.c			\
		src/exec/exec_or.c			\
		src/exec/exec_if.c			\
		src/exec/exec_red.c			\
		src/exec/exec_sep.c			\
		src/exec/exec_sepand.c			\
		src/exec/exec_while.c			\
		src/parser/alias.h			\
		src/parser/alias.c			\
		src/parser/getline.h			\
		src/parser/getline.c			\
		src/parser/parser.h			\
		src/parser/parser.c			\
		src/parser/lexer.c			\
		src/shell/getoptions.c			\
		src/shell/option.h			\
		src/shell/option.c			\
		src/shell/shell.h			\
		src/shell/shell_entry.c			\
		src/shell/shell_init.c			\
		src/shell/shell_destroy.c		\
		src/shell/prompt.c

CLEANFILES= *~ \#*\#

EXTRA_DIST = AUTHORS README TODO

.PHONY: tar doc re

tar: distcheck

re: clean all

doc:
	cd $(srcdir)/doc && $(MAKE) doc
