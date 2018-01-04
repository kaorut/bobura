# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

headers =

include_HEADERS = $(headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS =

lint-iwyu:
	for f in $(headers); \
	do \
	    echo "iwyu: "$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $$f || test $$? -eq 2; \
	done; \
	for d in $(SUBDIRS); do (cd $$d && $(MAKE) lint-iwyu); done
