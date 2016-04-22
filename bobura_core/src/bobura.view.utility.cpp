/*! \file
    \brief The definition of utilities for bobura::view.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <cassert>
#include <stdexcept>

#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <bobura/model/station_info/grade.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/utility.h>


namespace bobura { namespace view
{
    template <typename FontColorSet, typename StationGradeTypeSet>
    const typename FontColorSet::font_color_type& select_station_font_color(
        const FontColorSet&                             font_color_set,
        const typename StationGradeTypeSet::grade_type& grade
    )
    {
        if      (&grade == &StationGradeTypeSet::local_type::instance())
            return font_color_set.local_station();
        else if (&grade == &StationGradeTypeSet::principal_type::instance())
            return font_color_set.principal_station();
        else if (&grade == &StationGradeTypeSet::local_terminal_type::instance())
            return font_color_set.local_terminal_station();
        else if (&grade == &StationGradeTypeSet::principal_terminal_type::instance())
            return font_color_set.principal_terminal_station();

        assert(false);
        BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown station grade."));
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template const timetable_model<
        application::common_type_list_type::size_type,
        application::common_type_list_type::difference_type,
        application::common_type_list_type::string_type,
        application::common_type_list_type::operating_distance_type,
        application::common_type_list_type::speed_type,
        application::ui_type_list_type::canvas_type::font_type
    >::timetable_type::font_color_set_type::font_color_type&
    select_station_font_color<
        timetable_model<
            application::common_type_list_type::size_type,
            application::common_type_list_type::difference_type,
            application::common_type_list_type::string_type,
            application::common_type_list_type::operating_distance_type,
            application::common_type_list_type::speed_type,
            application::ui_type_list_type::canvas_type::font_type
        >::timetable_type::font_color_set_type,
        model::station_info::grade_type_set<application::common_type_list_type::string_type>
    >(
        const timetable_model<
            application::common_type_list_type::size_type,
            application::common_type_list_type::difference_type,
            application::common_type_list_type::string_type,
            application::common_type_list_type::operating_distance_type,
            application::common_type_list_type::speed_type,
            application::ui_type_list_type::canvas_type::font_type
        >::timetable_type::font_color_set_type&                                                         font_color_set,
        const model::station_info::grade_type_set<application::common_type_list_type::string_type>::grade_type& grade
    );
#endif

#if !defined(DOCUMENTATION)
    template const timetable_model<
        test::common_type_list_type::size_type,
        test::common_type_list_type::difference_type,
        test::common_type_list_type::string_type,
        test::common_type_list_type::operating_distance_type,
        test::common_type_list_type::speed_type,
        test::ui_type_list_type::canvas_type::font_type
    >::timetable_type::font_color_set_type::font_color_type&
    select_station_font_color<
        timetable_model<
            test::common_type_list_type::size_type,
            test::common_type_list_type::difference_type,
            test::common_type_list_type::string_type,
            test::common_type_list_type::operating_distance_type,
            test::common_type_list_type::speed_type,
            test::ui_type_list_type::canvas_type::font_type
        >::timetable_type::font_color_set_type,
        model::station_info::grade_type_set<test::common_type_list_type::string_type>
    >(
        const timetable_model<
            test::common_type_list_type::size_type,
            test::common_type_list_type::difference_type,
            test::common_type_list_type::string_type,
            test::common_type_list_type::operating_distance_type,
            test::common_type_list_type::speed_type,
            test::ui_type_list_type::canvas_type::font_type
        >::timetable_type::font_color_set_type&                                                         font_color_set,
        const model::station_info::grade_type_set<test::common_type_list_type::string_type>::grade_type& grade
    );
#endif


}}
