/*! \file
    \brief The definition of bobura::command::train_kind.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TRAINKIND_H)
#define BOBURA_COMMAND_TRAINKIND_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a train kind command.

        \tparam Traits         A traits type.
        \tparam Dialog         A dialog type.
        \tparam Color          A color type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename Traits, typename Dialog, typename Color, typename MessageCatalog>
    class train_kind : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The color type.
        using color_type = Color;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The base type.
        using base_type = command_base<traits_type>;


        // constructors and destructor

        /*!
            \brief Create a train kind command.

            \param message_catalog A message catalog.
        */
        explicit train_kind(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys a train kind command.
        */
        virtual ~train_kind()
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
