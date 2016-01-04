/*! \file
    \brief Test of class bobura::message::view_picture_box::timetable.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_view.h>
#include <bobura/message/view_picture_box/timetable.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using mouse_observer_set_type = picture_box_type::mouse_observer_set_type;

    using mouse_button_type = mouse_observer_set_type::mouse_button_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            common_type_list_type::string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using timetable_view_traits_type = traits_type_list_type::timetable_view_type;

    using timetable_view_type = bobura::timetable_view<timetable_view_traits_type>;

    using position_type = ui_type_list_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using window_type = ui_type_list_type::window_type;

    using mouse_pressed_type =
        bobura::message::view_picture_box::timetable::mouse_pressed<picture_box_type, timetable_view_traits_type>;

    using mouse_released_type =
        bobura::message::view_picture_box::timetable::mouse_released<picture_box_type, timetable_view_traits_type>;

    using mouse_moved_type =
        bobura::message::view_picture_box::timetable::mouse_moved<picture_box_type, timetable_view_traits_type>;

    using virtual_key_type = picture_box_type::keyboard_observer_set_type::virtual_key_type;

    using keyboard_key_down_type = bobura::message::view_picture_box::timetable::keyboard_key_down<picture_box_type>;

    using paint_paint_type =
        bobura::message::view_picture_box::timetable::paint_paint<picture_box_type, timetable_view_traits_type>;

    using scroll_bar_scrolled_type =
        bobura::message::view_picture_box::timetable::scroll_bar_scrolled<picture_box_type, timetable_view_traits_type>;


    // functions

    void set_mouse_capture(const mouse_button_type)
    {}

    bool release_mouse_capture(const mouse_button_type)
    {
        return false;
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(view_picture_box)
BOOST_AUTO_TEST_SUITE(timetable)
BOOST_AUTO_TEST_SUITE(mouse_pressed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::vertical };
        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const mouse_pressed_type mouse_pressed{ picture_box, set_mouse_capture, timetable_view };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::vertical };
        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const mouse_pressed_type mouse_pressed{ picture_box, set_mouse_capture, timetable_view };

        mouse_pressed(mouse_button_type::left, position_type{ left_type{ 24 }, top_type{ 42 } }, false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(mouse_released)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const mouse_released_type mouse_released{ release_mouse_capture, timetable_view };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const mouse_released_type mouse_released{ release_mouse_capture, timetable_view };

        mouse_released(mouse_button_type::left, position_type{ left_type{ 24 }, top_type{ 42 } }, false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(mouse_moved)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::vertical };
        const model_type model{};
        const message_catalog_type message_catalog{};
        const timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const mouse_moved_type mouse_moved{ picture_box, timetable_view };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::vertical };
        const model_type model{};
        const message_catalog_type message_catalog{};
        const timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const mouse_moved_type mouse_moved{ picture_box, timetable_view };

        mouse_moved(position_type{ left_type{ 24 }, top_type{ 42 } }, false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(mouse_wheeled)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        //window_type window{};
        //picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::vertical };
        //const model_type model{};
        //const message_catalog_type message_catalog{};
        //timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        //const mouse_wheeled_type mouse_wheeled{ picture_box, timetable_view };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        //window_type window{};
        //picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::vertical };
        //const model_type model{};
        //const message_catalog_type message_catalog{};
        //timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        //const mouse_wheeled_type mouse_wheeled{ picture_box, timetable_view };

        //mouse_wheeled(42, mouse_observer_set_type::direction_type::vertical, false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(keyboard_key_down)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::none };
        const keyboard_key_down_type keyboard_key_down{ picture_box };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::none };
        const keyboard_key_down_type keyboard_key_down{ picture_box };

        keyboard_key_down(virtual_key_type::char_a(), false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(paint_paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::none };
        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const paint_paint_type paint{ picture_box, timetable_view };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const paint_paint_type paint{ picture_box, timetable_view };

        auto p_canvas = picture_box.create_canvas();
        paint(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(scroll_bar_scrolled)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const scroll_bar_scrolled_type scrolled{ picture_box, timetable_view };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ timetable_view_type::direction_type::down, model, message_catalog };
        const scroll_bar_scrolled_type scrolled{ picture_box, timetable_view };

        scrolled(42);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
