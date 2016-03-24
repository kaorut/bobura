/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/command/command_base.h>
#include <bobura/command/set.h>
#include <bobura/main_window.h>
#include <bobura/message/main_window.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <typename Traits, typename CommandSetTraits>
    class main_window<Traits, CommandSetTraits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename main_window::traits_type;

        using string_type = typename main_window::string_type;

        using base_type = typename main_window::base_type;

        using icon_type = typename main_window::icon_type;

        using window_state_type = typename main_window::window_state_type;

        using abstract_window_type = typename main_window::abstract_window_type;

        using message_catalog_type = typename main_window::message_catalog_type;

        using tab_frame_type = typename main_window::tab_frame_type;

        using view_picture_box_type = typename main_window::view_picture_box_type;

        using property_bar_type = typename main_window::property_bar_type;
        
        using settings_type = typename main_window::settings_type;

        using confirm_file_save_type = typename main_window::confirm_file_save_type;


        // constructors and destructor

        impl(
            base_type&                    base,
            const message_catalog_type&   message_catalog,
            settings_type&                settings,
            const confirm_file_save_type& confirm_file_save
        )
        :
        m_base(base),
        m_message_catalog(message_catalog),
        m_p_tab_frame(),
        m_p_diagram_view_picture_box(),
        m_p_timetable_down_view_picture_box(),
        m_p_timetable_up_view_picture_box(),
        m_p_property_bar(),
        m_settings(settings),
        m_confirm_file_save(confirm_file_save)
        {
            initialize_window();
        }


        // functions

        void set_title(const boost::optional<string_type>& document_name, const bool changed)
        {
            auto title = document_name ? *document_name : m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));
            if (changed)
                title += string_type{ TETENGO2_TEXT(" *") };
            title += string_type{ TETENGO2_TEXT(" - ") };
            title += m_message_catalog.get(TETENGO2_TEXT("App:Bobura"));

            m_base.set_text(title);
        }

        const tab_frame_type& get_tab_frame()
        const
        {
            assert(m_p_tab_frame);
            return *m_p_tab_frame;
        }

        tab_frame_type& get_tab_frame()
        {
            assert(m_p_tab_frame);
            return *m_p_tab_frame;
        }

        void show_diagram_tab()
        {
            assert(m_p_tab_frame);
            assert(
                &m_p_tab_frame->tab_at(0).body().template get<view_picture_box_type>() ==
                m_p_diagram_view_picture_box.get()
            );
            m_p_tab_frame->select_tab(0);
        }

        void show_timetable_down_tab()
        {
            assert(m_p_tab_frame);
            assert(
                &m_p_tab_frame->tab_at(1).body().template get<view_picture_box_type>() ==
                m_p_timetable_down_view_picture_box.get()
            );
            m_p_tab_frame->select_tab(1);
        }

        void show_timetable_up_tab()
        {
            assert(m_p_tab_frame);
            assert(
                &m_p_tab_frame->tab_at(2).body().template get<view_picture_box_type>() ==
                m_p_timetable_up_view_picture_box.get()
            );
            m_p_tab_frame->select_tab(2);
        }

        const view_picture_box_type& get_diagram_view_picture_box()
        const
        {
            assert(m_p_diagram_view_picture_box);
            return *m_p_diagram_view_picture_box;
        }

        view_picture_box_type& get_diagram_view_picture_box()
        {
            assert(m_p_diagram_view_picture_box);
            return *m_p_diagram_view_picture_box;
        }

        const view_picture_box_type& get_timetable_down_view_picture_box()
        const
        {
            assert(m_p_timetable_down_view_picture_box);
            return *m_p_timetable_down_view_picture_box;
        }

        view_picture_box_type& get_timetable_down_view_picture_box()
        {
            assert(m_p_timetable_down_view_picture_box);
            return *m_p_timetable_down_view_picture_box;
        }

        const view_picture_box_type& get_timetable_up_view_picture_box()
        const
        {
            assert(m_p_timetable_up_view_picture_box);
            return *m_p_timetable_up_view_picture_box;
        }

        view_picture_box_type& get_timetable_up_view_picture_box()
        {
            assert(m_p_timetable_up_view_picture_box);
            return *m_p_timetable_up_view_picture_box;
        }

        const property_bar_type& get_property_bar()
        const
        {
            assert(m_p_property_bar);
            return *m_p_property_bar;
        }

        property_bar_type& get_property_bar()
        {
            assert(m_p_property_bar);
            return *m_p_property_bar;
        }


    private:
        // types

        using message_loop_break_type = typename traits_type::message_loop_break_type;

        using main_window_window_closing_observer_type =
            message::main_window::window_closing<abstract_window_type, confirm_file_save_type>;


        // variables

        base_type& m_base;

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<tab_frame_type> m_p_tab_frame;

        std::unique_ptr<view_picture_box_type> m_p_diagram_view_picture_box;

        std::unique_ptr<view_picture_box_type> m_p_timetable_down_view_picture_box;

        std::unique_ptr<view_picture_box_type> m_p_timetable_up_view_picture_box;

        std::unique_ptr<property_bar_type> m_p_property_bar;

        settings_type& m_settings;

        const confirm_file_save_type& m_confirm_file_save;


        // functions

        void initialize_window()
        {
            m_p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(m_base);

            m_p_diagram_view_picture_box = tetengo2::stdalt::make_unique<view_picture_box_type>(*m_p_tab_frame);
            m_p_tab_frame->tab_at(0).label().set_title(m_message_catalog.get(TETENGO2_TEXT("Tab:Diagram")));

            m_p_timetable_down_view_picture_box = tetengo2::stdalt::make_unique<view_picture_box_type>(*m_p_tab_frame);
            m_p_tab_frame->tab_at(1).label().set_title(m_message_catalog.get(TETENGO2_TEXT("Tab:Timetable (Down)")));

            m_p_timetable_up_view_picture_box = tetengo2::stdalt::make_unique<view_picture_box_type>(*m_p_tab_frame);
            m_p_tab_frame->tab_at(2).label().set_title(m_message_catalog.get(TETENGO2_TEXT("Tab:Timetable (Up)")));

            m_p_property_bar = tetengo2::stdalt::make_unique<property_bar_type>(m_base, m_settings, m_message_catalog);

            set_message_observers();

            set_window_icon();
            set_title(boost::none, false);
                
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
            auto dimension = m_settings.main_window_dimension();
            if (dimension)
                m_base.set_dimension(std::move(*dimension));
            const auto maximized = m_settings.main_window_maximized();
            if (maximized && *maximized)
                m_base.set_window_state(window_state_type::maximized);
            else
                m_base.set_window_state(window_state_type::normal);
#endif

            show_diagram_tab();
        }

        void set_message_observers()
        {
            m_base.focus_observer_set().got_focus().connect(
                [this]() { this->m_p_diagram_view_picture_box->set_focus(); }
            );
            m_base.paint_observer_set().paint_background().disconnect_all_slots();
            m_base.paint_observer_set().paint_background().connect(
                [](typename base_type::canvas_type&)
                {
                    return true;
                }
            );
            m_base.window_observer_set().closing().connect(
                main_window_window_closing_observer_type{
                    m_base, m_confirm_file_save, [this]() { this->save_settings(); }
                }
            );
            m_base.window_observer_set().destroyed().connect([](){ return message_loop_break_type{}(0); });
        }

        void set_window_icon()
        {
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(
                    m_settings.image_directory_path() / string_type{ TETENGO2_TEXT("bobura_app.ico") }
                );
            m_base.set_icon(std::move(p_icon));
#endif
        }

        void save_settings()
        {
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
            m_settings.set_main_window_dimension(m_base.normal_dimension());
            m_settings.set_main_window_maximized(m_base.window_state() == window_state_type::maximized);

            m_p_property_bar->save_settings();
#endif
        }


    };


    template <typename Traits, typename CommandSetTraits>
    main_window<Traits, CommandSetTraits>::main_window(
        const message_catalog_type&   message_catalog,
        settings_type&                settings,
        const confirm_file_save_type& confirm_file_save
    )
    :
    base_type(base_type::scroll_bar_style_type::none, true),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(*this, message_catalog, settings, confirm_file_save))
    {}

    template <typename Traits, typename CommandSetTraits>
    main_window<Traits, CommandSetTraits>::~main_window()
    noexcept
    {}

    template <typename Traits, typename CommandSetTraits>
    void main_window<Traits, CommandSetTraits>::set_title(
        const boost::optional<string_type>& document_name,
        const bool                          changed
    )
    {
        m_p_impl->set_title(document_name, changed);
    }

    template <typename Traits, typename CommandSetTraits>
    const typename main_window<Traits, CommandSetTraits>::tab_frame_type&
    main_window<Traits, CommandSetTraits>::get_tab_frame()
    const
    {
        return m_p_impl->get_tab_frame();
    }

    template <typename Traits, typename CommandSetTraits>
    typename main_window<Traits, CommandSetTraits>::tab_frame_type&
    main_window<Traits, CommandSetTraits>::get_tab_frame()
    {
        return m_p_impl->get_tab_frame();
    }

    template <typename Traits, typename CommandSetTraits>
    void main_window<Traits, CommandSetTraits>::show_diagram_tab()
    {
        m_p_impl->show_diagram_tab();
    }

    template <typename Traits, typename CommandSetTraits>
    void main_window<Traits, CommandSetTraits>::show_timetable_down_tab()
    {
        m_p_impl->show_timetable_down_tab();
    }

    template <typename Traits, typename CommandSetTraits>
    void main_window<Traits, CommandSetTraits>::show_timetable_up_tab()
    {
        m_p_impl->show_timetable_up_tab();
    }

    template <typename Traits, typename CommandSetTraits>
    const typename main_window<Traits, CommandSetTraits>::view_picture_box_type&
    main_window<Traits, CommandSetTraits>::get_diagram_view_picture_box()
    const
    {
        return m_p_impl->get_diagram_view_picture_box();
    }

    template <typename Traits, typename CommandSetTraits>
    typename main_window<Traits, CommandSetTraits>::view_picture_box_type&
    main_window<Traits, CommandSetTraits>::get_diagram_view_picture_box()
    {
        return m_p_impl->get_diagram_view_picture_box();
    }

    template <typename Traits, typename CommandSetTraits>
    const typename main_window<Traits, CommandSetTraits>::view_picture_box_type& 
    main_window<Traits, CommandSetTraits>::get_timetable_down_view_picture_box()
    const
    {
        return m_p_impl->get_timetable_down_view_picture_box();
    }

    template <typename Traits, typename CommandSetTraits>
    typename main_window<Traits, CommandSetTraits>::view_picture_box_type&
    main_window<Traits, CommandSetTraits>::get_timetable_down_view_picture_box()
    {
        return m_p_impl->get_timetable_down_view_picture_box();
    }

    template <typename Traits, typename CommandSetTraits>
    const typename main_window<Traits, CommandSetTraits>::view_picture_box_type& 
    main_window<Traits, CommandSetTraits>::get_timetable_up_view_picture_box()
    const
    {
        return m_p_impl->get_timetable_up_view_picture_box();
    }

    template <typename Traits, typename CommandSetTraits>
    typename main_window<Traits, CommandSetTraits>::view_picture_box_type&
    main_window<Traits, CommandSetTraits>::get_timetable_up_view_picture_box()
    {
        return m_p_impl->get_timetable_up_view_picture_box();
    }

    template <typename Traits, typename CommandSetTraits>
    const typename main_window<Traits, CommandSetTraits>::property_bar_type&
    main_window<Traits, CommandSetTraits>::get_property_bar()
    const
    {
        return m_p_impl->get_property_bar();
    }

    template <typename Traits, typename CommandSetTraits>
    typename main_window<Traits, CommandSetTraits>::property_bar_type&
    main_window<Traits, CommandSetTraits>::get_property_bar()
    {
        return m_p_impl->get_property_bar();
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
    template class main_window<
        typename application::traits_type_list_type::main_window_type,
        typename application::traits_type_list_type::command_set_type
    >;
#endif

    template class main_window<
        typename test::traits_type_list_type::main_window_type, typename test::traits_type_list_type::command_set_type
    >;


}
