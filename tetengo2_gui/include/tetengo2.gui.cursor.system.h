/*! \file
    \brief The definition of tetengo2::gui::cursor::system.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_SYSTEMCURSOR_H)
#define TETENGO2_GUI_CURSOR_SYSTEMCURSOR_H

//#include <boost/optional.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.cursor.cursor_base.h"


namespace tetengo2 { namespace gui { namespace cursor
{
    /*!
        \brief The class template for a system cursor.

        \tparam CursorDetails A detail implementation type of a cursor.
    */
    template <typename CursorDetails>
    class system : public cursor_base<CursorDetails>
    {
    public:
        // types

        //! The detail implemetation type of a cursor.
        typedef CursorDetails cursor_details_type;

        //! The base type.
        typedef cursor_base<cursor_details_type> base_type;

        //! The detail implementation type.
        typedef
            typename cursor_details_type::cursor_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename cursor_details_type::cursor_details_ptr_type
            details_ptr_type;

        //! The style type.
        enum style_type
        {
            style_default, //!< A default style.
            style_hand,    //!< A hand style.
        };


        // constructors and destructor

        /*!
            \brief Creates a system cursor.

            \param style A style.
        */
        explicit system(const style_type style)
        :
        m_style(style),
        m_p_details(
            cursor_details_type::template create_system_cursor<system>(
                style
            )
        )
        {}

        /*!
            \brief Destroys the system cursor.
        */
        virtual ~system()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        style_type style()
        const
        {
            return m_style;
        }


    private:
        // variables

        style_type m_style;

        details_ptr_type m_p_details;


        // virtual functions

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return *m_p_details;
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return *m_p_details;
        }


    };


}}}


#endif