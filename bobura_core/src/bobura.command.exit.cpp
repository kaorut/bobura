/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/exit.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits>
    class exit<Traits>::impl
    {
    public:
        // types

        using model_type = typename exit::model_type;

        using abstract_window_type = typename exit::abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            parent.close();
        }


    };


    template <typename Traits>
    exit<Traits>::exit()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits>
    exit<Traits>::~exit()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits>
    void exit<Traits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class exit<
        typename boost::mpl::at<main_window_type_list, type::main_window::command_traits>::type
    >;


}}
