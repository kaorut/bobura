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
#include <bobura/message/diagram_picture_box.h>
#include <bobura/message/diagram_view.h>
#include <bobura/message/file_property_dialog.h>
#include <bobura/message/font_color_dialog.h>
#include <bobura/message/main_window.h>
#include <bobura/message/oudia_diagram_dialog.h>
#include <bobura/message/property_bar.h>
#include <bobura/message/timetable_model.h>
#include <bobura/message/train_kind_dialog.h>
#include <bobura/message/type_list.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace message
{
    namespace timetable_model
    {
        /*!
            \brief The meta function for the type list of the timetable model messages.

            \tparam TimetableModel A timetable model type.
            \tparam DiagramView    A diagram view type.
            \tparam MainWindow     A main window type.
        */
        template <typename TimetableModel, typename DiagramView, typename MainWindow>
        using type_list =
            tetengo2::meta::assoc_list<boost::mpl::pair<type::reset, reset<TimetableModel, DiagramView, MainWindow>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::changed, changed<TimetableModel, DiagramView, MainWindow>>,
            tetengo2::meta::assoc_list_end
            >>;
    }

    namespace diagram_view
    {
        /*!
            \brief The meta function for the type list of the diagram view messages.

            \tparam Size              A size type.
            \tparam Difference        A difference type.
            \tparam String            A string type.
            \tparam Position          A position type.
            \tparam Dimension         A dimension type.
            \tparam OperatingDistance An operating distance type.
            \tparam Speed             A speed type.
            \tparam Font              A font type.
            \tparam AbstractWindow    An abstract window type.
            \tparam SideBar           A side bar type.
            \tparam MapBox            A map box type.
            \tparam MessageCatalog    A message catalog type.
            \tparam ConfigTraits      A configuration traits type.
        */
        template <
            typename Size,
            typename Difference,
            typename String,
            typename Position,
            typename Dimension,
            typename OperatingDistance,
            typename Speed,
            typename Font,
            typename AbstractWindow,
            typename SideBar,
            typename MapBox,
            typename MessageCatalog,
            typename ConfigTraits
        >
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::station_selected,
                    bobura::message::diagram_view::station_selected<
                        Size,
                        Difference,
                        String,
                        Position,
                        Dimension,
                        OperatingDistance,
                        Speed,
                        Font,
                        AbstractWindow,
                        SideBar,
                        MapBox,
                        ConfigTraits,
                        MessageCatalog
                    >
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::train_selected,
                    message::diagram_view::train_selected<
                        Size,
                        Difference,
                        String,
                        Position,
                        Dimension,
                        OperatingDistance,
                        Speed,
                        Font,
                        AbstractWindow,
                        SideBar,
                        MapBox,
                        ConfigTraits,
                        MessageCatalog
                    >
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::all_unselected,
                    message::diagram_view::all_unselected<
                        String,
                        Position,
                        Dimension,
                        AbstractWindow,
                        SideBar,
                        MapBox,
                        ConfigTraits,
                        MessageCatalog
                    >
                >,
            tetengo2::meta::assoc_list_end
            >>>;
    }

    namespace main_window
    {
        /*!
            \brief The meta function for the type list of the main window messages.

            \tparam PopupMenu         A popup menu type.
            \tparam CommandSet        A command set type.
            \tparam Command           A command type.
            \tparam Model             A model type.
            \tparam View              A view type.
            \tparam AbstractWindow    An abstract window type.
            \tparam DiagramPictureBox A diagram picture box type.
            \tparam PropertyBar       A property bar type.
            \tparam ConfirmFileSave   A file save confirmation type.
        */
        template <
            typename PopupMenu,
            typename CommandSet,
            typename Command,
            typename Model,
            typename View,
            typename AbstractWindow,
            typename DiagramPictureBox,
            typename PropertyBar,
            typename ConfirmFileSave
        >
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::popup_menu_selected, popup_menu_selected<PopupMenu, Command, Model>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::menu_command_selected, menu_command_selected<Command, Model, AbstractWindow>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::file_dropped, file_dropped<CommandSet, Model, AbstractWindow>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::window_resized, window_resized<View, AbstractWindow, DiagramPictureBox, PropertyBar>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::window_closing, window_closing<AbstractWindow, ConfirmFileSave>>,
            tetengo2::meta::assoc_list_end
            >>>>>;
    }

    namespace diagram_picture_box
    {
        /*!
            \brief The meta function for the type list of the diagram picture box messages.

            \tparam PictureBox     A picture box type.
            \tparam AbstractWindow An abstract window type.
            \tparam MouseCapture   A mouse capture type.
            \tparam ViewTraits     A view traits type.
        */
        template <typename PictureBox, typename AbstractWindow, typename MouseCapture, typename ViewTraits>
        using type_list =
            tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_pressed, mouse_pressed<PictureBox, ViewTraits>>,
            tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_released, mouse_released<PictureBox, ViewTraits>>,
            tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_moved, mouse_moved<PictureBox, ViewTraits>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::mouse_wheeled,
                    mouse_wheeled<
                        PictureBox,
                        view::diagram::zoom<ViewTraits, AbstractWindow, PictureBox, MouseCapture>,
                        ViewTraits
                    >
                >,
            tetengo2::meta::assoc_list<boost::mpl::pair<type::keyboard_key_down, keyboard_key_down<PictureBox>>,
            tetengo2::meta::assoc_list<boost::mpl::pair<type::paint_paint, paint_paint<PictureBox, ViewTraits>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::scroll_bar_scrolled, scroll_bar_scrolled<PictureBox, ViewTraits>>,
            tetengo2::meta::assoc_list_end
            >>>>>>>;
    }

    namespace property_bar
    {
        /*!
            \brief The meta function for the type list of the property bar messages.

            \tparam SideBar A side bar bar type.
            \tparam MapBox  A map box type.
        */
        template <typename SideBar, typename MapBox>
        using type_list =
            tetengo2::meta::assoc_list<boost::mpl::pair<type::resized, resized<SideBar, MapBox>>,
            tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_pressed, mouse_pressed<MapBox>>,
            tetengo2::meta::assoc_list_end
            >>;
    }

    namespace oudia_diagram_dialog
    {
        /*!
            \brief The meta function for the type list of the OuDia diagram dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list_end
            >>;
    }

    namespace file_property_dialog
    {
        /*!
            \brief The meta function for the type list of the file property dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list_end
            >>;
    }

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
