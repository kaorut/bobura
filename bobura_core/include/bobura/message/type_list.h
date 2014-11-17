/*! \file
    \brief The definition of type lists for bobura::message.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELIST_H)
#define BOBURA_MESSAGE_TYPELIST_H


namespace bobura { namespace message
{
    namespace oudia_diagram_dialog
    {
        namespace type
        {
            //! The OK button mouse click observer type.
            struct ok_button_mouse_clicked;

            //! The cancel button mouse click observer type.
            struct cancel_button_mouse_clicked;

        }
    }

    namespace file_property_dialog
    {
        namespace type
        {
            //! The OK button mouse click observer type.
            struct ok_button_mouse_clicked;

            //! The cancel button mouse click observer type.
            struct cancel_button_mouse_clicked;

        }
    }

    namespace font_color_dialog
    {
        namespace type
        {
            //! The category list box selection change observer type.
            struct category_list_box_selection_changed;

            //! The sample picture box paint observer type.
            struct sample_picture_box_paint;

            //! The font button mouse click observer type.
            struct font_button_mouse_clicked;

            //! The color button mouse click observer type.
            struct color_button_mouse_clicked;

            //! The OK button mouse click observer type.
            struct ok_button_mouse_clicked;

            //! The cancel button mouse click observer type.
            struct cancel_button_mouse_clicked;

        }
    }

    namespace train_kind_dialog
    {
        namespace type
        {
            //! The train kind list box selection change observer type.
            struct train_kind_list_box_selection_changed;

            //! The add button mouse click observer type.
            struct add_button_mouse_clicked;

            //! The delete button mouse click observer type.
            struct delete_button_mouse_clicked;

            //! The up button mouse click observer type.
            struct up_button_mouse_clicked;

            //! The down button mouse click observer type.
            struct down_button_mouse_clicked;

            //! The name text box change observer type.
            struct name_text_box_changed;

            //! The abbreviation text box change observer type.
            struct abbreviation_text_box_changed;

            //! The color button mouse click observer type.
            struct color_button_mouse_clicked;

            //! The weight dropdown box selection change observer type.
            struct weight_dropdown_box_selection_changed;

            //! The line style dropdown box selection change observer type.
            struct line_style_dropdown_box_selection_changed;

            //! The sample picture box paint observer type.
            struct sample_picture_box_paint;

            //! The OK button mouse click observer type.
            struct ok_button_mouse_clicked;

            //! The cancel button mouse click observer type.
            struct cancel_button_mouse_clicked;

        }
    }

    namespace about_dialog
    {
        namespace type
        {
            //! The OK button mouse click observer type.
            struct ok_button_mouse_clicked;

        }
    }


}}


#endif
