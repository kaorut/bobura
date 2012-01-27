/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <tetengo2.cpp11.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam AboutDialog    An about dialog type.
    */
    template <typename AboutDialog>
    class about
    {
    public:
        // types

        //! The about dialog type.
        typedef AboutDialog about_dialog_type;

        //! The abstract window type.
        typedef
            typename about_dialog_type::abstract_window_type
            abstract_window_type;

        //! The message catalog type.
        typedef
            typename about_dialog_type::message_catalog_type
            message_catalog_type;

        //! The settings type.
        typedef typename about_dialog_type::settings_type settings_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param parent          A parent window.
            \param message_catalog A message catalog.
            \param settings        Settings type.
        */
        about(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        :
        m_parent(parent),
        m_message_catalog(message_catalog),
        m_settings(settings)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            about_dialog_type(
                m_parent, m_message_catalog, m_settings
            ).do_modal();
        }


    private:
        // variables

        typename tetengo2::cpp11::reference_wrapper<
            abstract_window_type
        >::type m_parent;

        typename tetengo2::cpp11::reference_wrapper<
            const message_catalog_type
        >::type m_message_catalog;

        typename tetengo2::cpp11::reference_wrapper<const settings_type>::type
        m_settings;


    };


}}


#endif