# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

headers =

extra_headers =

sources = \
    bobura.model.message.timetable_observer_set.cpp \
    bobura.model.serializer.bzip2_reader.cpp \
    bobura.model.serializer.bzip2_writer.cpp \
    bobura.model.serializer.exec_json_reading_task.cpp \
    bobura.model.serializer.json_reader.cpp \
    bobura.model.serializer.json_writer.cpp \
    bobura.model.serializer.oudia_diagram_dialog.cpp \
    bobura.model.serializer.oudia_reader.cpp \
    bobura.model.serializer.reader.cpp \
    bobura.model.serializer.reader_selector.cpp \
    bobura.model.serializer.reader_set.cpp \
    bobura.model.serializer.select_oudia_diagram.cpp \
    bobura.model.serializer.windia_reader.cpp \
    bobura.model.serializer.writer.cpp \
    bobura.model.serializer.writer_selector.cpp \
    bobura.model.serializer.writer_set.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libbobura_model.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libbobura_model_a_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_GUI_INCLUDE) \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE)
libbobura_model_a_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu:
	for f in $(headers) $(sources); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libbobura_model_a_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

lint-iwyu-extra:
	for f in $(extra_headers) $(extra_sources); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libbobura_model_a_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
