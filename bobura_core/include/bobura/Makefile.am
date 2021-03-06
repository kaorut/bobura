# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$

pkg_headers = \
    about_dialog.h \
    application.h \
    application_traits.h \
    command/about.h \
    command/command_base.h \
    command/exit.h \
    command/file_property.h \
    command/font_color.h \
    command/horizontally_zoom_in.h \
    command/horizontally_zoom_out.h \
    command/load_from_file.h \
    command/new_file.h \
    command/nop.h \
    command/open_www_tetengo_org.h \
    command/save_to_file.h \
    command/set.h \
    command/set_horizontal_scale.h \
    command/set_traits.h \
    command/set_vertical_scale.h \
    command/show_diagram.h \
    command/show_timetable_down.h \
    command/show_timetable_up.h \
    command/train_kind.h \
    command/traits.h \
    command/vertically_zoom_in.h \
    command/vertically_zoom_out.h \
    detail_type_list.h \
    diagram_view.h \
    dialog_traits.h \
    file_property_dialog.h \
    font_color_dialog.h \
    load_save/confirm_file_save.h \
    load_save/load_from_file.h \
    load_save/new_file.h \
    load_save/save_to_file.h \
    load_save/traits.h \
    main_window.h \
    main_window_menu_builder.h \
    main_window_menu_builder_traits.h \
    main_window_traits.h \
    message/about_dialog.h \
    message/diagram_selection_observer_set.h \
    message/diagram_view.h \
    message/file_property_dialog.h \
    message/font_color_dialog.h \
    message/main_window.h \
    message/property_bar.h \
    message/timetable_model.h \
    message/timetable_model_observer_set.h \
    message/train_kind_dialog.h \
    message/view_picture_box/diagram.h \
    message/view_picture_box/timetable.h \
    property_bar.h \
    settings.h \
    timetable_model.h \
    timetable_view.h \
    train_kind_dialog.h \
    type_list.h \
    view/diagram/0namespace.dox \
    view/diagram/header.h \
    view/diagram/item.h \
    view/diagram/selection.h \
    view/diagram/station_line.h \
    view/diagram/time_line.h \
    view/diagram/train_line.h \
    view/diagram/traits.h \
    view/diagram/utility.h \
    view/diagram/zoom.h \
    view/scale_list.h \
    view/timetable/header.h \
    view/timetable/item.h \
    view/timetable/station_list.h \
    view/timetable/train_list.h \
    view/timetable/train_number_header.h \
    view/timetable/traits.h \
    view/timetable/utility.h \
    view/utility.h \
    view_picture_box.h

extra_headers = \
    0namespace.dox \
    command/0namespace.dox \
    load_save/0namespace.dox \
    message/0namespace.dox \
    message/view_picture_box/0namespace.dox \
    view/0namespace.dox \
    view/diagram/0namespace.dox \
    view/timetable/0namespace.dox

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
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

format:
	$(TETENGO2_TOOLS)/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(pkg_headers) $(extra_headers)

clean-local:
	-find -name "*.iwyuout.tmp" | xargs rm -f
	-find -name "*.iwyuout" | xargs rm -f
