/*! \file
    \brief The definition of bobura::view::diagram::traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_TRAITS_H)
#define BOBURA_VIEW_DIAGRAM_TRAITS_H


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view traits.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Scale             A scale type.
        \tparam Canvas            A canvas type.
        \tparam SolidBackground   A solid background type.
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
        typename MessageCatalog
    >
    class traits
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

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;


    };


}}}


#endif
