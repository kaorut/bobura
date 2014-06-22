/*! \file
    \brief The definition of bobura::command::horizontally_zoom_out.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_HORIZONTALLYZOOMOUT_H)
#define BOBURA_COMMAND_HORIZONTALLYZOOMOUT_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/command_base.h>

namespace bobura { namespace command
{
    /*!
        \brief The class for a horizontal zoom-out command.
    */
    class horizontally_zoom_out : public command_base
    {
    public:
        // types

        //! The base type.
        using base_type = command_base;

        //! The diagram view type.
        using diagram_view_type = boost::mpl::at<view_type_list, type::view::view>::type;


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