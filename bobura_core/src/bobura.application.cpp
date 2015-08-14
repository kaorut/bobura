/*! \file
    \brief The definition of bobura::application.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <cassert>
#include <chrono>
#include <memory>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/application.h>
#include <bobura/command/command_base.h>
#include <bobura/command/set.h>
#include <bobura/diagram_view.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/load_from_file.h>
#include <bobura/load_save/new_file.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/main_window.h>
#include <bobura/main_window_menu_builder.h>
#include <bobura/message/diagram_view.h>
#include <bobura/message/main_window.h>
#include <bobura/message/timetable_model.h>
#include <bobura/message/view_picture_box/diagram.h>
#include <bobura/timetable_model.h>
#include <bobura/timetable_view.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/zoom.h>
#include <bobura/view_picture_box.h>


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
            diagram_view_type diagram_view{ m_model, message_catalog };
            timetable_view_type timetable_view{ m_model, message_catalog };
            const command_set_holder_type command_set_holder{ m_settings, m_model, diagram_view, message_catalog };

            main_window_type main_window(message_catalog, m_settings, command_set_holder.confirm_file_save()); 
            set_message_observers(
                command_set_holder.command_set(), diagram_view, timetable_view, main_window, message_catalog
            );
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

        using diagram_view_traits_type = typename traits_type::diagram_view_traits_type;

        using diagram_view_type = diagram_view<diagram_view_traits_type>;

        using timetable_view_traits_type = typename traits_type::timetable_view_traits_type;

        using timetable_view_type = timetable_view<timetable_view_traits_type>;

        using main_window_traits_type = typename traits_type::main_window_traits_type;

        using command_set_traits_type = typename traits_type::command_set_traits_type;

        using main_window_type = main_window<main_window_traits_type, command_set_traits_type>;

        using model_reset_observer_type =
            message::timetable_model::reset<model_type, diagram_view_type, timetable_view_type, main_window_type>;

        using model_changed_observer_type =
            message::timetable_model::changed<model_type, diagram_view_type, timetable_view_type, main_window_type>;

        using abstract_window_type = typename traits_type::abstract_window_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using view_station_selected_observer_type =
            message::diagram_view::station_selected<
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
                message_catalog_type,
                config_traits_type
            >;

        using view_train_selected_observer_type =
            message::diagram_view::train_selected<
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
                message_catalog_type,
                config_traits_type
            >;

        using view_all_unselected_observer_type =
            message::diagram_view::all_unselected<
                string_type,
                position_type,
                dimension_type,
                abstract_window_type,
                typename traits_type::side_bar_type,
                typename traits_type::map_box_type,
                message_catalog_type,
                config_traits_type
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

        using tab_frame_type = typename traits_type::tab_frame_type;

        using view_picture_box_type = view_picture_box<picture_box_type, mouse_capture_type>;

        using main_window_file_dropped_observer_type =
            message::main_window::file_dropped<command_set_type, model_type, abstract_window_type>;

        using main_window_window_resized_observer_type =
            message::main_window::window_resized<
                diagram_view_type,
                timetable_view_type,
                abstract_window_type,
                tab_frame_type,
                view_picture_box_type,
                typename main_window_type::property_bar_type
            >;

        using main_window_window_closing_observer_type =
            message::main_window::window_closing<abstract_window_type, confirm_file_save_type>;

        using diagram_view_picture_box_mouse_pressed_observer_type =
            message::view_picture_box::diagram::mouse_pressed<picture_box_type, diagram_view_traits_type>;

        using diagram_view_picture_box_mouse_released_observer_type =
            message::view_picture_box::diagram::mouse_released<picture_box_type, diagram_view_traits_type>;

        using diagram_view_picture_box_mouse_moved_observer_type =
            message::view_picture_box::diagram::mouse_moved<picture_box_type, diagram_view_traits_type>;

        using diagram_view_picture_box_mouse_wheeled_observer_type =
            message::view_picture_box::diagram::mouse_wheeled<
                picture_box_type,
                view::diagram::zoom<
                    diagram_view_traits_type,  picture_box_type, mouse_capture_type
                >,
                diagram_view_traits_type
            >;

        using diagram_view_picture_box_paint_paint_observer_type =
            message::view_picture_box::diagram::paint_paint<picture_box_type, diagram_view_traits_type>;

        using diagram_view_picture_box_scroll_bar_scrolled_observer_type =
            message::view_picture_box::diagram::scroll_bar_scrolled<picture_box_type, diagram_view_traits_type>;

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
                diagram_view_type&          diagram_view,
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
                diagram_view,
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
            diagram_view_type&          diagram_view,
            timetable_view_type&        timetable_view,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        )
        {
            m_model.observer_set().reset().connect(
                model_reset_observer_type{ m_model, diagram_view, timetable_view, main_window }
            );
            m_model.observer_set().changed().connect(
                model_changed_observer_type{ m_model, diagram_view, timetable_view, main_window }
            );

            set_diagram_view_message_observers(diagram_view, main_window, message_catalog);
            set_timetable_view_message_observers(timetable_view, main_window);

            main_window.size_observer_set().resized().connect(
                main_window_window_resized_observer_type{
                    diagram_view,
                    timetable_view,
                    main_window,
                    main_window.get_tab_frame(),
                    main_window.get_diagram_view_picture_box(),
                    main_window.get_timetable_view_picture_box(),
                    main_window.get_property_bar()
                }
            );
            main_window.file_drop_observer_set().file_dropped().connect(
                main_window_file_dropped_observer_type{ command_set, m_model, main_window }
            );
        }

        void set_diagram_view_message_observers(
            diagram_view_type&          view,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        )
        {
            view.selection_observer_set().station_selected().connect(
                view_station_selected_observer_type( main_window.get_property_bar(), m_model, message_catalog )
            );
            view.selection_observer_set().train_selected().connect(
                view_train_selected_observer_type{ main_window.get_property_bar(), m_model, message_catalog }
            );
            view.selection_observer_set().all_unselected().connect(
                view_all_unselected_observer_type{ main_window.get_property_bar() }
            );
            
            auto& picture_box = main_window.get_diagram_view_picture_box();

            picture_box.mouse_observer_set().pressed().connect(
                diagram_view_picture_box_mouse_pressed_observer_type{
                    picture_box,
                    [&main_window, &picture_box](const mouse_button_type mouse_button)
                    {
                        picture_box.set_mouse_capture(mouse_button);
                    },
                    view
                }
            );
            picture_box.mouse_observer_set().released().connect(
                diagram_view_picture_box_mouse_released_observer_type{
                    [&main_window, &picture_box](const mouse_button_type mouse_button)
                    {
                        return picture_box.release_mouse_capture(mouse_button);
                    },
                    view
                }
            );
            picture_box.mouse_observer_set().moved().connect(
                diagram_view_picture_box_mouse_moved_observer_type{ picture_box, view }
            );
            picture_box.mouse_observer_set().wheeled().connect(
                diagram_view_picture_box_mouse_wheeled_observer_type{ picture_box, view }
            );
            picture_box.fast_paint_observer_set().paint().connect(
                diagram_view_picture_box_paint_paint_observer_type{ picture_box, view }
            );
            assert(picture_box.has_vertical_scroll_bar());
            picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                diagram_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
            picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                diagram_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
            assert(picture_box.has_horizontal_scroll_bar());
            picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                diagram_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
            picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                diagram_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
        }

        void set_timetable_view_message_observers(timetable_view_type& view, main_window_type& main_window)
        {
            boost::ignore_unused(view);

            /*auto& picture_box =*/ main_window.get_timetable_view_picture_box();

/*
            picture_box.mouse_observer_set().pressed().connect(
                timetable_view_picture_box_mouse_pressed_observer_type{
                    picture_box,
                    [&main_window, &picture_box](const mouse_button_type mouse_button)
                    {
                        picture_box.set_mouse_capture(mouse_button);
                    },
                    view
                }
            );
            picture_box.mouse_observer_set().released().connect(
                timetable_view_picture_box_mouse_released_observer_type{
                    [&main_window, &picture_box](const mouse_button_type mouse_button)
                    {
                        return picture_box.release_mouse_capture(mouse_button);
                    },
                    view
                }
            );
            picture_box.mouse_observer_set().moved().connect(
                timetable_view_picture_box_mouse_moved_observer_type{ picture_box, view }
            );
            picture_box.mouse_observer_set().wheeled().connect(
                timetable_view_picture_box_mouse_wheeled_observer_type{ picture_box, view }
            );
            picture_box.fast_paint_observer_set().paint().connect(
                timetable_view_picture_box_paint_paint_observer_type{ picture_box, view }
            );
            assert(picture_box.has_vertical_scroll_bar());
            picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                timetable_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
            picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                timetable_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
            assert(picture_box.has_horizontal_scroll_bar());
            picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                timetable_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
            picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                timetable_view_picture_box_scroll_bar_scrolled_observer_type{ picture_box, view }
            );
*/
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
    noexcept
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
    template class application<typename application_::traits_type_list_type::application_type>;
#endif

    template class application<typename test::traits_type_list_type::application_type>;


}
