/*! \file
    \brief The definition of utilities for bobura::view::timetable.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/predef.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>


namespace bobura { namespace view { namespace timetable {
    template <typename Size>
    Size normal_line_width()
    {
        return Size{ typename Size::value_type{ 1, 12 } };
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

            using canvas_type = application::traits_type_list_type::timetable_view_type::canvas_type;

            using dimension_unit_type = canvas_type::dimension_unit_type;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

            using canvas_type = test::traits_type_list_type::timetable_view_type::canvas_type;

            using dimension_unit_type = canvas_type::dimension_unit_type;
        }
    }

#if BOOST_COMP_MSVC
    template application::dimension_unit_type normal_line_width();
#endif

#if !defined(DOCUMENTATION)
    template test::dimension_unit_type normal_line_width();
#endif


}}}
