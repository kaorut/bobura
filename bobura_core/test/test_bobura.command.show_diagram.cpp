/*! \file
    \brief Test of class bobura::command::show_diagram.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/command/show_diagram.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using show_diagram_command_type =
        bobura::command::show_diagram<
            traits_type_list_type::command_type,
            traits_type_list_type::command_set_type,
            traits_type_list_type::main_window_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(show_diagram)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const show_diagram_command_type command{};
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
