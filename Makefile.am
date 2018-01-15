# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

SOURCE_SUBDIRS = \
    bobura_model \
    bobura_core \
    bobura \
    setup

SUBDIRS = \
    $(SOURCE_SUBDIRS) \
    docsrc \
    iconsrc \
    installer_bobura \
    precompiled \
    samples \
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

.PHONY: lint-iwyu
lint-iwyu:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

.PHONY: lint-iwyu-extra
lint-iwyu-extra:
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done

.PHONY: doc
doc:
	cd $(top_srcdir) && $(DOXYGEN) Doxyfile
	if test "$(top_srcdir)" != "$(top_builddir)"; \
	then \
	    rm -rf $(top_builddir)/doc; \
	    mv $(top_srcdir)/doc $(top_builddir); \
	fi

.PHONY: clean-doc
clean-doc:
	-rm -rf $(top_builddir)/doc

distclean-local: clean-doc
