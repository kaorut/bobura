/*! \file
    \brief The definition of tetengo2::detail::windows::cursor.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_CURSOR_H)
#define TETENGO2_DETAIL_WINDOWS_CURSOR_H

#include <memory>
#include <stdexcept>
#include <system_error>
#include <type_traits>
#include <utility>

#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.detail.windows.error_category.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct cursor_deleter
        {
            void operator()(const ::HCURSOR cursor_handle)
            const
            {}


        };


    }
#endif

    /*!
        \brief The class for a detail implementation of a cursor.
    */
    class cursor
    {
    public:
        // types

        //! The cursor details type.
        typedef std::remove_pointer< ::HCURSOR>::type cursor_details_type;

        //! The cursor details pointer type.
        typedef
            std::unique_ptr<cursor_details_type, detail::cursor_deleter>
            cursor_details_ptr_type;


        // static functions

        /*!
            \brief Creates a system cursor.

            \tparam SystemCursor A system cursor type.

            \param style A style.

            \return A unique pointer to a system cursor.

            \throw std::system_error When a system cursor cannot be created.
        */
        template <typename SystemCursor>
        static cursor_details_ptr_type create_system_cursor(
            const typename SystemCursor::style_type style
        )
        {
            cursor_details_ptr_type p_cursor(
                reinterpret_cast< ::HCURSOR>(
                    ::LoadImageW(
                        0,
                        MAKEINTRESOURCEW(
                            translate_style<SystemCursor>(style)
                        ),
                        IMAGE_CURSOR,
                        0,
                        0,
                        LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                )
            );
            if (!p_cursor)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't create a system cursor."
                    )
                );
            }

            return std::move(p_cursor);
        }


    private:
        // static functions

        template <typename SystemCursor>
        static ::WORD translate_style(
            const typename SystemCursor::style_type style
        )
        {
            switch (style)
            {
            case SystemCursor::style_hand: return OCR_HAND;
            default: return OCR_NORMAL;
            }
        }


    };


}}}


#endif
