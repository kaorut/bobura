/*! \file
    \brief Test of class bobura::view::diagram::station_line.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/view/diagram/station_line.h>


namespace
{
    // types

    using detail_type_list_type = bobura::detail_type_list;

    using common_type_list_type = bobura::common_type_list;

    using ui_type_list_type = bobura::ui_type_list<detail_type_list_type>;

    using traits_type_list_type = bobura::traits_type_list<detail_type_list_type>;

    using string_type = boost::mpl::at<common_type_list_type, bobura::type::string>::type;

    using model_type =
        bobura::timetable_model<
            boost::mpl::at<common_type_list_type, bobura::type::size>::type,
            boost::mpl::at<common_type_list_type, bobura::type::difference>::type,
            string_type,
            boost::mpl::at<common_type_list_type, bobura::type::operating_distance>::type,
            boost::mpl::at<common_type_list_type, bobura::type::speed>::type,
            boost::mpl::at<ui_type_list_type, bobura::type::ui::fast_font>::type
        >;

    using station_location_type = model_type::timetable_type::station_location_type;

    using station_type = station_location_type::station_type;

    using font_color_type = model_type::timetable_type::font_color_set_type::font_color_type;

    using train_type = model_type::timetable_type::train_type;

    using time_type = model_type::timetable_type::train_type::stop_type::time_type;

    using time_span_type = time_type::time_span_type;

    using picture_box_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::picture_box>::type;

    using position_type = picture_box_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using scale_type = boost::mpl::at<common_type_list_type, bobura::type::scale>::type;

    using canvas_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::canvas>::type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using traits_type = boost::mpl::at<traits_type_list_type, bobura::type::traits::view>::type;

    using selection_type = bobura::view::diagram::selection<traits_type>;

    using station_line_type = bobura::view::diagram::station_line<traits_type>;

    using station_line_list_type = bobura::view::diagram::station_line_list<traits_type>;

    using station_grade_type_set_type = station_line_list_type::station_grade_type_set_type;
    

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(station_line)
    // test cases

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        station_type station{
            string_type{ TETENGO2_TEXT("name") },
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type{ TETENGO2_TEXT("note") }
        };
        const station_location_type station_location{ std::move(station), 42 };
        selection_type selection{};
        station_line_type station_line1{
            station_location,
            selection,
            left_type{ 42 },
            left_type{ 12 },
            top_type{ 24 },
            font_color_type{ font_type::dialog_font(), color_type{ 12, 34, 56 } }
        };
        const station_line_type station_line2{ std::move(station_line1) };
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        station_type station1{
            string_type{ TETENGO2_TEXT("name1") },
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type{ TETENGO2_TEXT("note1") }
        };
        const station_location_type station_location1{ std::move(station1), 42 };
        selection_type selection{};
        station_line_type station_line1{
            station_location1,
            selection,
            left_type{ 42 },
            left_type{ 12 },
            top_type{ 24 },
            font_color_type{ font_type::dialog_font(), color_type{ 12, 34, 56 } }
        };
        station_type station2{
            string_type{ TETENGO2_TEXT("name2") },
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type{ TETENGO2_TEXT("note2") }
        };
        const station_location_type station_location2{ std::move(station2), 4242 };
        station_line_type station_line2{
            station_location2,
            selection,
            left_type{ 42 },
            left_type{ 12 },
            top_type{ 24 },
            font_color_type{ font_type::dialog_font(), color_type{ 12, 34, 56 } }
        };
        station_line1 = std::move(station_line2);
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(station_line_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        station_line_list_type station_line_list1{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            std::vector<top_type>(2, top_type{ 42 })
        };
        const station_line_list_type station_line_list2{ std::move(station_line_list1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        station_line_list_type station_line_list1{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            std::vector<top_type>(2, top_type{ 42 })
        };
        station_line_list_type station_line_list2{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            std::vector<top_type>(2, top_type{ 42 })
        };

        station_line_list1 = std::move(station_line_list2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
