/*! \file
    \brief The definition of bobura::application.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>
#include <chrono>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/mpl/at.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/application.h>
#include <bobura/command/command_base.h>
#include <bobura/command/set.h>
#include <bobura/diagram_picture_box.h>
#include <bobura/diagram_view.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/load_from_file.h>
#include <bobura/load_save/new_file.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/main_window.h>
#include <bobura/main_window_menu_builder.h>
#include <bobura/message/timetable_model.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <typename Traits>
    class application<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename application::traits_type;

        using position_type = typename application::position_type;

        using dimension_type = typename application::dimension_type;

        using config_traits_type = typename application::config_traits_type;

        using settings_type = typename application::settings_type;


        // constructors and destructor

        explicit impl(settings_type& settings)
        :
        m_gui_fixture(),
        m_settings(settings),
        m_model(),
        m_p_input_file_load_timer()
        {}


        // functions

        int run()
        {
            const message_catalog_type message_catalog{};
            view_type view{ m_model, message_catalog };
            const command_set_holder_type command_set_holder{ m_settings, m_model, view, message_catalog };

            main_window_type main_window(message_catalog, m_settings, command_set_holder.confirm_file_save()); 
            set_message_observers(command_set_holder.command_set(), view, main_window, message_catalog);
            m_model.reset_timetable();
            main_window.set_menu_bar(
                main_window_menu_builder_type(
                    command_set_holder.command_set(), m_model, main_window, message_catalog
                ).build()
            );
            main_window.set_visible(true);

            load_input_file(main_window, command_set_holder.command_set());

            return message_loop_type{ main_window }();
        }


    private:
        // types

        using size_type = typename traits_type::size_type;
        
        using difference_type = typename traits_type::difference_type;

        using string_type = typename traits_type::string_type;

        using operating_distance_type = typename traits_type::operating_distance_type;

        using speed_type = typename traits_type::speed_type;

        using font_type = typename traits_type::font_type;

        using model_type =
            timetable_model<
                size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
            >;

        using view_traits_type = typename traits_type::view_traits_type;

        using view_type = diagram_view<view_traits_type>;

        using main_window_traits_type = typename traits_type::main_window_traits_type;

        using command_set_traits_type = typename traits_type::command_set_traits_type;

        using main_window_type = main_window<main_window_traits_type, command_set_traits_type>;

        using model_reset_observer_type = message::timetable_model::reset<model_type, view_type, main_window_type>;

        using model_changed_observer_type = message::timetable_model::changed<model_type, view_type, main_window_type>;

        using abstract_window_type = typename traits_type::abstract_window_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using diagram_view_message_type_list_type =
            message::diagram_view::type_list<
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                operating_distance_type,
                speed_type,
                font_type,
                abstract_window_type,
                typename traits_type::side_bar_type,
                typename traits_type::map_box_type,
                config_traits_type,
                message_catalog_type
            >;

        using load_save_traits_type = typename traits_type::load_save_traits_type;

        using confirm_file_save_type = load_save::confirm_file_save<load_save_traits_type>;

        using new_file_type = load_save::new_file<load_save_traits_type>;

        using load_from_file_type = load_save::load_from_file<load_save_traits_type>;

        using save_to_file_type = load_save::save_to_file<load_save_traits_type>;

        using command_set_type = command::set<command_set_traits_type>;

        using main_window_menu_builder_type =
            main_window_menu_builder<typename traits_type::main_window_menu_builder_traits_type>;

        using picture_box_type = typename traits_type::picture_box_type;

        using mouse_capture_type = typename traits_type::mouse_capture_type;

        using diagram_picture_box_message_type_list =
            message::diagram_picture_box::type_list<
                picture_box_type, abstract_window_type, mouse_capture_type, view_traits_type
            >;

        using main_window_message_type_list_type =
            message::main_window::type_list<
                typename traits_type::popup_menu_type,
                command_set_type,
                typename command_set_type::command_type,
                model_type,
                view_type,
                abstract_window_type,
                diagram_picture_box<
                    picture_box_type, abstract_window_type, mouse_capture_type, diagram_picture_box_message_type_list
                >,
                typename main_window_type::property_bar_type,
                confirm_file_save_type
            >;

        using message_loop_type = typename traits_type::message_loop_type;

        using gui_fixture_type = typename traits_type::gui_fixture_type;

        using mouse_button_type = typename mouse_capture_type::mouse_button_type;

        using timer_type = typename traits_type::timer_type;

        class command_set_holder_type : private boost::noncopyable
        {
        public:
            command_set_holder_type(
                settings_type&              settings,
                model_type&                 model,
                view_type&                  view,
                const message_catalog_type& message_catalog
            )
            :
            m_save_to_file(false, message_catalog),
            m_ask_file_path_and_save_to_file(true, message_catalog),
            m_confirm_file_save(model, m_save_to_file, message_catalog),
            m_new_file(m_confirm_file_save),
            m_reload(false, m_confirm_file_save, message_catalog),
            m_load_from_file(true, m_confirm_file_save, message_catalog),
            m_command_set(
                m_new_file,
                m_load_from_file,
                m_reload,
                m_save_to_file,
                m_ask_file_path_and_save_to_file,
                view,
                settings,
                message_catalog
            )
            {}

            const confirm_file_save_type& confirm_file_save()
            const
            {
                return m_confirm_file_save;
            }

            const command_set_type& command_set()
            const
            {
                return m_command_set;
            }

        private:
            const save_to_file_type m_save_to_file;

            const save_to_file_type m_ask_file_path_and_save_to_file;

            const confirm_file_save_type m_confirm_file_save;

            const new_file_type m_new_file;

            const load_from_file_type m_reload;

            const load_from_file_type m_load_from_file;

            const command_set_type m_command_set;

        };


        // variables

        const gui_fixture_type m_gui_fixture;

        settings_type& m_settings;

        model_type m_model;

        std::unique_ptr<timer_type> m_p_input_file_load_timer;


        // functions

        void set_message_observers(
            const command_set_type&     command_set,
            view_type&                  view,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        )
        {
            m_model.observer_set().reset().connect(model_reset_observer_type{ m_model, view, main_window });
            m_model.observer_set().changed().connect(model_changed_observer_type{ m_model, view, main_window });

            view.selection_observer_set().station_selected().connect(
                typename boost::mpl::at<
                    diagram_view_message_type_list_type, message::diagram_view::type::station_selected
                >::type{ main_window.get_property_bar(), m_model, message_catalog }
            );
            view.selection_observer_set().train_selected().connect(
                typename boost::mpl::at<
                    diagram_view_message_type_list_type, message::diagram_view::type::train_selected
                >::type{ main_window.get_property_bar(), m_model, message_catalog }
            );
            view.selection_observer_set().all_unselected().connect(
                typename boost::mpl::at<
                    diagram_view_message_type_list_type, message::diagram_view::type::all_unselected
                >::type{ main_window.get_property_bar() }
            );
            
            main_window.file_drop_observer_set().file_dropped().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::file_dropped
                >::type{ command_set, m_model, main_window }
            );
            main_window.size_observer_set().resized().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type, message::main_window::type::window_resized
                >::type{ view, main_window, main_window.get_diagram_picture_box(), main_window.get_property_bar() }
            );

            main_window.get_diagram_picture_box().mouse_observer_set().pressed().connect(
                typename boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_pressed
                >::type(
                    main_window.get_diagram_picture_box(),
                    [&main_window](const mouse_button_type mouse_button)
                    {
                        main_window.get_diagram_picture_box().set_mouse_capture(mouse_button);
                    },
                    view
                )
            );
            main_window.get_diagram_picture_box().mouse_observer_set().released().connect(
                typename boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_released
                >::type(
                    [&main_window](const mouse_button_type mouse_button)
                    {
                        return main_window.get_diagram_picture_box().release_mouse_capture(mouse_button);
                    },
                    view
                )
            );
            main_window.get_diagram_picture_box().mouse_observer_set().moved().connect(
                typename boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_moved
                >::type{ main_window.get_diagram_picture_box(), view }
            );
            main_window.get_diagram_picture_box().mouse_observer_set().wheeled().connect(
                typename boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_wheeled
                >::type{ main_window.get_diagram_picture_box(), view }
            );
            main_window.get_diagram_picture_box().fast_paint_observer_set().paint().connect(
                typename boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::paint_paint
                >::type{ main_window.get_diagram_picture_box(), view }
            );
            using scroll_bar_scrolled_type =
                typename boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type;
            assert(main_window.get_diagram_picture_box().has_vertical_scroll_bar());
            main_window.get_diagram_picture_box().vertical_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                scroll_bar_scrolled_type{ main_window.get_diagram_picture_box(), view }
            );
            main_window.get_diagram_picture_box().vertical_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                scroll_bar_scrolled_type{ main_window.get_diagram_picture_box(), view }
            );
            assert(main_window.get_diagram_picture_box().has_horizontal_scroll_bar());
            main_window.get_diagram_picture_box().horizontal_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                scroll_bar_scrolled_type{ main_window.get_diagram_picture_box(), view }
            );
            main_window.get_diagram_picture_box().horizontal_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                scroll_bar_scrolled_type{ main_window.get_diagram_picture_box(), view }
            );
        }

        void load_input_file(main_window_type& main_window, const command_set_type& command_set)
        {
            if (!m_settings.input())
                return;

            m_p_input_file_load_timer =
                tetengo2::stdalt::make_unique<timer_type>(
                    main_window,
                    [this, &main_window, &command_set](bool& stop)
                    {
                        const auto p_parameter =
                            command_set.create_load_from_file_parameter(*this->m_settings.input());
                        command_set.load_from_file().execute(this->m_model, main_window, *p_parameter);

                        stop = true;
                    },
                    std::chrono::milliseconds(100),
                    true
                );
        }


    };


    template <typename Traits>
    application<Traits>::application(settings_type& settings)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(settings))
    {}

    template <typename Traits>
    application<Traits>::~application()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits>
    int application<Traits>::run()
    {
        return m_p_impl->run();
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application_
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
    template class application<application_::traits_type_list_type::application_type>;
#endif

    template class application<test::traits_type_list_type::application_type>;


}
