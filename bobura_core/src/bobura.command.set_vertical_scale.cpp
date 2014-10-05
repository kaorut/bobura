/*! \file
    \brief The definition of bobura::command::set_vertical_scale.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/set_vertical_scale.h>
#include <bobura/command/traits.h>
#include <bobura/main_window.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace command
{
    template <typename Traits, typename MainWindowTraits, typename ViewTraits, typename Scale>
    class set_vertical_scale<Traits, MainWindowTraits, ViewTraits, Scale>::impl
    {
    public:
        // types

        using model_type = typename set_vertical_scale::model_type;

        using abstract_window_type = typename set_vertical_scale::abstract_window_type;

        using main_window_traits_type = typename set_vertical_scale::main_window_traits_type;

        using view_traits_type = typename set_vertical_scale::view_traits_type;

        using diagram_view_type = typename set_vertical_scale::diagram_view_type;

        using scale_type = typename set_vertical_scale::scale_type;


        // constructors and destructor

        impl(diagram_view_type& diagram_view, const scale_type& scale)
        :
        m_diagram_view(diagram_view),
        m_scale(scale)
        {}


        // functions

        state_type state()
        const
        {
            return m_scale == m_diagram_view.vertical_scale() ? state_type::selected : state_type::default_;
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom{ p_main_window->get_diagram_picture_box(), m_diagram_view };

            zoom.set_vertical_scale(m_scale);
        }


    private:
        // types

        using main_window_type = main_window<main_window_traits_type>;

        using zoom_type = view::diagram::zoom<view_traits_type, typename main_window_traits_type::picture_box_type>;


        // variables

        diagram_view_type& m_diagram_view;

        scale_type m_scale;


    };


    template <typename Traits, typename MainWindowTraits, typename ViewTraits, typename Scale>
    set_vertical_scale<Traits, MainWindowTraits, ViewTraits, Scale>::set_vertical_scale(
        diagram_view_type& diagram_view,
        const scale_type&  scale
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view, scale))
    {}

    template <typename Traits, typename MainWindowTraits, typename ViewTraits, typename Scale>
    set_vertical_scale<Traits, MainWindowTraits, ViewTraits, Scale>::~set_vertical_scale()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename MainWindowTraits, typename ViewTraits, typename Scale>
    typename set_vertical_scale<Traits, MainWindowTraits, ViewTraits, Scale>::state_type
    set_vertical_scale<Traits, MainWindowTraits, ViewTraits, Scale>::state_impl()
    const
    {
        return m_p_impl->state();
    }

    template <typename Traits, typename MainWindowTraits, typename ViewTraits, typename Scale>
    void set_vertical_scale<Traits, MainWindowTraits, ViewTraits, Scale>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class set_vertical_scale<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type
        >,
        typename boost::mpl::at<main_window_type_list, type::main_window::traits>::type,
        typename boost::mpl::at<view_type_list, type::view::traits>::type,
        typename boost::mpl::at<view_type_list, type::view::scale>::type
    >;


}}
