/*! \file
    \brief The definition of type lists for bobura::message.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELISTIMPL_H)
#define BOBURA_MESSAGE_TYPELISTIMPL_H

#include <boost/mpl/pair.hpp>

#include <tetengo2.h>

#include <bobura/message/about_dialog.h>
#include <bobura/message/type_list.h>


namespace bobura { namespace message
{
    namespace about_dialog
    {
        /*!
            \brief The meta function for the type list of the about dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        using type_list =
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
            tetengo2::meta::assoc_list_end
            >;
    }


}}


#endif
