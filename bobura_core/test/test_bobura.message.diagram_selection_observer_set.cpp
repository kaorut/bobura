/*! \file
    \brief Test of class bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using size_type = boost::mpl::at<bobura::common_type_list, bobura::type::size>::type;

    using difference_type = boost::mpl::at<bobura::common_type_list, bobura::type::difference>::type;

    using string_type = boost::mpl::at<bobura::common_type_list, bobura::type::string>::type;

    using model_type =
        bobura::timetable_model<
            size_type,
            difference_type,
            string_type,
            boost::mpl::at<bobura::common_type_list, bobura::type::operating_distance>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::speed>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::fast_font>::type
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
