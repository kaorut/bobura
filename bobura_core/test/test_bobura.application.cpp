/*! \file
    \brief Test of class bobura::application.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <vector>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/application.h>
#include <bobura/settings.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using settings_type =
        bobura::settings<
            string_type, ui_type_list_type::position_type, ui_type_list_type::dimension_type
        >;

    using application_type = bobura::application<traits_type_list_type::application_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(application)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        settings_type settings{
            std::vector<string_type>{1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
            string_type{ TETENGO2_TEXT("test_bobura") }
        };
        const application_type application{ settings };
    }

    BOOST_AUTO_TEST_CASE(run)
    {
        BOOST_TEST_PASSPOINT();

        settings_type settings{
            std::vector<string_type>{1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
            string_type{ TETENGO2_TEXT("test_bobura") }
        };
        application_type application{ settings };

        application.run();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
