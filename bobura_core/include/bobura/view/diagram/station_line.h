/*! \file
    \brief The definition of bobura::view::diagram::station_line.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_STATIONLINE_H)
#define BOBURA_VIEW_DIAGRAM_STATIONLINE_H

#include <memory>
#include <vector>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/view/diagram/item.h>
#include <bobura/view/diagram/selection.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a station line in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class station_line : public item<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The left type.
        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        //! The top type.
        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The selection type.
        using selection_type = selection<traits_type>;

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
        );

        /*!
            \brief Moves a station line.

            \param another Another station line.
        */
        station_line(station_line&& another);

        /*!
            \brief Destroys the station line.
        */
        virtual ~station_line()
        noexcept;


        // functions

        /*!
            \brief Assigns a station line.

            \param another Another station line.

            \return This station line.
        */
        station_line& operator=(station_line&& another);


    private:
        // types

        using base_type = item<traits_type>;

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override;

        virtual base_type* p_item_by_position_impl(const position_type& position)
        override;

        virtual bool selected_impl()
        const override;

        virtual void select_impl(bool switch_selection_style)
        override;


    };


     /*!
        \brief The class template for a station line list in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class station_line_list : public item<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The scale type.
        using scale_type = typename traits_type::scale_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The left type.
        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        //! The top type.
        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The height type.
        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The selection type.
        using selection_type = selection<traits_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The time type.
        using time_type = typename model_type::timetable_type::train_type::stop_type::time_type;

        //! The time span type.
        using time_span_type = typename time_type::time_span_type;


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
            const scale_type&            horizontal_scale,
            const std::vector<top_type>& station_positions
        );

        /*!
            \brief Moves a station line list.

            \param another Another station line list.
        */
        station_line_list(station_line_list&& another);

        /*!
            \brief Destroys the station line list.
        */
        virtual ~station_line_list()
        noexcept;


        // functions

        /*!
            \brief Assigns a station line list.

            \param another Another station line list.

            \return This station line list.
        */
        station_line_list& operator=(station_line_list&& another);


    private:
        // types

        using base_type = item<traits_type>;

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override;

        virtual base_type* p_item_by_position_impl(const position_type& position)
        override;


    };


}}}


#endif
