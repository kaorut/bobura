# Automake Settings
# Copyright (C) 2007-2019 kaoru
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
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

format:
	$(TETENGO2_TOOLS)/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(pkg_headers) $(extra_headers)

clean-local:
	-find -name "*.iwyuout.tmp" | xargs rm -f
	-find -name "*.iwyuout" | xargs rm -f
