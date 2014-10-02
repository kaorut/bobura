/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <memory>

#include <tetengo2.h>

#include <bobura/about_dialog.h>
#include <bobura/command/command_base.h>
#include <bobura/settings.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam Traits         A traits type.
        \tparam Position       A position type.
        \tparam Dimension      A dimension type.
        \tparam Dialog         A dialog type.
        \tparam ConfigTraits   A config traits type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename ConfigTraits,
        typename MessageCatalog
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

        //! The dialog type.
        using dialog_type = Dialog;

        //! The config traits type.
        using config_traits_type = ConfigTraits;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The about dialog type.
        using about_dialog_type =
            about_dialog<
                string_type, position_type, dimension_type, dialog_type, message_catalog_type, config_traits_type
            >;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type, config_traits_type>;


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
