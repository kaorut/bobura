/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/file_property.h>
#include <bobura/file_property_dialog.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename Dialog, typename MessageCatalog, typename DialogTraits>
    class file_property<Traits, Dialog, MessageCatalog, DialogTraits>::impl
    {
    public:
        // types

        using string_type = typename file_property::string_type;

        using model_type = typename file_property::model_type;

        using abstract_window_type = typename file_property::abstract_window_type;

        using dialog_type = typename file_property::dialog_type;

        using message_catalog_type = typename file_property::message_catalog_type;

        using dialog_traits_type = typename file_property::dialog_traits_type;


        // constructors and destructor

        explicit impl(const message_catalog_type& message_catalog)
        :
        m_message_catalog(message_catalog)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            file_property_dialog_type dialog{ parent, m_message_catalog };

            dialog.set_company_name(model.timetable().company_name());
            dialog.set_line_name(model.timetable().line_name());
            dialog.set_note(model.timetable().note());
            if (model.has_path())
                dialog.set_file_name(model.path().template string<string_type>());

            dialog.do_modal();
            if (dialog.result() != dialog_type::result_type::accepted)
                return;

            model.timetable().set_company_name(dialog.company_name());
            model.timetable().set_line_name(dialog.line_name());
            model.timetable().set_note(dialog.note());
        }


    private:
        // types

        using file_property_dialog_type = file_property_dialog<dialog_traits_type>;


        // variables

        const message_catalog_type& m_message_catalog;


    };


    template <typename Traits, typename Dialog, typename MessageCatalog, typename DialogTraits>
    file_property<Traits, Dialog, MessageCatalog, DialogTraits>::file_property(
        const message_catalog_type& message_catalog
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog))
    {}

    template <typename Traits, typename Dialog, typename MessageCatalog, typename DialogTraits>
    file_property<Traits, Dialog, MessageCatalog, DialogTraits>::~file_property()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename Dialog, typename MessageCatalog, typename DialogTraits>
    void file_property<Traits, Dialog, MessageCatalog, DialogTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class file_property<
        typename boost::mpl::at<traits_type_list, type::traits::command>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<traits_type_list, type::traits::dialog>::type
    >;


}}
