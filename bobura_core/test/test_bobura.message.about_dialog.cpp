/*! \file
    \brief Test of class bobura::message::about_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/message/about_dialog.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::detail_type_list;

    using ui_type_list_type = bobura::ui_type_list<detail_type_list_type>;

    using dialog_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::dialog>::type;

    using window_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::window>::type;

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
BOOST_AUTO_TEST_SUITE(about_dialog)
BOOST_AUTO_TEST_SUITE(ok_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        const bobura::message::about_dialog::ok_button_mouse_clicked<dialog_type> observer{ dialog };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        const bobura::message::about_dialog::ok_button_mouse_clicked<dialog_type> observer{ dialog };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
