/*! \file
    \brief Test of class bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <bobura/model/station.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable_info/station_location.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::detail_type_list_for_test;

    using common_type_list_type = test_bobura::model::common_type_list<detail_type_list_type>;

    using string_type = boost::mpl::at<common_type_list_type, test_bobura::model::type::string>::type;

    using operating_distance_type =
        boost::mpl::at<common_type_list_type, test_bobura::model::type::operating_distance>::type;

    using station_type = bobura::model::station<string_type>;

    using grade_type_set_type = bobura::model::station_info::grade_type_set<string_type>;

    using local_type = grade_type_set_type::local_type;

    using station_location_type =
        bobura::model::timetable_info::station_location<string_type, operating_distance_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable_info)
BOOST_AUTO_TEST_SUITE(station_location)
    // test cases

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();
        
        const station_location_type station_location{
            station_type(string_type{}, local_type::instance(), false, false, string_type{}), 0
        };
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_location_type station_location1{
                station_type{
                    string_type{ TETENGO2_TEXT("A") },
                    local_type::instance(),
                    false,
                    false,
                    string_type{ TETENGO2_TEXT("N") }
                },
                1
            };
            const station_location_type station_location2{
                station_type{
                    string_type{ TETENGO2_TEXT("A") },
                    local_type::instance(),
                    false,
                    false,
                    string_type{ TETENGO2_TEXT("N") }
                },
                1
            };

            BOOST_CHECK(station_location1 == station_location2);
        }
        {
            const station_location_type station_location1{
                station_type{
                    string_type{ TETENGO2_TEXT("A") },
                    local_type::instance(),
                    false,
                    false,
                    string_type{ TETENGO2_TEXT("N") }
                },
                1
            };
            const station_location_type station_location2{
                station_type{
                    string_type{ TETENGO2_TEXT("B") },
                    local_type::instance(),
                    false,
                    false,
                    string_type{ TETENGO2_TEXT("N") }
                },
                2
            };

            BOOST_CHECK(station_location1 != station_location2);
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(get_station)
    {
        BOOST_TEST_PASSPOINT();

        const station_location_type station_location{
            station_type(string_type{}, local_type::instance(), false, false, string_type{}), 0
        };

        BOOST_CHECK(
            station_location.get_station() ==
            station_type(string_type{}, local_type::instance(), false, false, string_type{})
        );
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(operating_distance)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_location_type station_location{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 0
            };

            BOOST_CHECK_EQUAL(station_location.operating_distance(), 0U);
        }
        {
            const station_location_type station_location{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 1
            };

            BOOST_CHECK_EQUAL(station_location.operating_distance(), 1U);
        }
        {
            const station_location_type station_location{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 2
            };

            BOOST_CHECK_EQUAL(station_location.operating_distance(), 2U);
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(before)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_location_type station_location1{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 1
            };
            const station_location_type station_location2{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 1
            };

            BOOST_CHECK(!station_location1.before(station_location2));
        }
        {
            const station_location_type station_location1{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 1
            };
            const station_location_type station_location2{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 2
            };

            BOOST_CHECK(station_location1.before(station_location2));
        }
        {
            const station_location_type station_location1{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 2
            };
            const station_location_type station_location2{
                station_type(string_type{}, local_type::instance(), false, false, string_type{}), 1
            };

            BOOST_CHECK(!station_location1.before(station_location2));
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
