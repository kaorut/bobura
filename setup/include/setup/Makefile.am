# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

pkg_headers =

extra_headers = \
    0namespace.dox \
    encode.h

EXTRA_DIST = $(extra_headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(pkg_headers))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers))

%.iwyuout: %
	mkdir -p $(dir $@)
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || test $$? -eq 2
	mv $(addsuffix .tmp, $@) $@

format:
	$(top_srcdir)/lib/tetengo2/tools/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(pkg_headers) $(extra_headers)

clean-local:
	-find -name "*.iwyuout.tmp" | xargs rm -f
	-find -name "*.iwyuout" | xargs rm -f
