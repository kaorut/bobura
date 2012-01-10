/*! \file
    \brief Test of class tetengo2::gui::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.virtual_key.h"

#include "tetengo2.gui.virtual_key.h"


namespace
{
    // types

    typedef
        tetengo2::detail::stub::virtual_key<std::string>
        virtual_key_details_type;

    typedef
        tetengo2::gui::virtual_key<virtual_key_details_type>
        virtual_key_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(virtual_key)
    // test cases

    BOOST_AUTO_TEST_CASE(static_member_functions)
    {
        BOOST_TEST_PASSPOINT();

        virtual_key_type::backspace();
        virtual_key_type::tab();
        virtual_key_type::enter();
        virtual_key_type::shift();
        virtual_key_type::control();
        virtual_key_type::meta();
        virtual_key_type::escape();
        virtual_key_type::space();
        virtual_key_type::page_up();
        virtual_key_type::page_down();
        virtual_key_type::end();
        virtual_key_type::home();
        virtual_key_type::left();
        virtual_key_type::up();
        virtual_key_type::right();
        virtual_key_type::down();
        virtual_key_type::insert();
        virtual_key_type::del();
        virtual_key_type::char_0();
        virtual_key_type::char_1();
        virtual_key_type::char_2();
        virtual_key_type::char_3();
        virtual_key_type::char_4();
        virtual_key_type::char_5();
        virtual_key_type::char_6();
        virtual_key_type::char_7();
        virtual_key_type::char_8();
        virtual_key_type::char_9();
        virtual_key_type::char_a();
        virtual_key_type::char_b();
        virtual_key_type::char_c();
        virtual_key_type::char_d();
        virtual_key_type::char_e();
        virtual_key_type::char_f();
        virtual_key_type::char_g();
        virtual_key_type::char_h();
        virtual_key_type::char_i();
        virtual_key_type::char_j();
        virtual_key_type::char_k();
        virtual_key_type::char_l();
        virtual_key_type::char_m();
        virtual_key_type::char_n();
        virtual_key_type::char_o();
        virtual_key_type::char_p();
        virtual_key_type::char_q();
        virtual_key_type::char_r();
        virtual_key_type::char_s();
        virtual_key_type::char_t();
        virtual_key_type::char_u();
        virtual_key_type::char_v();
        virtual_key_type::char_w();
        virtual_key_type::char_x();
        virtual_key_type::char_y();
        virtual_key_type::char_z();
        virtual_key_type::f1();
        virtual_key_type::f2();
        virtual_key_type::f3();
        virtual_key_type::f4();
        virtual_key_type::f5();
        virtual_key_type::f6();
        virtual_key_type::f7();
        virtual_key_type::f8();
        virtual_key_type::f9();
        virtual_key_type::f10();
        virtual_key_type::f11();
        virtual_key_type::f12();
    }

    BOOST_AUTO_TEST_CASE(code)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK_EQUAL(
            virtual_key_type::backspace().code(),
            virtual_key_details_type::backspace().first
        );
        BOOST_CHECK_EQUAL(
            virtual_key_type::char_0().code(),
            virtual_key_details_type::char_0().first
        );
        BOOST_CHECK_EQUAL(
            virtual_key_type::char_a().code(),
            virtual_key_details_type::char_a().first
        );
        BOOST_CHECK_EQUAL(
            virtual_key_type::f1().code(),
            virtual_key_details_type::f1().first
        );
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(
            virtual_key_type::backspace().to_string() ==
            virtual_key_details_type::backspace().second
        );
        BOOST_CHECK(
            virtual_key_type::char_0().to_string() ==
            virtual_key_details_type::char_0().second
        );
        BOOST_CHECK(
            virtual_key_type::char_a().to_string() ==
            virtual_key_details_type::char_a().second
        );
        BOOST_CHECK(
            virtual_key_type::f1().to_string() ==
            virtual_key_details_type::f1().second
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
