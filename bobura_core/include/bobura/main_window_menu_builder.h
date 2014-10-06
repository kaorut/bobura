/*! \file
    \brief The definition of bobura::main_window_menu_builder.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOWMENUBUILDER_H)
#define BOBURA_MAINWINDOWMENUBUILDER_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/command/set.h>
#include <bobura/main_window.h>
#include <bobura/timetable_model.h>


namespace bobura
{
    /*!
        \brief The class template for the main window menu builder.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
        \tparam MenuBar           A menu bar type.
        \tparam MessageCatalog    A message catalog type.
        \tparam CommandSetTraits  A command set traits.
        \tparam MainWindowTraits  A main window traits type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename MenuBar,
        typename MessageCatalog,
        typename CommandSetTraits,
        typename MainWindowTraits
    >
    class main_window_menu_builder : private boost::noncopyable
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

        //! The font type.
        using font_type = Font;

        //! The menu bar type.
        using menu_bar_type = MenuBar;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The command set traits type.
        using command_set_traits = CommandSetTraits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The command set type.
        using command_set_type = command::set<command_set_traits>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The main window type.
        using main_window_type = main_window<main_window_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a main window menu builder.

            \param command_set     A command set.
            \param model           A model.
            \param main_window     A main window.
            \param message_catalog A message catalog.
        */
        main_window_menu_builder(
            const command_set_type&     command_set,
            model_type&                 model,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        );

        /*!
            \brief Destroys the main window menu builder.
        */
        ~main_window_menu_builder()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Builds a main window menu bar.

            \return A main window menu bar.
        */
        std::unique_ptr<menu_bar_type> build()
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}


#endif
