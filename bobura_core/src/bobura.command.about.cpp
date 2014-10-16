/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/about_dialog.h>
#include <bobura/command/about.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits,
        typename ConfigTraits
    >
    class about<Traits, Position, Dimension, MessageCatalog, DialogTraits, ConfigTraits>::impl
    {
    public:
        // types

        using model_type = typename about::model_type;

        using abstract_window_type = typename about::abstract_window_type;

        using message_catalog_type = typename about::message_catalog_type;

        using dialog_traits_type = typename about::dialog_traits_type;

        using config_traits_type = typename about::config_traits_type;

        using settings_type = typename about::settings_type;


        // constructors and destructor

        impl(const message_catalog_type& message_catalog, const settings_type& settings)
        :
        m_message_catalog(message_catalog),
        m_settings(settings)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            about_dialog_type{ parent, m_message_catalog, m_settings }.do_modal();
        }


    private:
        // types

        using about_dialog_type = about_dialog<dialog_traits_type, config_traits_type>;


        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


    };


    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits,
        typename ConfigTraits
    >
    about<Traits, Position, Dimension, MessageCatalog, DialogTraits, ConfigTraits>::about(
        const message_catalog_type& message_catalog,
        const settings_type&        settings
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog, settings))
    {}

    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits,
        typename ConfigTraits
    >
    about<Traits, Position, Dimension, MessageCatalog, DialogTraits, ConfigTraits>::~about()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits,
        typename ConfigTraits
    >
    void about<Traits, Position, Dimension, MessageCatalog, DialogTraits, ConfigTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class about<
        typename boost::mpl::at<main_window_type_list, type::main_window::command_traits>::type,
        typename boost::mpl::at<ui_type_list, type::ui::position>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dimension>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<main_window_type_list, type::main_window::dialog_traits>::type,
        typename boost::mpl::at<setting_type_list, type::setting::config_traits>::type
    >;


}}
