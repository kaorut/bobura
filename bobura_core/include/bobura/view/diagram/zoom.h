/*! \file
    \brief The definition of bobura::view::diagram::zoom.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_ZOOM_H)
#define BOBURA_VIEW_ZOOM_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <bobura/diagram_view.h>
#include <bobura/view/scale_list.h>


namespace bobura { namespace view { namespace diagram
{
    /*!
        \brief The class template for a zoom of a view.

        \tparam Traits         A traits type.
        \tparam AbstractWindow An abstract window type.
        \tparam PictureBox     A picture box type.
        \tparam MouseCapture   A mouse capture type.
    */
    template <typename Traits, typename AbstractWindow, typename PictureBox, typename MouseCapture>
    class zoom : boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The scale type.
        using scale_type = typename traits_type::scale_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The solid background type.
        using solid_background_type = typename traits_type::solid_background_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The mouse capture type.
        using mouse_capture_type = MouseCapture;

        //! The view type.
        using diagram_view_type = bobura::diagram_view<traits_type>;

        //! The scale list type.
        using scale_list_type = view::scale_list<size_type, string_type, scale_type>;


        // constructors and destructor

        /*!
            \brief Creates a zoom of a view.

            \param picture_box  A picture box.
            \param diagram_view A diagram view.
        */
        zoom(picture_box_type& picture_box, diagram_view_type& diagram_view);

        /*!
            \brief Destroys a zoom of a view.
        */
        ~zoom();


        // functions

        /*!
            \brief Sets a horizontal scale.

            \param scale A scale.
        */
        void set_horizontal_scale(scale_type scale);

        /*!
            \brief Hozirontally zoom in.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void horizontally_zoom_in(bool snap_to_scale_list);

        /*!
            \brief Hozirontally zoom out.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void horizontally_zoom_out(bool snap_to_scale_list);

        /*!
            \brief Sets a vertical scale.

            \param scale A scale.
        */
        void set_vertical_scale(scale_type scale);

        /*!
            \brief Vertically zoom in.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void vertically_zoom_in(bool snap_to_scale_list);

        /*!
            \brief Vertically zoom out.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void vertically_zoom_out(bool snap_to_scale_list);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
