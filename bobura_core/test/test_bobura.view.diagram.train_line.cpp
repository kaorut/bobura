/*! \file
    \brief Test of class bobura::view::diagram::train_line.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/view/diagram/train_line.h>


namespace
{
    // types

    using detail_type_list_type = bobura::detail_type_list_for_test;

    using common_type_list_type = bobura::common_type_list;

    using locale_type_list_type = bobura::locale_type_list<detail_type_list_type>;

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
    
    using train_type = model_type::timetable_type::train_type;

    using time_type = train_type::stop_type::time_type;

    using time_span_type = time_type::time_span_type;

    using train_kind_type = model_type::timetable_type::train_kind_type;

    using station_interval_calculator_type = model_type::timetable_type::station_interval_calculator_type;

    using station_intervals_type = station_interval_calculator_type::station_intervals_type;

    using picture_box_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::picture_box>::type;

    using position_type = picture_box_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using scale_type = boost::mpl::at<common_type_list_type, bobura::type::scale>::type;

    using canvas_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::canvas>::type;

    using color_type = canvas_type::color_type;

    using message_catalog_type = boost::mpl::at<locale_type_list_type, bobura::type::locale::message_catalog>::type;

    using traits_type = boost::mpl::at<traits_type_list_type, bobura::type::traits::view>::type;

    using selection_type = bobura::view::diagram::selection<traits_type>;

    using train_line_fragment_type = bobura::view::diagram::train_line_fragment<traits_type>;

    using train_line_type = bobura::view::diagram::train_line<traits_type>;

    using train_line_list_type = bobura::view::diagram::train_line_list<traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(train_line_fragment)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("number") },
            0,
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("name_number") },
            string_type{ TETENGO2_TEXT("note") }
        };
        selection_type selection{};
        const message_catalog_type message_catalog{};
        train_line_fragment_type train_line_fragment1{
            train,
            42,
            selection,
            position_type{ left_type{ 24 }, top_type{ 42 } },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            true,
            message_catalog
        };
        const train_line_fragment_type train_line_fragment2{ std::move(train_line_fragment1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("number") },
            0,
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("name_number") },
            string_type{ TETENGO2_TEXT("note") }
        };
        selection_type selection{};
        const message_catalog_type message_catalog{};
        train_line_fragment_type train_line_fragment1{
            train,
            42,
            selection,
            position_type{ left_type{ 24 }, top_type{ 42 } },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            false,
            message_catalog
        };
        train_line_fragment_type train_line_fragment2{
            train,
            42,
            selection,
            position_type{ left_type{ 24 }, top_type{ 42 } },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            true,
            message_catalog
        };
        train_line_fragment1 = std::move(train_line_fragment2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_line)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const train_kind_type train_kind{
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("abbrev") },
            color_type{ 0x12, 0x34, 0x56 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        train_line_type train_line1{
            train_type{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("number") },
                0,
                string_type{ TETENGO2_TEXT("name") },
                string_type{ TETENGO2_TEXT("name_number") },
                string_type{ TETENGO2_TEXT("note") }
            },
            train_kind,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<top_type>(2, top_type{ 0 }),
            message_catalog
        };
        const train_line_type train_line2{ std::move(train_line1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const train_kind_type train_kind{
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("abbrev") },
            color_type{ 0x12, 0x34, 0x56 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        train_line_type train_line1{
            train_type{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("number") },
                0,
                string_type{ TETENGO2_TEXT("name") },
                string_type{ TETENGO2_TEXT("name_number") },
                string_type{ TETENGO2_TEXT("note") }
            },
            train_kind,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<top_type>(2, top_type{ 0 }),
            message_catalog
        };
        train_line_type train_line2{
            train_type{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("number") },
                0,
                string_type{ TETENGO2_TEXT("name") },
                string_type{ TETENGO2_TEXT("name_number") },
                string_type{ TETENGO2_TEXT("note") }
            },
            train_kind,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<top_type>(2, top_type{ 0 }),
            message_catalog
        };
        train_line1 = std::move(train_line2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_line_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        train_line_list_type train_line_list1{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<top_type>(2, top_type{ 0 }),
            message_catalog
        };
        const train_line_list_type train_line_list2{ std::move(train_line_list1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        train_line_list_type train_line_list1{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<top_type>(2, top_type{ 0 }),
            message_catalog
        };
        train_line_list_type train_line_list2{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 24 }, top_type{ 42 } },
            left_type{ 24 },
            top_type{ 42 },
            height_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<top_type>(2, top_type{ 0 }),
            message_catalog
        };

        train_line_list1 = std::move(train_line_list2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()