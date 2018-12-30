/*! \file
    \brief The definition of utilities for bobura::view::timetable.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_TIMETABLE_UTILITY_H)
#define BOBURA_VIEW_TIMETABLE_UTILITY_H


namespace bobura::view::timetable {
    // types

    /*!
        \brief The direction type.
    */
    enum class direction_type
    {
        down, //!< Down.
        up, //!< Up.
    };


    // functions

    /*!
        \brief Returns the normal line width.

        \tparam Size A size type.

        \return The normal line width.
    */
    template <typename Size>
    Size normal_line_width();
}


#endif
