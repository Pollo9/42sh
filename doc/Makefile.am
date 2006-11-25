
EXTRA_DIST=doxyfile 42sh.man

.PHONY: doc man

doc:
	doxygen doxyfile
man:
	groff 42sh.man -man -T ascii > manual.txt
	groff 42sh.man -man -T ps | ps2pdf - manual.pdf

CLEANFILES=html *~ 
