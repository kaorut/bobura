/*! \file
    \brief Test of class bobura::message::property_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/impl_set.h>

#include <bobura/detail_type_list.h>
#include <bobura/message/property_bar.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using window_type = ui_type_list_type::window_type;

    using side_bar_type = ui_type_list_type::side_bar_type;

    using detail_impl_set_type = tetengo2::detail::stub::impl_set;

    using map_box_type = ui_type_list_type::map_box_type;

    using resized_type = bobura::message::property_bar::resized<side_bar_type, map_box_type>;

    using mouse_pressed_type = bobura::message::property_bar::mouse_pressed<map_box_type>;

    using position_type = mouse_pressed_type::position_type;

    using position_unit_type = position_type::unit_type;

    using mouse_button_type = mouse_pressed_type::mouse_button_type;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(message)
        BOOST_AUTO_TEST_SUITE(property_bar)
            BOOST_AUTO_TEST_SUITE(resized)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type        window{};
                    side_bar_type      side_bar{ window, detail_impl_set_type::instance().cursor_() };
                    map_box_type       map_box{ side_bar, detail_impl_set_type::instance().cursor_() };
                    const resized_type observer(side_bar, map_box);
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type        window{};
                    side_bar_type      side_bar{ window, detail_impl_set_type::instance().cursor_() };
                    map_box_type       map_box{ side_bar, detail_impl_set_type::instance().cursor_() };
                    const resized_type observer(side_bar, map_box);

                    observer();
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(mouse_pressed)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type              window{};
                    side_bar_type            side_bar{ window, detail_impl_set_type::instance().cursor_() };
                    map_box_type             map_box{ side_bar, detail_impl_set_type::instance().cursor_() };
                    const mouse_pressed_type observer{ map_box };
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type              window{};
                    side_bar_type            side_bar{ window, detail_impl_set_type::instance().cursor_() };
                    map_box_type             map_box{ side_bar, detail_impl_set_type::instance().cursor_() };
                    const mouse_pressed_type observer{ map_box };

                    observer(
                        mouse_button_type::left,
                        position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
                        false,
                        false,
                        false);
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
