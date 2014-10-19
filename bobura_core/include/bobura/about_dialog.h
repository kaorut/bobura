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

        \tparam Traits       A traits type.
        \tparam ConfigTraits A configuration traits type.
    */
    template <typename Traits, typename ConfigTraits>
    class about_dialog : public Traits::dialog_type
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
        using base_type = typename traits_type::dialog_type;

        //! The abstract window type.
        using abstract_window_type = typename traits_type::abstract_window_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

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
