# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$

EXTRA_DIST = precompiled.h precompiled.cpp

PRECOMPILE_OUTPUT = $(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT)

all-local: $(PRECOMPILE_OUTPUT)

TETENGO2_CPPFLAGS = \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE) \
    -I$(TETENGO2_GUI_INCLUDE)
TETENGO2_CXXFLAGS = \
    -x c++-header
PRECOMPILE_CXX = \
    $(CXX) \
    $(DEFS) \
    $(DEFAULT_INCLUDES) $(INCLUDES) \
    $(AM_CPPFLAGS) $(CPPFLAGS) $(TETENGO2_CPPFLAGS) \
    $(AM_CXXFLAGS) $(CXXFLAGS) $(TETENGO2_CXXFLAGS)
$(PRECOMPILE_OUTPUT): precompiled.h
	test -z "$(PRECOMPILE_CPPFLAGS)" || $(PRECOMPILE_CXX) -o $(PRECOMPILE_OUTPUT) $<

clean-local:
	-test -z "$(PRECOMPILE_CPPFLAGS)" || rm -f $(PRECOMPILE_OUTPUT)
