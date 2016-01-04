/*! \file
    \brief The definition of bobura::view::timetable::item.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/type_list.h>
#include <bobura/view/timetable/item.h>


namespace bobura { namespace view { namespace timetable
{
    template <typename Traits>
    class item<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename canvas_type::position_type;


        // constructors and destructor

        impl()
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            boost::ignore_unused(canvas);
        }


    };


    template <typename Traits>
    item<Traits>::item()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits>
    item<Traits>::~item()
    noexcept
    {}

    template <typename Traits>
    item<Traits>& item<Traits>::operator=(item&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);

        return *this;
    }

    template <typename Traits>
    void item<Traits>::draw_on(canvas_type& canvas)
    const
    {
        draw_on_impl(canvas);
    }

    template <typename Traits>
    void item<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
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
    template class item<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class item<typename test::traits_type_list_type::timetable_view_type>;


}}}
