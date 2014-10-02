/*! \file
    \brief The definition of bobura::command::horizontally_zoom_out.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_HORIZONTALLYZOOMOUT_H)
#define BOBURA_COMMAND_HORIZONTALLYZOOMOUT_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/diagram_view.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a horizontal zoom-out command.

        \tparam Traits     A traits type.
        \tparam ViewTraits A view traits type.
    */
    template <typename Traits, typename ViewTraits>
    class horizontally_zoom_out : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The diagram view type.
        using diagram_view_type = diagram_view<view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a horizontal zoom-out command.

            \param diagram_view A diagram view.
        */
        explicit horizontally_zoom_out(diagram_view_type& diagram_view);

        /*!
            \brief Destroys the horizontal zoom-out command.
        */
        virtual ~horizontally_zoom_out()
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
