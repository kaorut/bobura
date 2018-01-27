/*! \file
    \brief Test of class bobura::about_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/impl_set.h>
#include <tetengo2/text.h>

#include <bobura/about_dialog.h>
#include <bobura/detail_type_list.h>
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

    using detail_detail_impl_set_type = tetengo2::detail::stub::impl_set;


}


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
        const about_dialog_type about_dialog{ parent, message_catalog, settings, detail_detail_impl_set_type::instance() };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
