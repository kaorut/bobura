/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>
#include <boost/predef.h>

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


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = detail_type_list_for_application;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = detail_type_list_for_test;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class exit<typename boost::mpl::at<application::traits_type_list_type, type::traits::command>::type>;
#endif

    template class exit<typename boost::mpl::at<test::traits_type_list_type, type::traits::command>::type>;


}}
