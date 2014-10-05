/*! \file
    \brief The definition of bobura::command::set_vertical_scale.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SETVERTICALSCALE_H)
#define BOBURA_COMMAND_SETVERTICALSCALE_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/diagram_view.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a set-vertical-scale command.

        \tparam Traits           A traits type.
        \tparam MainWindowTraits A main window traits type.
        \tparam ViewTraits       A view traits type.
        \tparam Scale            A scale type.
    */
    template <typename Traits, typename MainWindowTraits, typename ViewTraits, typename Scale>
    class set_vertical_scale : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The scale type.
        using scale_type = Scale;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The diagram view type.
        using diagram_view_type = diagram_view<view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a set-vertical-scale command.

            \param diagram_view A diagram view.
            \param scale        A scale.
        */
        set_vertical_scale(diagram_view_type& diagram_view, const scale_type& scale);

        /*!
            \brief Destroys the set-vertical-scale command.
        */
        virtual ~set_vertical_scale()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual state_type state_impl()
        const override;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
