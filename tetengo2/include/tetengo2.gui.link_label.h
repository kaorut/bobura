/*! \file
    \brief The definition of tetengo2::gui::link_label.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_LINKLABEL_H)
#define TETENGO2_GUI_LINKLABEL_H

#include <cassert>
#include <utility>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.label.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a link label.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a
                                      widget.
        \tparam MessageHandlerDetails A detail implementation type of a
                                      message handler.
   */
    template <
        typename Traits,
        typename WidgetDetails,
        typename MessageHandlerDetails
    >
    class link_label :
        public label<
            typename Traits::base_type, WidgetDetails, MessageHandlerDetails
        >
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            label<
                typename traits_type::base_type,
                widget_details_type,
                message_handler_details_type
            >
            base_type;

        //! The widget type.
        typedef typename base_type::base_type::base_type widget_type;

        //! The font type.
        typedef typename base_type::font_type font_type;

        //! The system cursor type.
        typedef typename base_type::system_cursor_type system_cursor_type;

        //! The cursor type.
        typedef typename base_type::cursor_type cursor_type;

        //! The color type.
        typedef typename base_type::color_type color_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a link label.

            \param parent A parent widget.

            \throw std::runtime_error When a link label cannot be created.
        */
        explicit link_label(widget_type& parent)
        :
        base_type(parent)
        {
            initialize(this);
        }

        /*!
            \brief Destroys the link label.
        */
        virtual ~link_label()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        // static functions

        static void initialize(link_label* const p_link_label)
        {
            assert(p_link_label);

            const font_type original_font = p_link_label->font();
            p_link_label->set_font(
                font_type(
                    original_font.family(),
                    original_font.size(),
                    original_font.bold(),
                    original_font.italic(),
                    true,
                    original_font.strikeout()
                )
            );

            p_link_label->set_text_color(color_type(0, 0, 255));

            typename cpp0x::unique_ptr<cursor_type>::type p_cursor(
                new system_cursor_type(system_cursor_type::style_hand)
            );
            p_link_label->set_cursor(std::move(p_cursor));
        }


    };


}}


#endif
