/*! \file
    \brief Test of class bobura::message::file_property_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include <bobura/message/file_property_dialog.h>


namespace
{
    // types

    using dialog_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dialog>::type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    class concrete_dialog : public dialog_type
    {
    public:
        explicit concrete_dialog(window_type::base_type& parent)
        :
        dialog_type(parent)
        {}

    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(file_property_dialog)
BOOST_AUTO_TEST_SUITE(ok_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::file_property_dialog::ok_button_mouse_clicked<dialog_type> observer(dialog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::file_property_dialog::ok_button_mouse_clicked<dialog_type> observer(dialog);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(cancel_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::file_property_dialog::cancel_button_mouse_clicked<dialog_type> observer(dialog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::file_property_dialog::cancel_button_mouse_clicked<dialog_type> observer(dialog);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
