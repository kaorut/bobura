# Automake Settings
# Copyright (C) 2007-2015 kaoru
# $Id$

headers =

extra_headers =

sources = \
    bobura.model.serializer.bzip2_reader.cpp \
    bobura.model.serializer.bzip2_writer.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libbobura_model.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libbobura_model_a_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE) \
    -I$(TETENGO2_GUI_INCLUDE)
libbobura_model_a_SOURCES = $(headers) $(sources)

$(top_builddir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
