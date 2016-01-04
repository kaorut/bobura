/*! \file
    \brief Test of class bobura::property_bar.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <vector>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <bobura/property_bar.h>
#include <bobura/settings.h>
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

    using window_type = ui_type_list_type::window_type;

    using position_type = ui_type_list_type::position_type;

    using dimension_type = ui_type_list_type::dimension_type;

    using config_traits_type = traits_type_list_type::config_type;

    using settings_type = bobura::settings<string_type, position_type, dimension_type, config_traits_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using property_bar_type =
        bobura::property_bar<
            string_type,
            position_type,
            dimension_type,
            ui_type_list_type::abstract_window_type,
            ui_type_list_type::side_bar_type,
            ui_type_list_type::map_box_type,
            message_catalog_type,
            config_traits_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(property_bar)
    // test cases

// This test case causes a segmentation fault with GCC.
#if !( \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const message_catalog_type message_catalog{};
        const property_bar_type property_bar{ window, settings, message_catalog };

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(map_box)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type window{};
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
            const message_catalog_type message_catalog{};
            const property_bar_type property_bar{ window, settings, message_catalog };

            property_bar.map_box();

            settings.clear_config();
        }
        {
            window_type window{};
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
            const message_catalog_type message_catalog{};
            property_bar_type property_bar{ window, settings, message_catalog };

            property_bar.map_box();

            settings.clear_config();
        }
    }

    BOOST_AUTO_TEST_CASE(save_settings)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const message_catalog_type message_catalog{};
        property_bar_type property_bar{ window, settings, message_catalog };

        property_bar.save_settings();

        settings.clear_config();
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
