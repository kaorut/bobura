/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/file_property.h>
#include <bobura/command/traits.h>
#include <bobura/file_property_dialog.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename Dialog, typename MessageCatalog>
    class file_property<Traits, Dialog, MessageCatalog>::impl
    {
    public:
        // types

        using string_type = typename file_property::string_type;

        using model_type = typename file_property::model_type;

        using abstract_window_type = typename file_property::abstract_window_type;

        using dialog_type = typename file_property::dialog_type;

        using message_catalog_type = typename file_property::message_catalog_type;


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

        using file_property_dialog_type = file_property_dialog<dialog_type, message_catalog_type>;


        // variables

        const message_catalog_type& m_message_catalog;


    };


    template <typename Traits, typename Dialog, typename MessageCatalog>
    file_property<Traits, Dialog, MessageCatalog>::file_property(const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog))
    {}

    template <typename Traits, typename Dialog, typename MessageCatalog>
    file_property<Traits, Dialog, MessageCatalog>::~file_property()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename Dialog, typename MessageCatalog>
    void file_property<Traits, Dialog, MessageCatalog>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class file_property<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
            typename boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type
        >,
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
    >;


}}
