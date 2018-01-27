/*! \file
    \brief The definition of bobura::view::diagram::time_line.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TIMELINE_H)
#define BOBURA_VIEW_DIAGRAM_TIMELINE_H

#include <memory>

#include <bobura/timetable_model.h>
#include <bobura/view/diagram/item.h>
#include <bobura/view/diagram/selection.h>

namespace boost
{
    template <class T> class optional;
}


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a time line in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class time_line : public item<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The dimension unit type.
        using dimension_unit_type = typename canvas_type::dimension_unit_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The position unit type.
        using position_unit_type = typename position_type::unit_type;

        //! The selection type.
        using selection_type = selection<traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a time line.

            \param selection A selection.
            \param left      A left position.
            \param top       A top position.
            \param bottom    A bottom position.
            \param width     A width.
            \param hours     Hours.
        */
        time_line(
            selection_type&            selection,
            position_unit_type         left,
            const position_unit_type&  top,
            const position_unit_type&  bottom,
            dimension_unit_type        width,
            boost::optional<size_type> hours
        );

        /*!
            \brief Moves a time line.

            \param another Another time line.
        */
        time_line(time_line&& another);

        /*!
            \brief Destroys the time line.
        */
        virtual ~time_line()
        noexcept;


        // functions

        /*!
            \brief Assigns a time line.

            \param another Another time line.

            \return This time line.
        */
        time_line& operator=(time_line&& another);


    private:
        // types

        using base_type = item<traits_type>;

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override;


    };


     /*!
        \brief The class template for a time line list in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class time_line_list : public item<Traits>
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

        //! The position unit type.
        using position_unit_type = typename position_type::unit_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The dimension unit type.
        using dimension_unit_type = typename dimension_type::unit_type;

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
            \brief Creates a time line list.

            \param model                A model.
            \param time_offset          A time offset.
            \param selection            A selection.
            \param canvas_dimension     A canvas dimension.
            \param timetable_dimension  A timetable dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A right position of the station header.
            \param header_bottom        A bottom position of the header.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
        */
        time_line_list(
            const model_type&          model,
            const time_span_type&      time_offset,
            selection_type&            selection,
            const dimension_type&      canvas_dimension,
            const dimension_type&      timetable_dimension,
            const position_type&       scroll_bar_position,
            const position_unit_type&  station_header_right,
            const position_unit_type&  header_bottom,
            const dimension_unit_type& time_header_height,
            const scale_type&          horizontal_scale
        );

        /*!
            \brief Moves a time line list.

            \param another Another time line list.
        */
        time_line_list(time_line_list&& another);

        /*!
            \brief Destroys the time line list.
        */
        virtual ~time_line_list()
        noexcept;


        // functions

        /*!
            \brief Assigns a time line list.

            \param another Another time line list.

            \return This time line list.
        */
        time_line_list& operator=(time_line_list&& another);


    private:
        // types

        using base_type = item<traits_type>;

        class impl;

        
        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override;


    };


}}}


#endif
