/*! \file
    \brief The definition of bobura::application_traits.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_APPLICATIONTRAITS_H)
#define BOBURA_APPLICATIONTRAITS_H


namespace bobura
{
   /*!
        \brief The class template for an application traits.

        \tparam Size                        A size type.
        \tparam Difference                  A difference type.
        \tparam String                      A string type.
        \tparam Position                    A position type.
        \tparam Dimension                   A dimension type.
        \tparam OperatingDistance           A string type.
        \tparam Spped                       A string type.
        \tparam Scale                       A scale type.
        \tparam GuiFixture                  A GUI fixture type.
        \tparam Font                        A font type.
        \tparam AbstractWindow              An abstract window type.
        \tparam PictureBox                  A picture box type.
        \tparam TabFrame                    A tab frame type.
        \tparam MapBox                      A map box type.
        \tparam SideBar                     A side bar type.
        \tparam MenuBar                     A menu bar type.
        \tparam PopupMenu                   A popup menu type.
        \tparam MenuCommand                 A menu command type.
        \tparam MenuSeparator               A menu separator type.
        \tparam MessageLoop                 A message loop type.
        \tparam MouseCapture                A mouse capture_type.
        \tparam Timer                       A timer type.
        \tparam MessageCatalog              A message catalog type.
        \tparam MainWindowTraits            A main window traits type.
        \tparam DiagramViewTraits           A diagram view traits type.
        \tparam LoadSaveTraits              A loading and saving processing traits type.
        \tparam CommandSetTraits            A command set traits type.
        \tparam MainWindowMenuBuilderTraits A main window menu builder traits type.
        \tparam ConfigTraits                A configuration traits type.
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
        typename TabFrame,
        typename MapBox,
        typename SideBar,
        typename MenuBar,
        typename PopupMenu,
        typename MenuCommand,
        typename MenuSeparator,
        typename MessageLoop,
        typename MouseCapture,
        typename Timer,
        typename MessageCatalog,
        typename MainWindowTraits,
        typename DiagramViewTraits,
        typename LoadSaveTraits,
        typename CommandSetTraits,
        typename MainWindowMenuBuilderTraits,
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

        //! The tab frame type.
        using tab_frame_type = TabFrame;

        //! The max box type.
        using map_box_type = MapBox;

        //! The side bar type.
        using side_bar_type = SideBar;

        //! The menu bar type.
        using menu_bar_type = MenuBar;

        //! The popup menu type.
        using popup_menu_type = PopupMenu;

        //! The menu command type.
        using menu_command_type = MenuCommand;

        //! The menu separator type.
        using menu_separator_type = MenuSeparator;

        //! The message loop type.
        using message_loop_type = MessageLoop;

        //! The mouse capture type.
        using mouse_capture_type = MouseCapture;

        //! The timer type.
        using timer_type = Timer;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The diagram view traits type.
        using diagram_view_traits_type = DiagramViewTraits;

        //! The loading and saving processing traits type.
        using load_save_traits_type = LoadSaveTraits;

        //! The command set traits type.
        using command_set_traits_type = CommandSetTraits;

        //! The main window menu builder traits type.
        using main_window_menu_builder_traits_type = MainWindowMenuBuilderTraits;

        //! The configuration traits type.
        using config_traits_type = ConfigTraits;


    };


}


#endif
