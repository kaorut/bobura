/*! \file
    \brief The definition of bobura::command::vertically_zoom_out.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_VERTICALLYZOOMOUT_H)
#define BOBURA_COMMAND_VERTICALLYZOOMOUT_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/diagram_view.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a vertical zoom-out command.

        \tparam Traits           A traits type.
        \tparam CommandSetTraits A command set traits type.
        \tparam MainWindowTraits A main window traits type.
        \tparam ViewTraits       A view traits type.
    */
    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits, typename ViewTraits>
    class vertically_zoom_out : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The command set traits type.
        using command_set_traits_type = CommandSetTraits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The diagram view type.
        using diagram_view_type = diagram_view<view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a vertical zoom-out command.

            \param diagram_view A diagram view.
        */
        explicit vertically_zoom_out(diagram_view_type& diagram_view);

        /*!
            \brief Destroys the vertical zoom-out command.
        */
        virtual ~vertically_zoom_out()
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
