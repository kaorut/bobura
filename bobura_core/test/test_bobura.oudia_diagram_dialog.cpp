/*! \file
    \brief Test of class bobura::oudia_diagram_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(oudia_diagram_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(file_name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_file_name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(names)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_names)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(selected_index)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_selected_index)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
