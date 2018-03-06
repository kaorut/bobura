# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

headers =

extra_headers =

sources =

extra_sources = \
    main.cpp

EXTRA_DIST = $(extra_sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(headers) $(sources))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers) $(extra_sources))

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || test $$? -eq 2
	mv $(addsuffix .tmp, $@) $@

format:
	$(TETENGO2_TOOLS)/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(headers) $(sources) $(extra_headers) $(extra_sources)

clean-local:
	-rm -f *.iwyuout.tmp
	-rm -f *.iwyuout
