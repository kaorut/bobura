/*! \file
    \brief The definition of bobura::main_window_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOWTRAITS_H)
#define BOBURA_MAINWINDOWTRAITS_H


namespace bobura
{
     /*!
        \brief The class template for the main window traits.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam Position          A position type.
        \tparam Dimension         A dimension type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Window            A window type.
        \tparam PictureBox        A picture box type.
        \tparam MapBox            A map box type.
        \tparam SideBar           A side bar type.
        \tparam PopupMenu         A popup menu type.
        \tparam MessageLoopBreak  A message loop break type.
        \tparam Font              A font type.
        \tparam MouseCapture      A mouse capture type.
        \tparam MessageCatalog    A message catalog type.
        \tparam ViewTraits        A view traits type.
        \tparam LoadSaveTraits    A loading and saving processing traits type.
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
        typename Window,
        typename PictureBox,
        typename MapBox,
        typename SideBar,
        typename PopupMenu,
        typename MessageLoopBreak,
        typename Font,
        typename MouseCapture,
        typename MessageCatalog,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename ConfigTraits
    >
    class main_window_traits
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

        //! The window type.
        using window_type = Window;

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The map box type.
        using map_box_type = MapBox;

        //! The side bar type.
        using side_bar_type = SideBar;

        //! The popup menu type.
        using popup_menu_type = PopupMenu;

        //! The message loop break type.
        using message_loop_break_type = MessageLoopBreak;

        //! The font type.
        using font_type = Font;

        //! The mouse capture type.
        using mouse_capture_type = MouseCapture;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The loading and saving processing traits type.
        using load_save_traits_type = LoadSaveTraits;

        //! The config traits type.
        using config_traits_type = ConfigTraits;


    };


}


#endif
