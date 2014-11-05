# Automake Settings
# Copyright (C) 2007-2014 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_bobura.diagram_picture_box.cpp \
    test_bobura.diagram_view.cpp \
    test_bobura.load_save.confirm_file_save.cpp \
    test_bobura.load_save.load_from_file.cpp \
    test_bobura.load_save.new_file.cpp \
    test_bobura.load_save.save_to_file.cpp \
    test_bobura.message.about_dialog.cpp \
    test_bobura.message.diagram_picture_box.cpp \
    test_bobura.message.diagram_selection_observer_set.cpp \
    test_bobura.message.diagram_view.cpp \
    test_bobura.message.file_property_dialog.cpp \
    test_bobura.message.font_color_dialog.cpp \
    test_bobura.message.main_window.cpp \
    test_bobura.message.oudia_diagram_dialog.cpp \
    test_bobura.message.property_bar.cpp \
    test_bobura.message.timetable_model.cpp \
    test_bobura.message.timetable_model_observer_set.cpp \
    test_bobura.message.train_kind_dialog.cpp \
    test_bobura.property_bar.cpp \
    test_bobura.settings.cpp \
    test_bobura.timetable_model.cpp \
    test_bobura.view.diagram.header.cpp \
    test_bobura.view.diagram.item.cpp \
    test_bobura.view.diagram.selection.cpp \
    test_bobura.view.diagram.station_line.cpp \
    test_bobura.view.diagram.time_line.cpp \
    test_bobura.view.diagram.train_line.cpp \
    test_bobura.view.diagram.utility.cpp \
    test_bobura.view.scale_list.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = bobura_core.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = bobura_core.test

bobura_core_test_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE) \
    -I$(TETENGO2_GUI_INCLUDE)
bobura_core_test_LDFLAGS = \
    -L$(TETENGO2_LIB)
bobura_core_test_LDADD = \
    -ltetengo2 \
    $(UNITTEST_LIBS)
bobura_core_test_SOURCES = $(headers) $(sources)

$(top_builddir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd