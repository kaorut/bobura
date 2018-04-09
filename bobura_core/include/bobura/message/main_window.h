/*! \file
    \brief The definition of bobura::message::main_window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOW_H)
#define BOBURA_MESSAGE_MAINWINDOW_H

#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/throw_exception.hpp>

#include <tetengo2/stdalt.h>

#include <bobura/command/command_base.h> // IWYU pragma: keep


namespace bobura::message::main_window {
    /*!
        \brief The class template for a popup menu selection observer of the main window.

        \tparam PopupMenu A popup menu type.
        \tparam Command   A command type.
        \tparam Model     A model type.
    */
    template <typename PopupMenu, typename Command, typename Model>
    class popup_menu_selected
    {
    public:
        // types

        //! The popup menu type.
        using popup_menu_type = PopupMenu;

        //! The command type.
        using command_type = Command;

        //! The model type.
        using model_type = Model;


        // constructors and destructor

        /*!
            \brief Creates a popup menu selection observer of the main window.

            \param popup_menu A popup menu type.
            \param commands   Commands.
            \param model      A model.
        */
        popup_menu_selected(
            popup_menu_type&                   popup_menu,
            std::vector<const command_type*>&& commands,
            const model_type&                  model)
        : m_popup_menu{ popup_menu }, m_commands{ commands }, m_model{ model }
        {
            assert(
                static_cast<std::size_t>(std::distance(m_popup_menu.begin(), m_popup_menu.end())) == m_commands.size());
        }


        // functions

        /*!
            \brief Called when the menu is selected.
        */
        void operator()() const
        {
            std::size_t i = 0;
            for (auto& menu_item : m_popup_menu)
            {
                assert(i < m_commands.size());
                const auto* const p_command = m_commands[i];
                if (!p_command)
                {
                    ++i;
                    continue;
                }

                menu_item.set_enabled(p_command->enabled(m_model));
                menu_item.set_state(translate_state(p_command->state()));

                ++i;
            }
        }


    private:
        // types

        using menu_base_type = typename popup_menu_type::base_type::base_type;


        // static functions

        static typename menu_base_type::state_type translate_state(const typename command_type::state_type state)
        {
            switch (state)
            {
            case command_type::state_type::default_:
                return menu_base_type::state_type::default_;
            case command_type::state_type::checked:
                return menu_base_type::state_type::checked;
            case command_type::state_type::selected:
                return menu_base_type::state_type::selected;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid command state."));
            }
        }


        // variables

        popup_menu_type& m_popup_menu;

        std::vector<const command_type*> m_commands;

        const model_type& m_model;
    };


    /*!
        \brief The class template for a menu command selection observer of the main window.

        \tparam Command        A command type.
        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename Command, typename Model, typename AbstractWindow>
    class menu_command_selected
    {
    public:
        // types

        //! The command type.
        using command_type = Command;

        //! The model type.
        using model_type = Model;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;


        // constructors and destructor

        /*!
            \brief Creates a menu command selection observer of the main window.

            \param command A command.
            \param model   A model.
            \param parent  A parent window.
        */
        menu_command_selected(const command_type& command, model_type& model, abstract_window_type& parent)
        : m_command{ command }, m_model{ model }, m_parent{ parent }
        {}


        // functions

        /*!
            \brief Called when the menu is selected.
        */
        void operator()() const
        {
            m_command.execute(m_model, m_parent);
        }


    private:
        // variables

        const command_type& m_command;

        model_type& m_model;

        abstract_window_type& m_parent;
    };


    /*!
        \brief The class template for a file drop observer of the main window.

        \tparam CommandSet     A command set type.
        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename CommandSet, typename Model, typename AbstractWindow>
    class file_dropped
    {
    public:
        // types

        //! The command set type.
        using command_set_type = CommandSet;

        //! The model type.
        using model_type = Model;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;


        // constructors and destructor

        /*!
            \brief Creates a file drop observer of the main window.

            \param command_set A command set.
            \param model       A model.
            \param parent      A parent window.
        */
        file_dropped(const command_set_type& command_set, model_type& model, abstract_window_type& parent)
        : m_command_set{ command_set }, m_model{ model }, m_parent{ parent }
        {}


        // functions

        /*!
            \brief Called when the menu is selected.

            \param paths Paths.
        */
        void operator()(const std::vector<tetengo2::stdalt::filesystem::path>& paths) const
        {
            if (paths.empty())
                return;

            const auto p_paramter = m_command_set.create_load_from_file_parameter(paths[0]);
            m_command_set.load_from_file().execute(m_model, m_parent, *p_paramter);
        }


    private:
        // variables

        const command_set_type& m_command_set;

        model_type& m_model;

        abstract_window_type& m_parent;
    };


    /*!
        \brief The class template for a window resized observer of the main window.

        \tparam DiagramView    A diagram view type.
        \tparam TimetableView  A timetable view type.
        \tparam AbstractWindow An abstract window type.
        \tparam TabFrame       A tab frame type.
        \tparam ViewPictureBox A view picture box type.
        \tparam PropertyBar    A property bar type.
    */
    template <
        typename DiagramView,
        typename TimetableView,
        typename AbstractWindow,
        typename TabFrame,
        typename ViewPictureBox,
        typename PropertyBar>
    class window_resized
    {
    public:
        // types

        //! The diagram view type.
        using diagram_view_type = DiagramView;

        //! The timetable view type.
        using timetable_view_type = TimetableView;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The tab frame type.
        using tab_frame_type = TabFrame;

        //! The view picture box type.
        using view_picture_box_type = ViewPictureBox;

        //! The property bar type.
        using property_bar_type = PropertyBar;


        // constructors and destructor

        /*!
            \brief Creates a window resized observer of the main window.

            \param diagram_view                    A diagram view.
            \param timetable_down_view             A timetable down view.
            \param timetable_up_view               A timetable up view.
            \param window                          A window.
            \param tab_frame                       A tab frame.
            \param diagram_view_picture_box        A diagram view picture box.
            \param timetable_down_view_picture_box A timetable down view picture box.
            \param timetable_up_view_picture_box   A timetable up view picture box.
            \param property_bar                    A property bar.
        */
        window_resized(
            diagram_view_type&     diagram_view,
            timetable_view_type&   timetable_down_view,
            timetable_view_type&   timetable_up_view,
            abstract_window_type&  window,
            tab_frame_type&        tab_frame,
            view_picture_box_type& diagram_view_picture_box,
            view_picture_box_type& timetable_down_view_picture_box,
            view_picture_box_type& timetable_up_view_picture_box,
            property_bar_type&     property_bar)
        : m_diagram_view{ diagram_view }, m_timetable_down_view{ timetable_down_view },
          m_timetable_up_view{ timetable_up_view }, m_window{ window }, m_tab_frame{ tab_frame },
          m_diagram_view_picture_box{ diagram_view_picture_box },
          m_timetable_down_view_picture_box{ timetable_down_view_picture_box },
          m_timetable_up_view_picture_box{ timetable_up_view_picture_box }, m_property_bar{ property_bar }
        {}


        // functions

        /*!
            \brief Called when the main window is resized.
        */
        void operator()() const
        {
            if (m_window.window_state() == window_state_type::minimized)
                return;

            const auto  window_dimension = m_window.client_dimension();
            const auto& window_width = window_dimension.width();
            const auto& window_height = window_dimension.height();
            const auto& property_bar_width = m_property_bar.preferred_width();
            {
                const position_type  position{ position_unit_type::from(window_width) -
                                                  position_unit_type::from(property_bar_width),
                                              position_unit_type{} };
                const dimension_type dimension{ property_bar_width, window_height };
                m_property_bar.set_position_and_dimension(position, dimension);
                m_property_bar.repaint();
                m_property_bar.size_observer_set().resized()();
            }
            {
                const position_type  position{};
                const dimension_type dimension{ window_width > property_bar_width ? window_width - property_bar_width :
                                                                                    dimension_unit_type{},
                                                window_height };
                m_tab_frame.set_position_and_dimension(position, dimension);
                m_tab_frame.repaint();

                m_diagram_view.update_dimension();
                m_diagram_view_picture_box.update_scroll_bars(
                    m_diagram_view.dimension(),
                    m_diagram_view.page_size(m_diagram_view_picture_box.client_dimension()));
                m_diagram_view_picture_box.repaint();

                m_timetable_down_view.update_dimension();
                m_timetable_down_view_picture_box.update_scroll_bars(
                    m_timetable_down_view.dimension(),
                    m_timetable_down_view.page_size(m_timetable_down_view_picture_box.client_dimension()));
                m_timetable_down_view_picture_box.repaint();

                m_timetable_up_view.update_dimension();
                m_timetable_up_view_picture_box.update_scroll_bars(
                    m_timetable_up_view.dimension(),
                    m_timetable_up_view.page_size(m_timetable_up_view_picture_box.client_dimension()));
                m_timetable_up_view_picture_box.repaint();
            }
        }


    private:
        // types

        using window_state_type = typename abstract_window_type::window_state_type;

        using control_type = typename view_picture_box_type::base_type::base_type;

        using position_type = typename control_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_type = typename control_type::dimension_type;

        using dimension_unit_type = typename dimension_type::unit_type;


        // variables

        diagram_view_type& m_diagram_view;

        timetable_view_type& m_timetable_down_view;

        timetable_view_type& m_timetable_up_view;

        abstract_window_type& m_window;

        tab_frame_type& m_tab_frame;

        view_picture_box_type& m_diagram_view_picture_box;

        view_picture_box_type& m_timetable_down_view_picture_box;

        view_picture_box_type& m_timetable_up_view_picture_box;

        property_bar_type& m_property_bar;
    };


    /*!
        \brief The class template for a window closing observer of the main window.

        \tparam AbstractWindow  An abstract window type.
        \tparam ConfirmFileSave A file save confirmation type.
    */
    template <typename AbstractWindow, typename ConfirmFileSave>
    class window_closing
    {
    public:
        // types

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The file save confirmation type.
        using confirm_file_save_type = ConfirmFileSave;

        //! The setting saver type.
        using save_settings_type = std::function<void()>;


        // constructors and destructor

        /*!
            \brief Creates a window closing observer of the main window.

            \param window            A window.
            \param confirm_file_save A file save confirmation.
            \param save_settings     A setting saver.
        */
        window_closing(
            abstract_window_type&         window,
            const confirm_file_save_type& confirm_file_save,
            save_settings_type            save_settings)
        : m_window{ window }, m_confirm_file_save{ confirm_file_save }, m_save_settings{ std::move(save_settings) }
        {}


        // functions

        /*!
            \brief Called when the main window is closing.

            \param cancel Set true to cancel the window closing.
        */
        void operator()(bool& cancel) const
        {
            cancel = !m_confirm_file_save(m_window);
            if (cancel)
                return;

            m_save_settings();
        }


    private:
        // variables

        abstract_window_type& m_window;

        const confirm_file_save_type& m_confirm_file_save;

        const save_settings_type m_save_settings;
    };
}


#endif
