/*! \file
    \brief Test of class bobura::view::diagram::train_line.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/test/unit_test.hpp>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/view/diagram/train_line.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using font_type = ui_type_list_type::font_type;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;
    
    using train_type = model_type::timetable_type::train_type;

    using time_type = train_type::stop_type::time_type;

    using time_span_type = time_type::time_span_type;

    using train_kind_type = model_type::timetable_type::train_kind_type;

    using station_interval_calculator_type = model_type::timetable_type::station_interval_calculator_type;

    using station_intervals_type = station_interval_calculator_type::station_intervals_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using position_type = picture_box_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = picture_box_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using scale_type = common_type_list_type::scale_type;

    using window_type = ui_type_list_type::window_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using color_type = canvas_type::color_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using traits_type = traits_type_list_type::diagram_view_type;

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
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
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
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            false,
            message_catalog
        };
        train_line_fragment_type train_line_fragment2{
            train,
            42,
            selection,
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            true,
            message_catalog
        };
        train_line_fragment1 = std::move(train_line_fragment2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
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
        const train_line_fragment_type train_line_fragment{
            train,
            42,
            selection,
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            true,
            message_catalog
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        train_line_fragment.draw_on(*p_canvas);
    }

    BOOST_AUTO_TEST_CASE(p_item_by_position)
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
        const train_line_fragment_type train_line_fragment{
            train,
            42,
            selection,
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            true,
            message_catalog
        };

        {
            const position_type position{ position_unit_type{ 24 }, position_unit_type{ 42 } };
            BOOST_TEST(train_line_fragment.p_item_by_position(position) == &train_line_fragment);
        }
        {
            const position_type position{ position_unit_type{ 42 }, position_unit_type{ 42 } };
            BOOST_TEST(!train_line_fragment.p_item_by_position(position));
        }
    }

    BOOST_AUTO_TEST_CASE(selected)
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
        const train_line_fragment_type train_line_fragment{
            train,
            42,
            selection,
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            true,
            message_catalog
        };

        BOOST_TEST(!train_line_fragment.selected());
    }

    BOOST_AUTO_TEST_CASE(select)
    {
        BOOST_TEST_PASSPOINT();

        {
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
            train_line_fragment_type train_line_fragment{
                train,
                42,
                selection,
                position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
                position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
                true,
                message_catalog
            };

            train_line_fragment.select(false);

            BOOST_TEST(train_line_fragment.selected());
        }
        {
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
            train_line_fragment_type train_line_fragment{
                train,
                42,
                selection,
                position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
                position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
                true,
                message_catalog
            };

            train_line_fragment.select(true);

            BOOST_TEST(train_line_fragment.selected());
        }
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
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0x12, 0x34, 0x56 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0x78, 0x9A, 0xBC }
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
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
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
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0x12, 0x34, 0x56 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0x78, 0x9A, 0xBC }
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
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
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
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
            message_catalog
        };
        train_line1 = std::move(train_line2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const train_kind_type train_kind{
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("abbrev") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0x12, 0x34, 0x56 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0x78, 0x9A, 0xBC }
        };
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        const train_line_type train_line{
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
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
            message_catalog
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        train_line.draw_on(*p_canvas);
    }

    BOOST_AUTO_TEST_CASE(p_item_by_position)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const train_kind_type train_kind{
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("abbrev") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0x12, 0x34, 0x56 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0x78, 0x9A, 0xBC }
        };
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        const train_line_type train_line{
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
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
            message_catalog
        };

        const position_type position{ position_unit_type{ 24 }, position_unit_type{ 42 } };
        BOOST_TEST(!train_line.p_item_by_position(position));
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
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
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
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
            message_catalog
        };
        train_line_list_type train_line_list2{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
            message_catalog
        };

        train_line_list1 = std::move(train_line_list2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        const train_line_list_type train_line_list{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
            message_catalog
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        train_line_list.draw_on(*p_canvas);
    }

    BOOST_AUTO_TEST_CASE(p_item_by_position)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        const station_intervals_type station_intervals{ 2, station_interval_calculator_type::default_interval() };
        const message_catalog_type message_catalog{};
        const train_line_list_type train_line_list{
            model,
            time_span_type{ 42 * 60 },
            selection,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
            position_unit_type{ 24 },
            position_unit_type{ 42 },
            dimension_unit_type{ 24 },
            scale_type{ 42 },
            station_intervals,
            std::vector<position_unit_type>(2, position_unit_type{}),
            message_catalog
        };

        const position_type position{ position_unit_type{ 24 }, position_unit_type{ 42 } };
        BOOST_TEST(!train_line_list.p_item_by_position(position));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
