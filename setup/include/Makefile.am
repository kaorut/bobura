# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$

SUBDIRS = setup

headers =

include_HEADERS = $(headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(headers))
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

lint-iwyu-extra:
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

format:
	$(TETENGO2_TOOLS)/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(headers)
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) format); done

clean-local:
	-rm -f *.iwyuout.tmp
	-rm -f *.iwyuout
