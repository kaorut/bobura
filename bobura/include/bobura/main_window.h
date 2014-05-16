/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <memory>

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>

#include <tetengo2.h>

#include <bobura/type_list.h>


namespace bobura
{
    /*!
        \brief The class for the main window.
    */
    class main_window : public boost::mpl::at<ui_type_list, type::ui::window>::type
    {
    public:
        // types

        //! The base type.
        using base_type = boost::mpl::at<ui_type_list, type::ui::window>::type;

        //! The string type.
        using string_type = base_type::string_type;

        //! The message catalog type.
        using message_catalog_type = boost::mpl::at<locale_type_list, type::locale::message_catalog>::type;

        //! The diagram picture box type.
        using diagram_picture_box_type =
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box>::type;

        //! The property bar type.
        using property_bar_type = boost::mpl::at<main_window_type_list, type::main_window::property_bar>::type;
        
        //! The settings type.
        using settings_type = boost::mpl::at<setting_type_list, type::setting::settings>::type;

        //! The file save confirmation type.
        using confirm_file_save_type = boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type;


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
        const diagram_picture_box_type& diagram_picture_box()
        const;

        /*!
            \brief Returns the diagram picture box.

            \return The diagram picture box.
        */
        diagram_picture_box_type& diagram_picture_box();

        /*!
            \brief Returns the property bar.

            \return The property bar.
        */
        const property_bar_type& property_bar()
        const;

        /*!
            \brief Returns the property bar.

            \return The property bar.
        */
        property_bar_type& property_bar();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}

#endif
