/*! \file
    \brief The definition of bobura::view::zoom.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <cassert>

#include <boost/mpl/at.hpp>
#include <boost/noncopyable.hpp>

#include "bobura.type_list.h"

#include <tetengo2.unique.h>

#include "bobura.view.zoom.h"


namespace bobura { namespace view
{
    class zoom::impl : private boost::noncopyable
    {
    public:
        // types

        typedef zoom::picture_box_type picture_box_type;

        typedef zoom::diagram_view_type diagram_view_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box>::type
            diagram_picture_box_type;


        // constructors and destructor

        impl(picture_box_type& picture_box, diagram_view_type& diagram_view)
        :
        m_p_diagram_picture_box(dynamic_cast<diagram_picture_box_type*>(&picture_box)),
        m_diagram_view(diagram_view)
        {
            assert(m_p_diagram_picture_box);
        }


        // functions

        void horizontally_zoom_in()
        {

        }

        void horizontally_zoom_out()
        {

        }

        void vertically_zoom_in()
        {

        }

        void vertically_zoom_out()
        {

        }


    private:
        // variables

        diagram_picture_box_type* const m_p_diagram_picture_box;

        diagram_view_type& m_diagram_view;


    };


    zoom::zoom(picture_box_type& picture_box, diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::make_unique<impl>(picture_box, diagram_view))
    {}

    zoom::~zoom()
    {}

    void zoom::horizontally_zoom_in()
    {
        m_p_impl->horizontally_zoom_in();
    }

    void zoom::horizontally_zoom_out()
    {
        m_p_impl->horizontally_zoom_out();
    }

    void zoom::vertically_zoom_in()
    {
        m_p_impl->vertically_zoom_in();
    }

    void zoom::vertically_zoom_out()
    {
        m_p_impl->vertically_zoom_out();
    }


}}
