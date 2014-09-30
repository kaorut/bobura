/*! \file
    \brief The definition of bobura::command::set_vertical_scale.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SETVERTICALSCALE_H)
#define BOBURA_COMMAND_SETVERTICALSCALE_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a set-vertical-scale command.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class set_vertical_scale : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The diagram view type.
        using diagram_view_type = boost::mpl::at<view_type_list, type::view::view>::type;

        //! The scale list type.
        using scale_list_type = boost::mpl::at<view_type_list, type::view::scale_list>::type;

        //! The scale type.
        using scale_type = scale_list_type::scale_type;


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
