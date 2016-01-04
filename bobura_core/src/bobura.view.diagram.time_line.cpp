/*! \file
    \brief The definition of bobura::view::diagram::time_line.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/type_list.h>
#include <bobura/view/diagram/time_line.h>
#include <bobura/view/diagram/utility.h>


namespace bobura { namespace view { namespace diagram
{
    template <typename Traits>
    class time_line<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using size_type = typename traits_type::size_type;

        using canvas_type = typename traits_type::canvas_type;

        using unit_size_type = typename time_line::unit_size_type;

        using position_type = typename time_line::position_type;

        using left_type = typename time_line::left_type;

        using top_type = typename time_line::top_type;

        using selection_type = typename time_line::selection_type;


        // constructors and destructor

        impl(
            selection_type&,
            left_type                  left,
            const top_type&            top,
            const top_type&            bottom,
            unit_size_type             width,
            boost::optional<size_type> hours
        )
        :
        m_left(std::move(left)),
        m_top(top),
        m_bottom(bottom),
        m_width(std::move(width)),
        m_hours(std::move(hours))
        {}

        impl(impl&& another)
        :
        m_left(std::move(another.m_left)),
        m_top(std::move(another.m_top)),
        m_bottom(std::move(another.m_bottom)),
        m_width(std::move(another.m_width)),
        m_hours(another.m_hours)
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_left = std::move(another.m_left);
            m_top = std::move(another.m_top);
            m_bottom = std::move(another.m_bottom);
            m_width = std::move(another.m_width);
            m_hours = another.m_hours;

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            if (m_hours)
                canvas.draw_text(boost::lexical_cast<string_type>(*m_hours), position_type{ m_left, m_top });

            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.set_line_width(m_width);
            canvas.draw_line(position_type{ m_left, m_top }, position_type{ m_left, m_bottom });
        }


    private:
        // types

        using string_type = typename traits_type::string_type;


        // variables

        left_type m_left;

        top_type m_top;

        top_type m_bottom;

        unit_size_type m_width;

        boost::optional<size_type> m_hours;


    };


    template <typename Traits>
    time_line<Traits>::time_line(
        selection_type&            selection,
        left_type                  left,
        const top_type&            top,
        const top_type&            bottom,
        unit_size_type             width,
        boost::optional<size_type> hours
    )
    :
    base_type(selection),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(selection, left, top, bottom, width, hours))
    {}

    template <typename Traits>
    time_line<Traits>::time_line(time_line&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    time_line<Traits>::~time_line()
    noexcept
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
    void time_line<Traits>::draw_on_impl(canvas_type& canvas)
    const
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

        using left_type = typename time_line_list::left_type;

        using top_type = typename time_line_list::top_type;

        using dimension_type = typename time_line_list::dimension_type;

        using height_type = typename time_line_list::height_type;

        using selection_type = typename time_line_list::selection_type;

        using model_type = typename time_line_list::model_type;

        using time_span_type = typename time_line_list::time_span_type;


        // constructors and destructor

        impl(
            const model_type&     model,
            const time_span_type& time_offset,
            selection_type&       selection,
            const dimension_type& canvas_dimension,
            const dimension_type& timetable_dimension,
            const position_type&  scroll_bar_position,
            const left_type&      station_header_right,
            const top_type&       header_bottom,
            const height_type&    time_header_height,
            const scale_type&     horizontal_scale
        )
        :
        m_p_font(&model.timetable().font_color_set().time_line().font()),
        m_p_color(&model.timetable().font_color_set().time_line().color()),
        m_time_lines(
            make_time_lines(
                time_offset,
                selection,
                canvas_dimension,
                timetable_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale
            )
        )
        {}

        impl(impl&& another)
        :
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_time_lines(std::move(another.m_time_lines))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_time_lines = std::move(another.m_time_lines);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);

            for (const auto& time_line: m_time_lines)
                time_line.draw_on(canvas);
        }


    private:
        // types

        using size_type = typename traits_type::size_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using font_type = typename time_line_list::font_type;

        using color_type = typename canvas_type::color_type;

        using time_type = typename time_line_list::time_type;

        using time_line_type = time_line<traits_type>;

        using unit_size_type = typename canvas_type::unit_size_type;


        // static functions

        std::vector<time_line_type> make_time_lines(
            const time_span_type& time_offset,
            selection_type&       selection,
            const dimension_type& canvas_dimension,
            const dimension_type& timetable_dimension,
            const position_type&  scroll_bar_position,
            const left_type&      station_header_right,
            const top_type&       header_bottom,
            const height_type&    time_header_height,
            const scale_type&     horizontal_scale
        )
        {
            const auto canvas_left = station_header_right;
            const auto canvas_right =
                left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));

            const auto canvas_top = header_bottom + top_type::from(time_header_height);
            const auto canvas_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));
            const auto station_position_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(timetable_dimension)) +
                canvas_top -
                tetengo2::gui::position<position_type>::top(scroll_bar_position);
            const auto line_bottom = std::min(canvas_bottom, station_position_bottom);

            const auto horizontal_scale_left = left_type::from(width_type{ horizontal_scale });
            const auto minute_interval =
                time_to_left(
                    time_type{ 60 }, time_offset, 0, left_type{ 0 }, station_header_right, horizontal_scale_left
                ) -
                time_to_left(
                    time_type{ 0 }, time_offset, 0, left_type{ 0 }, station_header_right, horizontal_scale_left
                );

            std::vector<time_line_type> time_lines{};
            time_lines.reserve(24 * 60);
            for (size_type i = 0; i <= 24 * 60; ++i)
            {
                const time_type time{ i * 60 + time_offset.seconds() };
                const auto hours_minutes_seconds = time.hours_minutes_seconds();
                const auto hours = hours_minutes_seconds.hours();
                const auto minutes = hours_minutes_seconds.minutes();
                assert(hours_minutes_seconds.seconds() == 0);

                auto position =
                    time_to_left(
                        time,
                        time_offset,
                        i == 24 * 60,
                        tetengo2::gui::position<position_type>::left(scroll_bar_position),
                        station_header_right,
                        horizontal_scale_left
                    );
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
                        normal_line_width<unit_size_type>(),
                        boost::make_optional(hours)
                    );
                }
                else if (minutes % 10 == 0)
                {
                    if (minute_interval >= typename left_type::value_type{ 4, 12 * 10 })
                    {
                        time_lines.emplace_back(
                            selection,
                            std::move(position),
                            canvas_top,
                            line_bottom,
                            normal_line_width<unit_size_type>() / 2,
                            boost::none
                        );
                    }
                }
                else if (minutes % 2 == 0)
                {
                    if (minute_interval >= typename left_type::value_type{ 4, 12 * 2 })
                    {
                        time_lines.emplace_back(
                            selection,
                            std::move(position),
                            canvas_top,
                            line_bottom,
                            normal_line_width<unit_size_type>() / 4,
                            boost::none
                        );
                    }
                }
                else
                {
                    if (minute_interval >= typename left_type::value_type{ 4, 12 })
                    {
                        time_lines.emplace_back(
                            selection,
                            std::move(position),
                            canvas_top,
                            line_bottom,
                            normal_line_width<unit_size_type>() / 4,
                            boost::none
                        );
                    }
                }
            }
            time_lines.shrink_to_fit();

            return std::move(time_lines);
        }


        // variables

        const font_type* m_p_font;

        const color_type* m_p_color;

        std::vector<time_line_type> m_time_lines;


    };


    template <typename Traits>
    time_line_list<Traits>::time_line_list(
        const model_type&     model,
        const time_span_type& time_offset,
        selection_type&       selection,
        const dimension_type& canvas_dimension,
        const dimension_type& timetable_dimension,
        const position_type&  scroll_bar_position,
        const left_type&      station_header_right,
        const top_type&       header_bottom,
        const height_type&    time_header_height,
        const scale_type&     horizontal_scale
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            model,
            time_offset,
            selection,
            canvas_dimension,
            timetable_dimension,
            scroll_bar_position,
            station_header_right,
            header_bottom,
            time_header_height,
            horizontal_scale
        )
    )
    {}

    template <typename Traits>
    time_line_list<Traits>::time_line_list(time_line_list&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    time_line_list<Traits>::~time_line_list()
    noexcept
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
    void time_line_list<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }

        
    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
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


}}}
