/*! \file
    \brief Test of class bobura::view::diagram::time_line.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/view/diagram/time_line.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using model_type =
        bobura::timetable_model<
            size_type,
            common_type_list_type::difference_type,
            common_type_list_type::string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using time_type = model_type::timetable_type::train_type::stop_type::time_type;

    using time_span_type = time_type::time_span_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using position_type = picture_box_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using scale_type = common_type_list_type::scale_type;

    using window_type = ui_type_list_type::window_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using unit_size_type = canvas_type::unit_size_type;

    using traits_type = traits_type_list_type::diagram_view_type;

    using selection_type = bobura::view::diagram::selection<traits_type>;

    using time_line_type = bobura::view::diagram::time_line<traits_type>;

    using time_line_list_type = bobura::view::diagram::time_line_list<traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(time_line)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        time_line_type time_line1{
            selection,
            left_type{ 42 },
            top_type{ 24 },
            top_type{ 42 },
            unit_size_type{ unit_size_type::value_type{ 1, 2 } },
            boost::make_optional<time_type::size_type>(12)
        };
        const time_line_type time_line2{ std::move(time_line1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        time_line_type time_line1{
            selection,
            left_type{ 42 },
            top_type{ 24 },
            top_type{ 42 },
            unit_size_type{ unit_size_type::value_type{ 1, 2 } },
            boost::make_optional<time_type::size_type>(12)
        };
        time_line_type time_line2{
            selection,
            left_type{ 42 },
            top_type{ 24 },
            top_type{ 42 },
            unit_size_type{ unit_size_type::value_type{ 1, 2 } },
            boost::make_optional<time_type::size_type>(12)
        };

        time_line1 = std::move(time_line2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const time_line_type time_line{
            selection,
            left_type{ 42 },
            top_type{ 24 },
            top_type{ 42 },
            unit_size_type{ unit_size_type::value_type{ 1, 2 } },
            boost::make_optional<time_type::size_type>(12)
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        time_line.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(time_line_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        time_line_list_type time_line_list1{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 }
        };
        const time_line_list_type time_line_list2{ std::move(time_line_list1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        time_line_list_type time_line_list1{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 }
        };
        time_line_list_type time_line_list2{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 }
        };

        time_line_list1 = std::move(time_line_list2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        const time_line_list_type time_line_list{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 }
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        time_line_list.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
