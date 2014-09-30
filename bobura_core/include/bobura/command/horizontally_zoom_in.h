/*! \file
    \brief The definition of bobura::command::horizontally_zoom_in.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_HORIZONTALLYZOOMIN_H)
#define BOBURA_COMMAND_HORIZONTALLYZOOMIN_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a horizontal zoom-in command.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class horizontally_zoom_in : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The diagram view type.
        using diagram_view_type = boost::mpl::at<view_type_list, type::view::view>::type;


        // constructors and destructor

        /*!
            \brief Creates a horizontal zoom-in command.

            \param diagram_view A diagram view.
        */
        explicit horizontally_zoom_in(diagram_view_type& diagram_view);

        /*!
            \brief Destroys the horizontal zoom-in command.
        */
        virtual ~horizontally_zoom_in()
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
