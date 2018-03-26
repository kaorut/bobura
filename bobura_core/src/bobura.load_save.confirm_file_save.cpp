/*! \file
    \brief The definition of bobura::load_save::confirm_file_save.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/type_list.h>


namespace bobura::load_save {
    template <typename Traits>
    class confirm_file_save<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using abstract_window_type = typename traits_type::abstract_window_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename confirm_file_save::model_type;

        using save_to_file_type = typename confirm_file_save::save_to_file_type;


        // constructors and destructor

        impl(model_type& model, const save_to_file_type& save_to_file, const message_catalog_type& message_catalog)
        : m_model{ model }, m_save_to_file{ save_to_file }, m_message_catalog{ message_catalog }
        {}


        // functions

        bool operator()(abstract_window_type& parent) const
        {
            if (!m_model.changed())
                return true;

            const auto selected_button = create_message_box(parent)->do_modal();
            if (selected_button == message_box_type::button_id_type::cancel)
                return false;
            if (selected_button == message_box_type::button_id_type::yes)
            {
                if (!m_save_to_file(m_model, parent))
                    return false;
            }

            return true;
        }


    private:
        // types

        using string_type = typename traits_type::string_type;

        using message_box_type = typename traits_type::message_box_type;


        // variables

        model_type& m_model;

        const save_to_file_type& m_save_to_file;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_message_box(abstract_window_type& parent) const
        {
            const auto file_path = m_model.has_path() ? m_model.path().template string<string_type>() :
                                                        m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));

            return tetengo2::stdalt::make_unique<message_box_type>(
                parent,
                m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                m_message_catalog.get(
                    TETENGO2_TEXT("Message:File:The file has been changed. Do you want to save the changes?")),
                file_path,
                message_box_type::button_style_type::yes_no(
                    true,
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:&Save")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:&Don't save"))),
                message_box_type::icon_style_type::warning);
        }
    };


    template <typename Traits>
    confirm_file_save<Traits>::confirm_file_save(
        model_type&                 model,
        const save_to_file_type&    save_to_file,
        const message_catalog_type& message_catalog)
    : m_p_impl{ tetengo2::stdalt::make_unique<impl>(model, save_to_file, message_catalog) }
    {}

    template <typename Traits>
    confirm_file_save<Traits>::~confirm_file_save() noexcept
    {}

    template <typename Traits>
    bool confirm_file_save<Traits>::operator()(abstract_window_type& parent) const
    {
        return (*m_p_impl)(parent);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class confirm_file_save<application::traits_type_list_type::load_save_type>;
#endif

    template class confirm_file_save<test::traits_type_list_type::load_save_type>;
}
