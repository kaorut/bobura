/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/nop.h>
#include <bobura/command/traits.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits>
    class nop<Traits>::impl
    {
    public:
        // types

        using model_type = typename nop::model_type;

        using abstract_window_type = typename nop::abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model, parent);
        }


    };


    template <typename Traits>
    nop<Traits>::nop()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits>
    nop<Traits>::~nop()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits>
    void nop<Traits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class nop<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
            typename boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type
        >
    >;


}}
