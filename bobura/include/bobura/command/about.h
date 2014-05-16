/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class for an about command.
    */
    class about : public command_base
    {
    public:
        // types

        //! The base type.
        using base_type = command_base;

        //! The about dialog type.
        using about_dialog_type = boost::mpl::at<dialog_type_list, type::dialog::about_dialog>::type;

        //! The message catalog type.
        using message_catalog_type = about_dialog_type::message_catalog_type;

        //! The settings type.
        using settings_type = about_dialog_type::settings_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param message_catalog A message catalog.
            \param settings        Settings type.
        */
        about(const message_catalog_type& message_catalog, const settings_type& settings);

        /*!
            \brief Destroys the about command.
        */
        virtual ~about()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
