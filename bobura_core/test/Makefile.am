# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$
#
headers =

extra_headers =

sources = \
    master.cpp \
    test_bobura.about_dialog.cpp \
    test_bobura.application.cpp \
    test_bobura.command.about.cpp \
    test_bobura.command.command_base.cpp \
    test_bobura.command.exit.cpp \
    test_bobura.command.file_property.cpp \
    test_bobura.command.font_color.cpp \
    test_bobura.command.horizontally_zoom_in.cpp \
    test_bobura.command.horizontally_zoom_out.cpp \
    test_bobura.command.load_from_file.cpp \
    test_bobura.command.new_file.cpp \
    test_bobura.command.nop.cpp \
    test_bobura.command.open_www_tetengo_org.cpp \
    test_bobura.command.save_to_file.cpp \
    test_bobura.command.set.cpp \
    test_bobura.command.set_horizontal_scale.cpp \
    test_bobura.command.set_vertical_scale.cpp \
    test_bobura.command.show_diagram.cpp \
    test_bobura.command.show_timetable_down.cpp \
    test_bobura.command.show_timetable_up.cpp \
    test_bobura.command.train_kind.cpp \
    test_bobura.command.vertically_zoom_in.cpp \
    test_bobura.command.vertically_zoom_out.cpp \
    test_bobura.diagram_view.cpp \
    test_bobura.file_property_dialog.cpp \
    test_bobura.font_color_dialog.cpp \
    test_bobura.load_save.confirm_file_save.cpp \
    test_bobura.load_save.load_from_file.cpp \
    test_bobura.load_save.new_file.cpp \
    test_bobura.load_save.save_to_file.cpp \
    test_bobura.main_window.cpp \
    test_bobura.main_window_menu_builder.cpp \
    test_bobura.message.about_dialog.cpp \
    test_bobura.message.diagram_selection_observer_set.cpp \
    test_bobura.message.diagram_view.cpp \
    test_bobura.message.file_property_dialog.cpp \
    test_bobura.message.font_color_dialog.cpp \
    test_bobura.message.main_window.cpp \
    test_bobura.message.property_bar.cpp \
    test_bobura.message.timetable_model.cpp \
    test_bobura.message.timetable_model_observer_set.cpp \
    test_bobura.message.train_kind_dialog.cpp \
    test_bobura.message.view_picture_box.diagram.cpp \
    test_bobura.message.view_picture_box.timetable.cpp \
    test_bobura.property_bar.cpp \
    test_bobura.settings.cpp \
    test_bobura.timetable_model.cpp \
    test_bobura.timetable_view.cpp \
    test_bobura.train_kind_dialog.cpp \
    test_bobura.view.diagram.header.cpp \
    test_bobura.view.diagram.item.cpp \
    test_bobura.view.diagram.selection.cpp \
    test_bobura.view.diagram.station_line.cpp \
    test_bobura.view.diagram.time_line.cpp \
    test_bobura.view.diagram.train_line.cpp \
    test_bobura.view.diagram.utility.cpp \
    test_bobura.view.diagram.zoom.cpp \
    test_bobura.view.scale_list.cpp \
    test_bobura.view.timetable.header.cpp \
    test_bobura.view.timetable.item.cpp \
    test_bobura.view.timetable.station_list.cpp \
    test_bobura.view.timetable.train_list.cpp \
    test_bobura.view.timetable.train_number_header.cpp \
    test_bobura.view.timetable.utility.cpp \
    test_bobura.view.utility.cpp \
    test_bobura.view_picture_box.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = bobura_core.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = bobura_core.test

bobura_core_test_DEPENDENCIES = \
    $(top_builddir)/bobura_core/src/libbobura_core.a \
    $(top_builddir)/bobura_model/src/libbobura_model.a
bobura_core_test_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_GUI_INCLUDE) \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE)
bobura_core_test_LDFLAGS = \
    -L$(top_builddir)/bobura_core/src \
    -L$(top_builddir)/bobura_model/src \
    -L$(TETENGO2_GUI_LIB) \
    -L$(TETENGO2_LIB) \
    -L$(TETENGO2_DETAIL_LIB)
bobura_core_test_LDADD = \
    -lbobura_core \
    -lbobura_model \
    -ltetengo2_gui \
    -ltetengo2 \
    -ltetengo2_detail \
    $(UNITTEST_LIBS)
bobura_core_test_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(headers) $(sources))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers) $(extra_sources))

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(bobura_core_test_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
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

$(top_builddir)/bobura_core/src/libbobura_core.a:
	pushd $(top_builddir)/bobura_core/src; \
	$(MAKE) all; \
	popd

$(top_builddir)/bobura_model/src/libbobura_model.a:
	pushd $(top_builddir)/bobura_model/src; \
	$(MAKE) all; \
	popd
