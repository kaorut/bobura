/*! \file
    \brief The definition of bobura::command::show_timetable_down.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/command/show_timetable_down.h>
#include <bobura/detail_type_list.h>
#include <bobura/main_window.h>
#include <bobura/type_list.h>


namespace bobura::command {
    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits>
    class show_timetable_down<Traits, CommandSetTraits, MainWindowTraits>::impl : private boost::noncopyable
    {
    public:
        // types

        using command_set_traits_type = typename show_timetable_down::command_set_traits_type;

        using main_window_traits_type = typename show_timetable_down::main_window_traits_type;

        using abstract_window_type = typename show_timetable_down::abstract_window_type;

        using model_type = typename show_timetable_down::model_type;


        // functions

        void execute(TETENGO2_STDALT_MAYBE_UNUSED model_type& model, abstract_window_type& parent) const
        {
            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            p_main_window->show_timetable_down_tab();
        }


    private:
        // types

        using main_window_type = main_window<main_window_traits_type, command_set_traits_type>;
    };


    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits>
    show_timetable_down<Traits, CommandSetTraits, MainWindowTraits>::show_timetable_down()
    : m_p_impl{ std::make_unique<impl>() }
    {}

    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits>
    show_timetable_down<Traits, CommandSetTraits, MainWindowTraits>::~show_timetable_down() noexcept
    {}

    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits>
    void show_timetable_down<Traits, CommandSetTraits, MainWindowTraits>::execute_impl(
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
    template class show_timetable_down<
        typename application::traits_type_list_type::command_type,
        typename application::traits_type_list_type::command_set_type,
        typename application::traits_type_list_type::main_window_type>;
#endif

    template class show_timetable_down<
        typename test::traits_type_list_type::command_type,
        typename test::traits_type_list_type::command_set_type,
        typename test::traits_type_list_type::main_window_type>;
}
