/*! \file
    \brief Test of class bobura::about_dialog.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <vector>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/about_dialog.h>
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

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using settings_type =
        bobura::settings<
            string_type, ui_type_list_type::position_type, ui_type_list_type::dimension_type
        >;

    using about_dialog_type = bobura::about_dialog<traits_type_list_type::dialog_type>;


}


#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(about_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const settings_type settings{
            std::vector<string_type>{1, string_type{ TETENGO2_TEXT("bobura_core.test.exe") } },
            string_type{ TETENGO2_TEXT("test_bobura") }
        };
        const about_dialog_type about_dialog{ parent, message_catalog, settings };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
