/*! \file
    \brief The definition of bobura::view::diagram::station_line.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_STATIONLINE_H)
#define BOBURA_VIEW_DIAGRAM_STATIONLINE_H

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/range/adaptors.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/station_info/grade.h>
#include <bobura/view/diagram/item.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/view/diagram/utility.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a station line in the diagram view.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Canvas            A canvas type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Canvas
    >
    class station_line : public item<Size, Difference, String, OperatingDistance, Canvas>
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The left type.
        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        //! The top type.
        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The base type.
        using base_type = item<size_type, difference_type, string_type, operating_distance_type, canvas_type>;

        //! The selection type.
        using selection_type = selection<size_type, difference_type, string_type, operating_distance_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The station location type.
        using station_location_type = typename model_type::timetable_type::station_location_type;

        //! The font and color type.
        using font_color_type = typename model_type::timetable_type::font_color_set_type::font_color_type;


        // constructors and destructor

        /*!
            \brief Creates a station line.

            \param station_location     A station location.
            \param selection            A selection.
            \param right                A right position.
            \param station_header_right A station header right position.
            \param top                  A top position.
            \param font_color           A font and color.
        */
        station_line(
            const station_location_type& station_location,
            selection_type&              selection,
            const left_type&             right,
            const left_type&             station_header_right,
            top_type                     top,
            const font_color_type&       font_color
        )
        :
        base_type(selection),
        m_p_station_location(&station_location),
        m_right(right),
        m_station_header_right(station_header_right),
        m_top(std::move(top)),
        m_p_font_color(&font_color)
        {}

        /*!
            \brief Moves a station line.

            \param another Another station line.
        */
        station_line(station_line&& another)
        :
        base_type(another.get_selection()),
        m_p_station_location(another.m_p_station_location),
        m_right(std::move(another.m_right)),
        m_station_header_right(another.m_station_header_right),
        m_top(std::move(another.m_top)),
        m_p_font_color(another.m_p_font_color)
        {}

        /*!
            \brief Destroys the station line.
        */
        virtual ~station_line()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Assigns a station line.

            \param another Another station line.

            \return This station line.
        */
        station_line& operator=(station_line&& another)
        {
            if (&another == this)
                return *this;

            m_p_station_location = another.m_p_station_location;
            m_right = std::move(another.m_right);
            m_station_header_right = std::move(another.m_station_header_right);
            m_top = std::move(another.m_top);
            m_p_font_color = another.m_p_font_color;
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // variables

        const station_location_type* m_p_station_location;

        left_type m_right;

        left_type m_station_header_right;

        top_type m_top;

        const font_color_type* m_p_font_color;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override
        {
            canvas.set_font(m_p_font_color->font());
            canvas.set_color(m_p_font_color->color());

            draw_selectable_line(
                canvas, position_type{ left_type{ 0 }, m_top }, position_type{ m_right, m_top }, this->selected()
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

        virtual base_type* p_item_by_position_impl(const position_type& position)
        override
        {
            const auto& x = tetengo2::gui::position<position_type>::left(position);
            const auto& y = tetengo2::gui::position<position_type>::top(position);
            if (
                (left_type{ 0 } <= x && x <= m_station_header_right) &&
                (m_top - selected_line_margin<top_type>() <= y && y <= m_top + selected_line_margin<top_type>())
            )
            {
                return this;
            }
            else
            {
                return nullptr;
            }
        }

        virtual bool selected_impl()
        const override
        {
            return this->get_selection().selected(*m_p_station_location);
        }

        virtual void select_impl(const bool switch_selection_style)
        override
        {
            tetengo2::suppress_unused_variable_warning(switch_selection_style);

            this->get_selection().select(*m_p_station_location);
        }


    };


     /*!
        \brief The class template for a station line list in the diagram view.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Canvas            A canvas type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Canvas
    >
    class station_line_list : public item<Size, Difference, String, OperatingDistance, Canvas>
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The left type.
        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        //! The top type.
        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The width type.
        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        //! The height type.
        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        //! The horizontal scale type.
        using horizontal_scale_type = typename width_type::value_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The base type.
        using base_type = item<size_type, difference_type, string_type, operating_distance_type, canvas_type>;

        //! The selection type.
        using selection_type = selection<size_type, difference_type, string_type, operating_distance_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The time type.
        using time_type = typename model_type::timetable_type::train_type::stop_type::time_type;

        //! The time span type.
        using time_span_type = typename time_type::time_span_type;

        //! The station grade type set type.
        using station_grade_type_set_type = model::station_info::grade_type_set<string_type>;


        // constructors and destructor

        /*!
            \brief Creates a station line list.

            \param model                A model.
            \param time_offset          A time offset.
            \param selection            A selection.
            \param canvas_dimension     A canvas dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A right position of the station header.
            \param header_bottom        A bottom position of the header.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param station_positions    Station positions.
        */
        station_line_list(
            const model_type&            model,
            const time_span_type&        time_offset,
            selection_type&              selection,
            const dimension_type&        canvas_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const horizontal_scale_type& horizontal_scale,
            const std::vector<top_type>& station_positions
        )
        :
        base_type(selection),
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

        /*!
            \brief Moves a station line list.

            \param another Another station line list.
        */
        station_line_list(station_line_list&& another)
        :
        base_type(another.get_selection()),
        m_station_lines(std::move(another.m_station_lines))
        {}

        /*!
            \brief Destroys the station line list.
        */
        virtual ~station_line_list()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Assigns a station line list.

            \param another Another station line list.

            \return This station line list.
        */
        station_line_list& operator=(station_line_list&& another)
        {
            if (&another == this)
                return *this;

            m_station_lines = std::move(another.m_station_lines);
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // types

        using station_line_type =
            station_line<size_type, difference_type, string_type, operating_distance_type, speed_type, canvas_type>;

        using timetable_type = typename model_type::timetable_type;

        using font_color_set_type = typename timetable_type::font_color_set_type;

        using font_color_type = typename font_color_set_type::font_color_type;

        using station_location_type = typename timetable_type::station_location_type;

        using station_type = typename station_location_type::station_type;

        using station_grade_type = typename station_type::grade_type;

        using unit_size_type = typename canvas_type::unit_size_type;


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
            const horizontal_scale_type& horizontal_scale,
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


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override
        {
            canvas.set_line_width(normal_line_width<unit_size_type>());
            canvas.set_line_style(canvas_type::line_style_type::solid);

            for (const auto& station_line: m_station_lines)
                station_line.draw_on(canvas);
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        override
        {
            for (auto& station_line: boost::adaptors::reverse(m_station_lines))
            {
                auto* const p_item = station_line.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return nullptr;
        }


    };


}}}


#endif
