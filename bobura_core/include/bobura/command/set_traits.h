/*! \file
    \brief The definition of bobura::command::set_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SETTRAITS_H)
#define BOBURA_COMMAND_SETTRAITS_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for the command set_traits.

        \tparam Size             A size type.
        \tparam Position         A position type.
        \tparam Dimension        A dimension type.
        \tparam Dialog           A dialog type.
        \tparam Color            A color type.
        \tparam PointUnitSize    A point unit size type.
        \tparam Scale            A scale type.
        \tparam Shell            A shell type.
        \tparam MessageCatalog   A message catalog type.
        \tparam CommandTraits    A command traits type.
        \tparam MainWindowTraits A main window traits type.
        \tparam ViewTraits       A view traits type.
        \tparam LoadSaveTraits   A loading and saving processing traits type.
        \tparam ConfigTraits     A config traits type.
    */
    template <
        typename Size,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Color,
        typename PointUnitSize,
        typename Scale,
        typename Shell,
        typename MessageCatalog,
        typename CommandTraits,
        typename MainWindowTraits,
        typename ViewTraits,
        typename LoadSaveTraits,
        typename ConfigTraits
    >
    class set_traits
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The color type.
        using color_type = Color;

        //! The point unit size type.
        using point_unit_size_type = PointUnitSize;

        //! The scale type.
        using scale_type = Scale;

        //! The shell type.
        using shell_type = Shell;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The command traits type.
        using command_traits_type = CommandTraits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The loading and saving processing traits type.
        using load_save_traits_type = LoadSaveTraits;

        //! The config traits type.
        using config_traits_type = ConfigTraits;


    };


}}


#endif
