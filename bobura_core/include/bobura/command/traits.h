/*! \file
    \brief The definition of bobura::command::traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TRAITS_H)
#define BOBURA_COMMAND_TRAITS_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for the command traits.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
        \tparam AbstractWindow    An abstract window type.
        \tparam MouseCapture      A mouse capture type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename AbstractWindow,
        typename MouseCapture
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

        //! The font type.
        using font_type = Font;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The mouse capture type.
        using mouse_capture_type = MouseCapture;


    };


}}


#endif
