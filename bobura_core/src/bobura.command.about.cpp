/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.detail.h>

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
        typename DialogTraits
    >
    class about<Traits, Position, Dimension, MessageCatalog, DialogTraits>::impl
    {
    public:
        // types

        using message_catalog_type = typename about::message_catalog_type;

        using dialog_traits_type = typename about::dialog_traits_type;

        using abstract_window_type = typename about::abstract_window_type;

        using model_type = typename about::model_type;

        using settings_type = typename about::settings_type;

        using cursor_details_type = typename about::cursor_details_type;


        // constructors and destructor

        impl(
            const message_catalog_type& message_catalog,
            const settings_type&        settings,
            const cursor_details_type&  cursor_details
        )
        :
        m_message_catalog(message_catalog),
        m_settings(settings),
        m_cursor_details(cursor_details)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            about_dialog_type{ parent, m_message_catalog, m_settings, m_cursor_details }.do_modal();
        }


    private:
        // types

        using about_dialog_type = about_dialog<dialog_traits_type>;


        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;

        const cursor_details_type& m_cursor_details;


    };


    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits
    >
    about<Traits, Position, Dimension, MessageCatalog, DialogTraits>::about(
        const message_catalog_type& message_catalog,
        const settings_type&        settings,
        const cursor_details_type&  cursor_details
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog, settings, cursor_details))
    {}

    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits
    >
    about<Traits, Position, Dimension, MessageCatalog, DialogTraits>::~about()
    noexcept
    {}
    
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename MessageCatalog,
        typename DialogTraits
    >
    void about<Traits, Position, Dimension, MessageCatalog, DialogTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;
    
            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;
    
            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class about<
        typename application::traits_type_list_type::command_type,
        typename application::ui_type_list_type::position_type,
        typename application::ui_type_list_type::dimension_type,
        typename application::locale_type_list_type::message_catalog_type,
        typename application::traits_type_list_type::dialog_type
    >;
#endif

    template class about<
        typename test::traits_type_list_type::command_type,
        typename test::ui_type_list_type::position_type,
        typename test::ui_type_list_type::dimension_type,
        typename test::locale_type_list_type::message_catalog_type,
        typename test::traits_type_list_type::dialog_type
    >;


}}
