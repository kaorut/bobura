/*! \file
    \brief The definition of bobura::detail_type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_DETAILTYPELIST_H)
#define BOBURA_DETAILTYPELIST_H

#include <boost/mpl/pair.hpp>

#if defined(USE_TETENGO2_DETAIL_TYPES_FOR_APPLICATION)
#   include <tetengo2/detail/windows/alert.h>
#   include <tetengo2/detail/windows/common_dialog.h>
#   include <tetengo2/detail/windows/config.h>
#   include <tetengo2/detail/windows/cursor.h>
#   include <tetengo2/detail/windows/direct2d/drawing.h>
#   include <tetengo2/detail/windows/encoding.h>
#   include <tetengo2/detail/windows/gdiplus/drawing.h>
#   include <tetengo2/detail/windows/gdiplus/gui_fixture.h>
#   include <tetengo2/detail/windows/gui_fixture.h>
#   include <tetengo2/detail/windows/icon.h>
#   include <tetengo2/detail/windows/menu.h>
#   include <tetengo2/detail/windows/message_handler.h>
#   include <tetengo2/detail/windows/message_loop.h>
#   include <tetengo2/detail/windows/mouse_capture.h>
#   include <tetengo2/detail/windows/scroll.h>
#   include <tetengo2/detail/windows/shell.h>
#   include <tetengo2/detail/windows/system_color.h>
#   include <tetengo2/detail/windows/timer.h>
#   include <tetengo2/detail/windows/unit.h>
#   include <tetengo2/detail/windows/virtual_key.h>
#   include <tetengo2/detail/windows/widget.h>
#else
#   include <tetengo2/detail/stub/alert.h>
#   include <tetengo2/detail/stub/common_dialog.h>
#   if BOOST_COMP_MSVC
#       include <tetengo2/detail/windows/config.h>
#   else
#       include <tetengo2/detail/unixos/config.h>
#   endif
#   include <tetengo2/detail/stub/cursor.h>
#   include <tetengo2/detail/stub/drawing.h>
#   if BOOST_COMP_MSVC
#       include <tetengo2/detail/windows/encoding.h>
#   else
#       include <tetengo2/detail/unixos/encoding.h>
#   endif
#   include <tetengo2/detail/stub/gui_fixture.h>
#   include <tetengo2/detail/stub/icon.h>
#   include <tetengo2/detail/stub/menu.h>
#   include <tetengo2/detail/stub/message_handler.h>
#   include <tetengo2/detail/stub/message_loop.h>
#   include <tetengo2/detail/stub/mouse_capture.h>
#   include <tetengo2/detail/stub/scroll.h>
#   include <tetengo2/detail/stub/shell.h>
#   include <tetengo2/detail/stub/system_color.h>
#   include <tetengo2/detail/stub/timer.h>
#   include <tetengo2/detail/stub/unit.h>
#   include <tetengo2/detail/stub/virtual_key.h>
#   include <tetengo2/detail/stub/widget.h>
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
        using alert_type = tetengo2::detail::windows::alert;
        using common_dialog_type = tetengo2::detail::windows::common_dialog;
        using config_type = tetengo2::detail::windows::config;
        using cursor_type = tetengo2::detail::windows::cursor;
        using drawing_type = tetengo2::detail::windows::gdiplus::drawing;
        using fast_drawing_type = tetengo2::detail::windows::direct2d::drawing;
        using encoding_type = tetengo2::detail::windows::encoding;
        struct gui_fixture_type
        {
            tetengo2::detail::windows::gui_fixture m_windows_gui_fixture;
            tetengo2::detail::windows::gdiplus::gui_fixture m_gdiplus_gui_fixutre;
        };
        using icon_type = tetengo2::detail::windows::icon;
        using menu_type = tetengo2::detail::windows::menu;
        using message_handler_type = tetengo2::detail::windows::message_handler;
        using message_loop_type = tetengo2::detail::windows::message_loop;
        using mouse_capture_type = tetengo2::detail::windows::mouse_capture;
        using scroll_type = tetengo2::detail::windows::scroll;
        using shell_type = tetengo2::detail::windows::shell;
        using system_color_type = tetengo2::detail::windows::system_color;
        using timer_type = tetengo2::detail::windows::timer;
        using unit_type = tetengo2::detail::windows::unit;
        using virtual_key_type = tetengo2::detail::windows::virtual_key;
        using widget_type = tetengo2::detail::windows::widget;
#else
        using alert_type = tetengo2::detail::stub::alert;
        using common_dialog_type = tetengo2::detail::stub::common_dialog;
#   if BOOST_COMP_MSVC
        using config_type = tetengo2::detail::windows::config;
#   else
        using config_type = tetengo2::detail::unixos::config;
#   endif
        using cursor_type = tetengo2::detail::stub::cursor;
        using drawing_type = tetengo2::detail::stub::drawing;
        using fast_drawing_type = tetengo2::detail::stub::drawing;
#   if BOOST_COMP_MSVC
        using encoding_type = tetengo2::detail::windows::encoding;
#   else
        using encoding_type = tetengo2::detail::unixos::encoding;
#   endif
        struct gui_fixture_type
        {
            tetengo2::detail::stub::gui_fixture m_stub_gui_fixture;
        };
        using icon_type = tetengo2::detail::stub::icon;
        using menu_type = tetengo2::detail::stub::menu;
        using message_handler_type = tetengo2::detail::stub::message_handler;
        using message_loop_type = tetengo2::detail::stub::message_loop;
        using mouse_capture_type = tetengo2::detail::stub::mouse_capture;
        using scroll_type = tetengo2::detail::stub::scroll;
        using shell_type = tetengo2::detail::stub::shell;
        using system_color_type = tetengo2::detail::stub::system_color;
        using timer_type = tetengo2::detail::stub::timer;
        using unit_type = tetengo2::detail::stub::unit;
        using virtual_key_type = tetengo2::detail::stub::virtual_key;
        using widget_type = tetengo2::detail::stub::widget;
#endif
    }}
#endif

    //! The detail type list.
    using detail_type_list =
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
        >>>>>>>>>>>>>>>>>>>>;


}


#endif
