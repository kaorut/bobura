/*! \file
    \brief The definition of bobura::view::diagram::station_line.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/range/adaptors.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/station_info/grade.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/station_line.h>
#include <bobura/view/diagram/utility.h>


namespace bobura { namespace view { namespace diagram
{
    template <typename Traits>
    class station_line<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using left_type = typename station_line::left_type;

        using top_type = typename station_line::top_type;

        using base_type = item<traits_type>;

        using selection_type = selection<traits_type>;

        using station_location_type = typename station_line::station_location_type;

        using font_color_type = typename station_line::font_color_type;


        // constructors and destructor

        impl(
            const station_location_type& station_location,
            selection_type&,
            const left_type&             right,
            const left_type&             station_header_right,
            top_type                     top,
            const font_color_type&       font_color
        )
        :
        m_p_station_location(&station_location),
        m_right(right),
        m_station_header_right(station_header_right),
        m_top(std::move(top)),
        m_p_font_color(&font_color)
        {}

        impl(impl&& another)
        :
        m_p_station_location(another.m_p_station_location),
        m_right(std::move(another.m_right)),
        m_station_header_right(another.m_station_header_right),
        m_top(std::move(another.m_top)),
        m_p_font_color(another.m_p_font_color)
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_station_location = another.m_p_station_location;
            m_right = std::move(another.m_right);
            m_station_header_right = std::move(another.m_station_header_right);
            m_top = std::move(another.m_top);
            m_p_font_color = another.m_p_font_color;

            return *this;
        }

        void draw_on_impl(const station_line& self, canvas_type& canvas)
        const
        {
            canvas.set_font(m_p_font_color->font());
            canvas.set_color(m_p_font_color->color());

            draw_selectable_line(
                canvas, position_type{ left_type{ 0 }, m_top }, position_type{ m_right, m_top }, self.selected()
            );

            const auto& name = m_p_station_location->get_station().name();
            const auto name_dimension = canvas.calc_text_dimension(name);
            canvas.draw_text(
                name,
                position_type{
                    left_type{ 0 },
                    m_top - top_type::from(tetengo2::gui::dimension<dimension_type>::height(name_dimension))
                }
            );
        }

        base_type* p_item_by_position_impl(station_line& self, const position_type& position)
        {
            const auto& x = tetengo2::gui::position<position_type>::left(position);
            const auto& y = tetengo2::gui::position<position_type>::top(position);
            if (
                (left_type{ 0 } <= x && x <= m_station_header_right) &&
                (m_top - selected_line_margin<top_type>() <= y && y <= m_top + selected_line_margin<top_type>())
            )
            {
                return &self;
            }
            else
            {
                return nullptr;
            }
        }

        bool selected_impl(const station_line& self)
        const
        {
            return self.get_selection().selected(*m_p_station_location);
        }

        void select_impl(station_line& self, const bool switch_selection_style)
        {
            boost::ignore_unused(switch_selection_style);

            self.get_selection().select(*m_p_station_location);
        }


    private:
        // types

        using dimension_type = typename canvas_type::dimension_type;

        using position_type = typename canvas_type::position_type;


        // variables

        const station_location_type* m_p_station_location;

        left_type m_right;

        left_type m_station_header_right;

        top_type m_top;

        const font_color_type* m_p_font_color;


    };


    template <typename Traits>
    station_line<Traits>::station_line(
        const station_location_type& station_location,
        selection_type&              selection,
        const left_type&             right,
        const left_type&             station_header_right,
        top_type                     top,
        const font_color_type&       font_color
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            station_location, selection, right, station_header_right, std::move(top), font_color
        )
    )
    {}

    template <typename Traits>
    station_line<Traits>::station_line(station_line&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    station_line<Traits>::~station_line()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits>
    station_line<Traits>& station_line<Traits>::operator=(station_line&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void station_line<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(*this, canvas);
    }

    template <typename Traits>
    typename station_line<Traits>::base_type* station_line<Traits>::p_item_by_position_impl(
        const position_type& position
    )
    {
        return m_p_impl->p_item_by_position_impl(*this, position);
    }

    template <typename Traits>
    bool station_line<Traits>::selected_impl()
    const
    {
        return m_p_impl->selected_impl(*this);
    }

    template <typename Traits>
    void station_line<Traits>::select_impl(const bool switch_selection_style)
    {
        m_p_impl->select_impl(*this, switch_selection_style);
    }

        
    template <typename Traits>
    class station_line_list<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using scale_type = typename traits_type::scale_type;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename station_line_list::position_type;

        using left_type = typename station_line_list::left_type;

        using top_type = typename station_line_list::top_type;

        using dimension_type = typename station_line_list::dimension_type;

        using height_type = typename station_line_list::height_type;

        using base_type = typename station_line_list::base_type;

        using selection_type = typename station_line_list::selection_type;

        using model_type = typename station_line_list::model_type;

        using time_span_type = typename station_line_list::time_span_type;


        // constructors and destructor

        impl(
            const model_type&            model,
            const time_span_type&        time_offset,
            selection_type&              selection,
            const dimension_type&        canvas_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const scale_type&            horizontal_scale,
            const std::vector<top_type>& station_positions
        )
        :
        m_station_lines(
            make_station_lines(
                model,
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                station_positions
            )
        )
        {}

        impl(impl&& another)
        :
        m_station_lines(std::move(another.m_station_lines))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_station_lines = std::move(another.m_station_lines);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_line_width(normal_line_width<unit_size_type>());
            canvas.set_line_style(canvas_type::line_style_type::solid);

            for (const auto& station_line: m_station_lines)
                station_line.draw_on(canvas);
        }

        base_type* p_item_by_position_impl(const position_type& position)
        {
            for (auto& station_line: boost::adaptors::reverse(m_station_lines))
            {
                auto* const p_item = station_line.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return nullptr;
        }


    private:
        // types

        using string_type = typename traits_type::string_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using time_type = typename station_line_list::time_type;

        using station_line_type = station_line<traits_type>;

        using timetable_type = typename model_type::timetable_type;

        using font_color_set_type = typename timetable_type::font_color_set_type;

        using font_color_type = typename font_color_set_type::font_color_type;

        using station_location_type = typename timetable_type::station_location_type;

        using station_type = typename station_location_type::station_type;

        using station_grade_type = typename station_type::grade_type;

        using unit_size_type = typename canvas_type::unit_size_type;

        using station_grade_type_set_type = model::station_info::grade_type_set<string_type>;


        // static functions

        static std::vector<station_line_type> make_station_lines(
            const model_type&            model,
            const time_span_type&        time_offset,
            selection_type&              selection,
            const dimension_type&        canvas_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const scale_type&            horizontal_scale,
            const std::vector<top_type>& station_positions
        )
        {
            const auto canvas_right =
                left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));
            const auto horizontal_scale_left = left_type::from(width_type{ horizontal_scale });
            const auto last_time_position =
                time_to_left(
                    time_type{ static_cast<typename time_type::size_type>(24 * 60 * 60 + time_offset.seconds()) },
                    time_offset,
                    1,
                    tetengo2::gui::position<position_type>::left(scroll_bar_position),
                    station_header_right,
                    horizontal_scale_left
                );
            const auto line_right = std::min(canvas_right, last_time_position);

            const auto canvas_top = header_bottom + top_type::from(time_header_height);
            const auto canvas_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));

            std::vector<station_line_type> station_lines{};
            station_lines.reserve(station_positions.size());
            for (decltype(station_positions.size()) i = 0; i < station_positions.size(); ++i)
            {
                const auto& position = station_positions[i];
                auto line_position =
                    position + canvas_top - tetengo2::gui::position<position_type>::top(scroll_bar_position);
                if (line_position < canvas_top)
                    continue;
                if (line_position > canvas_bottom)
                    break;

                const auto& station_location = model.timetable().station_locations()[i];
                station_lines.emplace_back(
                    station_location,
                    selection,
                    line_right,
                    station_header_right,
                    std::move(line_position),
                    select_station_font_color(
                        model.timetable().font_color_set(), station_location.get_station().grade()
                    )
                );
            }
            station_lines.shrink_to_fit();

            return std::move(station_lines);
        }

        static const font_color_type& select_station_font_color(
            const font_color_set_type& font_color_set,
            const station_grade_type&  grade
        )
        {
            if      (&grade == &station_grade_type_set_type::local_type::instance())
                return font_color_set.local_station();
            else if (&grade == &station_grade_type_set_type::principal_type::instance())
                return font_color_set.principal_station();
            else if (&grade == &station_grade_type_set_type::local_terminal_type::instance())
                return font_color_set.local_terminal_station();
            else if (&grade == &station_grade_type_set_type::principal_terminal_type::instance())
                return font_color_set.principal_terminal_station();

            assert(false);
            BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown station grade."));
        }


        // variables

        std::vector<station_line_type> m_station_lines;


    };


    template <typename Traits>
    station_line_list<Traits>::station_line_list(
        const model_type&            model,
        const time_span_type&        time_offset,
        selection_type&              selection,
        const dimension_type&        canvas_dimension,
        const position_type&         scroll_bar_position,
        const left_type&             station_header_right,
        const top_type&              header_bottom,
        const height_type&           time_header_height,
        const scale_type&            horizontal_scale,
        const std::vector<top_type>& station_positions
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            model,
            time_offset,
            selection,
            canvas_dimension,
            scroll_bar_position,
            station_header_right,
            header_bottom,
            time_header_height,
            horizontal_scale,
            station_positions
        )
    )
    {}

    template <typename Traits>
    station_line_list<Traits>::station_line_list(station_line_list&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    station_line_list<Traits>::~station_line_list()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits>
    station_line_list<Traits>& station_line_list<Traits>::operator=(station_line_list&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void station_line_list<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }

    template <typename Traits>
    typename station_line_list<Traits>::base_type* station_line_list<Traits>::p_item_by_position_impl(
        const position_type& position
    )
    {
        return m_p_impl->p_item_by_position_impl(position);
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
    template class station_line<typename application::traits_type_list_type::diagram_view_type>;

    template class station_line_list<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class station_line<typename test::traits_type_list_type::diagram_view_type>;

    template class station_line_list<typename test::traits_type_list_type::diagram_view_type>;


}}}
