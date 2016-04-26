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

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using direction_type = bobura::view::timetable::direction_type;

    using traits_type = traits_type_list_type::timetable_view_type;

    using company_name_header_type = bobura::view::timetable::company_name_header<traits_type>;

    using line_name_header_type = bobura::view::timetable::line_name_header<traits_type>;

    using note_header_type = bobura::view::timetable::note_header<traits_type>;

    using header_type = bobura::view::timetable::header<traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(timetable)
BOOST_AUTO_TEST_SUITE(company_name_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        company_name_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        const company_name_header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        company_name_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        company_name_header_type header2{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };

        header1 = std::move(header2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const company_name_header_type header{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(line_name_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        line_name_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        const line_name_header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        line_name_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        line_name_header_type header2{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };

        header1 = std::move(header2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const line_name_header_type header{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(note_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        note_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        const note_header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        note_header_type header1{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        note_header_type header2{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };

        header1 = std::move(header2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const note_header_type header{
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        header_type header1{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 1 }, height_type{ 1 } }
        };
        const header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        header_type header1{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 1 }, height_type{ 1 } }
        };
        header_type header2{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 1 }, height_type{ 1 } }
        };

        header1 = std::move(header2);
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        const header_type header{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 1 }, height_type{ 1 } }
        };

        header.dimension();
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        const header_type header{
            direction_type::down,
            model,
            message_catalog,
            *p_canvas,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            dimension_type{ width_type{ 1 }, height_type{ 1 } }
        };

        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
