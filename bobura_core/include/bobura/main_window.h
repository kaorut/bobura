/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <memory>

#include <boost/optional.hpp>

#include <tetengo2.h>

#include <bobura/diagram_picture_box.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/property_bar.h>
#include <bobura/settings.h>


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class main_window : public Traits::window_type
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

        //! The position type.
        using position_type = typename traits_type::position_type;

        //! The dimension type.
        using dimension_type = typename traits_type::dimension_type;

        //! The output_stream type.
        using output_stream_type = typename traits_type::output_stream_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The base type.
        using base_type = typename traits_type::window_type;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The picture box type.
        using picture_box_type = typename traits_type::picture_box_type;

        //! The map box type.
        using map_box_type = typename traits_type::map_box_type;

        //! The side bar type.
        using side_bar_type = typename traits_type::side_bar_type;

        //! The message box type.
        using message_box_type = typename traits_type::message_box_type;

        //! The file save dialog type.
        using file_save_dialog_type = typename traits_type::file_save_dialog_type;

        //! The font type.
        using font_type = typename traits_type::font_type;

        //! The mouse capture type.
        using mouse_capture_type = typename traits_type::mouse_capture_type;

        //! The config traits type.
        using config_traits_type = typename traits_type::config_traits_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The timetable file encoder type.
        using timetable_file_encoder_type = typename traits_type::timetable_file_encoder_type;

        //! The diagram picture box message type list type.
        using diagram_picture_box_message_type_list_type =
            typename traits_type::diagram_picture_box_message_type_list_type;

        //! The diagram picture box type.
        using diagram_picture_box_type =
            diagram_picture_box<
                picture_box_type,
                abstract_window_type,
                mouse_capture_type,
                diagram_picture_box_message_type_list_type
            >;

        //! The property bar type.
        using property_bar_type =
            property_bar<
                string_type,
                position_type,
                dimension_type,
                abstract_window_type,
                side_bar_type,
                map_box_type,
                config_traits_type,
                message_catalog_type
            >;
        
        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type, config_traits_type>;

        //! The file save confirmation type.
        using confirm_file_save_type =
            load_save::confirm_file_save<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type, font_type,
                abstract_window_type,
                message_box_type,
                file_save_dialog_type,
                message_catalog_type,
                timetable_file_encoder_type
            >;


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
            const confirm_file_save_type& confirm_file_save
        );

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Sets a title.

            \param document_name A document name.
            \param changed       A changed status.
        */
        void set_title(const boost::optional<string_type>& document_name, const bool changed);

        /*!
            \brief Returns the diagram picture box.

            \return The diagram picture box.
        */
        const diagram_picture_box_type& get_diagram_picture_box()
        const;

        /*!
            \brief Returns the diagram picture box.

            \return The diagram picture box.
        */
        diagram_picture_box_type& get_diagram_picture_box();

        /*!
            \brief Returns the property bar.

            \return The property bar.
        */
        const property_bar_type& get_property_bar()
        const;

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
