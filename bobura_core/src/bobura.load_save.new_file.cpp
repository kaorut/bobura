/*! \file
    \brief The definition of bobura::load_save::new_file.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <bobura/detail_type_list.h>
#include <bobura/load_save/new_file.h>
#include <bobura/type_list.h>


namespace bobura::load_save {
    template <typename Traits>
    class new_file<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using abstract_window_type = typename traits_type::abstract_window_type;

        using model_type = typename new_file::model_type;

        using confirm_file_save_type = typename new_file::confirm_file_save_type;


        // constructors and destructor

        explicit impl(const confirm_file_save_type& confirm_file_save) : m_confirm_file_save{ confirm_file_save } {}


        // functions

        void operator()(model_type& model, abstract_window_type& parent) const
        {
            if (!m_confirm_file_save(parent))
                return;

            model.reset_timetable(tetengo2::stdalt::make_unique<timetable_type>());
        }


    private:
        // types

        using timetable_type = typename model_type::timetable_type;


        // variables

        const confirm_file_save_type& m_confirm_file_save;
    };


    template <typename Traits>
    new_file<Traits>::new_file(const confirm_file_save_type& confirm_file_save)
    : m_p_impl{ tetengo2::stdalt::make_unique<impl>(confirm_file_save) }
    {}

    template <typename Traits>
    new_file<Traits>::~new_file() noexcept
    {}

    template <typename Traits>
    void new_file<Traits>::operator()(model_type& model, abstract_window_type& parent) const
    {
        (*m_p_impl)(model, parent);
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
    template class new_file<application::traits_type_list_type::load_save_type>;
#endif

    template class new_file<test::traits_type_list_type::load_save_type>;
}
