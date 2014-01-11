/*! \file
    \brief The definition of bobura::detail_type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_DETAILTYPELIST_H)
#define BOBURA_DETAILTYPELIST_H

#include <boost/mpl/pair.hpp>

#if defined(USE_TETENGO2_DETAIL_TYPES_FOR_APPLICATION)
#   include <tetengo2.detail.windows.alert.h>
#   include <tetengo2.detail.windows.common_dialog.h>
#   include <tetengo2.detail.windows.config.h>
#   include <tetengo2.detail.windows.cursor.h>
#   include <tetengo2.detail.windows.direct2d.drawing.h>
#   include <tetengo2.detail.windows.encoding.h>
#   include <tetengo2.detail.windows.gdiplus.drawing.h>
#   include <tetengo2.detail.windows.gdiplus.gui_fixture.h>
#   include <tetengo2.detail.windows.gui_fixture.h>
#   include <tetengo2.detail.windows.icon.h>
#   include <tetengo2.detail.windows.menu.h>
#   include <tetengo2.detail.windows.message_handler.h>
#   include <tetengo2.detail.windows.message_loop.h>
#   include <tetengo2.detail.windows.mouse_capture.h>
#   include <tetengo2.detail.windows.scroll.h>
#   include <tetengo2.detail.windows.shell.h>
#   include <tetengo2.detail.windows.system_color.h>
#   include <tetengo2.detail.windows.timer.h>
#   include <tetengo2.detail.windows.unit.h>
#   include <tetengo2.detail.windows.virtual_key.h>
#   include <tetengo2.detail.windows.widget.h>
#else
#   include <tetengo2.detail.stub.alert.h>
#   include <tetengo2.detail.stub.common_dialog.h>
#   include <tetengo2.detail.stub.config.h>
#   include <tetengo2.detail.stub.cursor.h>
#   include <tetengo2.detail.stub.drawing.h>
#   include <tetengo2.detail.stub.encoding.h>
#   include <tetengo2.detail.stub.gui_fixture.h>
#   include <tetengo2.detail.stub.icon.h>
#   include <tetengo2.detail.stub.menu.h>
#   include <tetengo2.detail.stub.message_handler.h>
#   include <tetengo2.detail.stub.message_loop.h>
#   include <tetengo2.detail.stub.mouse_capture.h>
#   include <tetengo2.detail.stub.scroll.h>
#   include <tetengo2.detail.stub.shell.h>
#   include <tetengo2.detail.stub.system_color.h>
#   include <tetengo2.detail.stub.timer.h>
#   include <tetengo2.detail.stub.unit.h>
#   include <tetengo2.detail.stub.virtual_key.h>
#   include <tetengo2.detail.stub.widget.h>
#endif


namespace bobura
{
    /**** Detail Implementation *********************************************/

    namespace type { namespace detail
    {
        struct alert;          //!< The detail implementation type of the alert.
        struct common_dialog;  //!< The detail implementation type of the common dialogs.
        struct config;         //!< The detail implementation type of the configuration.
        struct cursor;         //!< The detail implementation type of the cursor.
        struct drawing;        //!< The detail implementation type of the drawing.
        struct fast_drawing;   //!< The detail implementation type of the fast drawing.
        struct encoding;       //!< The detail implementation type of the encoding.
        struct gui_fixture;    //!< The detail implementation type of the GUI fixture.
        struct icon;           //!< The detail implementation type of the icon.
        struct menu;           //!< The detail implementation type of the menu.
        struct message_handler; //!< The detail implementation type of the message handler.
        struct message_loop;   //!< The detail implementation type of the message loop.
        struct mouse_capture;  //!< The detail implementation type of the mouse capture.
        struct scroll;         //!< The detail implementation type of the scroll.
        struct shell;          //!< The detail implementation type of the shell.
        struct system_color;   //!< The detail implementation type of the system color.
        struct timer;          //!< The detail implementation type of the timer.
        struct unit;           //!< The detail implementation type of the unit.
        struct virtual_key;    //!< The detail implementation type of the virtual key.
        struct widget;         //!< The detail implementation type of the widget.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
#if defined(USE_TETENGO2_DETAIL_TYPES_FOR_APPLICATION)
        typedef tetengo2::detail::windows::alert alert_type;
        typedef tetengo2::detail::windows::common_dialog common_dialog_type;
        typedef tetengo2::detail::windows::config config_type;
        typedef tetengo2::detail::windows::cursor cursor_type;
        typedef tetengo2::detail::windows::gdiplus::drawing drawing_type;
        typedef tetengo2::detail::windows::direct2d::drawing fast_drawing_type;
        typedef tetengo2::detail::windows::encoding encoding_type;
        struct gui_fixture_type
        {
            tetengo2::detail::windows::gui_fixture m_windows_gui_fixture;
            tetengo2::detail::windows::gdiplus::gui_fixture m_gdiplus_gui_fixutre;
        };
        typedef tetengo2::detail::windows::icon icon_type;
        typedef tetengo2::detail::windows::menu menu_type;
        typedef tetengo2::detail::windows::message_handler message_handler_type;
        typedef tetengo2::detail::windows::message_loop message_loop_type;
        typedef tetengo2::detail::windows::mouse_capture mouse_capture_type;
        typedef tetengo2::detail::windows::scroll scroll_type;
        typedef tetengo2::detail::windows::shell shell_type;
        typedef tetengo2::detail::windows::system_color system_color_type;
        typedef tetengo2::detail::windows::timer timer_type;
        typedef tetengo2::detail::windows::unit unit_type;
        typedef tetengo2::detail::windows::virtual_key virtual_key_type;
        typedef tetengo2::detail::windows::widget widget_type;
#else
        typedef tetengo2::detail::stub::alert alert_type;
        typedef tetengo2::detail::stub::common_dialog common_dialog_type;
        typedef tetengo2::detail::stub::config config_type;
        typedef tetengo2::detail::stub::cursor cursor_type;
        typedef tetengo2::detail::stub::drawing drawing_type;
        typedef tetengo2::detail::stub::drawing fast_drawing_type;
        typedef tetengo2::detail::stub::encoding encoding_type;
        struct gui_fixture_type
        {
            tetengo2::detail::stub::gui_fixture m_stub_gui_fixture;
        };
        typedef tetengo2::detail::stub::icon icon_type;
        typedef tetengo2::detail::stub::menu menu_type;
        typedef tetengo2::detail::stub::message_handler message_handler_type;
        typedef tetengo2::detail::stub::message_loop message_loop_type;
        typedef tetengo2::detail::stub::mouse_capture mouse_capture_type;
        typedef tetengo2::detail::stub::scroll scroll_type;
        typedef tetengo2::detail::stub::shell shell_type;
        typedef tetengo2::detail::stub::system_color system_color_type;
        typedef tetengo2::detail::stub::timer timer_type;
        typedef tetengo2::detail::stub::unit unit_type;
        typedef tetengo2::detail::stub::virtual_key virtual_key_type;
        typedef tetengo2::detail::stub::widget widget_type;
#endif
    }}
#endif

    //! The detail type list.
    typedef
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::alert, detail::detail::alert_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::common_dialog, detail::detail::common_dialog_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::cursor, detail::detail::cursor_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::config, detail::detail::config_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::drawing, detail::detail::drawing_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::fast_drawing, detail::detail::fast_drawing_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::encoding, detail::detail::encoding_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::gui_fixture, detail::detail::gui_fixture_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::icon, detail::detail::icon_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::menu, detail::detail::menu_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::message_handler, detail::detail::message_handler_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::message_loop, detail::detail::message_loop_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::mouse_capture, detail::detail::mouse_capture_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::scroll, detail::detail::scroll_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::shell, detail::detail::shell_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::system_color, detail::detail::system_color_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::timer, detail::detail::timer_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::unit, detail::detail::unit_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::virtual_key, detail::detail::virtual_key_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::widget, detail::detail::widget_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>>>
        detail_type_list;


}


#endif
