# Automake Settings
# Copyright (C) 2007-2014 kaoru
# $Id$

EXTRA_DIST = precompiled.h precompiled.cpp

all-local: $(top_srcdir)/precompiled/precompiled.h.gch

TETENGO2_CPPFLAGS = \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE) \
    -I$(TETENGO2_GUI_INCLUDE)

$(top_srcdir)/precompiled/precompiled.h.gch: precompiled.h
	test -z "$(PRECOMPILE_CPPFLAGS)" || $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TETENGO2_CPPFLAGS) $(BOOST_CPPFLAGS) $<

clean-local:
	-test -z "$(PRECOMPILE_CPPFLAGS)" || rm -f $(top_srcdir)/precompiled/precompiled.h.gch
