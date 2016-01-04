/*! \file
    \brief Test of class bobura::main_window_menu_builder.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <vector>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <bobura/command/set.h>
#include <bobura/diagram_view.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/load_from_file.h>
#include <bobura/load_save/new_file.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/main_window.h>
#include <bobura/main_window_menu_builder.h>
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

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using config_traits_type = traits_type_list_type::config_type;

    using settings_type =
        bobura::settings<
            string_type, ui_type_list_type::position_type, ui_type_list_type::dimension_type, config_traits_type
        >;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using load_save_traits_type = traits_type_list_type::load_save_type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using confirm_file_save_type = bobura::load_save::confirm_file_save<load_save_traits_type>;

    using new_file_type = bobura::load_save::new_file<load_save_traits_type>;

    using load_from_file_type = bobura::load_save::load_from_file<load_save_traits_type>;

    using diagram_view_type = bobura::diagram_view<traits_type_list_type::diagram_view_type>;

    using command_set_type = bobura::command::set<traits_type_list_type::command_set_type>;

    using main_window_type =
        bobura::main_window<traits_type_list_type::main_window_type, traits_type_list_type::command_set_type>;

    using main_window_menu_builder_type =
        bobura::main_window_menu_builder<traits_type_list_type::main_window_menu_builder_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(main_window_menu_builder)
    // test cases

// This test case causes a segmentation fault with GCC.
#if !( \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog{};
        settings_type settings{
            std::vector<string_type>{1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
            string_type{ TETENGO2_TEXT("test_bobura") }
        };
        model_type model{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const save_to_file_type ask_file_path_and_save_to_file{ true, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const new_file_type new_file{ confirm_file_save };
        const load_from_file_type load_from_file{ true, confirm_file_save, message_catalog };
        const load_from_file_type reload{ false, confirm_file_save, message_catalog };
        diagram_view_type diagram_view{ model, message_catalog };
        const command_set_type command_set{
            new_file,
            load_from_file,
            reload,
            save_to_file,
            ask_file_path_and_save_to_file,
            diagram_view,
            settings,
            message_catalog
        };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const main_window_menu_builder_type main_window_menu_builder{ command_set, model, main_window, message_catalog };
    }

    BOOST_AUTO_TEST_CASE(build)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog{};
        settings_type settings{
            std::vector<string_type>{1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
            string_type{ TETENGO2_TEXT("test_bobura") }
        };
        model_type model{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const save_to_file_type ask_file_path_and_save_to_file{ true, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const new_file_type new_file{ confirm_file_save };
        const load_from_file_type load_from_file{ true, confirm_file_save, message_catalog };
        const load_from_file_type reload{ false, confirm_file_save, message_catalog };
        diagram_view_type diagram_view{ model, message_catalog };
        const command_set_type command_set{
            new_file,
            load_from_file,
            reload,
            save_to_file,
            ask_file_path_and_save_to_file,
            diagram_view,
            settings,
            message_catalog
        };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const main_window_menu_builder_type main_window_menu_builder{ command_set, model, main_window, message_catalog };

        BOOST_TEST(main_window_menu_builder.build().get());
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
