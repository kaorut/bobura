/*! \file
    \brief The definition of tetengo2::gui::win32::label.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_LABEL_H)
#define TETENGO2_GUI_WIN32_LABEL_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.control.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a label for Win32 platforms.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class label : public control<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef control<typename traits_type::base_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;


        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.

            \throw std::runtime_error When a label cannot be created.
        */
        explicit label(widget_type& parent)
        :
        base_type(
            make_message_handler_map(message_handler_map_type()),
            create_window(parent)
        )
        {
            initialize(this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label()
        TETENGO2_NOEXCEPT
        {}


    private:
        // static functions

        static handle_type create_window(const widget_type& parent)
        {
            const handle_type handle = ::CreateWindowExW(
                0,
                L"Static",
                L"tetengo2::gui::win32::label",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE,
                0,
                0,
                64,
                64,
                parent.handle(),
                NULL,
                ::GetModuleHandle(NULL),
                NULL
            );
            if (handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a label!")
                );
            }

            return handle;
        }


        // functions

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            return map;
        }


    };


}}}

#endif