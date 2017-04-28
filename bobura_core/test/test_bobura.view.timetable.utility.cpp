/*! \file
    \brief Test of class bobura::view::timetable::utility.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/type_list.h>
#include <bobura/view/timetable/utility.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using canvas_type = ui_type_list_type::canvas_type;

    using unit_size_type = canvas_type::unit_size_type;


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(timetable)
    // test cases

    BOOST_AUTO_TEST_CASE(normal_line_width)
    {
        BOOST_TEST_PASSPOINT();

        bobura::view::timetable::normal_line_width<unit_size_type>();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
