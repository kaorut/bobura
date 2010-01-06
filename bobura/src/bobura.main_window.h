/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.GuiTypeList.h>

#include "concept_bobura.command.CommandTypeList.h"
#include "concept_bobura.message.MessageTypeLists.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam GuiTypeList               A GUI type list type. It must
                                          conform to
                                          concept_tetengo2::gui::GuiTypeList<GuiTypeList>.
        \tparam CommandTypeList           A command type. It must conform to
                                          concept_bobura::command::CommandTypeList<CommandTypeList>.
        \tparam MainWindowMessageTypeList A message type. It must conform to
                                          concept_bobura::message::MainWindowMessageTypeList<MainWindowMessageTypeList>.
    */
    template <
        typename GuiTypeList,
        typename CommandTypeList,
        typename MainWindowMessageTypeList
    >
    class main_window : public GuiTypeList::window_type
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::GuiTypeList<GuiTypeList>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_bobura::command::CommandTypeList<CommandTypeList>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_bobura::message::MainWindowMessageTypeList<
                MainWindowMessageTypeList
            >
        ));


    public:
        // types

        //! The GUI type list type.
        typedef GuiTypeList gui_type_list_type;

        //! The window type.
        typedef typename gui_type_list_type::window_type window_type;

        //! \copydoc tetengo2::gui::win32::window::abstract_window_type.
        typedef
            typename window_type::abstract_window_type abstract_window_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::widget_type.
        typedef typename abstract_window_type::widget_type widget_type;

        //! \copydoc tetengo2::gui::win32::widget::handle_type
        typedef typename widget_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::widget::canvas_type
        typedef typename widget_type::canvas_type canvas_type;

        //! \copydoc tetengo2::gui::win32::widget::alert_type
        typedef typename widget_type::alert_type alert_type;

        //! \copydoc tetengo2::gui::win32::widget::difference_type
        typedef typename widget_type::difference_type difference_type;

        //! \copydoc tetengo2::gui::win32::widget::size_type
        typedef typename widget_type::size_type size_type;

        //! \copydoc tetengo2::gui::win32::widget::position_type
        typedef typename widget_type::position_type position_type;

        //! \copydoc tetengo2::gui::win32::widget::dimension_type
        typedef typename widget_type::dimension_type dimension_type;

        //! \copydoc tetengo2::gui::win32::widget::string_type
        typedef typename widget_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_from_native_type
        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_to_native_type
        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        //! \copydoc tetengo2::gui::win32::widget::font_type
        typedef typename widget_type::font_type font_type;

        //! \copydoc tetengo2::gui::win32::widget::child_type
        typedef typename widget_type::child_type child_type;

        //! \copydoc tetengo2::gui::win32::widget::paint_observer_type
        typedef typename widget_type::paint_observer_type paint_observer_type;

        //! \copydoc tetengo2::gui::win32::widget::mouse_observer_type
        typedef typename widget_type::mouse_observer_type mouse_observer_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::main_menu_type.
        typedef typename abstract_window_type::main_menu_type main_menu_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::window_observer_type.
        typedef
            typename abstract_window_type::window_observer_type
            window_observer_type;

        //! The command type list type.
        typedef CommandTypeList command_type_list_type;

        //! The message type list type.
        typedef MainWindowMessageTypeList main_window_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.
        */
        main_window()
        {
            initialize_window(*this);
        }

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        throw ()
        {}


    private:
        //types

        typedef
            typename gui_type_list_type::quit_message_loop_type
            quit_message_loop_type;

        typedef typename main_menu_type::menu_item_type menu_item_type;

        typedef
            typename menu_item_type::menu_observer_type menu_observer_type;

        typedef
            typename gui_type_list_type::menu_command_type menu_command_type;

        typedef typename gui_type_list_type::popup_menu_type popup_menu_type;

        typedef
            typename gui_type_list_type::menu_separator_type
            menu_separator_type;

        typedef typename command_type_list_type::command_type command_type;


        // static functions

        static void initialize_window(main_window& window)
        {
            set_message_observers(window);
            set_menus(window);
#if defined(_MSC_VER)
            window.set_text(L"�ڂ��Ԃ� �e�X�g�v���O����");
#endif
        }

        static void set_message_observers(window_type& window)
        {
            window.add_window_observer(
                std::auto_ptr<window_observer_type>(
                    new typename main_window_message_type_list_type::main_window_window_observer_type(
                        quit_message_loop_type()
                    )
                )
            );

            window.add_paint_observer(
                std::auto_ptr<paint_observer_type>(
                    new typename main_window_message_type_list_type::main_window_paint_observer_type()
                )
            );
        }

        static void set_menus(window_type& window)
        {
            std::auto_ptr<main_menu_type> p_main_menu(new main_menu_type());

#if defined(_MSC_VER)
            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    new popup_menu_type(L"�t�@�C��(&F)")
                );

                append_menu_command(
                    *p_popup_menu,
                    L"�V�K�쐬(&N)\tCtrl+N",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"�J��(&O)...\tCtrl+O",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"�㏑���ۑ�(&S)\tCtrl+S",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"���O��t���ĕۑ�(&A)...",
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    L"�I��(&X)",
                    typename command_type_list_type::exit_type(window)
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }
            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    new popup_menu_type(L"�ҏW(&E)")
                );

                append_menu_command(
                    *p_popup_menu,
                    L"���ɖ߂�(&U)\tCtrl+Z",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"��蒼��(&R)\tCtrl+Y",
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    L"�؂���(&T)\tCtrl+X",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"�R�s�[(&C)\tCtrl+C",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"�\��t��(&P)\tCtrl+V",
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    L"����(&F)...\tCtrl+F",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"�u��(&R)...\tCtrl+H",
                    typename command_type_list_type::nop_type()
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }
            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    new popup_menu_type(L"�w���v(&H)")
                );

                append_menu_command(
                    *p_popup_menu,
                    L"�o�[�W�������(&A)...",
                    typename command_type_list_type::about_type(window)
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }
#endif

            window.set_main_menu(p_main_menu);
        }

        static void append_menu_command(
            popup_menu_type&                            popup_menu,
            const typename menu_item_type::string_type& text,
            const command_type&                         command
        )
        {
            std::auto_ptr<menu_item_type> p_menu_command(
                new menu_command_type(text)
            );

            std::auto_ptr<menu_observer_type> p_menu_observer(
                new typename main_window_message_type_list_type::main_window_menu_observer_type(
                    command
                )
            );
            p_menu_command->add_menu_observer(p_menu_observer);

            popup_menu.insert(
                popup_menu.menu_item_end(), p_menu_command
            );
        }

        static void append_menu_separator(popup_menu_type& popup_menu)
        {
            std::auto_ptr<menu_item_type> p_menu_separator(
                new menu_separator_type()
            );
            popup_menu.insert(
                popup_menu.menu_item_end(), p_menu_separator
            );
        }


    };


}

#endif
