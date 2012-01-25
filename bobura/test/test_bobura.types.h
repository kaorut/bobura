/*! \file
    \brief The type list for test_bobura.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_TYPES_H)
#define TESTBOBURA_TYPES_H

//#include <cstddef>
//#include <iterator>
//#include <string>
//#include <utility>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.detail.stub.alert.h>
#include <tetengo2.detail.stub.common_dialog.h>
#include <tetengo2.detail.stub.cursor.h>
#include <tetengo2.detail.stub.drawing.h>
#include <tetengo2.detail.stub.encoding.h>
#include <tetengo2.detail.stub.gui_fixture.h>
#include <tetengo2.detail.stub.menu.h>
#include <tetengo2.detail.stub.message_handler.h>
#include <tetengo2.detail.stub.message_loop.h>
#include <tetengo2.detail.stub.unit.h>
#include <tetengo2.detail.stub.virtual_key.h>
#include <tetengo2.detail.stub.widget.h>
#include <tetengo2.gui.alert.h>
#include <tetengo2.gui.common_dialog.file_open.h>
#include <tetengo2.gui.common_dialog.message_box.h>
#include <tetengo2.gui.cursor.system.h>
#include <tetengo2.gui.drawing.background.h>
#include <tetengo2.gui.drawing.color.h>
#include <tetengo2.gui.drawing.font.h>
#include <tetengo2.gui.drawing.picture.h>
#include <tetengo2.gui.drawing.picture_reader.h>
#include <tetengo2.gui.drawing.transparent_background.h>
#include <tetengo2.gui.drawing.widget_canvas.h>
#include <tetengo2.gui.fixture.h>
#include <tetengo2.gui.menu.command.h>
#include <tetengo2.gui.menu.menu_bar.h>
#include <tetengo2.gui.menu.menu_base.h>
#include <tetengo2.gui.menu.popup.h>
#include <tetengo2.gui.menu.separator.h>
#include <tetengo2.gui.menu.shortcut_key.h>
#include <tetengo2.gui.menu.shortcut_key_table.h>
#include <tetengo2.gui.menu.traits.h>
#include <tetengo2.gui.message.dialog_message_loop.h>
#include <tetengo2.gui.message.menu_observer_set.h>
#include <tetengo2.gui.message.message_loop.h>
#include <tetengo2.gui.message.message_loop_break.h>
#include <tetengo2.gui.message.mouse_observer_set.h>
#include <tetengo2.gui.message.paint_observer_set.h>
#include <tetengo2.gui.message.window_observer_set.h>
#include <tetengo2.gui.unit.em.h>
#include <tetengo2.gui.virtual_key.h>
#include <tetengo2.gui.widget.abstract_window.h>
#include <tetengo2.gui.widget.button.h>
#include <tetengo2.gui.widget.dialog.h>
#include <tetengo2.gui.widget.image.h>
#include <tetengo2.gui.widget.label.h>
#include <tetengo2.gui.widget.link_label.h>
#include <tetengo2.gui.widget.traits.abstract_window_traits.h>
#include <tetengo2.gui.widget.traits.button_traits.h>
#include <tetengo2.gui.widget.traits.control_traits.h>
#include <tetengo2.gui.widget.traits.dialog_traits.h>
#include <tetengo2.gui.widget.traits.image_traits.h>
#include <tetengo2.gui.widget.traits.label_traits.h>
#include <tetengo2.gui.widget.traits.link_label_traits.h>
#include <tetengo2.gui.widget.traits.widget_traits.h>
#include <tetengo2.gui.widget.traits.window_traits.h>
#include <tetengo2.gui.widget.window.h>
#include <tetengo2.message.messages.h>
#include <tetengo2.message.message_catalog.h>
#include <tetengo2.message.message_catalog_parser.h>
#include <tetengo2.text.encoder.h>
#include <tetengo2.text.encoding.locale.h>
#include <tetengo2.text.encoding.utf8.h>
#include <tetengo2.text.grammar.json.h>
#include <tetengo2.text.pull_parser.h>
#include <tetengo2.text.push_parser.h>

#include "bobura.about_dialog.h"
#include "bobura.application.h"
#include "bobura.command.set.h"
#include "bobura.command.type_list_impl.h"
#include "bobura.main_window.h"
#include "bobura.message.timetable_model_observer_set.h"
#include "bobura.message.type_list_impl.h"
#include "bobura.model.serializer.json_reader.h"
#include "bobura.model.station.h"
#include "bobura.model.train.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"
#include "bobura.settings.h"
#include "bobura.timetable_model.h"


// types

typedef tetengo2::detail::stub::encoding encoding_details_type;

typedef
    tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
    internal_encoding_type;

typedef
    tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
    ui_encoding_type;

typedef
    tetengo2::text::encoder<internal_encoding_type, ui_encoding_type>
    ui_encoder_type;

typedef
    tetengo2::text::encoding::locale<std::string, encoding_details_type>
    exception_encoding_type;

typedef
    tetengo2::text::encoder<internal_encoding_type, exception_encoding_type>
    exception_encoder_type;

typedef bobura::settings<std::wstring, boost::filesystem::path> settings_type;

typedef
    bobura::model::station_info::grade_type_set<std::wstring>
    station_grade_type_set_type;

typedef station_grade_type_set_type::grade_type grade_type;

typedef bobura::model::station<std::wstring, grade_type> station_type;

typedef
    bobura::model::timetable_info::station_location<
        station_type, std::size_t
    >
    station_location_type;

typedef
    bobura::model::train_info::time<
        std::size_t,
        bobura::model::train_info::time_span<std::ptrdiff_t>
    >
    time_type;

typedef
    bobura::model::train_info::stop<time_type, std::wstring>
    stop_type;

typedef
    bobura::model::train<std::wstring, std::wstring, stop_type>
    train_type;

typedef
    bobura::model::timetable<std::wstring, station_location_type, train_type>
    timetable_type;

typedef
    bobura::message::timetable_model_observer_set<
        timetable_type, boost::filesystem::path
    >
    timetable_model_observer_set_type;

typedef
    bobura::timetable_model<
        timetable_type,
        boost::filesystem::path,
        timetable_model_observer_set_type
    >
    model_type;

typedef
    tetengo2::detail::stub::alert<std::string, ui_encoder_type>
    alert_details_type;

typedef
    tetengo2::gui::alert<
        ui_encoder_type, exception_encoder_type, alert_details_type
    >
    alert_type;

typedef tetengo2::detail::stub::unit unit_details_type;

typedef
    tetengo2::gui::unit::em<std::ptrdiff_t, std::ptrdiff_t, unit_details_type>
    unit_difference_type;

typedef std::pair<unit_difference_type, unit_difference_type> position_type;

typedef
    tetengo2::gui::unit::em<std::size_t, std::size_t, unit_details_type>
    unit_size_type;

typedef std::pair<unit_size_type, unit_size_type> dimension_type;

typedef tetengo2::detail::stub::drawing drawing_details_type;

typedef
    tetengo2::gui::drawing::background<drawing_details_type> background_type;

typedef
    tetengo2::gui::drawing::transparent_background<drawing_details_type>
    transparent_background_type;

typedef
    tetengo2::gui::drawing::font<
        std::wstring, std::size_t, drawing_details_type
    >
    font_type;

typedef
    tetengo2::gui::drawing::picture<std::size_t, drawing_details_type>
    picture_type;

typedef
    tetengo2::gui::drawing::picture_reader<
        picture_type, boost::filesystem::path, drawing_details_type
    >
    picture_reader_type;

typedef
    tetengo2::gui::drawing::widget_canvas<
        std::size_t,
        std::wstring,
        dimension_type,
        ui_encoder_type,
        background_type,
        font_type,
        picture_type,
        drawing_details_type
    >
    canvas_type;

typedef
    tetengo2::gui::cursor::system<tetengo2::detail::stub::cursor>
    system_cursor_type;

typedef
    tetengo2::gui::widget::traits::widget_traits<
        canvas_type,
        alert_type,
        position_type,
        dimension_type,
        std::wstring,
        ui_encoder_type,
        background_type,
        font_type,
        system_cursor_type,
        tetengo2::gui::message::paint_observer_set<canvas_type>,
        tetengo2::gui::message::mouse_observer_set
    >
    widget_traits_type;

typedef
    tetengo2::gui::menu::shortcut_key<
        tetengo2::gui::virtual_key<
            tetengo2::detail::stub::virtual_key<std::wstring>
        >
    >
    shortcut_key_type;

typedef
    tetengo2::gui::menu::traits<
        std::wstring,
        shortcut_key_type,
        ui_encoder_type,
        tetengo2::gui::message::menu_observer_set
    >
    menu_traits_type;

typedef tetengo2::detail::stub::menu menu_details_type;

typedef
    tetengo2::gui::menu::menu_base<menu_traits_type, menu_details_type>
    menu_base_type;

typedef
    tetengo2::gui::menu::shortcut_key_table<
        shortcut_key_type, menu_base_type, menu_details_type
    >
    shortcut_key_table_type;

typedef
    tetengo2::gui::menu::menu_bar<
        menu_traits_type, shortcut_key_table_type, menu_details_type
    >
    menu_bar_type;

typedef tetengo2::detail::stub::widget widget_details_type;

typedef
    tetengo2::detail::stub::message_handler<widget_details_type>
    message_handler_details_type;

typedef
    tetengo2::gui::widget::traits::abstract_window_traits<
        widget_traits_type,
        menu_bar_type,
        tetengo2::gui::message::window_observer_set
    >
    abstract_window_traits_type;

typedef
    tetengo2::gui::widget::abstract_window<
        abstract_window_traits_type,
        widget_details_type,
        message_handler_details_type
    >
    abstract_window_type;

typedef
    tetengo2::gui::widget::traits::window_traits<abstract_window_traits_type>
    window_traits_type;

typedef
    tetengo2::gui::widget::window<
        window_traits_type, widget_details_type, message_handler_details_type
    >
    window_type;

typedef
    tetengo2::text::grammar::json<std::string::const_iterator>
    grammar_type;

typedef
    tetengo2::text::push_parser<
        std::string::const_iterator, grammar_type, int, double
    >
    push_parser_type;

typedef
    tetengo2::text::pull_parser<push_parser_type, std::size_t>
    pull_parser_type;

typedef
    tetengo2::text::encoding::utf8<encoding_details_type>
    message_catalog_encoding_type;

typedef
    tetengo2::text::encoding::locale<std::string, encoding_details_type>
    locale_name_encoding_type;

typedef
    tetengo2::text::encoder<
        internal_encoding_type, message_catalog_encoding_type
    >
    message_catalog_encoder_type;

typedef
    tetengo2::message::message_catalog_parser<
        pull_parser_type, std::wstring, message_catalog_encoder_type
    >
    message_catalog_parser_type;

typedef
    tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type>
    locale_name_encoder_type;

typedef
    tetengo2::message::messages<
        boost::filesystem::path,
        message_catalog_parser_type,
        locale_name_encoder_type
    >
    messages_type;

typedef
    tetengo2::message::message_catalog<messages_type> message_catalog_type;

typedef
    tetengo2::gui::common_dialog::message_box<
        window_type::base_type,
        std::wstring,
        ui_encoder_type,
        tetengo2::detail::stub::common_dialog
    >
    message_box_type;

typedef
    tetengo2::gui::common_dialog::file_open<
        window_type::base_type,
        std::wstring,
        boost::filesystem::path,
        ui_encoder_type,
        tetengo2::detail::stub::common_dialog
    >
    file_open_type;

typedef tetengo2::detail::stub::message_loop message_loop_details_type;

typedef
    tetengo2::gui::message::dialog_message_loop<
        abstract_window_type, message_loop_details_type
    >
    dialog_message_loop_type;

typedef
    tetengo2::gui::message::message_loop_break<message_loop_details_type>
    message_loop_break_type;

typedef
    tetengo2::gui::widget::traits::dialog_traits<
        abstract_window_traits_type,
        dialog_message_loop_type,
        message_loop_break_type
    >
    dialog_traits_type;

typedef
    tetengo2::gui::widget::dialog<
        dialog_traits_type, widget_details_type, message_handler_details_type
    >
    dialog_type;

typedef
    bobura::message::about_dialog::type_list<dialog_type>::type
    about_dialog_message_type_list_type;

typedef tetengo2::gui::drawing::color<unsigned char> color_type;

typedef
    tetengo2::gui::widget::traits::control_traits<
        widget_traits_type, color_type
    >
    control_traits_type;

typedef
    tetengo2::gui::widget::traits::label_traits<control_traits_type>
    label_traits_type;

typedef
    tetengo2::gui::widget::label<
        label_traits_type, widget_details_type, message_handler_details_type
    >
    label_type;

typedef
    tetengo2::gui::widget::traits::link_label_traits<label_traits_type>
    link_label_traits_type;

typedef
    tetengo2::gui::widget::link_label<
        link_label_traits_type,
        widget_details_type,
        message_handler_details_type
    >
    link_label_type;

typedef
    tetengo2::gui::widget::traits::image_traits<
        control_traits_type, picture_type
    >
    image_traits_type;

typedef
    tetengo2::gui::widget::image<
        image_traits_type, widget_details_type, message_handler_details_type
    >
    image_type;

typedef
    tetengo2::gui::widget::traits::button_traits<control_traits_type>
    button_traits_type;

typedef
    tetengo2::gui::widget::button<
        button_traits_type, widget_details_type, message_handler_details_type
    >
    button_type;

typedef
    bobura::about_dialog<
        dialog_type,
        message_catalog_type,
        settings_type,
        label_type,
        link_label_type,
        image_type,
        button_type,
        picture_reader_type,
        transparent_background_type,
        about_dialog_message_type_list_type
    >
    about_dialog_type;

typedef
    boost::spirit::multi_pass<std::istreambuf_iterator<char>>
    timetable_file_input_stream_iterator_type;

typedef
    tetengo2::text::grammar::json<timetable_file_input_stream_iterator_type>
    timetable_file_grammar_type;

typedef
    tetengo2::text::push_parser<
        timetable_file_input_stream_iterator_type,
        timetable_file_grammar_type,
        int,
        double
    >
    timetable_file_push_parser_type;

typedef
    tetengo2::text::pull_parser<timetable_file_push_parser_type, std::size_t>
    timetable_file_pull_parser_type;

typedef
    tetengo2::text::encoding::utf8<encoding_details_type>
    timetable_file_encoding_type;

typedef
    tetengo2::text::encoder<
        internal_encoding_type, timetable_file_encoding_type
    >
    timetable_file_encoder_type;

typedef
    bobura::model::serializer::json_reader<
        timetable_type,
        station_grade_type_set_type,
        timetable_file_pull_parser_type,
        timetable_file_encoder_type
    >
    reader_type;

typedef
    bobura::command::type_list<
        window_type,
        message_box_type,
        file_open_type,
        about_dialog_type,
        model_type,
        reader_type,
        message_catalog_type
    >::type
    command_type_list_type;

typedef
    bobura::message::main_window::type_list<
        boost::mpl::at<
            command_type_list_type, bobura::command::type::command
        >::type,
        canvas_type,
        position_type,
        picture_reader_type
    >::type
    main_window_message_type_list_type;

typedef
    tetengo2::gui::menu::command<menu_traits_type, menu_details_type>
    menu_command_type;

typedef
    tetengo2::gui::menu::popup<menu_traits_type, menu_details_type>
    popup_menu_type;

typedef
    tetengo2::gui::menu::separator<menu_traits_type, menu_details_type>
    menu_separator_type;

typedef
    bobura::main_window<
        window_type,
        message_catalog_type,
        settings_type,
        message_loop_break_type,
        main_window_message_type_list_type
    >
    main_window_type;

typedef
    bobura::message::timetable_model::type_list<
        timetable_type, boost::filesystem::path, main_window_type
    >::type
    timetable_model_message_type_list_type;

typedef
    bobura::command::set<
        command_type_list_type,
        model_type,
        reader_type,
        main_window_type,
        settings_type,
        message_catalog_type
    >
    command_set_type;

typedef
    tetengo2::gui::message::message_loop<
        abstract_window_type, message_loop_details_type
    >
    message_loop_type;

typedef
    bobura::application<
        settings_type,
        model_type,
        timetable_model_message_type_list_type,
        reader_type,
        message_catalog_type,
        command_set_type,
        main_window_type,
        main_window_message_type_list_type,
        menu_bar_type,
        menu_command_type,
        popup_menu_type,
        menu_separator_type,
        message_loop_type,
        message_loop_break_type,
        tetengo2::gui::fixture<tetengo2::detail::stub::gui_fixture>
    >
    application_type;


#endif
