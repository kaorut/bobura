/*! \file
    \brief Test of class bobura::message::diagram_picture_box.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "bobura.type_list.h"

#include <bobura/message/diagram_picture_box.h>


namespace
{
    // types

    using canvas_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type;

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using message_catalog_type =
        boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using view_type = boost::mpl::at<bobura::view_type_list, bobura::type::view::view>::type;

    using position_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    using picture_box_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type;

    using mouse_observer_set_type = picture_box_type::mouse_observer_set_type;

    using mouse_button_type = mouse_observer_set_type::mouse_button_type;

    using mouse_pressed_type = bobura::message::diagram_picture_box::mouse_pressed<picture_box_type, view_type>;

    using mouse_released_type = bobura::message::diagram_picture_box::mouse_released<picture_box_type, view_type>;

    using mouse_moved_type = bobura::message::diagram_picture_box::mouse_moved<picture_box_type, view_type>;

    struct dummy_view_zoom_type
    {
    public:
        dummy_view_zoom_type(picture_box_type& picture_box, view_type& diagram_view)
        {
            tetengo2::suppress_unused_variable_warning(picture_box, diagram_view);
        }

        void horizontally_zoom_in(bool snap_to_scale_list)
        {
            tetengo2::suppress_unused_variable_warning(snap_to_scale_list);
        }

        void horizontally_zoom_out(bool snap_to_scale_list)
        {
            tetengo2::suppress_unused_variable_warning(snap_to_scale_list);
        }

        void vertically_zoom_in(bool snap_to_scale_list)
        {
            tetengo2::suppress_unused_variable_warning(snap_to_scale_list);
        }

        void vertically_zoom_out(bool snap_to_scale_list)
        {
            tetengo2::suppress_unused_variable_warning(snap_to_scale_list);
        }

    };

    using mouse_wheeled_type =
        bobura::message::diagram_picture_box::mouse_wheeled<picture_box_type, view_type, dummy_view_zoom_type>;

    using virtual_key_type = picture_box_type::keyboard_observer_set_type::virtual_key_type;

    using keyboard_key_down_type = bobura::message::diagram_picture_box::keyboard_key_down<picture_box_type>;

    using paint_paint_type =
        bobura::message::diagram_picture_box::paint_paint<canvas_type, picture_box_type, view_type>;

    using scroll_bar_scrolled_type =
        bobura::message::diagram_picture_box::scroll_bar_scrolled<picture_box_type, view_type>;


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
BOOST_AUTO_TEST_SUITE(diagram_picture_box)
BOOST_AUTO_TEST_SUITE(mouse_pressed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_pressed_type mouse_pressed(picture_box, set_mouse_capture, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_pressed_type mouse_pressed(picture_box, set_mouse_capture, view);

        mouse_pressed(mouse_button_type::left, position_type(left_type(24), top_type(42)), false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(mouse_released)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_released_type mouse_released(release_mouse_capture, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_released_type mouse_released(release_mouse_capture, view);

        mouse_released(mouse_button_type::left, position_type(left_type(24), top_type(42)), false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(mouse_moved)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        const view_type view(model, message_catalog);
        const mouse_moved_type mouse_moved(picture_box, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        const view_type view(model, message_catalog);
        const mouse_moved_type mouse_moved(picture_box, view);

        mouse_moved(position_type(left_type(24), top_type(42)), false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(mouse_wheeled)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_wheeled_type mouse_wheeled(picture_box, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_wheeled_type mouse_wheeled(picture_box, view);

        mouse_wheeled(42, mouse_observer_set_type::direction_type::vertical, false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(keyboard_key_down)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::none);
        const keyboard_key_down_type keyboard_key_down(picture_box);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::none);
        const keyboard_key_down_type keyboard_key_down(picture_box);

        keyboard_key_down(virtual_key_type::char_a(), false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(paint_paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::none);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const paint_paint_type paint(picture_box, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const paint_paint_type paint(picture_box, view);

        auto p_canvas = picture_box.create_canvas();
        paint(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(scroll_bar_scrolled)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const scroll_bar_scrolled_type scrolled(picture_box, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const scroll_bar_scrolled_type scrolled(picture_box, view);

        scrolled(42);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
