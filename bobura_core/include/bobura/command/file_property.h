/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FILEPROPERTY_H)
#define BOBURA_COMMAND_FILEPROPERTY_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a file property command.

        \tparam Traits         A traits type.
        \tparam Dialog         A dialog type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Traits, typename Dialog, typename MessageCatalog>
    class file_property : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The base type.
        using base_type = command_base<traits_type>;


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
