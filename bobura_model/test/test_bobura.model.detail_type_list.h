/*! \file
    \brief The definition of test_bobura::model::detail_type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_DETAILTYPELIST_H)
#define TESTBOBURA_MODEL_DETAILTYPELIST_H

#include <boost/mpl/pair.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2/detail/stub/alert.h>
#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/detail/stub/icon.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/detail/stub/scroll.h>
#include <tetengo2/detail/stub/virtual_key.h>
#include <tetengo2/detail/stub/widget.h>
#if BOOST_COMP_MSVC
#   include <tetengo2/detail/windows/config.h>
#   include <tetengo2/detail/windows/encoding.h>
#else
#   include <tetengo2/detail/unixos/config.h>
#   include <tetengo2/detail/unixos/encoding.h>
#endif


namespace test_bobura { namespace model
{
    /**** Detail Implementation *********************************************/

    namespace type { namespace detail
    {
        struct alert;          //!< The alert type.
        struct config;         //!< The configuration type.
        struct drawing;        //!< The drawing type.
        struct cursor;         //!< The cursor type.
        struct encoding;       //!< The encoding type.
        struct icon;           //!< The icon type.
        struct menu;           //!< The menu type.
        struct message_handler; //!< The message handler type.
        struct scroll;         //!< The scroll type.
        struct virtual_key;    //!< The virtual key type.
        struct widget;         //!< The widget type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
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
        using menu_details_type = tetengo2::detail::stub::menu;
        using scroll_details_type = tetengo2::detail::stub::scroll;
        using virtual_key_details_type = tetengo2::detail::stub::virtual_key;
        using widget_details_type = tetengo2::detail::stub::widget;
    }}
#endif

    //! The detail type list.
    using detail_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::alert, detail::detail::alert_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::config, detail::detail::config_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::drawing, detail::detail::drawing_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::cursor, detail::detail::cursor_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::encoding, detail::detail::encoding_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::icon, detail::detail::icon_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::message_handler, detail::detail::message_handler_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::menu, detail::detail::menu_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::scroll, detail::detail::scroll_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<
            type::detail::virtual_key, detail::detail::virtual_key_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::widget, detail::detail::widget_details_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>;


}}


#endif
