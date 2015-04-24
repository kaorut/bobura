/*! \file
    \brief Test of class bobura::view::diagram::header.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/header.h>
#include <bobura/view/diagram/selection.h>


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

    using position_type = picture_box_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using traits_type = traits_type_list_type::diagram_view_type;

    using selection_type = bobura::view::diagram::selection<traits_type>;

    using company_line_name_header_type = bobura::view::diagram::company_line_name_header<traits_type>;

    using note_header_type = bobura::view::diagram::note_header<traits_type>;

    using header_type = bobura::view::diagram::header<traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(company_line_name_header)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        company_line_name_header_type header1{
            selection,
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        const company_line_name_header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        company_line_name_header_type header1{
            selection,
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        company_line_name_header_type header2{
            selection,
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

        selection_type selection{};
        const company_line_name_header_type header{
            selection,
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

        selection_type selection{};
        note_header_type header1{
            selection,
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

        selection_type selection{};
        note_header_type header1{
            selection,
            string_type{ TETENGO2_TEXT("hoge") },
            font_type::dialog_font(),
            color_type{ 12, 34, 56 },
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 24 }, height_type{ 42 } }
        };
        note_header_type header2{
            selection,
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

        selection_type selection{};
        const note_header_type header{
            selection,
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
        selection_type selection{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        header_type header1{ model, selection, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };
        const header_type header2{ std::move(header1) };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        header_type header1{ model, selection, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };
        header_type header2{ model, selection, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };

        header1 = std::move(header2);
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        const header_type header{ model, selection, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };

        header.dimension();
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        selection_type selection{};
        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        const header_type header{ model, selection, *p_canvas, dimension_type{ width_type{ 42 }, height_type{ 24 } } };

        header.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
