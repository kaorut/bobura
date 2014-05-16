/*! \file
    \brief The definition of bobura::command::train_kind.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TRAINKIND_H)
#define BOBURA_COMMAND_TRAINKIND_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a train kind command.
    */
    class train_kind : public command_base
    {
    public:
        // types

        //! The base type.
        using base_type = command_base;

        //! The train kind dialog type.
        using train_kind_dialog_type = boost::mpl::at<dialog_type_list, type::dialog::train_kind_dialog>::type;

        //! The dialog base type.
        using dialog_base_type = train_kind_dialog_type::base_type;

        //! The message catalog type.
        using message_catalog_type = train_kind_dialog_type::message_catalog_type;


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
