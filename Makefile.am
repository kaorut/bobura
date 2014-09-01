# Automake Settings
# Copyright (C) 2007-2014 kaoru
# $Id$

SUBDIRS = \
     bobura bobura_core bobura_model \
     docsrc \
     iconsrc \
     installer_bobura \
     precompiled \
     samples \
     setup \
     tools \
     vsprops

EXTRA_DIST = bobura.sln bobura_config.h-original TODO Doxyfile

.PHONY: lint
lint: lint-includes lint-test-cases

lint-includes: $(top_srcdir)/lib/tetengo2/tools
	$(top_srcdir)/lib/tetengo2/tools/check_includes.sh $(top_srcdir)

lint-test-cases: $(top_srcdir)/lib/tetengo2/tools
	$(top_srcdir)/lib/tetengo2/tools/check_test_cases.sh $(top_srcdir) silent

$(top_srcdir)/lib/tetengo2/tools:
	git submodule update --init
	git submodule foreach 'git checkout master && git pull'

.PHONY: doc
doc:
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    test ! -e $(top_srcdir)/doc || rm -rf $(top_srcdir)/doc; \
	    test ! -e $(top_builddir)/doc || mv $(top_builddir)/doc $(top_srcdir)/doc; \
	    pushd $(top_srcdir); \
	fi
	$(DOXYGEN) $(top_srcdir)/Doxyfile
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    popd; \
	    test ! -e $(top_builddir)/doc || rm -rf $(top_builddir)/doc; \
	    test ! -e $(top_srcdir)/doc || mv -f $(top_srcdir)/doc $(top_builddir)/doc; \
	fi

.PHONY: clean-doc
clean-doc:
	-rm -rf $(top_builddir)/doc

distclean-local: clean-doc
