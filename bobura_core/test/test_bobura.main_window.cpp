/*! \file
    \brief Test of class bobura::main_window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/main_window.h>
#include <bobura/settings.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using settings_type =
        bobura::settings<string_type, ui_type_list_type::position_type, ui_type_list_type::dimension_type>;

    using load_save_traits_type = traits_type_list_type::load_save_type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using confirm_file_save_type = bobura::load_save::confirm_file_save<load_save_traits_type>;

    using model_type = bobura::timetable_model<
        common_type_list_type::size_type,
        common_type_list_type::difference_type,
        string_type,
        common_type_list_type::operating_distance_type,
        common_type_list_type::speed_type,
        ui_type_list_type::fast_font_type>;

    using main_window_type =
        bobura::main_window<traits_type_list_type::main_window_type, traits_type_list_type::command_set_type>;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(main_window)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            const message_catalog_type message_catalog{};
            settings_type settings{ std::vector<string_type>{ 1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                    string_type{ TETENGO2_TEXT("test_bobura") } };
            model_type    model{};
            const save_to_file_type      save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const main_window_type       main_window{ message_catalog, settings, confirm_file_save };
        }

        BOOST_AUTO_TEST_CASE(set_title)
        {
            BOOST_TEST_PASSPOINT();

            const message_catalog_type message_catalog{};
            settings_type settings{ std::vector<string_type>{ 1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                    string_type{ TETENGO2_TEXT("test_bobura") } };
            model_type    model{};
            const save_to_file_type      save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            main_window_type             main_window{ message_catalog, settings, confirm_file_save };

            {
                main_window.set_title(TETENGO2_STDALT_NULLOPT, false);

                const auto expected = message_catalog.get(TETENGO2_TEXT("Common:Untitled")) +
                                      string_type{ TETENGO2_TEXT(" - ") } +
                                      message_catalog.get(TETENGO2_TEXT("App:Bobura"));
                BOOST_CHECK(main_window.text() == expected);
            }
            {
                main_window.set_title(TETENGO2_STDALT_NULLOPT, true);

                const auto expected = message_catalog.get(TETENGO2_TEXT("Common:Untitled")) +
                                      string_type{ TETENGO2_TEXT(" *") } + string_type{ TETENGO2_TEXT(" - ") } +
                                      message_catalog.get(TETENGO2_TEXT("App:Bobura"));
                BOOST_CHECK(main_window.text() == expected);
            }
            {
                main_window.set_title(tetengo2::stdalt::make_optional(string_type{ TETENGO2_TEXT("hoge") }), false);

                const auto expected = string_type{ TETENGO2_TEXT("hoge") } + string_type{ TETENGO2_TEXT(" - ") } +
                                      message_catalog.get(TETENGO2_TEXT("App:Bobura"));
                BOOST_CHECK(main_window.text() == expected);
            }
            {
                main_window.set_title(tetengo2::stdalt::make_optional(string_type{ TETENGO2_TEXT("hoge") }), true);

                const auto expected = string_type{ TETENGO2_TEXT("hoge") } + string_type{ TETENGO2_TEXT(" *") } +
                                      string_type{ TETENGO2_TEXT(" - ") } +
                                      message_catalog.get(TETENGO2_TEXT("App:Bobura"));
                BOOST_CHECK(main_window.text() == expected);
            }
        }

        BOOST_AUTO_TEST_CASE(get_tab_frame)
        {
            BOOST_TEST_PASSPOINT();

            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                const main_window_type       main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_tab_frame();
            }
            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                main_window_type             main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_tab_frame();
            }
        }

        BOOST_AUTO_TEST_CASE(show_diagram_tab)
        {
            BOOST_TEST_PASSPOINT();

            const message_catalog_type message_catalog{};
            settings_type settings{ std::vector<string_type>{ 1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                    string_type{ TETENGO2_TEXT("test_bobura") } };
            model_type    model{};
            const save_to_file_type      save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            main_window_type             main_window{ message_catalog, settings, confirm_file_save };

            main_window.show_diagram_tab();
        }

        BOOST_AUTO_TEST_CASE(show_timetable_down_tab)
        {
            BOOST_TEST_PASSPOINT();

            const message_catalog_type message_catalog{};
            settings_type settings{ std::vector<string_type>{ 1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                    string_type{ TETENGO2_TEXT("test_bobura") } };
            model_type    model{};
            const save_to_file_type      save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            main_window_type             main_window{ message_catalog, settings, confirm_file_save };

            main_window.show_timetable_down_tab();
        }

        BOOST_AUTO_TEST_CASE(show_timetable_up_tab)
        {
            BOOST_TEST_PASSPOINT();

            const message_catalog_type message_catalog{};
            settings_type settings{ std::vector<string_type>{ 1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                    string_type{ TETENGO2_TEXT("test_bobura") } };
            model_type    model{};
            const save_to_file_type      save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            main_window_type             main_window{ message_catalog, settings, confirm_file_save };

            main_window.show_timetable_up_tab();
        }

        BOOST_AUTO_TEST_CASE(get_diagram_view_picture_box)
        {
            BOOST_TEST_PASSPOINT();

            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                const main_window_type       main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_diagram_view_picture_box();
            }
            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                main_window_type             main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_diagram_view_picture_box();
            }
        }

        BOOST_AUTO_TEST_CASE(get_timetable_down_view_picture_box)
        {
            BOOST_TEST_PASSPOINT();

            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                const main_window_type       main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_timetable_down_view_picture_box();
            }
            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                main_window_type             main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_timetable_down_view_picture_box();
            }
        }

        BOOST_AUTO_TEST_CASE(get_timetable_up_view_picture_box)
        {
            BOOST_TEST_PASSPOINT();

            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                const main_window_type       main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_timetable_up_view_picture_box();
            }
            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                main_window_type             main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_timetable_up_view_picture_box();
            }
        }

        BOOST_AUTO_TEST_CASE(get_property_bar)
        {
            BOOST_TEST_PASSPOINT();

            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                const main_window_type       main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_property_bar();
            }
            {
                const message_catalog_type   message_catalog{};
                settings_type                settings{ std::vector<string_type>{
                                            1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
                                        string_type{ TETENGO2_TEXT("test_bobura") } };
                model_type                   model{};
                const save_to_file_type      save_to_file{ false, message_catalog };
                const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
                main_window_type             main_window{ message_catalog, settings, confirm_file_save };

                main_window.get_property_bar();
            }
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
