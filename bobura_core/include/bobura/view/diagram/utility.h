/*! \file
    \brief The definition of utilities for bobura::view::diagram.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_UTILITY_H)
#define BOBURA_VIEW_DIAGRAM_UTILITY_H

#include <vector>

namespace bobura::model::train_info {
    class time;

    class time_span;
}


namespace bobura::view::diagram {
    /*!
        \brief Calculates a horizontal position by a time.

        \tparam Left A left type.

        \param time                           A time.
        \param time_offset                    A time offset
        \param previous_or_next_day           Set -1 for previous day, 0 for today or +1 for next day.
        \param horizontal_scroll_bar_position A horizontal scroll bar position.
        \param station_header_right           The right position of a station header.
        \param horizontal_scale               A horizontal scale.

        \return The horizontal position.
    */
    template <typename Left>
    Left time_to_left(
        const model::train_info::time&      time,
        const model::train_info::time_span& time_offset,
        int                                 previous_or_next_day,
        const Left&                         horizontal_scroll_bar_position,
        const Left&                         station_header_right,
        const Left&                         horizontal_scale);

    /*!
        \brief Calculates a vertical position by a station index.

        \tparam Size A size type.
        \tparam Top  A top type.

        \param station_positions            Station positions.
        \param station_index                A station index.
        \param vertical_scroll_bar_position A vertical scroll bar position.
        \param header_bottom                A header bottom.
        \param time_header_bottom           A time header bottom.

        \return The vertical position.
    */
    template <typename Size, typename Top>
    Top station_index_to_top(
        const std::vector<Top>& station_positions,
        Size                    station_index,
        const Top&              vertical_scroll_bar_position,
        const Top&              header_bottom,
        const Top&              time_header_bottom);

    /*!
        \brief Returns the normal line width.

        \tparam Size A size type.

        \return The normal line width.
    */
    template <typename Size>
    Size normal_line_width();

    /*!
        \brief Returns the bold line width.

        \tparam Size A size type.

        \return The bold line width.
    */
    template <typename Size>
    Size bold_line_width();

    /*!
        \brief Returns the selected line margin.

        \tparam Size A size type.

        \return The selected line margin.
    */
    template <typename Size>
    Size selected_line_margin();

    /*!
        \brief Draws a selectable line.

        \tparam Canvas   A canvas type.
        \tparam Position A position type.

        \param canvas   A canvas.
        \param from     A start position.
        \param to       An end position.
        \param selected A selected status.
    */
    template <typename Canvas, typename Position>
    void draw_selectable_line(Canvas& canvas, const Position& from, const Position& to, bool selected);
}


#endif
