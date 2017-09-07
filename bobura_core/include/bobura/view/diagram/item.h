/*! \file
    \brief The definition of bobura::view::diagram::item.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_ITEM_H)
#define BOBURA_VIEW_DIAGRAM_ITEM_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <bobura/view/diagram/selection.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view item.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class item : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The selection type.
        using selection_type = selection<traits_type>;


        // constructors and destructor

        /*!
            \brief Creates an item.

            \param selection A selection.
        */
        explicit item(selection_type& selection);

        /*!
            \brief Destroys the item.
        */
        virtual ~item()
        noexcept;


        // functions

        /*!
            \brief Assigns an item.

            \param another Another item.

            \return This item.
        */
        item& operator=(item&& another);

        /*!
            \brief Draws this item on the canvas.

            \param canvas A canvas.
        */
        void draw_on(canvas_type& canvas)
        const;

        /*!
            \brief Returns a ponter to the item by the position.

            When position is in the region of this item or its child, this function returns a pointer to the item.
            Otherwise, this function returns nullptr;

            \param position A position.

            \return A pointer to the item.
        */
        item* p_item_by_position(const position_type& position);

        /*!
            \brief Returns a ponter to the item by the position.

            When position is in the region of this item or its child, this function returns a pointer to the item.
            Otherwise, this function returns nullptr;

            \param position A position.

            \return A pointer to the item.
        */
        const item* p_item_by_position(const position_type& position)
        const;

        /*!
            \brief Returns the selection.

            \return The selection.
        */
        const selection_type& get_selection()
        const;

        /*!
            \brief Returns the selection.

            \return The selection.
        */
        selection_type& get_selection();

        /*!
            \brief Returns the selected status.

            \return The selected status.
        */
        bool selected()
        const;

        /*!
            \brief Selects this item.

            \param switch_selection_style Specify true to switch the selection style.
        */
        void select(bool switch_selection_style);


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const;

        virtual item* p_item_by_position_impl(const position_type& position);

        virtual bool selected_impl()
        const;

        virtual void select_impl(bool switch_selection_style);


    };


}}}


#endif
