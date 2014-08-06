/*! \file
    \brief The definition of bobura::application.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>
#include <chrono>
#include <memory>

#include <boost/mpl/at.hpp>
#include <boost/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/application.h>
#include <bobura/config_traits.h>
#include <bobura/main_window.h>
#include <bobura/main_window_menu_builder.h>
#include <bobura/message/type_list.h>
#include <bobura/message/type_list_impl.h>


namespace bobura
{
    namespace
    {
        using model_type = boost::mpl::at<model_type_list, type::model::model>::type;

        using model_message_type_list_type =
            bobura::message::timetable_model::type_list<
                boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type,
                boost::mpl::at<bobura::view_type_list, bobura::type::view::view>::type,
                boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::main_window>::type
            >;

        using view_type = boost::mpl::at<view_type_list, type::view::view>::type;

        using diagram_view_message_type_list_type =
            bobura::message::diagram_view::type_list<
                boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::property_bar>::type,
                boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type,
                boost::mpl::at<bobura::model_type_list, bobura::type::model::station_grade_type_set>::type,
                boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type
            >;

        using message_catalog_type = boost::mpl::at<locale_type_list, type::locale::message_catalog>::type;

        using confirm_file_save_type = boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type;

        using new_file_type = boost::mpl::at<load_save_type_list, type::load_save::new_file>::type;

        using load_from_file_type = boost::mpl::at<load_save_type_list, type::load_save::load_from_file>::type;

        using save_to_file_type = boost::mpl::at<load_save_type_list, type::load_save::save_to_file>::type;

        using command_set_type = boost::mpl::at<main_window_type_list, type::main_window::command_set>::type;

        using main_window_type = boost::mpl::at<main_window_type_list, type::main_window::main_window>::type;

        using diagram_picture_box_type =
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box>::type;

        using main_window_message_type_list_type =
            boost::mpl::at<main_window_type_list, type::main_window::message_type_list>::type;

        using diagram_picture_box_message_type_list =
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box_message_type_list>::type;

        using message_loop_type = boost::mpl::at<ui_type_list, type::ui::message_loop>::type;

        using gui_fixture_type = boost::mpl::at<ui_type_list, type::ui::gui_fixture>::type;

        using mouse_capture_type = boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type;

        using mouse_button_type = mouse_capture_type::mouse_button_type;

        using timer_type = boost::mpl::at<ui_type_list, type::ui::timer>::type;


    }


    template <typename String, typename Position, typename Dimension, typename ConfigTraits>
    class application<String, Position, Dimension, ConfigTraits>::impl : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The configuration traits type.
        using config_traits_type = ConfigTraits;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type, config_traits_type>;


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
                main_window_menu_builder(
                    command_set_holder.command_set(), m_model, main_window, message_catalog
                ).build()
            );
            main_window.set_visible(true);

            load_input_file(main_window, command_set_holder.command_set());

            return message_loop_type{ main_window }();
        }


    private:
        // types

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
            m_model.observer_set().reset().connect(
                boost::mpl::at<model_message_type_list_type, message::timetable_model::type::reset>::type{
                    m_model, view, main_window
                }
            );
            m_model.observer_set().changed().connect(
                boost::mpl::at<model_message_type_list_type, message::timetable_model::type::changed>::type{
                    m_model, view, main_window
                }
            );

            view.selection_observer_set().station_selected().connect(
                boost::mpl::at<
                    diagram_view_message_type_list_type, message::diagram_view::type::station_selected
                >::type{ main_window.property_bar(), m_model, message_catalog }
            );
            view.selection_observer_set().train_selected().connect(
                boost::mpl::at<diagram_view_message_type_list_type, message::diagram_view::type::train_selected>::type{
                    main_window.property_bar(), m_model, message_catalog
                }
            );
            view.selection_observer_set().all_unselected().connect(
                boost::mpl::at<diagram_view_message_type_list_type, message::diagram_view::type::all_unselected>::type{
                    main_window.property_bar()
                }
            );
            
            main_window.file_drop_observer_set().file_dropped().connect(
                boost::mpl::at<main_window_message_type_list_type, message::main_window::type::file_dropped>::type{
                    command_set, m_model, main_window
                }
            );
            main_window.size_observer_set().resized().connect(
                boost::mpl::at<main_window_message_type_list_type, message::main_window::type::window_resized>::type{
                    view, main_window, main_window.diagram_picture_box(), main_window.property_bar()
                }
            );

            main_window.diagram_picture_box().mouse_observer_set().pressed().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_pressed
                >::type(
                    main_window.diagram_picture_box(),
                    [&main_window](const mouse_button_type mouse_button)
                    {
                        main_window.diagram_picture_box().set_mouse_capture(mouse_button);
                    },
                    view
                )
            );
            main_window.diagram_picture_box().mouse_observer_set().released().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_released
                >::type(
                    [&main_window](const mouse_button_type mouse_button)
                    {
                        return main_window.diagram_picture_box().release_mouse_capture(mouse_button);
                    },
                    view
                )
            );
            main_window.diagram_picture_box().mouse_observer_set().moved().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_moved
                >::type{ main_window.diagram_picture_box(), view }
            );
            main_window.diagram_picture_box().mouse_observer_set().wheeled().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::mouse_wheeled
                >::type{ main_window.diagram_picture_box(), view }
            );
            main_window.diagram_picture_box().fast_paint_observer_set().paint().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::paint_paint
                >::type{ main_window.diagram_picture_box(), view }
            );
            assert(main_window.diagram_picture_box().has_vertical_scroll_bar());
            main_window.diagram_picture_box().vertical_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type{ main_window.diagram_picture_box(), view }
            );
            main_window.diagram_picture_box().vertical_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type{ main_window.diagram_picture_box(), view }
            );
            assert(main_window.diagram_picture_box().has_horizontal_scroll_bar());
            main_window.diagram_picture_box().horizontal_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type{ main_window.diagram_picture_box(), view }
            );
            main_window.diagram_picture_box().horizontal_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                boost::mpl::at<
                    diagram_picture_box_message_type_list, message::diagram_picture_box::type::scroll_bar_scrolled
                >::type{ main_window.diagram_picture_box(), view }
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


    template <typename String, typename Position, typename Dimension, typename ConfigTraits>
    application<String, Position, Dimension, ConfigTraits>::application(settings_type& settings)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(settings))
    {}

    template <typename String, typename Position, typename Dimension, typename ConfigTraits>
    application<String, Position, Dimension, ConfigTraits>::~application()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename String, typename Position, typename Dimension, typename ConfigTraits>
    int application<String, Position, Dimension, ConfigTraits>::run()
    {
        return m_p_impl->run();
    }


    template class application<
        boost::mpl::at<common_type_list, type::string>::type,
        boost::mpl::at<ui_type_list, type::ui::position>::type,
        boost::mpl::at<ui_type_list, type::ui::dimension>::type,
        config_traits<
            boost::mpl::at<common_type_list, type::string>::type,
            boost::mpl::at<common_type_list, type::size>::type,
            boost::mpl::at<locale_type_list, type::locale::config_encoder>::type,
            boost::mpl::at<detail_type_list, type::detail::config>::type
        >
    >;


}
