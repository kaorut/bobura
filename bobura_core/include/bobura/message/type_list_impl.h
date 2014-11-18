/*! \file
    \brief The definition of type lists for bobura::message.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELISTIMPL_H)
#define BOBURA_MESSAGE_TYPELISTIMPL_H

#include <boost/mpl/pair.hpp>

#include <tetengo2.h>

#include <bobura/message/about_dialog.h>
#include <bobura/message/font_color_dialog.h>
#include <bobura/message/train_kind_dialog.h>
#include <bobura/message/type_list.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace message
{
    namespace font_color_dialog
    {
        /*!
            \brief The meta function for the type list of the font and color dialog messages.

            \tparam Size           A size type.
            \tparam Dialog         A dialog type.
            \tparam ListBox        A list box type.
            \tparam Canvas         A canvas type.
            \tparam FontDialog     A font dialog type.
            \tparam ColorDialog    A color dialog type.
            \tparam MessageCatalog A message catalog type.
        */
        template <
            typename Size,
            typename Dialog,
            typename ListBox,
            typename Canvas,
            typename FontDialog,
            typename ColorDialog,
            typename MessageCatalog
        >
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::category_list_box_selection_changed, category_list_box_selection_changed<Size, ListBox>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::sample_picture_box_paint, sample_picture_box_paint<Size, Canvas, MessageCatalog>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::font_button_mouse_clicked,
                    font_button_mouse_clicked<Size, Dialog, FontDialog, Canvas, MessageCatalog>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::color_button_mouse_clicked,
                    color_button_mouse_clicked<Size, Dialog, ColorDialog, Canvas, MessageCatalog>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list_end
            >>>>>>;
    }

    namespace train_kind_dialog
    {
        /*!
            \brief The meta function for the type list of the train kind dialog messages.

            \tparam InfoSet        An information set type.
            \tparam Size           A size type.
            \tparam Dialog         A dialog type.
            \tparam ListBox        A list box type.
            \tparam Canvas         A canvas type.
            \tparam ColorDialog    A color dialog type.
            \tparam MessageCatalog A message catalog type.
        */
        template <
            typename InfoSet,
            typename Size,
            typename Dialog,
            typename ListBox,
            typename Canvas,
            typename ColorDialog,
            typename MessageCatalog
        >
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::train_kind_list_box_selection_changed, train_kind_list_box_selection_changed<Size, ListBox>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::add_button_mouse_clicked, add_button_mouse_clicked<InfoSet, Size, MessageCatalog>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::delete_button_mouse_clicked, delete_button_mouse_clicked<InfoSet, Size>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::up_button_mouse_clicked, up_button_mouse_clicked<InfoSet, Size>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::down_button_mouse_clicked, down_button_mouse_clicked<InfoSet, Size>>,
            tetengo2::meta::assoc_list<boost::mpl::pair<type::name_text_box_changed, name_text_box_changed>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::abbreviation_text_box_changed, abbreviation_text_box_changed>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::color_button_mouse_clicked, color_button_mouse_clicked<Dialog, ColorDialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::weight_dropdown_box_selection_changed, weight_dropdown_box_selection_changed>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::line_style_dropdown_box_selection_changed, line_style_dropdown_box_selection_changed
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::sample_picture_box_paint, sample_picture_box_paint<InfoSet, Size, Canvas>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list_end
            >>>>>>>>>>>>>;
    }

    namespace about_dialog
    {
        /*!
            \brief The meta function for the type list of the about dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list_end
            >;
    }


}}


#endif
