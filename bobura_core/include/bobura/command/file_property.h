/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FILEPROPERTY_H)
#define BOBURA_COMMAND_FILEPROPERTY_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/file_property_dialog.h>


namespace bobura { namespace command
{
    /*!
        \brief The class for a file property command.
    */
    class file_property : public command_base
    {
    public:
        // types

        //! The base type.
        using base_type = command_base;

        //! The file property dialog type.
        using file_property_dialog_type =
            file_property_dialog<
                boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;

        //! The dialog base type.
        using dialog_base_type = file_property_dialog_type::base_type;

        //! The string type.
        using string_type = file_property_dialog_type::string_type;

        //! The message catalog type.
        using message_catalog_type = file_property_dialog_type::message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file property command.

            \param message_catalog A message catalog.
        */
        explicit file_property(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the file property command.
        */
        virtual ~file_property()
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
