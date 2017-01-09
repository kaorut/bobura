/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/command/nop.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits>
    class nop<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using abstract_window_type = typename nop::abstract_window_type;

        using model_type = typename nop::model_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model, parent);
        }


    };


    template <typename Traits>
    nop<Traits>::nop()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits>
    nop<Traits>::~nop()
    noexcept
    {}
    
    template <typename Traits>
    void nop<Traits>::execute_impl(model_type& model, abstract_window_type& parent)
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

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class nop<typename application::traits_type_list_type::command_type>;
#endif

    template class nop<typename test::traits_type_list_type::command_type>;


}}
