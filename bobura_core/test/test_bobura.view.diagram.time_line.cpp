/*! \file
    \brief Test of class bobura::view::diagram::time_line.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/view/diagram/time_line.h>


namespace
{
    // types

    using size_type = boost::mpl::at<bobura::common_type_list, bobura::type::size>::type;

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using time_type = model_type::timetable_type::train_type::stop_type::time_type;

    using time_span_type = time_type::time_span_type;

    using picture_box_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type;

    using position_type = picture_box_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using scale_type = boost::mpl::at<bobura::view_type_list, bobura::type::view::scale>::type;

    using canvas_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type;

    using unit_size_type = canvas_type::unit_size_type;

    using traits_type = boost::mpl::at<bobura::view_type_list, bobura::type::view::traits>::type;

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


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
