/*! \file
    \brief The definition of bobura::timetable_view.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_view.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <typename Traits>
    class timetable_view<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename timetable_view::position_type;

        using dimension_type = typename timetable_view::dimension_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename timetable_view::model_type;


        // constructors and destructor

        impl(const model_type& model, const message_catalog_type& message_catalog)
        :
        m_model(model),
        m_message_catalog(message_catalog)
        {}


        // functions

        void draw_on(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            boost::ignore_unused(canvas, canvas_dimension, scroll_bar_position);
        }

        const dimension_type& dimension()
        const
        {
            static const dimension_type singleton{ width_type{ 42 }, height_type{ 24 } };
            return singleton;
        }

        void update_dimension()
        {

        }

        dimension_type page_size(const dimension_type& canvas_dimension)
        const
        {
            boost::ignore_unused(canvas_dimension);

            return dimension_type{ width_type{ 42 }, height_type{ 24 } };
        }

        void unselect_all_items()
        {

        }


    private:
        // types

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;


        // variables

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;


    };


    template <typename Traits>
    timetable_view<Traits>::timetable_view(const model_type& model, const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(model, message_catalog))
    {}

    template <typename Traits>
    timetable_view<Traits>::~timetable_view()
    noexcept
    {}

    template <typename Traits>
    void timetable_view<Traits>::draw_on(
        canvas_type&          canvas,
        const dimension_type& canvas_dimension,
        const position_type&  scroll_bar_position
    )
    {
        m_p_impl->draw_on(canvas, canvas_dimension, scroll_bar_position);
    }

    template <typename Traits>
    const typename timetable_view<Traits>::dimension_type& timetable_view<Traits>::dimension()
    const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void timetable_view<Traits>::update_dimension()
    {
        m_p_impl->update_dimension();
    }

    template <typename Traits>
    typename timetable_view<Traits>::dimension_type timetable_view<Traits>::page_size(
        const dimension_type& canvas_dimension
    )
    const
    {
        return m_p_impl->page_size(canvas_dimension);
    }

    template <typename Traits>
    void timetable_view<Traits>::unselect_all_items()
    {
        m_p_impl->unselect_all_items();
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
    template class timetable_view<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class timetable_view<typename test::traits_type_list_type::timetable_view_type>;


}
