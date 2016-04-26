/*! \file
    \brief The definition of bobura::view::timetable::train_number_header.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_TIMETABLE_TRAINNUMBERHEADER_H)
#define BOBURA_VIEW_TIMETABLE_TRAINNUMBERHEADER_H

#include <memory>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/view/timetable/item.h>
#include <bobura/view/timetable/utility.h>


namespace bobura { namespace view { namespace timetable
{
    /*!
        \brief The class template for a train number header in the timetable view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_number_header : public item<Traits>
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

        //! The top type.
        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The width type.
        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;


        // constructors and destructor

        /*!
            \brief Creates a train number header.

            \param direction              A direction.
            \param model                  A model.
            \param message_catalog        A message catalog.
            \param canvas                 A canvas.
            \param canvas_dimension       A canvas dimension.
            \param margin                 A margin.
            \param top                    A top.
            \param max_station_name_width A max station name width.
        */
        train_number_header(
            direction_type              direction,
            const model_type&           model,
            const message_catalog_type& message_catalog,
            canvas_type&                canvas,
            const dimension_type&       canvas_dimension,
            const dimension_type&       margin,
            const top_type&             top,
            const width_type&           max_station_name_width
        );

        /*!
            \brief Moves a train number header.

            \param another Another train number header
        */
        train_number_header(train_number_header&& another);

        /*!
            \brief Destroys the train number header.
        */
        virtual ~train_number_header()
        noexcept;


        // functions

        /*!
            \brief Assigns a train number header.

            \param another Another train number header.

            \return This train number header.
        */
        train_number_header& operator=(train_number_header&& another);

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const;


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
