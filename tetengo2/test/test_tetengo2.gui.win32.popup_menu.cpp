/*! \file
    \brief Test of class tetengo2::gui::win32::popup_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.popup_menu.h"

#include "test_tetengo2.gui.win32.popup_menu.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* popup_menu::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::popup_menu");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(is_command));
        p_suite->add(BOOST_TEST_CASE(is_popup));

        return p_suite;
    }

    void popup_menu::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void popup_menu::is_command()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void popup_menu::is_popup()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}
