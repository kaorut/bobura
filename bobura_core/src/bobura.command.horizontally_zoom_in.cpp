/*! \file
    \brief The definition of bobura::command::horizontally_zoom_in.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/command/horizontally_zoom_in.h>
#include <bobura/detail_type_list.h>
#include <bobura/main_window.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura::command {
    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits, typename DiagramViewTraits>
    class horizontally_zoom_in<Traits, CommandSetTraits, MainWindowTraits, DiagramViewTraits>::impl
    {
    public:
        // types

        using mouse_capture_type = typename horizontally_zoom_in::mouse_capture_type;

        using command_set_traits_type = typename horizontally_zoom_in::command_set_traits_type;

        using main_window_traits_type = typename horizontally_zoom_in::main_window_traits_type;

        using diagram_view_traits_type = typename horizontally_zoom_in::diagram_view_traits_type;

        using diagram_view_type = typename horizontally_zoom_in::diagram_view_type;

        using abstract_window_type = typename horizontally_zoom_in::abstract_window_type;

        using model_type = typename horizontally_zoom_in::model_type;


        // constructors and destructor

        explicit impl(diagram_view_type& diagram_view) : m_diagram_view{ diagram_view } {}


        // functions

        void execute(TETENGO2_STDALT_MAYBE_UNUSED model_type& model, abstract_window_type& parent) const
        {
            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom{ p_main_window->get_diagram_view_picture_box(), m_diagram_view };

            zoom.horizontally_zoom_in(true);
        }


    private:
        // types

        using main_window_type = main_window<main_window_traits_type, command_set_traits_type>;

        using zoom_type = view::diagram::
            zoom<diagram_view_traits_type, typename main_window_traits_type::picture_box_type, mouse_capture_type>;


        // variables

        diagram_view_type& m_diagram_view;
    };


    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits, typename DiagramViewTraits>
    horizontally_zoom_in<Traits, CommandSetTraits, MainWindowTraits, DiagramViewTraits>::horizontally_zoom_in(
        diagram_view_type& diagram_view)
    : m_p_impl{ std::make_unique<impl>(diagram_view) }
    {}

    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits, typename DiagramViewTraits>
    horizontally_zoom_in<Traits, CommandSetTraits, MainWindowTraits, DiagramViewTraits>::
        ~horizontally_zoom_in() noexcept
    {}

    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits, typename DiagramViewTraits>
    void horizontally_zoom_in<Traits, CommandSetTraits, MainWindowTraits, DiagramViewTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent) const
    {
        m_p_impl->execute(model, parent);
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
    template class horizontally_zoom_in<
        typename application::traits_type_list_type::command_type,
        typename application::traits_type_list_type::command_set_type,
        typename application::traits_type_list_type::main_window_type,
        typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class horizontally_zoom_in<
        typename test::traits_type_list_type::command_type,
        typename test::traits_type_list_type::command_set_type,
        typename test::traits_type_list_type::main_window_type,
        typename test::traits_type_list_type::diagram_view_type>;
}
