/*! \file
    \brief The definition of bobura::main_window_menu_builder_traits.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOWMENUBUILDERTRAITS_H)
#define BOBURA_MAINWINDOWMENUBUILDERTRAITS_H


namespace bobura {
    /*!
       \brief The class template for the main window menu builder traits.

       \tparam Size              A size type.
       \tparam Difference        A difference type.
       \tparam String            A string type.
       \tparam OperatingDistance An operating distance type.
       \tparam Speed             A speed type.
       \tparam Scale             A scale type.
       \tparam Font              A font type.
       \tparam MenuBar           A menu bar type.
       \tparam PopupMenu         A popup menu type.
       \tparam MenuCommand       A menu command type.
       \tparam MenuSeparator     A menu separator type.
       \tparam MessageCatalog    A message catalog type.
       \tparam CommandSetTraits  A command set traits.
       \tparam MainWindowTraits  A main window traits type.
       \tparam DiagramViewTraits A diagram view traits type.
   */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Scale,
        typename Font,
        typename MenuBar,
        typename PopupMenu,
        typename MenuCommand,
        typename MenuSeparator,
        typename MessageCatalog,
        typename CommandSetTraits,
        typename MainWindowTraits,
        typename DiagramViewTraits>
    class main_window_menu_builder_traits
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The scale type.
        using scale_type = Scale;

        //! The font type.
        using font_type = Font;

        //! The menu bar type.
        using menu_bar_type = MenuBar;

        //! The popup menu type.
        using popup_menu_type = PopupMenu;

        //! The menu command type.
        using menu_command_type = MenuCommand;

        //! The menu separator type.
        using menu_separator_type = MenuSeparator;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The command set traits type.
        using command_set_traits_type = CommandSetTraits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The diagram view traits type.
        using diagram_view_traits_type = DiagramViewTraits;
    };
}


#endif
