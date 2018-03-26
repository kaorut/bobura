/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/command/exit.h>
#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>


namespace bobura::command {
    template <typename Traits>
    class exit<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using model_type = typename exit::model_type;

        using abstract_window_type = typename exit::abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent) const
        {
            boost::ignore_unused(model);

            parent.close();
        }
    };


    template <typename Traits>
    exit<Traits>::exit() : m_p_impl{ tetengo2::stdalt::make_unique<impl>() }
    {}

    template <typename Traits>
    exit<Traits>::~exit() noexcept
    {}

    template <typename Traits>
    void exit<Traits>::execute_impl(model_type& model, abstract_window_type& parent) const
    {
        m_p_impl->execute(model, parent);
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
    template class exit<typename application::traits_type_list_type::command_type>;
#endif

    template class exit<typename test::traits_type_list_type::command_type>;
}
