/*! \file
    \brief Test of class bobura::message::main_window.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/command/nop.h>
#include <bobura/diagram_view.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/message/main_window.h>
#include <bobura/property_bar.h>
#include <bobura/settings.h>
#include <bobura/timetable_model.h>
#include <bobura/timetable_view.h>
#include <bobura/type_list.h>
#include <bobura/view_picture_box.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using popup_menu_type = ui_type_list_type::popup_menu_type;

    using abstract_window_type = ui_type_list_type::abstract_window_type;

    using command_type = bobura::command::nop<traits_type_list_type::command_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using load_save_traits_type = traits_type_list_type::load_save_type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using confirm_file_save_type = bobura::load_save::confirm_file_save<load_save_traits_type>;

    using position_type = ui_type_list_type::position_type;

    using dimension_type = ui_type_list_type::dimension_type;

    using config_traits_type = traits_type_list_type::config_type;

    using settings_type = bobura::settings<string_type, position_type, dimension_type, config_traits_type>;

    using window_type = ui_type_list_type::window_type;

    using diagram_view_traits_type = traits_type_list_type::diagram_view_type;

    using diagram_view_type = bobura::diagram_view<diagram_view_traits_type>;

    using timetable_view_traits_type = traits_type_list_type::timetable_view_type;

    using timetable_view_type = bobura::timetable_view<timetable_view_traits_type>;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using mouse_capture_type = ui_type_list_type::mouse_capture_type;

    using tab_frame_type = ui_type_list_type::tab_frame_type;

    using view_picture_box_type = bobura::view_picture_box<picture_box_type, mouse_capture_type>;

    using property_bar_type =
        bobura::property_bar<
            string_type,
            position_type,
            dimension_type,
            abstract_window_type,
            ui_type_list_type::side_bar_type,
            ui_type_list_type::map_box_type,
            message_catalog_type,
            config_traits_type
        >;

    using popup_menu_selected_type =
        bobura::message::main_window::popup_menu_selected<popup_menu_type, command_type, model_type>;

    using menu_command_selected_type =
        bobura::message::main_window::menu_command_selected<command_type, model_type, abstract_window_type>;

    using window_resized_type =
        bobura::message::main_window::window_resized<
            diagram_view_type,
            timetable_view_type,
            abstract_window_type,
            tab_frame_type,
            view_picture_box_type,
            property_bar_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(main_window)
BOOST_AUTO_TEST_SUITE(popup_menu_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("popup") } };
        std::vector<const command_type*> commands;
        const model_type model{};
        const popup_menu_selected_type observer{ popup_menu, std::move(commands), model };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("popup") } };
        std::vector<const command_type*> commands;
        const model_type model{};
        const popup_menu_selected_type observer{ popup_menu, std::move(commands), model };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(menu_command_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type menu{ command, model, window };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type observer{ command, model, window };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(file_dropped)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type menu{ command, model, window };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type observer{ command, model, window };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(window_resized)
    // test cases

// This test case causes a segmentation fault with GCC.
#if !( \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type diagram_view{ model, message_catalog };
        timetable_view_type timetable_down_view{ timetable_view_type::direction_type::down, model, message_catalog };
        timetable_view_type timetable_up_view{ timetable_view_type::direction_type::up, model, message_catalog };
        window_type window{};
        tab_frame_type tab_frame{ window };
        view_picture_box_type diagram_view_picture_box{ tab_frame };
        view_picture_box_type timetable_down_view_picture_box{ tab_frame };
        view_picture_box_type timetable_up_view_picture_box{ tab_frame };
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        property_bar_type property_bar{ window, settings, message_catalog };
        const window_resized_type observer{
            diagram_view,
            timetable_down_view,
            timetable_up_view,
            window,
            tab_frame,
            diagram_view_picture_box,
            timetable_down_view_picture_box,
            timetable_up_view_picture_box,
            property_bar
        };

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type diagram_view{ model, message_catalog };
        timetable_view_type timetable_down_view{ timetable_view_type::direction_type::down, model, message_catalog };
        timetable_view_type timetable_up_view{ timetable_view_type::direction_type::up, model, message_catalog };
        window_type window{};
        tab_frame_type tab_frame{ window };
        view_picture_box_type diagram_view_picture_box{ tab_frame };
        view_picture_box_type timetable_down_view_picture_box{ tab_frame };
        view_picture_box_type timetable_up_view_picture_box{ tab_frame };
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        property_bar_type property_bar{ window, settings, message_catalog };
        const window_resized_type observer{
            diagram_view,
            timetable_down_view,
            timetable_up_view,
            window,
            tab_frame,
            diagram_view_picture_box,
            timetable_down_view_picture_box,
            timetable_up_view_picture_box,
            property_bar
        };

        observer();

        settings.clear_config();
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(window_closing)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const std::vector<string_type> command_line_arguments{ 1, string_type{ TETENGO2_TEXT("path/to/exe") } };
        const bobura::message::main_window::window_closing<abstract_window_type, confirm_file_save_type> observer(
            parent, confirm_file_save, []() {}
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const bobura::message::main_window::window_closing<abstract_window_type, confirm_file_save_type> observer(
            parent, confirm_file_save, []() {}
        );

        auto cancel = false;
        observer(cancel);

        BOOST_TEST(!cancel);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
