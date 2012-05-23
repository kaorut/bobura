/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_CANVAS_H)
#define TETENGO2_GUI_DRAWING_CANVAS_H

//#include <cstddef>
#include <memory>
#include <stdexcept>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a canvas.

        \tparam Size            A size type.
        \tparam String          A string type.
        \tparam Position        A position type.
        \tparam Dimension       A dimension type.
        \tparam Encoder         An encoder type.
        \tparam Color           A color type.
        \tparam Background      A background type.
        \tparam SolidBackground A solid background type.
        \tparam Font            A font type.
        \tparam Picture         A picture type.
        \tparam DrawingDetails  A detail implementation type of a drawing.
    */
    template <
        typename Size,
        typename String,
        typename Position,
        typename Dimension,
        typename Encoder,
        typename Color,
        typename Background,
        typename SolidBackground,
        typename Font,
        typename Picture,
        typename DrawingDetails
    >
    class canvas : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The string type.
        typedef String string_type;

        //! The position type.
        typedef Position position_type;

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The color type.
        typedef Color color_type;

        //! The background type.
        typedef Background background_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;

        //! The font type.
        typedef Font font_type;

        //! The picture type.
        typedef Picture picture_type;

        //! The detail implementation type of a drawing.
        typedef DrawingDetails drawing_details_type;

        //! The detail implementation type.
        typedef typename drawing_details_type::canvas_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename drawing_details_type::canvas_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the canvas.
        */
        virtual ~canvas()
        {}


        // functions

        /*!
            \brief Returns the color.

            \return The color.
        */
        const color_type& color()
        const
        {
            return m_color;
        }

        /*!
            \brief Sets a color.

            \tparam C A color type.

            \param color A color.
        */
        template <typename C>
        void set_color(C&& color)
        {
            m_color = std::forward<C>(color);
        }

        /*!
            \brief Returns the background.

            \return The background.
        */
        const background_type& background()
        const
        {
            assert(m_p_background);
            return *m_p_background;
        }

        /*!
            \brief Sets a background.

            \param p_background A unique pointer to a background.
        */
        void set_background(std::unique_ptr<const background_type> p_background)
        {
            m_p_background = std::move(p_background);
        }

        /*!
            \brief Returns the font.

            \return The font.
        */
        const font_type& font()
        const
        {
            return m_font;
        }

        /*!
            \brief Sets a font.

            \tparam F A font type.

            \param font A font.
        */
        template <typename F>
        void set_font(F&& font)
        {
            m_font = std::forward<F>(font);
        }

        /*!
            \brief Draws a line.

            \tparam P A position type.

            \param from  A beginning position.
            \param to    An ending position.
            \param width A width.
        */
        template <typename P>
        void draw_line(const P& from, const P& to, const size_type width)
        {
            drawing_details_type::draw_line(*m_p_details, from, to, width, m_color);
        }

        /*!
            \brief Draws a focus indication.

            \tparam P A position type.
            \tparam D A dimension type.

            \param position  A position of a region.
            \param dimension A dimension of a region.
        */
        template <typename P, typename D>
        void draw_focus_indication(const P& position, const D& dimension)
        {
            drawing_details_type::draw_focus_indication(*m_p_details, position, dimension);
        }

        /*!
            \brief Fills a rectangle region.

            \tparam P A position type.
            \tparam D A dimension type.

            \param position   A position of a region.
            \param dimension  A dimension of a region.
        */
        template <typename P, typename D>
        void fill_rectangle(const P& position, const D& dimension)
        {
            assert(m_p_background);
            drawing_details_type::fill_rectangle(*m_p_details, position, dimension, *m_p_background);
        }

        /*!
            \brief Calculates the dimension of a text.

            \param text A text.

            \return The dimension of the text.
        */
        dimension_type calc_text_dimension(const string_type& text)
        const
        {
            return
                drawing_details_type::template calc_text_dimension<dimension_type>(
                    *m_p_details, m_font, text, encoder()
                );
        }

        /*!
            \brief Draws a text.

            \tparam P A position type.

            \param text     A text to draw.
            \param position A position where the text is drawn.
        */
        template <typename P>
        void draw_text(const string_type& text, const P& position)
        {
            drawing_details_type::draw_text(*m_p_details, m_font, text, encoder(), position, m_color);
        }

        /*!
            \brief Paints a picture.

            \tparam P A position type.
            \tparam D A dimension type.

            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.
        */
        template <typename P, typename D /* = typename P::dimension_type */>
        void paint_picture(
            const picture_type& picture,
            const P&            position,
            const D&            dimension /* = picture.dimension() */
        )
        {
            drawing_details_type::paint_picture(*m_p_details, picture, position, dimension);
        }

#if !defined(DOCUMENTATION)
        template <typename P>
        void paint_picture(const picture_type& picture, const P& position)
        {
            paint_picture(picture, position, picture.dimension());
        }
#endif

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<const details_type&> details()
        const
        {
            return boost::make_optional<const details_type&>(m_p_details.get(), *m_p_details);
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<details_type&> details()
        {
            return boost::make_optional<details_type&>(m_p_details.get(), *m_p_details);
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a canvas.

            The initial foreground color is black.
            The initial background is a solid white color background.
            The initlai font is a dialog font.

            \param p_details A detail implementation.

            \throw std::invalid_argument When p_details is NULL.
        */
        explicit canvas(details_ptr_type p_details)
        :
        m_p_details(std::move(p_details)),
        m_color(0, 0, 0, 255),
        m_p_background(make_unique<const solid_background_type>(color_type(255, 255, 255, 255))),
        m_font(font_type::dialog_font())
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION(std::invalid_argument("The detail implementation is NULL."));
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        const details_ptr_type m_p_details;

        color_type m_color;

        std::unique_ptr<const background_type> m_p_background;

        font_type m_font;


    };


}}}


#endif
