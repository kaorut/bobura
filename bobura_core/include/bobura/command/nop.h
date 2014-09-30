/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NOP_H)
#define BOBURA_COMMAND_NOP_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a no-operation command.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class nop : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = command_base<traits_type>;


        // constructors and destructor

        /*!
            \brief Create a no-operation command.
        */
        nop();

        /*!
            \brief Destroys a no-operation command.
        */
        virtual ~nop()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
