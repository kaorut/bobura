/*! \file
    \brief The definition of bobura::command::set_vertical_scale.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/command/set_vertical_scale.h>
#include <bobura/main_window.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename Scale,
        typename CommandSetTraits,
        typename MainWindowTraits,
        typename ViewTraits
    >
    class set_vertical_scale<Traits, Scale, CommandSetTraits, MainWindowTraits, ViewTraits>::impl
    {
    public:
        // types

        using mouse_capture_type = typename set_vertical_scale::mouse_capture_type;

        using scale_type = typename set_vertical_scale::scale_type;

        using command_set_traits_type = typename set_vertical_scale::command_set_traits_type;

        using main_window_traits_type = typename set_vertical_scale::main_window_traits_type;

        using view_traits_type = typename set_vertical_scale::view_traits_type;

        using abstract_window_type = typename set_vertical_scale::abstract_window_type;

        using model_type = typename set_vertical_scale::model_type;

        using state_type = typename set_vertical_scale::state_type;

        using diagram_view_type = typename set_vertical_scale::diagram_view_type;


        // constructors and destructor

        impl(diagram_view_type& diagram_view, const scale_type& scale)
        :
        m_diagram_view(diagram_view),
        m_scale(scale)
        {}


        // functions

        state_type state()
        const
        {
            return m_scale == m_diagram_view.vertical_scale() ? state_type::selected : state_type::default_;
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom{ p_main_window->get_diagram_picture_box(), m_diagram_view };

            zoom.set_vertical_scale(m_scale);
        }


    private:
        // types

        using main_window_type = main_window<main_window_traits_type, command_set_traits_type>;

        using zoom_type =
            view::diagram::zoom<
                view_traits_type,
                abstract_window_type,
                typename main_window_traits_type::picture_box_type,
                mouse_capture_type
            >;


        // variables

        diagram_view_type& m_diagram_view;

        scale_type m_scale;


    };


    template <
        typename Traits,
        typename Scale,
        typename CommandSetTraits,
        typename MainWindowTraits,
        typename ViewTraits
    >
    set_vertical_scale<Traits, Scale, CommandSetTraits, MainWindowTraits, ViewTraits>::set_vertical_scale(
        diagram_view_type& diagram_view,
        const scale_type&  scale
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view, scale))
    {}

    template <
        typename Traits,
        typename Scale,
        typename CommandSetTraits,
        typename MainWindowTraits,
        typename ViewTraits
    >
    set_vertical_scale<Traits, Scale, CommandSetTraits, MainWindowTraits, ViewTraits>::~set_vertical_scale()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <
        typename Traits,
        typename Scale,
        typename CommandSetTraits,
        typename MainWindowTraits,
        typename ViewTraits
    >
    typename set_vertical_scale<Traits, Scale, CommandSetTraits, MainWindowTraits, ViewTraits>::state_type
    set_vertical_scale<Traits, Scale, CommandSetTraits, MainWindowTraits, ViewTraits>::state_impl()
    const
    {
        return m_p_impl->state();
    }

    template <
        typename Traits,
        typename Scale,
        typename CommandSetTraits,
        typename MainWindowTraits,
        typename ViewTraits
    >
    void set_vertical_scale<Traits, Scale, CommandSetTraits, MainWindowTraits, ViewTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list_temp::detail_for_application;

            using common_type_list_type = type_list_temp::common;

            using traits_type_list_type = type_list_temp::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list_temp::detail_for_test;

            using common_type_list_type = type_list_temp::common;

            using traits_type_list_type = type_list_temp::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class set_vertical_scale<
        typename application::traits_type_list_type::command_type,
        typename application::common_type_list_type::scale_type,
        typename application::traits_type_list_type::command_set_type,
        typename application::traits_type_list_type::main_window_type,
        typename application::traits_type_list_type::view_type
    >;
#endif

    template class set_vertical_scale<
        typename test::traits_type_list_type::command_type,
        typename test::common_type_list_type::scale_type,
        typename test::traits_type_list_type::command_set_type,
        typename test::traits_type_list_type::main_window_type,
        typename test::traits_type_list_type::view_type
    >;


}}
