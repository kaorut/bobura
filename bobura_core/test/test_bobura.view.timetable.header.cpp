/*! \file
    \brief Test of class bobura::view::timetable::header.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/header.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using traits_type = traits_type_list_type::timetable_view_type;

    using header_type = bobura::view::timetable::header<traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(timetable)
BOOST_AUTO_TEST_SUITE(header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        header_type header1{ model, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };
        const header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        header_type header1{ model, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };
        header_type header2{ model, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };

        header1 = std::move(header2);
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        const header_type header{ model, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };

        header.dimension();
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        const header_type header{ model, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };

        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
