/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <memory>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>

#include <bobura/load_save/confirm_file_save.h>
#include <bobura/property_bar.h>
#include <bobura/settings.h>
#include <bobura/view_picture_box.h>


namespace bobura {
    /*!
        \brief The class template for the main window.

        \tparam Traits           A traits type.
        \tparam CommandSetTraits A command set traits type.
    */
    template <typename Traits, typename CommandSetTraits>
    class main_window : public Traits::window_type
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The position type.
        using position_type = typename traits_type::position_type;

        //! The dimension type.
        using dimension_type = typename traits_type::dimension_type;

        //! The base type.
        using base_type = typename traits_type::window_type;

        //! The abstract window type.
        using abstract_window_type = tetengo2::gui::widget::abstract_window;

        //! The icon type.
        using icon_type = typename base_type::icon_type;

        //! The window state type.
        using window_state_type = typename base_type::window_state_type;

        //! The picture box type.
        using picture_box_type = typename traits_type::picture_box_type;

        //! The tab frame type.
        using tab_frame_type = typename traits_type::tab_frame_type;

        //! The map box type.
        using map_box_type = typename traits_type::map_box_type;

        //! The side bar type.
        using side_bar_type = typename traits_type::side_bar_type;

        //! The font type.
        using font_type = typename traits_type::font_type;

        //! The mouse capture type.
        using mouse_capture_type = typename traits_type::mouse_capture_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The loading and saving processing traits type.
        using load_save_traits_type = typename traits_type::load_save_traits_type;

        //! The command set traits type.
        using command_set_traits_type = CommandSetTraits;

        //! The view picture box type.
        using view_picture_box_type = view_picture_box<picture_box_type, mouse_capture_type>;

        //! The property bar type.
        using property_bar_type = property_bar<
            string_type,
            position_type,
            dimension_type,
            abstract_window_type,
            side_bar_type,
            map_box_type,
            message_catalog_type>;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type>;

        //! The file save confirmation type.
        using confirm_file_save_type = load_save::confirm_file_save<load_save_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a main window.

            \param message_catalog   A message catalog.
            \param settings          Settings.
            \param confirm_file_save A file save confirmation.
        */
        main_window(
            const message_catalog_type&   message_catalog,
            settings_type&                settings,
            const confirm_file_save_type& confirm_file_save);

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window() noexcept;


        // functions

        /*!
            \brief Sets a title.

            \param document_name A document name.
            \param changed       A changed status.
        */
        void set_title(const tetengo2::stdalt::optional<string_type>& document_name, bool changed);

        /*!
            \brief Returns the tab frame.

            \return The tab frame.
        */
        const tab_frame_type& get_tab_frame() const;

        /*!
            \brief Returns the tab frame.

            \return The tab frame.
        */
        tab_frame_type& get_tab_frame();

        /*!
            \brief Returns the diagram view picture box.

            \return The diagram view picture box.
        */
        const view_picture_box_type& get_diagram_view_picture_box() const;

        /*!
            \brief Shows the diagram tab.
        */
        void show_diagram_tab();

        /*!
            \brief Shows the timetable down tab.
        */
        void show_timetable_down_tab();

        /*!
            \brief Shows the timetable up tab.
        */
        void show_timetable_up_tab();

        /*!
            \brief Returns the diagram view picture box.

            \return The diagram view picture box.
        */
        view_picture_box_type& get_diagram_view_picture_box();

        /*!
            \brief Returns the timetable down view picture box.

            \return The timetable down view picture box.
        */
        const view_picture_box_type& get_timetable_down_view_picture_box() const;

        /*!
            \brief Returns the timetable down view picture box.

            \return The timetable down view picture box.
        */
        view_picture_box_type& get_timetable_down_view_picture_box();

        /*!
            \brief Returns the timetable up view picture box.

            \return The timetable up view picture box.
        */
        const view_picture_box_type& get_timetable_up_view_picture_box() const;

        /*!
            \brief Returns the timetable up view picture box.

            \return The timetable up view picture box.
        */
        view_picture_box_type& get_timetable_up_view_picture_box();

        /*!
            \brief Returns the property bar.

            \return The property bar.
        */
        const property_bar_type& get_property_bar() const;

        /*!
            \brief Returns the property bar.

            \return The property bar.
        */
        property_bar_type& get_property_bar();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}

#endif
