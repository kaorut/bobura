/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::list_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_LISTBOX_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_LISTBOX_H

#include <boost/optional.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    namespace list_box
    {
        template <typename ListBox>
        boost::optional< ::LRESULT> on_tetengo2_command(
            ListBox&       list_box,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        {
            suppress_unused_variable_warning(l_param);

            switch (HIWORD(w_param))
            {
            case LBN_SELCANCEL:
            case LBN_SELCHANGE:
                list_box.list_selection_observer_set().selection_changed()();
                break;
            default:
                break;
            }

            return boost::make_optional< ::LRESULT>(0);
        }


    }


}}}}


#endif
#endif
