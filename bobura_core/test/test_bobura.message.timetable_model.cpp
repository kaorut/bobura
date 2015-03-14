/*! \file
    \brief Test of class bobura::message::timetable_model.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <vector>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/diagram_picture_box.h>
#include <bobura/diagram_view.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/main_window.h>
#include <bobura/message/timetable_model.h>
#include <bobura/settings.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


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

    using view_traits_type = traits_type_list_type::view_type;

    using view_type = bobura::diagram_view<view_traits_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using settings_type =
        bobura::settings<
            string_type,
            ui_type_list_type::position_type,
            ui_type_list_type::dimension_type,
            traits_type_list_type::config_type
        >;

    using load_save_traits_type = traits_type_list_type::load_save_type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using confirm_file_save_type = bobura::load_save::confirm_file_save<load_save_traits_type>;

    using window_type = ui_type_list_type::window_type;

    using main_window_type =
        bobura::main_window<traits_type_list_type::main_window_type, traits_type_list_type::command_set_type>;


}


#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(timetable_model)
BOOST_AUTO_TEST_SUITE(reset)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::reset<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::reset<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        observer();

        settings.clear_config();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::changed<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::changed<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        observer();

        settings.clear_config();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
