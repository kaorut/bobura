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

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Scale             A scale type.
        \tparam Canvas            A canvas type.
        \tparam SolidBackground   A solid background type.
        \tparam PictureBox        A picture box type.
        \tparam MessageCatalog    A message catalog type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Scale,
        typename Canvas,
        typename SolidBackground,
        typename PictureBox,
        typename MessageCatalog
    >
    class zoom : boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The scale type.
        using scale_type = Scale;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The solid background type.
        using solid_background_type = SolidBackground;

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The diagram view type.
        using diagram_view_type =
            diagram_view<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                canvas_type,
                solid_background_type,
                message_catalog_type
            >;

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
