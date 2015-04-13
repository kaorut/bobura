/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/view/diagram/item.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/timetable_model.h>


namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class diagram_view : private boost::noncopyable
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

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The item type.
        using item_type = view::diagram::item<traits_type>;

        //! The selection type.
        using selection_type = view::diagram::selection<traits_type>;

        //! The selection observer set type.
        using selection_observer_set_type = typename selection_type::selection_observer_set_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram view.

            \param model           A model.
            \param message_catalog A message catalog.
        */
        diagram_view(const model_type& model, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the diagram view.
        */
        ~diagram_view()
        TETENGO2_STDALT_NOEXCEPT;


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
            \brief Returns the horizontal scale.

            \return The horizontal scale.
        */
        const scale_type& horizontal_scale()
        const;

        /*!
            \brief Sets a horizontal scale.

            \param scale A horizontal scale.
        */
        void set_horizontal_scale(scale_type scale);

        /*!
            \brief Returns the vertical scale.

            \return The vertical scale.
        */
        const scale_type& vertical_scale()
        const;

        /*!
            \brief Sets a vertical scale.

            \param scale A vertical scale.
        */
        void set_vertical_scale(scale_type scale);

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
            \brief Returns a ponter to the item by the position.

            When position is in the region of an item, this function returns a pointer to the item.
            Otherwise, this function returns nullptr;

            \param position A position.

            \return A pointer to the item.
        */
        const item_type* p_item_by_position(const position_type& position)
        const;

        /*!
            \brief Returns a ponter to the item by the position.

            When position is in the region of an item, this function returns a pointer to the item.
            Otherwise, this function returns nullptr.

            \param position A position.

            \return A pointer to the item.
        */
        item_type* p_item_by_position(const position_type& position);

        /*!
            \brief Unselects all items.
        */
        void unselect_all_items();

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        const selection_observer_set_type& selection_observer_set()
        const;

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        selection_observer_set_type& selection_observer_set();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}


#endif
