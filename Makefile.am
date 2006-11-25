bin_PROGRAMS=	42sh

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
		src/builtin/builtin_alias.c		\
		src/builtin/builtin_cd.c		\
		src/builtin/builtin_echo.c		\
		src/builtin/builtin_exec.c		\
		src/builtin/builtin_exit.c		\
		src/builtin/builtin_export.c		\
		src/builtin/builtin_unalias.c		\
		src/builtin/builtin_unset.c		\
		src/builtin/builtin_set.c		\
		src/builtin/builtin_shopt.c		\
		src/common/basename.c			\
		src/common/constant.h			\
		src/common/env.c			\
		src/common/function.h			\
		src/common/getcwd2.c			\
		src/common/isdigitstr.c			\
		src/common/macro.h			\
		src/common/strmerge.c			\
		src/common/strvectoradd.c		\
		src/common/strvmerge.c			\
		src/common/strndup.c			\
		src/exec/exec.h				\
		src/exec/exec_and.c			\
		src/exec/exec_bang.c			\
		src/exec/exec_case.c			\
		src/exec/exec_cmd.c			\
		src/exec/exec_for.c			\
		src/exec/exec_funcdec.c			\
		src/exec/exec_node.c			\
		src/exec/exec_or.c			\
		src/exec/exec_if.c			\
		src/exec/exec_pipe.c			\
		src/exec/exec_red.c			\
		src/exec/exec_sep.c			\
		src/exec/exec_sepand.c			\
		src/exec/exec_subshell.c		\
		src/exec/exec_while.c			\
		src/parser/getline.c			\
		src/parser/getline.h			\
		src/parser/parser.c			\
		src/parser/parser.h			\
		src/parser/lexer.c			\
		src/shell/alias.c			\
		src/shell/alias.h			\
		src/shell/func.c			\
		src/shell/func.h			\
		src/shell/getoptions.c			\
		src/shell/option.c			\
		src/shell/option.h			\
		src/shell/shell.c			\
		src/shell/shell.h			\
		src/shell/prompt.c			\
		src/shell/var.c				\
		src/shell/var.h


CLEANFILES= *~ \#*\#

EXTRA_DIST = AUTHORS README TODO doc

.PHONY: tar doc man re

tar: distcheck

re: clean all

doc:
	cd $(srcdir)/doc && $(MAKE) doc

man:
	cd $(srcdir)/doc && $(MAKE) man
