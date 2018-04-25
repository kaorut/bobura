/*! \file
    \brief Test of class bobura::view::utility.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/detail_type_list.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable_info/font_color_set.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/utility.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using model_type = bobura::
        timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

    using font_color_set_type = model_type::timetable_type::font_color_set_type;

    using font_color_type = font_color_set_type::font_color_type;

    using station_grade_type_set_type = bobura::model::station_info::grade_type_set<string_type>;

    using grade_type = station_grade_type_set_type::grade_type;
}

BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(view)
        // test cases

        BOOST_AUTO_TEST_CASE(select_station_font_color)
        {
            BOOST_TEST_PASSPOINT();

            const auto& font_color_set = font_color_set_type::default_();

            {
                const auto& font_color =
                    bobura::view::select_station_font_color<font_color_set_type, station_grade_type_set_type>(
                        font_color_set, station_grade_type_set_type::local_type::instance());

                BOOST_TEST(&font_color == &font_color_set.local_station());
            }
            {
                const auto& font_color =
                    bobura::view::select_station_font_color<font_color_set_type, station_grade_type_set_type>(
                        font_color_set, station_grade_type_set_type::principal_type::instance());

                BOOST_TEST(&font_color == &font_color_set.principal_station());
            }
            {
                const auto& font_color =
                    bobura::view::select_station_font_color<font_color_set_type, station_grade_type_set_type>(
                        font_color_set, station_grade_type_set_type::local_terminal_type::instance());

                BOOST_TEST(&font_color == &font_color_set.local_terminal_station());
            }
            {
                const auto& font_color =
                    bobura::view::select_station_font_color<font_color_set_type, station_grade_type_set_type>(
                        font_color_set, station_grade_type_set_type::principal_terminal_type::instance());

                BOOST_TEST(&font_color == &font_color_set.principal_terminal_station());
            }
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
