# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

headers =

extra_headers =

sources = \
    bobura.about_dialog.cpp \
    bobura.application.cpp \
    bobura.command.about.cpp \
    bobura.command.command_base.cpp \
    bobura.command.exit.cpp \
    bobura.command.file_property.cpp \
    bobura.command.font_color.cpp \
    bobura.command.horizontally_zoom_in.cpp \
    bobura.command.horizontally_zoom_out.cpp \
    bobura.command.load_from_file.cpp \
    bobura.command.new_file.cpp \
    bobura.command.nop.cpp \
    bobura.command.open_www_tetengo_org.cpp \
    bobura.command.save_to_file.cpp \
    bobura.command.set.cpp \
    bobura.command.set_horizontal_scale.cpp \
    bobura.command.set_vertical_scale.cpp \
    bobura.command.show_diagram.cpp \
    bobura.command.show_timetable_down.cpp \
    bobura.command.show_timetable_up.cpp \
    bobura.command.train_kind.cpp \
    bobura.command.vertically_zoom_in.cpp \
    bobura.command.vertically_zoom_out.cpp \
    bobura.diagram_view.cpp \
    bobura.file_property_dialog.cpp \
    bobura.font_color_dialog.cpp \
    bobura.load_save.confirm_file_save.cpp \
    bobura.load_save.load_from_file.cpp \
    bobura.load_save.new_file.cpp \
    bobura.load_save.save_to_file.cpp \
    bobura.main_window.cpp \
    bobura.main_window_menu_builder.cpp \
    bobura.message.diagram_selection_observer_set.cpp \
    bobura.message.timetable_model_observer_set.cpp \
    bobura.property_bar.cpp \
    bobura.settings.cpp \
    bobura.timetable_model.cpp \
    bobura.timetable_view.cpp \
    bobura.train_kind_dialog.cpp \
    bobura.view.diagram.header.cpp \
    bobura.view.diagram.item.cpp \
    bobura.view.diagram.selection.cpp \
    bobura.view.diagram.station_line.cpp \
    bobura.view.diagram.time_line.cpp \
    bobura.view.diagram.train_line.cpp \
    bobura.view.diagram.utility.cpp \
    bobura.view.diagram.zoom.cpp \
    bobura.view.scale_list.cpp \
    bobura.view.timetable.header.cpp \
    bobura.view.timetable.item.cpp \
    bobura.view.timetable.station_list.cpp \
    bobura.view.timetable.train_list.cpp \
    bobura.view.timetable.train_number_header.cpp \
    bobura.view.timetable.utility.cpp \
    bobura.view.utility.cpp \
    bobura.view_picture_box.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libbobura_core.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libbobura_core_a_CPPFLAGS = \
    -I$(top_srcdir)/bobura_core/include \
    -I$(top_srcdir)/bobura_model/include \
    -I$(TETENGO2_GUI_INCLUDE) \
    -I$(TETENGO2_INCLUDE) \
    -I$(TETENGO2_DETAIL_INCLUDE)
libbobura_core_a_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu:
	for f in $(headers) $(sources); \
	do \
	    echo "iwyu: "$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libbobura_core_a_CPPFLAGS) $(CXXFLAGS) $$f || test $$? -eq 2; \
	done

lint-iwyu-extra:
	for f in $(extra_headers) $(extra_sources); \
	do \
	    echo "iwyu: "$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libbobura_core_a_CPPFLAGS) $(CXXFLAGS) $$f || test $$? -eq 2; \
	done

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
