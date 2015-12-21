/*! \file
    \brief The definition of bobura::view::timetable::header.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/type_list.h>
#include <bobura/view/timetable/header.h>


namespace bobura { namespace view { namespace timetable
{
    template <typename Traits>
    class header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using dimension_type = typename canvas_type::dimension_type;

        using model_type = typename header::model_type;


        // constructors and destructor

        impl(const model_type& model, canvas_type& canvas, const dimension_type& canvas_dimension)
        :
        m_position(left_type{ 0 }, top_type{ 0 }),
        m_dimension(width_type{ 0 }, height_type{ 0 })
        {
            boost::ignore_unused(model, canvas, canvas_dimension);
        }

        impl(impl&& another)
        :
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            boost::ignore_unused(canvas);
            // TODO Implement it.
        }


    private:
        // types

        using position_type = typename canvas_type::position_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;


        // variables

        position_type m_position;

        dimension_type m_dimension;


    };


    template <typename Traits>
    header<Traits>::header(const model_type& model, canvas_type& canvas, const dimension_type& canvas_dimension)
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(model, canvas, canvas_dimension))
    {}

    template <typename Traits>
    header<Traits>::header(header&& another)
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    header<Traits>::~header()
    noexcept
    {}

    template <typename Traits>
    header<Traits>& header<Traits>::operator=(header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    const typename header<Traits>::dimension_type& header<Traits>::dimension()
    const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void header<Traits>::draw_on_impl(canvas_type& canvas)
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
    template class header<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class header<typename test::traits_type_list_type::timetable_view_type>;


}}}
