/*! \file
    \brief The definition of bobura::timetable_view.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_TIMETABLEVIEW_H)
#define BOBURA_TIMETABLEVIEW_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <bobura/timetable_model.h>
#include <bobura/view/timetable/utility.h>


namespace bobura
{
   /*!
        \brief The class template for a timetable view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class timetable_view : private boost::noncopyable
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

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;


        // constructors and destructor

        /*!
            \brief Creates a timetable view.

            \param direction       A direction.
            \param model           A model.
            \param message_catalog A message catalog.
        */
        timetable_view(
            view::timetable::direction_type direction,
            const model_type&               model,
            const message_catalog_type&     message_catalog
        );

        /*!
            \brief Destroys the timetable view.
        */
        ~timetable_view()
        noexcept;


        // functions

        /*!
            \brief Draws the view.

            \param canvas              A canvas.
            \param canvas_dimension    A canvas dimension.
            \param scroll_bar_position A scroll bar position.
        */
        void draw_on(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        );

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const;

        /*!
            \brief Update the dimension.
        */
        void update_dimension();

        /*!
            \brief Returns the page size.

            \param canvas_dimension A canvas dimension.

            \return The page size.
        */
        dimension_type page_size(const dimension_type& canvas_dimension)
        const;

        /*!
            \brief Unselects all items.
        */
        void unselect_all_items();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}


#endif
