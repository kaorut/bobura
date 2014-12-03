/*! \file
    \brief Test of class bobura::command::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/command/save_to_file.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using load_save_traits_type = traits_type_list_type::load_save_type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using save_to_file_command_type =
        bobura::command::save_to_file<traits_type_list_type::command_type, load_save_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(save_to_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const save_to_file_command_type command{ save_to_file };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
