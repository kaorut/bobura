# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

SUBDIRS = \
     bobura_model bobura_core bobura \
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
lint: lint-includes lint-test-cases lint-type-list-type-duplication

lint-includes: $(top_srcdir)/lib/tetengo2/tools/check_includes.sh
	$< $(top_srcdir)

$(top_srcdir)/lib/tetengo2/tools/check_includes.sh:
	git submodule update --init
	git submodule foreach 'git checkout -f master && git pull -p'

lint-test-cases: $(top_srcdir)/lib/tetengo2/tools/check_test_cases.sh
	$< $(top_srcdir) silent

$(top_srcdir)/lib/tetengo2/tools/check_test_cases.sh:
	git submodule update --init
	git submodule foreach 'git checkout -f master && git pull -p'

lint-type-list-type-duplication: $(top_srcdir)/lib/tetengo2/tools/check_type_list_type_duplication.sh
	$< $(top_srcdir)

$(top_srcdir)/lib/tetengo2/tools/check_type_list_type_duplication.sh:
	git submodule update --init
	git submodule foreach 'git checkout -f master && git pull -p'

.PHONY: doc
doc:
	$(DOXYGEN) $(top_srcdir)/Doxyfile

.PHONY: clean-doc
clean-doc:
	-rm -rf $(top_builddir)/doc

distclean-local: clean-doc
