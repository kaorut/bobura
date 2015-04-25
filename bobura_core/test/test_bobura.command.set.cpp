/*! \file
    \brief Test of class bobura::command::set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <vector>

#include <boost/filesystem.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/command/set.h>
#include <bobura/diagram_view.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/load_from_file.h>
#include <bobura/load_save/new_file.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/settings.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/scale_list.h>


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

    using size_type = common_type_list_type::size_type;

    using model_type =
        bobura::timetable_model<
            size_type,
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

    using scale_list_type = bobura::view::scale_list<size_type, string_type, common_type_list_type::scale_type>;

    using command_set_type = bobura::command::set<traits_type_list_type::command_set_type>;


}


#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(set)
    // test cases

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
    }

    BOOST_AUTO_TEST_CASE(about)
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

        command_set.about();
    }

    BOOST_AUTO_TEST_CASE(ask_file_path_and_save_to_file)
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

        command_set.ask_file_path_and_save_to_file();
    }

    BOOST_AUTO_TEST_CASE(exit)
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

        command_set.exit();
    }

    BOOST_AUTO_TEST_CASE(file_property)
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

        command_set.file_property();
    }

    BOOST_AUTO_TEST_CASE(font_color)
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

        command_set.font_color();
    }

    BOOST_AUTO_TEST_CASE(horizontally_zoom_in)
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

        command_set.horizontally_zoom_in();
    }

    BOOST_AUTO_TEST_CASE(horizontally_zoom_out)
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

        command_set.horizontally_zoom_out();
    }

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(load_from_file)
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

        command_set.load_from_file();
    }

    BOOST_AUTO_TEST_CASE(create_load_from_file_parameter)
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

        const boost::filesystem::path path{ string_type{ TETENGO2_TEXT("hoge.txt") } };
        command_set.create_load_from_file_parameter(path);
    }
#endif

    BOOST_AUTO_TEST_CASE(new_file)
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

        command_set.new_file();
    }

    BOOST_AUTO_TEST_CASE(nop)
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

        command_set.nop();
    }

    BOOST_AUTO_TEST_CASE(open_www_tetengo_org)
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

        command_set.open_www_tetengo_org();
    }

    BOOST_AUTO_TEST_CASE(reload)
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

        command_set.reload();
    }

    BOOST_AUTO_TEST_CASE(save_to_file)
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

        command_set.save_to_file();
    }

    BOOST_AUTO_TEST_CASE(set_horizontal_scale)
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

        const scale_list_type scale_list{};
        command_set.set_horizontal_scale(0);
        command_set.set_horizontal_scale(scale_list.size() - 1);
    }

    BOOST_AUTO_TEST_CASE(set_vertical_scale)
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

        const scale_list_type scale_list{};
        command_set.set_vertical_scale(0);
        command_set.set_vertical_scale(scale_list.size() - 1);
    }

    BOOST_AUTO_TEST_CASE(train_kind)
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

        command_set.train_kind();
    }

    BOOST_AUTO_TEST_CASE(vertically_zoom_in)
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

        command_set.vertically_zoom_in();
    }

    BOOST_AUTO_TEST_CASE(vertically_zoom_out)
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

        command_set.vertically_zoom_out();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
