/*! \file
    \brief The definition of bobura::view::diagram::time_line.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/time_line.h>
#include <bobura/view/diagram/utility.h>


namespace bobura::view::diagram {
    template <typename Traits>
    class time_line<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using size_type = typename traits_type::size_type;

        using canvas_type = typename traits_type::canvas_type;

        using color_type = typename time_line::color_type;

        using position_type = typename time_line::position_type;

        using position_unit_type = typename time_line::position_unit_type;

        using selection_type = typename time_line::selection_type;


        // constructors and destructor

        impl(
            selection_type&,
            position_unit_type                    left,
            position_unit_type                    top,
            position_unit_type                    bottom,
            color_type                            color,
            tetengo2::stdalt::optional<size_type> hours)
        : m_left{ std::move(left) }, m_top{ std::move(top) }, m_bottom{ std::move(bottom) },
          m_color{ std::move(color) }, m_hours{ std::move(hours) }
        {}

        impl(impl&& another)
        : m_left{ std::move(another.m_left) }, m_top{ std::move(another.m_top) },
          m_bottom{ std::move(another.m_bottom) }, m_color{ std::move(another.m_color) }, m_hours{ std::move(
                                                                                              another.m_hours) }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_left = std::move(another.m_left);
            m_top = std::move(another.m_top);
            m_bottom = std::move(another.m_bottom);
            m_color = std::move(another.m_color);
            m_hours = std::move(another.m_hours);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas) const
        {
            canvas.set_color(m_color);

            if (m_hours)
                canvas.draw_text(boost::lexical_cast<string_type>(*m_hours), position_type{ m_left, m_top });

            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.draw_line(position_type{ m_left, m_top }, position_type{ m_left, m_bottom });
        }


    private:
        // types

        using string_type = typename traits_type::string_type;


        // variables

        position_unit_type m_left;

        position_unit_type m_top;

        position_unit_type m_bottom;

        color_type m_color;

        tetengo2::stdalt::optional<size_type> m_hours;
    };


    template <typename Traits>
    time_line<Traits>::time_line(
        selection_type&                       selection,
        position_unit_type                    left,
        position_unit_type                    top,
        position_unit_type                    bottom,
        color_type                            color,
        tetengo2::stdalt::optional<size_type> hours)
    : base_type{ selection }, m_p_impl{ std::make_unique<impl>(
                                  selection,
                                  std::move(left),
                                  std::move(top),
                                  std::move(bottom),
                                  std::move(color),
                                  std::move(hours)) }
    {}

    template <typename Traits>
    time_line<Traits>::time_line(time_line&& another)
    : base_type{ another.get_selection() }, m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    time_line<Traits>::~time_line() noexcept
    {}

    template <typename Traits>
    time_line<Traits>& time_line<Traits>::operator=(time_line&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void time_line<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    template <typename Traits>
    class time_line_list<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using scale_type = typename traits_type::scale_type;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename time_line_list::position_type;

        using position_unit_type = typename time_line_list::position_unit_type;

        using dimension_type = typename time_line_list::dimension_type;

        using dimension_unit_type = typename time_line_list::dimension_unit_type;

        using selection_type = typename time_line_list::selection_type;

        using model_type = typename time_line_list::model_type;

        using time_span_type = typename time_line_list::time_span_type;


        // constructors and destructor

        impl(
            const model_type&          model,
            const time_span_type&      time_offset,
            selection_type&            selection,
            const dimension_type&      canvas_dimension,
            const dimension_type&      timetable_dimension,
            const position_type&       scroll_bar_position,
            const position_unit_type&  station_header_right,
            const position_unit_type&  header_bottom,
            const dimension_unit_type& time_header_height,
            const scale_type&          horizontal_scale)
        : m_p_font{ &*model.timetable().font_color_set().general().diagram_font() },
          m_p_color{ &*model.timetable().font_color_set().general().diagram_color() },
          m_p_background_color{ &*model.timetable().font_color_set().background().diagram_color() }, m_time_lines{
              make_time_lines(
                  time_offset,
                  selection,
                  canvas_dimension,
                  timetable_dimension,
                  scroll_bar_position,
                  station_header_right,
                  header_bottom,
                  time_header_height,
                  horizontal_scale)
          }
        {}

        impl(impl&& another)
        : m_p_font{ another.m_p_font }, m_p_color{ another.m_p_color },
          m_p_background_color{ another.m_p_background_color }, m_time_lines{ std::move(another.m_time_lines) }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_p_background_color = another.m_p_background_color;
            m_time_lines = std::move(another.m_time_lines);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas) const
        {
            canvas.set_font(*m_p_font);
            canvas.set_line_width(normal_line_width<dimension_unit_type>());

            for (const auto& time_line : m_time_lines)
                time_line.draw_on(canvas);
        }


    private:
        // types

        using size_type = typename traits_type::size_type;

        using font_type = typename time_line_list::font_type;

        using color_type = typename canvas_type::color_type;

        using time_type = typename time_line_list::time_type;

        using time_line_type = time_line<traits_type>;


        // static functions

        std::vector<time_line_type> make_time_lines(
            const time_span_type&      time_offset,
            selection_type&            selection,
            const dimension_type&      canvas_dimension,
            const dimension_type&      timetable_dimension,
            const position_type&       scroll_bar_position,
            const position_unit_type&  station_header_right,
            const position_unit_type&  header_bottom,
            const dimension_unit_type& time_header_height,
            const scale_type&          horizontal_scale)
        {
            const auto canvas_left = station_header_right;
            const auto canvas_right = position_unit_type::from(canvas_dimension.width());

            const auto canvas_top = header_bottom + position_unit_type::from(time_header_height);
            const auto canvas_bottom = position_unit_type::from(canvas_dimension.height());
            const auto station_position_bottom =
                position_unit_type::from(timetable_dimension.height()) + canvas_top - scroll_bar_position.top();
            const auto line_bottom = std::min(canvas_bottom, station_position_bottom);

            const auto horizontal_scale_left = position_unit_type::from(dimension_unit_type{ horizontal_scale });
            const auto minute_interval =
                time_to_left(
                    time_type{ 60 },
                    time_offset,
                    0,
                    position_unit_type{},
                    station_header_right,
                    horizontal_scale_left) -
                time_to_left(
                    time_type{ 0 }, time_offset, 0, position_unit_type{}, station_header_right, horizontal_scale_left);

            std::vector<time_line_type> time_lines{};
            time_lines.reserve(24 * 60);
            for (size_type i = 0; i <= 24 * 60; ++i)
            {
                const time_type time{ i * 60 + time_offset.seconds() };
                const auto      hours_minutes_seconds = time.hours_minutes_seconds();
                auto            hours = hours_minutes_seconds.hours();
                const auto      minutes = hours_minutes_seconds.minutes();
                assert(hours_minutes_seconds.seconds() == 0);

                auto position = time_to_left(
                    time,
                    time_offset,
                    i == 24 * 60,
                    scroll_bar_position.left(),
                    station_header_right,
                    horizontal_scale_left);
                if (position < canvas_left)
                    continue;
                if (position > canvas_right)
                    break;

                if (minutes == 0)
                {
                    time_lines.emplace_back(
                        selection,
                        std::move(position),
                        header_bottom,
                        line_bottom,
                        *m_p_color,
                        tetengo2::stdalt::make_optional(std::move(hours)));
                }
                else if (minutes % 10 == 0)
                {
                    if (minute_interval >= typename position_unit_type::value_type{ 4, 12 * 10 })
                    {
                        time_lines.emplace_back(
                            selection,
                            std::move(position),
                            canvas_top,
                            line_bottom,
                            m_p_color->mix(*m_p_background_color, 0.5),
                            TETENGO2_STDALT_NULLOPT);
                    }
                }
                else if (minutes % 2 == 0)
                {
                    if (minute_interval >= typename position_unit_type::value_type{ 4, 12 * 2 })
                    {
                        time_lines.emplace_back(
                            selection,
                            std::move(position),
                            canvas_top,
                            line_bottom,
                            m_p_color->mix(*m_p_background_color, 0.75),
                            TETENGO2_STDALT_NULLOPT);
                    }
                }
                else
                {
                    if (minute_interval >= typename position_unit_type::value_type{ 4, 12 })
                    {
                        time_lines.emplace_back(
                            selection,
                            std::move(position),
                            canvas_top,
                            line_bottom,
                            m_p_color->mix(*m_p_background_color, 0.75),
                            TETENGO2_STDALT_NULLOPT);
                    }
                }
            }
            time_lines.shrink_to_fit();

            return std::move(time_lines);
        }


        // variables

        const font_type* m_p_font;

        const color_type* m_p_color;

        const color_type* m_p_background_color;

        std::vector<time_line_type> m_time_lines;
    };


    template <typename Traits>
    time_line_list<Traits>::time_line_list(
        const model_type&          model,
        const time_span_type&      time_offset,
        selection_type&            selection,
        const dimension_type&      canvas_dimension,
        const dimension_type&      timetable_dimension,
        const position_type&       scroll_bar_position,
        const position_unit_type&  station_header_right,
        const position_unit_type&  header_bottom,
        const dimension_unit_type& time_header_height,
        const scale_type&          horizontal_scale)
    : base_type{ selection }, m_p_impl{ std::make_unique<impl>(
                                  model,
                                  time_offset,
                                  selection,
                                  canvas_dimension,
                                  timetable_dimension,
                                  scroll_bar_position,
                                  station_header_right,
                                  header_bottom,
                                  time_header_height,
                                  horizontal_scale) }
    {}

    template <typename Traits>
    time_line_list<Traits>::time_line_list(time_line_list&& another)
    : base_type{ another.get_selection() }, m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    time_line_list<Traits>::~time_line_list() noexcept
    {}

    template <typename Traits>
    time_line_list<Traits>& time_line_list<Traits>::operator=(time_line_list&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void time_line_list<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class time_line<typename application::traits_type_list_type::diagram_view_type>;

    template class time_line_list<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class time_line<typename test::traits_type_list_type::diagram_view_type>;

    template class time_line_list<typename test::traits_type_list_type::diagram_view_type>;
}
