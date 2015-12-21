/*! \file
    \brief The definition of bobura::view::timetable::item.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_TIMETABLE_ITEM_H)
#define BOBURA_VIEW_TIMETABLE_ITEM_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>


namespace bobura { namespace view { namespace timetable
{
     /*!
        \brief The class template for the timetable view item.

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


        // constructors and destructor

        /*!
            \brief Creates an item.
        */
        item();

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


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const;


    };


}}}


#endif