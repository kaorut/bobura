/*! \file
    \brief The definition of utilities for bobura::view.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_UTILITY_H)
#define BOBURA_VIEW_UTILITY_H


namespace bobura::view {
    // types

    /*!
        \brief Selects the station font and color.

        \tparam FontColorSet        A font and color set type.
        \tparam StationGradeTypeSet A station grade type set type.

        \param font_color_set A font and color set.
        \param grade          A grade.

        \return The station font and color.
    */
    template <typename FontColorSet, typename StationGradeTypeSet>
    const typename FontColorSet::font_color_type& select_station_font_color(
        const FontColorSet&                             font_color_set,
        const typename StationGradeTypeSet::grade_type& grade);
}


#endif
