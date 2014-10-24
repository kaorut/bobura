/*! \file
    \brief The definition of bobura::application_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_APPLICATIONTRAITS_H)
#define BOBURA_APPLICATIONTRAITS_H


namespace bobura
{
   /*!
        \brief The class template for an application traits.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam Position          A position type.
        \tparam Dimension         A dimension type.
        \tparam OperatingDistance A string type.
        \tparam Spped             A string type.
        \tparam Scale             A scale type.
        \tparam GuiFixture        A GUI fixture type.
        \tparam Font              A font type.
        \tparam AbstractWindow    An abstract window type.
        \tparam PictureBox        A picture box type.
        \tparam MapBox            A map box type.
        \tparam SideBar           A side bar type.
        \tparam MenuBar           A menu bar type.
        \tparam PopupMenu         A popup menu type.
        \tparam MessageLoop       A message loop type.
        \tparam MouseCapture      A mouse capture_type.
        \tparam Timer             A timer type.
        \tparam MessageCatalog    A message catalog type.
        \tparam MainWindowTraits  A main window traits type.
        \tparam ViewTraits        A view traits type.
        \tparam LoadSaveTraits    A loading and saving processing traits.
        \tparam CommandSetTraits  A command set traits type.
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
        typename Scale,
        typename GuiFixture,
        typename Font,
        typename AbstractWindow,
        typename PictureBox,
        typename MapBox,
        typename SideBar,
        typename MenuBar,
        typename PopupMenu,
        typename MessageLoop,
        typename MouseCapture,
        typename Timer,
        typename MessageCatalog,
        typename MainWindowTraits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename CommandSetTraits,
        typename ConfigTraits
    >
    class application_traits
    {
    public:
        // types

        //! The size type.
        using size_type = Size;
        
        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! THe scale type.
        using scale_type = Scale;

        //! The GUI fixture type.
        using gui_fixture_type = GuiFixture;

        //! The font type.
        using font_type = Font;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The max box type.
        using map_box_type = MapBox;

        //! The side bar type.
        using side_bar_type = SideBar;

        //! The menu bar type.
        using menu_bar_type = MenuBar;

        //! The popup menu type.
        using popup_menu_type = PopupMenu;

        //! The message loop type.
        using message_loop_type = MessageLoop;

        //! The mouse capture type.
        using mouse_capture_type = MouseCapture;

        //! The timer type.
        using timer_type = Timer;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The main window type.
        using main_window_traits_type = MainWindowTraits;

        //! The view type.
        using view_traits_type = ViewTraits;

        //! The loading and saving processing traits type.
        using load_save_traits_type = LoadSaveTraits;

        //! The command set type.
        using command_set_traits_type = CommandSetTraits;

        //! The configuration traits type.
        using config_traits_type = ConfigTraits;


    };


}


#endif
