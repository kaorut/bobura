# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

extra_headers = \
    0namespace.dox \
    encode.h

EXTRA_DIST = $(extra_headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS =

lint-iwyu:
	for f in $(pkg_headers); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

lint-iwyu-extra:
	for f in $(extra_headers); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done
