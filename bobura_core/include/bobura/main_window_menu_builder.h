/*! \file
    \brief The definition of bobura::main_window_menu_builder.

    Copyright (C) 2007-2015 kaoru

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

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class main_window_menu_builder : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The font type.
        using font_type = typename traits_type::font_type;

        //! The menu bar type.
        using menu_bar_type = typename traits_type::menu_bar_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The command set traits type.
        using command_set_traits_type = typename traits_type::command_set_traits_type;

        //! The main window traits type.
        using main_window_traits_type = typename traits_type::main_window_traits_type;

        //! The command set type.
        using command_set_type = command::set<command_set_traits_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The main window type.
        using main_window_type = main_window<main_window_traits_type, command_set_traits_type>;


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
        noexcept;


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
