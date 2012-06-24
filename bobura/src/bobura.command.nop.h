/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NOP_H)
#define BOBURA_COMMAND_NOP_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a no-operation command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename Model, typename AbstractWindow>
    class nop : public command_base
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The base type.
        typedef command_base base_type;


    private:
        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const
        {
            return true;
        }

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const
        {}


    };


}}


#endif
