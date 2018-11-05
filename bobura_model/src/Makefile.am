# Automake Settings
# Copyright (C) 2007-2018 kaoru
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
    bobura.model.serializer.writer_set.cpp \
    bobura.model.station.cpp \
    bobura.model.station_info.grade.cpp \
    bobura.model.timetable.cpp \
    bobura.model.timetable_info.font_color_set.cpp \
    bobura.model.timetable_info.station_interval_calculator.cpp \
    bobura.model.timetable_info.station_location.cpp \
    bobura.model.train.cpp \
    bobura.model.train_info.stop.cpp \
    bobura.model.train_info.time.cpp \
    bobura.model.train_info.time_span.cpp \
    bobura.model.train_kind.cpp

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

lint-iwyu: $(addsuffix .iwyuout, $(headers) $(sources))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers) $(extra_sources))

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libbobura_model_a_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
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
