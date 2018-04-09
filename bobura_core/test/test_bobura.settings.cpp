/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cstddef>
#include <vector>

#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/settings.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using position_type = ui_type_list_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = ui_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using settings_type = bobura::settings<string_type, position_type, dimension_type>;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(settings)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(base_path)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            BOOST_CHECK(
                settings.base_path() == tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("path/to") } });

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(input)
        {
            BOOST_TEST_PASSPOINT();

            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                BOOST_TEST(!settings.input().is_initialized());

                settings.clear_config();
            }
            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") },
                                                          string_type{ TETENGO2_TEXT("input_file") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                BOOST_TEST_REQUIRE(settings.input().is_initialized());
                BOOST_CHECK(
                    *settings.input() ==
                    tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("input_file") } });

                settings.clear_config();
            }
        }

        BOOST_AUTO_TEST_CASE(message_directory_path)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            BOOST_CHECK(
                settings.message_directory_path() ==
                tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("path/to/messages") } });

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(image_directory_path)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            BOOST_CHECK(
                settings.image_directory_path() ==
                tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("path/to/images") } });

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(main_window_dimension)
        {
            BOOST_TEST_PASSPOINT();

            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                settings.main_window_dimension();

                settings.clear_config();
            }
            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") },
                                                          string_type{ TETENGO2_TEXT("--dimension=240x120") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                const auto dimension = settings.main_window_dimension();

                BOOST_TEST_REQUIRE(dimension.is_initialized());
                BOOST_TEST(dimension->width().to_pixels<std::size_t>() == 240U);
                BOOST_TEST(dimension->height().to_pixels<std::size_t>() == 120U);

                settings.clear_config();
            }
            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") },
                                                          string_type{ TETENGO2_TEXT("-d") },
                                                          string_type{ TETENGO2_TEXT("240x120") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                const auto dimension = settings.main_window_dimension();

                BOOST_TEST_REQUIRE(dimension.is_initialized());
                BOOST_TEST(dimension->width().to_pixels<std::size_t>() == 240U);
                BOOST_TEST(dimension->height().to_pixels<std::size_t>() == 120U);

                settings.clear_config();
            }
        }

        BOOST_AUTO_TEST_CASE(set_main_window_dimension)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.set_main_window_dimension(dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } });

            const auto dimension = settings.main_window_dimension();

            BOOST_TEST_REQUIRE(dimension.is_initialized());
            BOOST_CHECK(dimension->width() == dimension_unit_type{ 42 });
            BOOST_CHECK(dimension->height() == dimension_unit_type{ 24 });

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(main_window_maximized)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.main_window_maximized();

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(set_main_window_maximized)
        {
            BOOST_TEST_PASSPOINT();

            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                settings.set_main_window_maximized(false);

                const auto maximized = settings.main_window_maximized();

                BOOST_TEST_REQUIRE(maximized.is_initialized());
                BOOST_TEST(!*maximized);

                settings.clear_config();
            }
            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                settings.set_main_window_maximized(true);

                const auto maximized = settings.main_window_maximized();

                BOOST_TEST_REQUIRE(maximized.is_initialized());
                BOOST_TEST(*maximized);

                settings.clear_config();
            }
        }

        BOOST_AUTO_TEST_CASE(property_bar_width)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.property_bar_width();

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(set_property_bar_width)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.set_property_bar_width(dimension_unit_type{ 42 });

            const auto width = settings.property_bar_width();

            BOOST_TEST_REQUIRE(width.is_initialized());
            BOOST_CHECK(*width == dimension_unit_type{ 42 });

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(property_bar_minimized)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.property_bar_minimized();

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(set_property_bar_minimized)
        {
            BOOST_TEST_PASSPOINT();

            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                settings.set_property_bar_minimized(false);

                const auto minimized = settings.property_bar_minimized();

                BOOST_TEST_REQUIRE(minimized.is_initialized());
                BOOST_TEST(!*minimized);

                settings.clear_config();
            }
            {
                const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
                settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

                settings.set_property_bar_minimized(true);

                const auto minimized = settings.property_bar_minimized();

                BOOST_TEST_REQUIRE(minimized.is_initialized());
                BOOST_TEST(*minimized);

                settings.clear_config();
            }
        }

        BOOST_AUTO_TEST_CASE(property_bar_splitter_position)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.property_bar_splitter_position();

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(set_property_bar_splitter_position)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.set_property_bar_splitter_position(position_unit_type{ 42 });

            const auto position = settings.property_bar_splitter_position();

            BOOST_TEST_REQUIRE(position.is_initialized());
            BOOST_CHECK(*position == position_unit_type{ 42 });

            settings.clear_config();
        }

        BOOST_AUTO_TEST_CASE(clear_config)
        {
            BOOST_TEST_PASSPOINT();

            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type                  settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
            settings.set_main_window_maximized(true);

            settings.clear_config();

            BOOST_TEST(!settings.main_window_maximized());

            settings.clear_config();
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
