# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

pkg_headers = \
    model/message/oudia_diagram_dialog.h \
    model/message/timetable_observer_set.h \
    model/serializer/bzip2_reader.h \
    model/serializer/bzip2_writer.h \
    model/serializer/exec_json_reading_task.h \
    model/serializer/json_reader.h \
    model/serializer/json_writer.h \
    model/serializer/oudia_diagram_dialog.h \
    model/serializer/oudia_reader.h \
    model/serializer/select_oudia_diagram.h \
    model/serializer/reader.h \
    model/serializer/reader_selector.h \
    model/serializer/reader_set.h \
    model/serializer/windia_reader.h \
    model/serializer/writer.h \
    model/serializer/writer_selector.h \
    model/serializer/writer_set.h \
    model/station.h \
    model/station_info/grade.h \
    model/timetable.h \
    model/timetable_info/font_color_set.h \
    model/timetable_info/station_interval_calculator.h \
    model/timetable_info/station_location.h \
    model/train.h \
    model/train_info/stop.h \
    model/train_info/time.h \
    model/train_info/time_span.h \
    model/train_kind.h

extra_headers = \
    model/0namespace.dox \
    model/message/0namespace.dox \
    model/serializer/0namespace.dox \
    model/station_info/0namespace.dox \
    model/timetable_info/0namespace.dox \
    model/train_info/0namespace.dox

nobase_pkginclude_HEADERS = $(pkg_headers)
EXTRA_DIST = $(extra_headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_GUI_INCLUDE) \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE)

lint-iwyu: $(addsuffix .iwyuout, $(pkg_headers))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers))

%.iwyuout: %
	mkdir -p $(dir $@)
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || test $$? -eq 2
	mv $(addsuffix .tmp, $@) $@

format:
	$(TETENGO2_TOOLS)/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(pkg_headers) $(extra_headers)

clean-local:
	-find -name "*.iwyuout.tmp" | xargs rm -f
	-find -name "*.iwyuout" | xargs rm -f
