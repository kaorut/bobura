# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

SUBDIRS = bobura

headers =

include_HEADERS = $(headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_GUI_INCLUDE) \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE)

lint-iwyu: $(addsuffix .iwyuout, $(headers))
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done

lint-iwyu-extra:
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu-extra); done

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || test $$? -eq 2
	mv $(addsuffix .tmp, $@) $@

format:
	$(top_srcdir)/lib/tetengo2/tools/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(headers)
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) format); done

clean-local:
	-rm -f "*.iwyuout.tmp"
	-rm -f "*.iwyuout"
