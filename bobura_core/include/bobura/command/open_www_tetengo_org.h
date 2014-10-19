/*! \file
    \brief The definition of bobura::command::open_www_tetengo_org.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_OPENWWWTETENGOORG_H)
#define BOBURA_COMMAND_OPENWWWTETENGOORG_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an open-www.tetengo.org command.

        \tparam Traits A traits type.
        \tparam Shell  A shell type.
    */
    template <typename Traits, typename Shell>
    class open_www_tetengo_org : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The shell type.
        using shell_type = Shell;

        //! The base type.
        using base_type = command_base<traits_type>;


        // constructors and destructor

        /*!
            \brief Create an open-www.tetengo.org command.
        */
        open_www_tetengo_org();

        /*!
            \brief Destroys the open-www.tetengo.org command.
        */
        virtual ~open_www_tetengo_org()
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
