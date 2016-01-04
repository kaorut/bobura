/*! \file
    \brief The definition of bobura::command::set_vertical_scale.

    Copyright (C) 2007-2016 kaoru

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

        \tparam Traits            A traits type.
        \tparam Scale             A scale type.
        \tparam CommandSetTraits  A command set traits type.
        \tparam MainWindowTraits  A main window traits type.
        \tparam DiagramViewTraits A diagram view traits type.
    */
    template <
        typename Traits,
        typename Scale,
        typename CommandSetTraits,
        typename MainWindowTraits,
        typename DiagramViewTraits
    >
    class set_vertical_scale : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The scale type.
        using scale_type = Scale;

        //! The command set traits type.
        using command_set_traits_type = CommandSetTraits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The diagram view traits type.
        using diagram_view_traits_type = DiagramViewTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::abstract_window_type;

        //! The model type.
        using model_type = typename base_type::model_type;

        //! The state type.
        using state_type = typename base_type::state_type;

        //! The diagram view type.
        using diagram_view_type = diagram_view<diagram_view_traits_type>;


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
        noexcept;


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
