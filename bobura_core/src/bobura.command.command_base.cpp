/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/command/traits.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    parameter_base::~parameter_base()
    TETENGO2_STDALT_NOEXCEPT
    {}

    parameter_base::parameter_base()
    {}

    template <typename Traits>
    command_base<Traits>::~command_base()
    TETENGO2_STDALT_NOEXCEPT
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


    template class command_base<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
            typename boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type
        >
    >;


}}
