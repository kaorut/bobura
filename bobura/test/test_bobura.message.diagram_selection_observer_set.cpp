/*! \file
    \brief Test of class bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using station_type = model_type::timetable_type::station_location_type::station_type;

    using train_type = model_type::timetable_type::train_type;

    using observer_set_type = bobura::message::diagram_selection_observer_set<station_type, train_type>;


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
