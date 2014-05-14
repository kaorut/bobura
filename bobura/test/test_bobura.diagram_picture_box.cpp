/*! \file
    \brief Test of class bobura::diagram_picture_box.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/measure.h>

#include "bobura.type_list.h"


namespace
{
    // types

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    using diagram_picture_box_type =
        boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::diagram_picture_box>::type;

    using dimension_type = diagram_picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using mouse_button_type = diagram_picture_box_type::mouse_button_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(diagram_picture_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const diagram_picture_box_type picture_box(window);
    }

    BOOST_AUTO_TEST_CASE(set_mouse_capture)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        diagram_picture_box_type picture_box(window);

        picture_box.set_mouse_capture(mouse_button_type::left);
        picture_box.release_mouse_capture(mouse_button_type::left);
    }

    BOOST_AUTO_TEST_CASE(release_mouse_capture)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type window;
            diagram_picture_box_type picture_box(window);

            const auto captured = picture_box.release_mouse_capture(mouse_button_type::left);

            BOOST_CHECK(!captured);
        }
        {
            window_type window;
            diagram_picture_box_type picture_box(window);

            picture_box.set_mouse_capture(mouse_button_type::left);
            const auto captured = picture_box.release_mouse_capture(mouse_button_type::left);

            BOOST_CHECK(captured);
        }
    }

    BOOST_AUTO_TEST_CASE(update_scroll_bars)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        diagram_picture_box_type picture_box(window);

        picture_box.update_scroll_bars(
            dimension_type(width_type(24), height_type(24)), dimension_type(width_type(42), width_type(42))
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
