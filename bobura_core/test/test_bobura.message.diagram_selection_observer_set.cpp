/*! \file
    \brief Test of class bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using model_type =
        bobura::timetable_model<
            size_type,
            difference_type,
            string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using station_location_type = model_type::timetable_type::station_location_type;

    using observer_set_type =
        bobura::message::diagram_selection_observer_set<
            size_type, difference_type, string_type, station_location_type::operating_distance_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(diagram_selection_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const observer_set_type observer_set{};
    }

    BOOST_AUTO_TEST_CASE(station_selected)
    {
        BOOST_TEST_PASSPOINT();

        {
            const observer_set_type observer_set{};

            observer_set.station_selected();
        }
        {
            observer_set_type observer_set{};

            observer_set.station_selected();
        }
    }

    BOOST_AUTO_TEST_CASE(train_selected)
    {
        BOOST_TEST_PASSPOINT();

        {
            const observer_set_type observer_set{};

            observer_set.train_selected();
        }
        {
            observer_set_type observer_set{};

            observer_set.train_selected();
        }
    }

    BOOST_AUTO_TEST_CASE(all_unselected)
    {
        BOOST_TEST_PASSPOINT();

        {
            const observer_set_type observer_set{};

            observer_set.all_unselected();
        }
        {
            observer_set_type observer_set{};

            observer_set.all_unselected();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
