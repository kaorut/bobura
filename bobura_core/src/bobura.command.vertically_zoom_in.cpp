/*! \file
    \brief The definition of bobura::command::vertically_zoom_in.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/vertically_zoom_in.h>
#include <bobura/command/traits.h>
#include <bobura/main_window.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace command
{
    template <typename Traits, typename MainWindowTraits, typename ViewTraits>
    class vertically_zoom_in<Traits, MainWindowTraits, ViewTraits>::impl
    {
    public:
        // types

        using model_type = typename vertically_zoom_in::model_type;

        using abstract_window_type = typename vertically_zoom_in::abstract_window_type;

        using main_window_traits_type = typename vertically_zoom_in::main_window_traits_type;

        using view_traits_type = typename vertically_zoom_in::view_traits_type;

        using diagram_view_type = typename vertically_zoom_in::diagram_view_type;


        // constructors and destructor

        explicit impl(diagram_view_type& diagram_view)
        :
        m_diagram_view(diagram_view)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom{ p_main_window->get_diagram_picture_box(), m_diagram_view };

            zoom.vertically_zoom_in(true);
        }


    private:
        // types

        using main_window_type = main_window<main_window_traits_type>;

        using zoom_type = view::diagram::zoom<view_traits_type, typename main_window_traits_type::picture_box_type>;


        // variables

        diagram_view_type& m_diagram_view;


    };


    template <typename Traits, typename MainWindowTraits, typename ViewTraits>
    vertically_zoom_in<Traits, MainWindowTraits, ViewTraits>::vertically_zoom_in(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view))
    {}

    template <typename Traits, typename MainWindowTraits, typename ViewTraits>
    vertically_zoom_in<Traits, MainWindowTraits, ViewTraits>::~vertically_zoom_in()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename MainWindowTraits, typename ViewTraits>
    void vertically_zoom_in<Traits, MainWindowTraits, ViewTraits>::execute_impl(
        model_type& model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class vertically_zoom_in<
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
        typename boost::mpl::at<view_type_list, type::view::traits>::type
    >;


}}
