/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_ABOUTDIALOG_H)
#define BOBURA_ABOUTDIALOG_H

#include <memory>

#include <tetengo2.h>

#include <bobura/settings.h>


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam String                A string type.
        \tparam Position              A position type.
        \tparam Dimension             A dimension type.
        \tparam Dialog                A dialog type.
        \tparam Label                 A label type.
        \tparam LinkLabel             A link label type.
        \tparam Image                 An image type.
        \tparam Button                A button type.
        \tparam TransparentBackground A transparent background type.
        \tparam MessageCatalog        A message catalog type.
        \tparam ConfigTraits          A configuration traits type.
    */
    template <
        typename String,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Label,
        typename LinkLabel,
        typename Image,
        typename Button,
        typename TransparentBackground,
        typename MessageCatalog,
        typename ConfigTraits
    >
    class about_dialog : public Dialog
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The base type.
        using base_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The label type.
        using label_type = Label;

        //! The link label type.
        using link_label_type = LinkLabel;

        //! The image type.
        using image_type = Image;

        //! The button type.
        using button_type = Button;

        //! The transparent background type.
        using transparent_background_type = TransparentBackground;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The configuration traits type.
        using config_traits_type = ConfigTraits;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type, config_traits_type>;


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
