/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <memory>

#include <bobura/command/command_base.h>
#include <bobura/settings.h>

#include <tetengo2/detail/base/impl_set.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam Traits         A traits type.
        \tparam Position       A position type.
        \tparam Dimension      A dimension type.
        \tparam MessageCatalog A message catalog type.
        \tparam DialogTraits   A dialog traits type.
    */
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits
    >
    class about : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The dialog traits type.
        using dialog_traits_type = DialogTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::abstract_window_type;

        //! The model type.
        using model_type = typename base_type::model_type;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type>;

        //! The detail implementation set type.
        using detail_impl_set_type = tetengo2::detail::base::impl_set;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param message_catalog A message catalog.
            \param settings        Settings type.
            \param detail_impl_set A detail implementation set.
        */
        about(
            const message_catalog_type& message_catalog,
            const settings_type&        settings,
            const detail_impl_set_type& detail_impl_set
        );

        /*!
            \brief Destroys the about command.
        */
        virtual ~about()
        noexcept;


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
