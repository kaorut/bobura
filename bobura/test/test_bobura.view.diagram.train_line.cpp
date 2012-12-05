/*! \file
    \brief Test of class bobura::view::diagram::train_line.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.type_list.h"

#include "bobura.view.diagram.train_line.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef model_type::timetable_type::train_type train_type;

    typedef train_type::stop_type::time_type time_type;

    typedef time_type::time_span_type time_span_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type picture_box_type;

    typedef picture_box_type::position_type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef tetengo2::gui::position<position_type>::top_type top_type;

    typedef picture_box_type::dimension_type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    typedef width_type::value_type horizontal_scale_type;

    typedef height_type::value_type vertical_scale_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef bobura::view::diagram::train_line_fragment<canvas_type> train_line_fragment_type;

    typedef bobura::view::diagram::train_line<train_type, canvas_type> train_line_type;

    typedef
        bobura::view::diagram::train_line_list<model_type, canvas_type> train_line_list_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(train_line_fragment)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        train_line_fragment_type train_line_fragment1(left_type(42), top_type(24));
        const train_line_fragment_type train_line_fragment2(std::move(train_line_fragment1));
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        train_line_fragment_type train_line_fragment1(left_type(42), top_type(24));
        train_line_fragment_type train_line_fragment2(left_type(42), top_type(24));
        train_line_fragment1 = std::move(train_line_fragment2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_line)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        train_line_type train_line1(
            train_type(
                string_type(TETENGO2_TEXT("number")),
                0,
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("name_number")),
                string_type(TETENGO2_TEXT("note"))
            )
        );
        const train_line_type train_line2(std::move(train_line1));
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        train_line_type train_line1(
            train_type(
                string_type(TETENGO2_TEXT("number")),
                0,
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("name_number")),
                string_type(TETENGO2_TEXT("note"))
            )
        );
        train_line_type train_line2(
            train_type(
                string_type(TETENGO2_TEXT("number")),
                0,
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("name_number")),
                string_type(TETENGO2_TEXT("note"))
            )
        );
        train_line1 = std::move(train_line2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_line_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        train_line_list_type train_line_list1(
            model,
            time_span_type(42 * 60),
            *p_canvas,
            dimension_type(width_type(42), height_type(24)),
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            vertical_scale_type(24)
        );
        const train_line_list_type train_line_list2(std::move(train_line_list1));
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        train_line_list_type train_line_list1(
            model,
            time_span_type(42 * 60),
            *p_canvas,
            dimension_type(width_type(42), height_type(24)),
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            vertical_scale_type(24)
        );
        train_line_list_type train_line_list2(
            model,
            time_span_type(42 * 60),
            *p_canvas,
            dimension_type(width_type(42), height_type(24)),
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            vertical_scale_type(24)
        );

        train_line_list1 = std::move(train_line_list2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
