/*! \file
    \brief The definition of tetengo2::gui::win32::canvas.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CANVAS_H)
#define TETENGO2_GUI_WIN32_CANVAS_H

#include <string>
#include <utility>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a canvas for Win32 platforms.

        \param Handle       A handle type for the native interface. It must
                            conform to tetengo2::gui::HandleConcept.
        \param Size         A size type. It must conform to
                            boost::IntegerConcept.
        \param WindowHandle A window handle type for the native interface. It
                            must conform to
                            tetengo2::gui::concpets::HandleConcept.
    */
    template <typename Handle, typename Size, typename WindowHandle>
    class canvas : private boost::noncopyable
    {
    public:
        // concept checks

        BOOST_CLASS_REQUIRE(Size, boost, IntegerConcept);


        // types

        //! The handle type for the native interface.
        typedef Handle handle_type;

        //! The size type.
        typedef Size size_type;

        //! The point type.
        typedef std::pair<size_type, size_type> point_type;

        //! The rectangle type.
        typedef std::pair<point_type, point_type> rectangle_type;

        //! The window handle type for the native interface.
        typedef WindowHandle window_handle_type;


        // constructors and destructor

        /*!
            \breif Creates a canvas object.

            \param window_handle A window handle.
        */
        canvas(const window_handle_type window_handle)
        :
        m_window_handle(window_handle),
        m_paint_info()
        {
            if (::BeginPaint(m_window_handle, &m_paint_info) == NULL)
                throw std::runtime_error("Can't begin paint!");
        }

        /*!
            \brief Destroys the canvas object.
        */
        ~canvas()
        throw ()
        {
            ::EndPaint(m_window_handle, &m_paint_info);
        }


        // functions

        /*!
            \brief Returns the handle.

            \return The handle.
        */
        handle_type handle()
        const
        {
            return m_paint_info.hdc;
        }

        /*!
            \brief Draws a text.

            \param text  A text to draw.
            \param point A point where the text is drawn.
        */
        void draw_text(const std::wstring& text, const point_type& point)
        const
        {
            const ::BOOL successful = ::TextOutW(
                this->handle(),
                static_cast<int>(point.first),
                static_cast<int>(point.second),
                text.c_str(),
                static_cast<int>(text.length())
            );
            if (successful == 0)
                throw std::runtime_error("Can't draw text!");
        }


    private:
        // variables

        const window_handle_type m_window_handle;

        ::PAINTSTRUCT m_paint_info;


    };
}}}

#endif
