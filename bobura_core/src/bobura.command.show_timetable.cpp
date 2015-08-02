/*! \file
    \brief The definition of bobura::command::show_timetable.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/command/show_timetable.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits>
    class show_timetable<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using abstract_window_type = typename show_timetable::abstract_window_type;

        using model_type = typename show_timetable::model_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model, parent);
        }


    };


    template <typename Traits>
    show_timetable<Traits>::show_timetable()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits>
    show_timetable<Traits>::~show_timetable()
    noexcept
    {}
    
    template <typename Traits>
    void show_timetable<Traits>::execute_impl(model_type& model, abstract_window_type& parent)
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
    template class show_timetable<typename application::traits_type_list_type::command_type>;
#endif

    template class show_timetable<typename test::traits_type_list_type::command_type>;


}}
