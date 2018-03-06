# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

SOURCE_SUBDIRS = \
    bobura \
    bobura_core \
    bobura_model \
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
lint: lint-test-cases lint-type-list-type-duplication lint-iwyu

lint-test-cases: $(TETENGO2_TOOLS)/check_test_cases.sh
	$< $(top_srcdir) silent

$(TETENGO2_TOOLS)/check_test_cases.sh:
	git submodule update --init
	git submodule foreach 'git checkout -f master && git pull -p'

lint-type-list-type-duplication: $(TETENGO2_TOOLS)/check_type_list_type_duplication.sh
	$< $(top_srcdir)

$(TETENGO2_TOOLS)/check_type_list_type_duplication.sh:
	git submodule update --init
	git submodule foreach 'git checkout -f master && git pull -p'

lint-iwyu: $(top_srcdir)/$(IWYU_IMP_PATH)
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

.PHONY: lint-iwyu-extra
lint-iwyu-extra: $(top_srcdir)/$(IWYU_IMP_PATH)
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done

$(top_srcdir)/$(IWYU_IMP_PATH):
	git submodule update --init
	git submodule foreach 'git checkout -f master && git pull -p'

.PHONY: format
format: $(top_srcdir)/.clang-format
	for d in $(SOURCE_SUBDIRS); do (cd $$d && $(MAKE) format); done

$(top_srcdir)/.clang-format: $(TETENGO2_TOOLS)/clang-format
	cp -f $(TETENGO2_TOOLS)/clang-format $(top_srcdir)/.clang-format

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
