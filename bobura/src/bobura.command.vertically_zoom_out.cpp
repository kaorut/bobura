/*! \file
    \brief The definition of bobura::command::vertically_zoom_out.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/vertically_zoom_out.h>
#include <bobura/main_window.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace command
{
    class vertically_zoom_out::impl
    {
    public:
        // types

        using model_type = vertically_zoom_out::model_type;

        using abstract_window_type = vertically_zoom_out::abstract_window_type;

        using diagram_view_type = vertically_zoom_out::diagram_view_type;


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
            zoom_type zoom{ p_main_window->diagram_picture_box(), m_diagram_view };

            zoom.vertically_zoom_out(true);
        }


    private:
        // types

        using main_window_type = boost::mpl::at<main_window_type_list, type::main_window::main_window>::type;

        using zoom_type =
            view::diagram::zoom<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                boost::mpl::at<model_type_list, type::model::speed>::type,
                boost::mpl::at<view_type_list, type::view::scale>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_solid_background>::type,
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;


        // variables

        diagram_view_type& m_diagram_view;


    };


    vertically_zoom_out::vertically_zoom_out(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view))
    {}

    vertically_zoom_out::~vertically_zoom_out()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void vertically_zoom_out::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
