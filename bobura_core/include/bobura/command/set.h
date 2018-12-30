/*! \file
    \brief The definition of bobura::command::set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SET_H)
#define BOBURA_COMMAND_SET_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/stdalt.h>

#include <bobura/command/command_base.h> // IWYU pragma: keep
#include <bobura/diagram_view.h>
#include <bobura/load_save/load_from_file.h>
#include <bobura/load_save/new_file.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/settings.h>


namespace bobura::command {
    /*!
        \brief The class template for a command set.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class set : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The position type.
        using position_type = typename traits_type::position_type;

        //! The dimension type.
        using dimension_type = typename traits_type::dimension_type;

        //! The dialog type.
        using dialog_type = typename traits_type::dialog_type;

        //! The color type.
        using color_type = typename traits_type::color_type;

        //! The point dimension unit type.
        using point_dimension_unit_type = typename traits_type::point_dimension_unit_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The scale type.
        using scale_type = typename traits_type::scale_type;

        //! The shell type.
        using shell_type = typename traits_type::shell_type;

        //! The font dialog type.
        using font_dialog_type = typename traits_type::font_dialog_type;

        //! The color dialog_type.
        using color_dialog_type = typename traits_type::color_dialog_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The command traits type.
        using command_traits_type = typename traits_type::command_traits_type;

        //! The main window traits type.
        using main_window_traits_type = typename traits_type::main_window_traits_type;

        //! The diagram view traits type.
        using diagram_view_traits_type = typename traits_type::diagram_view_traits_type;

        //! The loading and saving processing traits type.
        using load_save_traits_type = typename traits_type::load_save_traits_type;

        //! The dialog traits type.
        using dialog_traits_type = typename traits_type::dialog_traits_type;

        //! The file initialization type.
        using new_file_type = load_save::new_file<load_save_traits_type>;

        //! The file loading type.
        using load_from_file_type = load_save::load_from_file<load_save_traits_type>;

        //! The file saving type.
        using save_to_file_type = load_save::save_to_file<load_save_traits_type>;

        //! The diagram view type.
        using diagram_view_type = diagram_view<diagram_view_traits_type>;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type>;

        //! The command type.
        using command_type = command_base<command_traits_type>;

        //! The parameter type.
        using parameter_type = parameter_base;


        // constructors

        /*!
            \brief Creates a command set.

            \param new_file                       A file initialization.
            \param load_from_file                 A file loading.
            \param reload                         A file reloading.
            \param save_to_file                   A file saving.
            \param ask_file_path_and_save_to_file A file saving after file path query.
            \param diagram_view                   A diagram view.
            \param settings                       Settings.
            \param message_catalog                A message catalog.
        */
        set(const new_file_type&        new_file,
            const load_from_file_type&  load_from_file,
            const load_from_file_type&  reload,
            const save_to_file_type&    save_to_file,
            const save_to_file_type&    ask_file_path_and_save_to_file,
            diagram_view_type&          diagram_view,
            const settings_type&        settings,
            const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the command set.
        */
        virtual ~set() noexcept;


        // functions

        /*!
            \brief Returns the command about.

            \return The command.
        */
        const command_type& about() const;

        /*!
            \brief Returns the command save-to-file, in which a file selection
                   dialog is shown.

            \return The command.
        */
        const command_type& ask_file_path_and_save_to_file() const;

        /*!
            \brief Returns the command exit.

            \return The command.
        */
        const command_type& exit() const;

        /*!
            \brief Returns the command file property.

            \return The command.
        */
        const command_type& file_property() const;

        /*!
            \brief Returns the command font and color.

            \return The command.
        */
        const command_type& font_color() const;

        /*!
            \brief Returns the command horizontal zoom-in.

            \return The command.
        */
        const command_type& horizontally_zoom_in() const;

        /*!
            \brief Returns the command horizontal zoom-out.

            \return The command.
        */
        const command_type& horizontally_zoom_out() const;

        /*!
            \brief Returns the command load-from-file.

            \return The command.
        */
        const command_type& load_from_file() const;

        /*!
            \brief Creates a parameter for the command load-from-file.

            \param path A path.

            \return A unique pointer to a parameter for the command load-from-file.
        */
        std::unique_ptr<parameter_type>
        create_load_from_file_parameter(const tetengo2::stdalt::filesystem::path& path) const;

        /*!
            \brief Returns the command new-file.

            \return The command.
        */
        const command_type& new_file() const;

        /*!
            \brief Returns the command nop.

            \return The command.
        */
        const command_type& nop() const;

        /*!
            \brief Returns the command open-www.tetengo.org.

            \return The command.
        */
        const command_type& open_www_tetengo_org() const;

        /*!
            \brief Returns the command reload.

            \return The command.
        */
        const command_type& reload() const;

        /*!
            \brief Returns the command save-to-file.

            \return The command.
        */
        const command_type& save_to_file() const;

        /*!
            \brief Returns the command set-horizontal-scale.

            \param index An index.

            \return The command.
        */
        const command_type& set_horizontal_scale(size_type index) const;

        /*!
            \brief Returns the command set-vertical-scale.

            \param index An index.

            \return The command.
        */
        const command_type& set_vertical_scale(size_type index) const;

        /*!
            \brief Returns the command show-diagram.

            \return The command.
        */
        const command_type& show_diagram() const;

        /*!
            \brief Returns the command show-timetable-down.

            \return The command.
        */
        const command_type& show_timetable_down() const;

        /*!
            \brief Returns the command show-timetable-up.

            \return The command.
        */
        const command_type& show_timetable_up() const;

        /*!
            \brief Returns the command train-kind.

            \return The command.
        */
        const command_type& train_kind() const;

        /*!
            \brief Returns the command vertical zoom-in.

            \return The command.
        */
        const command_type& vertically_zoom_in() const;

        /*!
            \brief Returns the command vertical zoom-out.

            \return The command.
        */
        const command_type& vertically_zoom_out() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
