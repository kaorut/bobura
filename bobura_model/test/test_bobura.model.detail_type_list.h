/*! \file
    \brief The definition of test_bobura::model::detail_type_list.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_DETAILTYPELIST_H)
#define TESTBOBURA_MODEL_DETAILTYPELIST_H

#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2/detail/stub/alert.h>
#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/detail/stub/icon.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/detail/stub/message_loop.h>
#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/detail/stub/scroll.h>
#include <tetengo2/detail/stub/system_color.h>
#include <tetengo2/detail/stub/timer.h>
#include <tetengo2/detail/stub/virtual_key.h>
#include <tetengo2/detail/stub/widget.h>
#if BOOST_COMP_MSVC
#   include <tetengo2/detail/windows/config.h>
#   include <tetengo2/detail/windows/encoding.h>
#else
#   include <tetengo2/detail/unixos/config.h>
#   include <tetengo2/detail/unixos/encoding.h>
#endif


namespace test_bobura { namespace model { namespace type_list
{
    /**** Detail Implementation **************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
        namespace test
        {
            using alert_details_type = tetengo2::detail::stub::alert;

#if BOOST_COMP_MSVC
            using config_details_type = tetengo2::detail::windows::config;
#else
            using config_details_type = tetengo2::detail::unixos::config;
#endif

            using cursor_details_type = tetengo2::detail::stub::cursor;

            using drawing_details_type = tetengo2::detail::stub::drawing;

#if BOOST_COMP_MSVC
            using encoding_details_type = tetengo2::detail::windows::encoding;
#else
            using encoding_details_type = tetengo2::detail::unixos::encoding;
#endif

            using icon_details_type = tetengo2::detail::stub::icon;

            using message_handler_details_type = tetengo2::detail::stub::message_handler;

            using message_loop_type = tetengo2::detail::stub::message_loop;

            using menu_details_type = tetengo2::detail::stub::menu;

            using scroll_details_type = tetengo2::detail::stub::scroll;

            using virtual_key_details_type = tetengo2::detail::stub::virtual_key;

            using widget_details_type = tetengo2::detail::stub::widget;

            using widget_details_type = tetengo2::detail::stub::widget;

            using timer_details_type = tetengo2::detail::stub::timer;

            using system_color_details_type = tetengo2::detail::stub::system_color;

        }

    }}
#endif

    /*!
        \brief The detail type list for the testing.
    */
    struct detail_for_test
    {
        //! The alert type.
        using alert_type = detail::detail::test::alert_details_type;

        //! The configuration type.
        using config_type = detail::detail::test::config_details_type;

        //! The drawing type.
        using drawing_type = detail::detail::test::drawing_details_type;

        //! The cursor type.
        using cursor_type = detail::detail::test::cursor_details_type;

        //! The encoding type.
        using encoding_type = detail::detail::test::encoding_details_type;

        //! The icon type.
        using icon_type = detail::detail::test::icon_details_type;

        //! The menu type.
        using menu_type = detail::detail::test::menu_details_type;

        //! The message handler type.
        using message_handler_type = detail::detail::test::message_handler_details_type;

        //! The detail implementation type of the message loop.
        using message_loop_type = detail::detail::test::message_loop_type;

        //! The scroll type.
        using scroll_type = detail::detail::test::scroll_details_type;

        //! The virtual key type.
        using virtual_key_type = detail::detail::test::virtual_key_details_type;

        //! The widget type.
        using widget_type = detail::detail::test::widget_details_type;

        //! The timer type.
        using timer_type = detail::detail::test::timer_details_type; 

        //! The system color type.
        using system_color_type = detail::detail::test::system_color_details_type;

    };


}}}


#endif
