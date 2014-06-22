/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_ABOUTDIALOG_H)
#define BOBURA_ABOUTDIALOG_H

#include <memory>

#include <tetengo2.h>


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam Dialog         A dialog type.
        \tparam MessageCatalog A message catalog type.
        \tparam Settings       A settings type.
    */
    template <typename Dialog, typename MessageCatalog, typename Settings>
    class about_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        using base_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The settings type.
        using settings_type = Settings;


        // constructors and destructor

        /*!
            \brief Creates an about dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
            \param settings        Settings.
        */
        about_dialog(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        );

        /*!
            \brief Destroys the about dialog.
        */
        virtual ~about_dialog()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}

#endif