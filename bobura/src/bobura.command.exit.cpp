/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <tetengo2/stdalt.h>
#include <tetengo2/utility.h>

#include "bobura.command.exit.h"


namespace bobura { namespace command
{
    class exit::impl
    {
    public:
        // types

        using model_type = exit::model_type;

        using abstract_window_type = exit::abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            tetengo2::suppress_unused_variable_warning(model);

            parent.close();
        }


    };


    exit::exit()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    exit::~exit()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void exit::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
