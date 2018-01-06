/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>

#include <bobura/command/command_base.h>
#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    parameter_base::~parameter_base()
    noexcept
    {}

    parameter_base::parameter_base()
    {}

    template <typename Traits>
    command_base<Traits>::~command_base()
    noexcept
    {}

    template <typename Traits>
    bool command_base<Traits>::enabled(const model_type& model)
    const
    {
        return enabled_impl(model);
    }

    template <typename Traits>
    typename command_base<Traits>::state_type command_base<Traits>::state()
    const
    {
        return state_impl();
    }

    template <typename Traits>
    void command_base<Traits>::execute(model_type& model, abstract_window_type& parent)
    const
    {
        execute_impl(model, parent);
    }

    template <typename Traits>
    void command_base<Traits>::execute(
        model_type&           model,
        abstract_window_type& parent,
        const parameter_base& parameter
    )
    const
    {
        execute_impl(model, parent, parameter);
    }

    template <typename Traits>
    bool command_base<Traits>::enabled_impl(const model_type& model)
    const
    {
        boost::ignore_unused(model);

        return true;
    }

    template <typename Traits>
    typename command_base<Traits>::state_type command_base<Traits>::state_impl()
    const
    {
        return state_type::default_;
    }

    template <typename Traits>
    void command_base<Traits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent,
        const parameter_base& parameter
    )
    const
    {
        boost::ignore_unused(parameter);

        execute_impl(model, parent);
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
    template class command_base<typename application::traits_type_list_type::command_type>;
#endif

    template class command_base<typename test::traits_type_list_type::command_type>;


}}
