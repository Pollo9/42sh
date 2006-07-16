SUBDIRS = 	src

noinst_DATA=42sh$(EXEEXT)
DISTCLEANFILES=42sh$(EXEEXT)

.PHONY: tar doc re

42sh$(EXEEXT): src/42sh$(EXEEXT)

tar: distcheck

re: clean all

doc:
	cd $(srcdir)/doc && $(MAKE) doc

CLEANFILES= *~ '\#*'

EXTRA_DIST = AUTHORS README TODO
