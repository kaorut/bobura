/*! \file
    \brief Test of class bobura::command::about.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <vector>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/command/about.h>
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

    using position_type = ui_type_list_type::position_type;

    using dimension_type = ui_type_list_type::dimension_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using config_traits_type = traits_type_list_type::config_type;

    using settings_type = bobura::settings<string_type, position_type, dimension_type, config_traits_type>;

    using about_command_type =
        bobura::command::about<
            traits_type_list_type::command_type,
            position_type,
            dimension_type,
            message_catalog_type,
            traits_type_list_type::dialog_type,
            config_traits_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(about)
    // test cases

// This test case causes a segmentation fault with GCC.
#if !( \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog{};
        const settings_type settings{
            std::vector<string_type>{1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
            string_type{ TETENGO2_TEXT("test_bobura") }
        };
        const about_command_type command{ message_catalog, settings };
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
