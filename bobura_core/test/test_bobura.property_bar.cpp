/*! \file
    \brief Test of class bobura::property_bar.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/property_bar.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using string_type = boost::mpl::at<bobura::common_type_list, bobura::type::string>::type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    using settings_type = boost::mpl::at<bobura::setting_type_list, bobura::type::setting::settings>::type;

    using message_catalog_type = boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using property_bar_type =
        bobura::property_bar<
            string_type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dimension>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::side_bar>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::map_box>::type,
            message_catalog_type,
            boost::mpl::at<bobura::setting_type_list, bobura::type::setting::config_traits>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(property_bar)
    // test cases

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


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
