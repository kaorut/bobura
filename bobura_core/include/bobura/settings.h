/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_SETTINGS_H)
#define BOBURA_SETTINGS_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/stdalt.h>


namespace bobura {
    /*!
        \brief The class template for settings of bobura.

        \tparam String    A string type.
        \tparam Position  A position type.
        \tparam Dimension A dimension type.
    */
    template <typename String, typename Position, typename Dimension>
    class settings : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The position unit type.
        using position_unit_type = typename position_type::unit_type;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The dimension unit type.
        using dimension_unit_type = typename dimension_type::unit_type;


        // constructors and destructor

        /*!
            \brief Creates settings.

            \param command_line_arguments Command line arguments.
            \param config_group_name      A group name for the configuration.
        */
        settings(const std::vector<string_type>& command_line_arguments, string_type config_group_name);

        /*!
            \brief Destroys the settings.
        */
        ~settings() noexcept;


        // functions

        /*!
            \brief Returns the base path.

            \return The base path.
        */
        const tetengo2::stdalt::filesystem::path& base_path() const;

        /*!
            \brief Returns the input.

            \return The input.
        */
        const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& input() const;

        /*!
            \brief Returns the message directory path.

            \return The message directory path.
        */
        tetengo2::stdalt::filesystem::path message_directory_path() const;

        /*!
            \brief Returns the image directory path.

            \return The image directory path.
        */
        tetengo2::stdalt::filesystem::path image_directory_path() const;

        /*!
            \brief Returns the main window dimension.

            \return The main window dimension.
        */
        tetengo2::stdalt::optional<dimension_type> main_window_dimension() const;

        /*!
            \brief Sets a main window dimension.

            \param dimension A dimension.
        */
        void set_main_window_dimension(const dimension_type& dimension);

        /*!
            \brief Returns the maximized status of the main window.

            \return The maximized status.
        */
        tetengo2::stdalt::optional<bool> main_window_maximized() const;

        /*!
            \brief Sets a maximized status of the main window.

            \param status A maximized status.
        */
        void set_main_window_maximized(bool status);

        /*!
            \brief Returns the property bar width.

            \return The property bar width.
        */
        tetengo2::stdalt::optional<dimension_unit_type> property_bar_width() const;

        /*!
            \brief Sets a property bar width.

            \param width A width.
        */
        void set_property_bar_width(const dimension_unit_type& width);

        /*!
            \brief Returns the minimized status of the property bar.

            \return The minimized status.
        */
        tetengo2::stdalt::optional<bool> property_bar_minimized() const;

        /*!
            \brief Sets a minimized status of the property bar.

            \param status A minimized status.
        */
        void set_property_bar_minimized(bool status);

        /*!
            \brief Returns the splitter bar position in the property bar.

            \return The splitter bar position.
        */
        tetengo2::stdalt::optional<position_unit_type> property_bar_splitter_position() const;

        /*!
            \brief Sets a splitter bar position in the property bar.

            \param position A position.
        */
        void set_property_bar_splitter_position(const position_unit_type& position);

        /*!
            \brief Clears the configuration.
        */
        void clear_config();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
