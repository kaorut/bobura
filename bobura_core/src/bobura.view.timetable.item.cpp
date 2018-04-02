/*! \file
    \brief The definition of bobura::view::timetable::item.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/item.h>


namespace bobura::view::timetable {
    template <typename Traits>
    class item<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;


        // constructors and destructor

        impl() : m_position{}, m_dimension{} {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            return *this;
        }

        const position_type& position() const
        {
            return m_position;
        }

        position_type& position()
        {
            return m_position;
        }

        const dimension_type& dimension() const
        {
            return m_dimension;
        }

        dimension_type& dimension()
        {
            return m_dimension;
        }

        void draw_on_impl([[maybe_unused]] canvas_type& canvas) const {}

        void set_position(position_type position)
        {
            m_position = std::move(position);
        }

        void set_dimension(dimension_type dimension)
        {
            m_dimension = std::move(dimension);
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;


        // variables

        position_type m_position;

        dimension_type m_dimension;
    };


    template <typename Traits>
    item<Traits>::item() : m_p_impl{ std::make_unique<impl>() }
    {}

    template <typename Traits>
    item<Traits>::~item() noexcept
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
    const typename item<Traits>::position_type& item<Traits>::position() const
    {
        return m_p_impl->position();
    }

    template <typename Traits>
    typename item<Traits>::position_type& item<Traits>::position()
    {
        return m_p_impl->position();
    }

    template <typename Traits>
    const typename item<Traits>::dimension_type& item<Traits>::dimension() const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    typename item<Traits>::dimension_type& item<Traits>::dimension()
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void item<Traits>::draw_on(canvas_type& canvas) const
    {
        draw_on_impl(canvas);
    }

    template <typename Traits>
    void item<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
    }

    template <typename Traits>
    void item<Traits>::set_position(position_type position)
    {
        m_p_impl->set_position(std::move(position));
    }

    template <typename Traits>
    void item<Traits>::set_dimension(dimension_type dimension)
    {
        m_p_impl->set_dimension(std::move(dimension));
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
    template class item<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class item<typename test::traits_type_list_type::timetable_view_type>;
}
