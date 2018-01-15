# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

headers =

extra_headers =

sources =

extra_sources = \
    main.cpp \
    setup.encode.cpp

EXTRA_DIST = $(extra_sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu:
	for f in $(headers) $(sources); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

lint-iwyu-extra:
	for f in $(extra_headers) $(extra_sources); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done
