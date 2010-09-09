/*! \file
    \brief The definition of stub_tetengo2::gui::gui_initializer_finalizer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZER_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZER_H

#include <boost/noncopyable.hpp>

#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    class gui_initializer_finalizer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        gui_initializer_finalizer()
        {}

        ~gui_initializer_finalizer()
        TETENGO2_NOEXCEPT
        {}


    };


}}

#endif
