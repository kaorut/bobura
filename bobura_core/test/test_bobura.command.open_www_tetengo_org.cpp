/*! \file
    \brief Test of class bobura::command::open_www_tetengo_org.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/impl_set.h>

#include <bobura/command/open_www_tetengo_org.h>
#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using open_www_tetengo_org_command_type =
        bobura::command::open_www_tetengo_org<traits_type_list_type::command_type, ui_type_list_type::shell_type>;

    using detail_detail_impl_set_type = tetengo2::detail::stub::impl_set;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(command)
        BOOST_AUTO_TEST_SUITE(open_www_tetengo_org)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                const open_www_tetengo_org_command_type command{ detail_detail_impl_set_type::instance().shell_() };
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
