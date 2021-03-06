/*! \file
    \brief The definition of bobura::view::timetable::train_list.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/train_list.h>
#include <bobura/view/timetable/utility.h>


namespace bobura::view::timetable {
    template <typename Traits>
    class train_list<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using dimension_type = typename canvas_type::dimension_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename train_list::model_type;


        // constructors and destructor

        impl(
            const direction_type /*direction*/,
            const model_type& model,
            const message_catalog_type& /*message_catalog*/,
            canvas_type& /*canvas*/,
            const dimension_type& /*canvas_dimension*/
            )
        : m_p_general_color{ &*model.timetable().font_color_set().general().timetable_color() }
        {}

        impl(impl&& another) : m_p_general_color{ another.m_p_general_color } {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_general_color = another.m_p_general_color;

            return *this;
        }

        void draw_on_impl(canvas_type& /*canvas*/) const {}


    private:
        // types

        using color_type = typename canvas_type::color_type;


        // variables

        const color_type* m_p_general_color;
    };


    template <typename Traits>
    train_list<Traits>::train_list(
        const direction_type        direction,
        const model_type&           model,
        const message_catalog_type& message_catalog,
        canvas_type&                canvas,
        const dimension_type&       canvas_dimension)
    : base_type{}, m_p_impl{ std::make_unique<impl>(direction, model, message_catalog, canvas, canvas_dimension) }
    {}

    template <typename Traits>
    train_list<Traits>::train_list(train_list&& another)
    : base_type{}, m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    train_list<Traits>::~train_list() noexcept
    {}

    template <typename Traits>
    train_list<Traits>& train_list<Traits>::operator=(train_list&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void train_list<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
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
    template class train_list<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class train_list<typename test::traits_type_list_type::timetable_view_type>;
}
