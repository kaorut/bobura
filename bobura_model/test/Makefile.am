# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

headers = \
    test_bobura.model.detail_type_list.h \
    test_bobura.model.type_list.h

extra_headers =

sources = \
    master.cpp \
    test_bobura.model.message.oudia_diagram_dialog.cpp \
    test_bobura.model.message.timetable_observer_set.cpp \
    test_bobura.model.serializer.bzip2_reader.cpp \
    test_bobura.model.serializer.bzip2_writer.cpp \
    test_bobura.model.serializer.exec_json_reading_task.cpp \
    test_bobura.model.serializer.json_reader.cpp \
    test_bobura.model.serializer.json_writer.cpp \
    test_bobura.model.serializer.oudia_diagram_dialog.cpp \
    test_bobura.model.serializer.oudia_reader.cpp \
    test_bobura.model.serializer.select_oudia_diagram.cpp \
    test_bobura.model.serializer.reader.cpp \
    test_bobura.model.serializer.reader_selector.cpp \
    test_bobura.model.serializer.reader_set.cpp \
    test_bobura.model.serializer.windia_reader.cpp \
    test_bobura.model.serializer.writer.cpp \
    test_bobura.model.serializer.writer_selector.cpp \
    test_bobura.model.serializer.writer_set.cpp \
    test_bobura.model.station.cpp \
    test_bobura.model.station_info.grade.cpp \
    test_bobura.model.timetable.cpp \
    test_bobura.model.timetable_info.font_color_set.cpp \
    test_bobura.model.timetable_info.station_interval_calcula.cpp \
    test_bobura.model.timetable_info.station_location.cpp \
    test_bobura.model.train.cpp \
    test_bobura.model.train_info.stop.cpp \
    test_bobura.model.train_info.time.cpp \
    test_bobura.model.train_info.time_span.cpp \
    test_bobura.model.train_kind.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = bobura_model.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = bobura_model.test

bobura_model_test_DEPENDENCIES = \
    $(top_builddir)/bobura_model/src/libbobura_model.a
bobura_model_test_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_GUI_INCLUDE) \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE)
bobura_model_test_LDFLAGS = \
    -L$(top_builddir)/bobura_model/src \
    -L$(TETENGO2_GUI_LIB) \
    -L$(TETENGO2_LIB) \
    -L$(TETENGO2_DETAIL_LIB)
bobura_model_test_LDADD = \
    -lbobura_model \
    -ltetengo2_gui \
    -ltetengo2 \
    -ltetengo2_detail \
    $(UNITTEST_LIBS)
bobura_model_test_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(headers) $(sources))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers) $(extra_sources))

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(bobura_model_test_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || test $$? -eq 2
	mv $(addsuffix .tmp, $@) $@

format:
	$(TETENGO2_TOOLS)/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(headers) $(sources) $(extra_headers) $(extra_sources)

clean-local:
	-rm -f *.iwyuout.tmp
	-rm -f *.iwyuout

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd

$(top_builddir)/bobura_model/src/libbobura_model.a:
	pushd $(top_builddir)/bobura_model/src; \
	$(MAKE) all; \
	popd
