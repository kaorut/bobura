/*! \file
    \brief The definition of bobura::view::diagram::train_line.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TRAINLINE_H)
#define BOBURA_VIEW_DIAGRAM_TRAINLINE_H

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
        \brief The class template for a train line fragment in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_line_fragment : public item<Traits>
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

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The selection type.
        using selection_type = selection<traits_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The train type.
        using train_type = typename model_type::timetable_type::train_type;


        // constructors and destructor

        /*!
            \brief Creates a train line fragment.

            \param train                A train.
            \param departure_stop_index A departure stop index.
            \param selection            A selection.
            \param departure            A departure position.
            \param arrival              A arrival position.
            \param draw_train_name      Set true to draw the train name.
            \param message_catalog      A message catalog.
        */
        train_line_fragment(
            const train_type&           train,
            const size_type             departure_stop_index,
            selection_type&             selection,
            position_type               departure,
            position_type               arrival,
            const bool                  draw_train_name,
            const message_catalog_type& message_catalog
        );

        /*!
            \brief Moves a train line fragment.

            \param another Another train line fragment.
        */
        train_line_fragment(train_line_fragment&& another);

        /*!
            \brief Destroys the train line fragment.
        */
        virtual ~train_line_fragment()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Assigns a train line fragment.

            \param another Another train line fragment.

            \return This train line fraqment.
        */
        train_line_fragment& operator=(train_line_fragment&& another);


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

        virtual void select_impl(const bool switch_selection_style)
        override;


    };


     /*!
        \brief The class template for a train line in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_line : public item<Traits>
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

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The selection type.
        using selection_type = selection<traits_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The train type.
        using train_type = typename model_type::timetable_type::train_type;

        //! The time type.
        using time_type = typename train_type::stop_type::time_type;

        //! The time span type.
        using time_span_type = typename time_type::time_span_type;

        //! The train kind type.
        using train_kind_type = typename model_type::timetable_type::train_kind_type;

        //! The station intervals type.
        using station_intervals_type = typename model_type::timetable_type::station_intervals_type;


        // constructors and destructor

        /*!
            \brief Creates a train line.

            \param train                A train.
            \param train_kind           A train kind.
            \param time_offset          A time offet.
            \param selection            A selection.
            \param canvas_dimension     A canvas dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A station header right position.
            \param header_bottom        A header bottom position.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param station_intervals    Station intervals.
            \param station_positions    Station positions.
            \param message_catalog      A mesage catalog.
        */
        train_line(
            const train_type&             train,
            const train_kind_type&        train_kind,
            const time_span_type&         time_offset,
            selection_type&               selection,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const scale_type&             horizontal_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        );

        /*!
            \brief Moves a train line.

            \param another Another train line.
        */
        train_line(train_line&& another);

        /*!
            \brief Destroys the train line.
        */
        virtual ~train_line()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Assigns a train line.

            \param another Another train line.

            \return This train line.
        */
        train_line& operator=(train_line&& another);


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


    };


     /*!
        \brief The class template for a train line list in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_line_list : public item<Traits>
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

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The selection type.
        using selection_type = selection<traits_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The time type.
        using time_type = typename model_type::timetable_type::train_type::stop_type::time_type;

        //! The time span type.
        using time_span_type = typename time_type::time_span_type;

        //! The station intervals type.
        using station_intervals_type = typename model_type::timetable_type::station_intervals_type;


        // constructors and destructor

        /*!
            \brief Creates a train line list.

            \param model                A model.
            \param time_offset          A time offset.
            \param selection            A selection.
            \param canvas_dimension     A canvas dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A right position of the station header.
            \param header_bottom        A bottom position of the header.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param station_intervals    Station intervals.
            \param station_positions    Station positions.
            \param message_catalog      A message catalog.
        */
        train_line_list(
            const model_type&             model,
            const time_span_type&         time_offset,
            selection_type&               selection,
            const dimension_type&         canvas_dimension,
            const position_type&          scroll_bar_position,
            const left_type&              station_header_right,
            const top_type&               header_bottom,
            const height_type&            time_header_height,
            const scale_type&             horizontal_scale,
            const station_intervals_type& station_intervals,
            const std::vector<top_type>&  station_positions,
            const message_catalog_type&   message_catalog
        );

        /*!
            \brief Moves a train line list.

            \param another Another train line list.
        */
        train_line_list(train_line_list&& another);

        /*!
            \brief Destroys the train line list.
        */
        virtual ~train_line_list()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Assigns a train line list.

            \param another Another train line list.

            \return This train line list.
        */
        train_line_list& operator=(train_line_list&& another);


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


    };


}}}


#endif
