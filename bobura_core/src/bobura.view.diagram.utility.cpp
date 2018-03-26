/*! \file
    \brief The definition of utilities for bobura::view::diagram.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <vector>

#include <boost/predef.h>

#include <bobura/model/train_info/time.h> // IWYU pragma: keep
#include <bobura/model/train_info/time_span.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>


namespace bobura::view::diagram {
    template <typename Size, typename Difference, typename Left>
    Left time_to_left(
        const model::train_info::time<Size, Difference>& time,
        const model::train_info::time_span<Difference>&  time_offset,
        const int                                        previous_or_next_day,
        const Left&                                      horizontal_scroll_bar_position,
        const Left&                                      station_header_right,
        const Left&                                      horizontal_scale)
    {
        using time_span_type = model::train_info::time_span<Difference>;

        typename Left::value_type left_value(time.seconds_from_midnight());
        left_value -= time_offset.seconds();
        if (left_value < 0)
            left_value += time_span_type::seconds_of_whole_day();
        left_value += previous_or_next_day * time_span_type::seconds_of_whole_day();
        left_value /= 180;
        left_value *= horizontal_scale.value();
        return Left{ left_value } - horizontal_scroll_bar_position + station_header_right;
    }

    template <typename Size, typename Top>
    Top station_index_to_top(
        const std::vector<Top>& station_positions,
        const Size              station_index,
        const Top&              vertical_scroll_bar_position,
        const Top&              header_bottom,
        const Top&              time_header_bottom)
    {
        const auto canvas_top = header_bottom + time_header_bottom;
        return station_positions[station_index] + canvas_top - vertical_scroll_bar_position;
    }

    template <typename Size>
    Size normal_line_width()
    {
        return Size{ typename Size::value_type{ 1, 12 } };
    }

    template <typename Size>
    Size bold_line_width()
    {
        return Size{ typename Size::value_type{ 1, 6 } };
    }

    template <typename Size>
    Size selected_line_margin()
    {
        return Size{ typename Size::value_type{ 1, 3 } };
    }

    template <typename Canvas, typename Position>
    void draw_selectable_line(Canvas& canvas, const Position& from, const Position& to, const bool selected)
    {
        if (selected)
        {
            using color_type = typename Canvas::color_type;
            using line_style_type = typename Canvas::line_style_type;
            using dimension_unit_type = typename Canvas::dimension_unit_type;

            auto       original_color = canvas.get_color();
            const auto original_line_style = canvas.line_style();
            auto       original_line_width = canvas.line_width();

            canvas.set_color(color_type{ original_color.red(), original_color.green(), original_color.blue(), 0x30 });
            canvas.set_line_style(line_style_type::solid);

            canvas.set_line_width(original_line_width + selected_line_margin<dimension_unit_type>() * 2);
            canvas.draw_line(from, to);

            canvas.set_line_width(original_line_width + selected_line_margin<dimension_unit_type>());
            canvas.draw_line(from, to);

            canvas.set_color(std::move(original_color));
            canvas.set_line_style(original_line_style);
            canvas.set_line_width(std::move(original_line_width));
        }

        canvas.draw_line(from, to);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

            using position_type = application::traits_type_list_type::diagram_view_type::canvas_type::position_type;

            using position_unit_type = position_type::unit_type;

            using size_type = application::traits_type_list_type::diagram_view_type::size_type;

            using difference_type = application::traits_type_list_type::diagram_view_type::difference_type;

            using canvas_type = application::traits_type_list_type::diagram_view_type::canvas_type;

            using dimension_unit_type = canvas_type::dimension_unit_type;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

            using position_type = test::traits_type_list_type::diagram_view_type::canvas_type::position_type;

            using position_unit_type = position_type::unit_type;

            using size_type = test::traits_type_list_type::diagram_view_type::size_type;

            using difference_type = test::traits_type_list_type::diagram_view_type::difference_type;

            using canvas_type = test::traits_type_list_type::diagram_view_type::canvas_type;

            using dimension_unit_type = canvas_type::dimension_unit_type;
        }
    }

#if BOOST_COMP_MSVC
    template application::position_unit_type time_to_left(
        const model::train_info::time<application::size_type, application::difference_type>&,
        const model::train_info::time_span<application::difference_type>&,
        int,
        const application::position_unit_type&,
        const application::position_unit_type&,
        const application::position_unit_type&);

    template application::position_unit_type station_index_to_top(
        const std::vector<application::position_unit_type>&,
        application::size_type,
        const application::position_unit_type&,
        const application::position_unit_type&,
        const application::position_unit_type&);

    template application::dimension_unit_type normal_line_width();

    template application::dimension_unit_type bold_line_width();

    template application::position_unit_type selected_line_margin();

    template application::dimension_unit_type selected_line_margin();

    template void draw_selectable_line(
        application::canvas_type&,
        const application::position_type&,
        const application::position_type&,
        bool);
#endif

#if !defined(DOCUMENTATION)
    template test::position_unit_type time_to_left(
        const model::train_info::time<test::size_type, test::difference_type>&,
        const model::train_info::time_span<test::difference_type>&,
        int,
        const test::position_unit_type&,
        const test::position_unit_type&,
        const test::position_unit_type&);

    template test::position_unit_type station_index_to_top(
        const std::vector<test::position_unit_type>&,
        test::size_type,
        const test::position_unit_type&,
        const test::position_unit_type&,
        const test::position_unit_type&);

    template test::dimension_unit_type normal_line_width();

    template test::dimension_unit_type bold_line_width();

    template test::position_unit_type selected_line_margin();

    template test::dimension_unit_type selected_line_margin();

    template void
    draw_selectable_line(test::canvas_type&, const test::position_type&, const test::position_type&, bool);
#endif
}
