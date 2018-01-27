/*! \file
    \brief Test of class bobura::view::timetable::train_number_header.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/train_number_header.h>
#include <bobura/view/timetable/utility.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

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

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using position_type = picture_box_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = picture_box_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using direction_type = bobura::view::timetable::direction_type;

    using traits_type = traits_type_list_type::timetable_view_type;

    using operating_distance_header_type = bobura::view::timetable::operating_distance_header<traits_type>;

    using train_number_description_header_type = bobura::view::timetable::train_number_description_header<traits_type>;

    using train_name_description_header_type = bobura::view::timetable::train_name_description_header<traits_type>;

    using train_number_header_type = bobura::view::timetable::train_number_header<traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(timetable)
BOOST_AUTO_TEST_SUITE(operating_distance_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        operating_distance_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };
        const operating_distance_header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        operating_distance_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };
        operating_distance_header_type header2{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };

        header2 = std::move(header1);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        operating_distance_header_type header{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };

        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_number_description_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        train_number_description_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };
        const train_number_description_header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        train_number_description_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };
        train_number_description_header_type header2{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };

        header2 = std::move(header1);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        train_number_description_header_type header{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };

        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_name_description_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        train_name_description_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };
        const train_name_description_header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        train_name_description_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };
        train_name_description_header_type header2{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };

        header2 = std::move(header1);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        train_name_description_header_type header{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 0x12, 0x34, 0x56 },
            position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 42 } }

        };

        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_number_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        train_number_header_type train_number_header1{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 1 }, dimension_unit_type{ 1 } },
            position_unit_type{ 2 },
            dimension_unit_type{ 3 },
            dimension_unit_type{ 4 },
            dimension_unit_type{ 1 },
            dimension_unit_type{ 5 }
        };
        const train_number_header_type train_number_header2{ std::move(train_number_header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        train_number_header_type train_number_header1{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 1 }, dimension_unit_type{ 1 } },
            position_unit_type{ 2 },
            dimension_unit_type{ 3 },
            dimension_unit_type{ 4 },
            dimension_unit_type{ 1 },
            dimension_unit_type{ 5 }
        };
        train_number_header_type train_number_header2{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 1 }, dimension_unit_type{ 1 } },
            position_unit_type{ 2 },
            dimension_unit_type{ 3 },
            dimension_unit_type{ 4 },
            dimension_unit_type{ 1 },
            dimension_unit_type{ 5 }
        };

        train_number_header1 = std::move(train_number_header2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        const train_number_header_type train_number_header{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            dimension_type{ dimension_unit_type{ 1 }, dimension_unit_type{ 1 } },
            position_unit_type{ 2 },
            dimension_unit_type{ 3 },
            dimension_unit_type{ 4 },
            dimension_unit_type{ 1 },
            dimension_unit_type{ 5 }
        };

        train_number_header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
