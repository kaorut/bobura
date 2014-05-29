/*! \file
    \brief Test of class bobura::model::station.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using grade_type_set_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::grade_type_set>::type;

    using local_type = grade_type_set_type::local_type;

    using principal_type = grade_type_set_type::principal_type;

    using local_terminal_type = grade_type_set_type::local_terminal_type;

    using principal_terminal_type = grade_type_set_type::principal_terminal_type;

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using station_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station>::type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(station)
    // test cases

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type{}, local_type::instance(), false, false, string_type{});
        }
        {
            const station_type station(
                string_type{ TETENGO2_TEXT("A") }, local_type::instance(), false, false, string_type{}
            );
        }
        {
            const station_type station(
                string_type{ TETENGO2_TEXT("AB") }, local_type::instance(), false, false, string_type{}
            );
        }
        {
            const station_type station(
                string_type(1024 * 1024, TETENGO2_TEXT('X')), local_type::instance(), false, false, string_type{}
            );
        }
        {
            const station_type station(
                string_type{ TETENGO2_TEXT("A") }, principal_type::instance(), false, false, string_type{}
            );
        }
        {
            const station_type station(
                string_type{ TETENGO2_TEXT("A") }, local_type::instance(), true, false, string_type{}
            );
        }
        {
            const station_type station(
                string_type{ TETENGO2_TEXT("A") }, local_type::instance(), false, true, string_type{}
            );
        }
        {
            const station_type station(
                string_type{}, local_type::instance(), false, false, string_type{ TETENGO2_TEXT("N") }
            );
        }
        {
            const station_type station(
                string_type{}, local_type::instance(), false, false, string_type{ TETENGO2_TEXT("NM") }
            );
        }
        {
            const station_type station(
                string_type{}, local_type::instance(), false, false, string_type(1024 * 1024, TETENGO2_TEXT('Y'))
            );
        }
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
            const station_type station1(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
            );
            const station_type station2(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station1 == station2);
        }
        {
            const station_type station1(
                string_type{ TETENGO2_TEXT("B") },
                principal_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
            );
            const station_type station2(
                string_type{ TETENGO2_TEXT("B") },
                principal_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station1 == station2);
        }
        {
            const station_type station1(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false,
                false, 
                string_type{ TETENGO2_TEXT("N") }
            );
            const station_type station2(
                string_type{ TETENGO2_TEXT("B") },
                principal_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station1 != station2);
        }
        {
            const station_type station1(
                string_type{ TETENGO2_TEXT("A") }, 
                local_type::instance(), 
                false, 
                false, 
                string_type{ TETENGO2_TEXT("N") }
            );
            const station_type station2(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(), 
                true, 
                false, 
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station1 != station2);
        }
        {
            const station_type station1(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false, 
                false,
                string_type{ TETENGO2_TEXT("N") }
            );
            const station_type station2(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(), 
                false, 
                true,
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station1 != station2);
        }
        {
            const station_type station1(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
            );
            const station_type station2(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("M") }
            );

            BOOST_CHECK(station1 != station2);
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(
                string_type{}, local_type::instance(), false, false, string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station.name() == string_type{});
        }
        {
            const station_type station(
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false,
                false, 
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station.name() == string_type{ TETENGO2_TEXT("A") });
        }
        {
            const station_type station(
                string_type{ TETENGO2_TEXT("AB") }, 
                local_type::instance(), 
                false, 
                false, 
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station.name() == string_type{ TETENGO2_TEXT("AB") });
        }
        {
            const station_type station(
                string_type(1024 * 1024, TETENGO2_TEXT('X')),
                local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station.name() == string_type(1024 * 1024, TETENGO2_TEXT('X')));
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(grade)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type{}, local_type::instance(), false, false, string_type{});

            BOOST_CHECK_EQUAL(&station.grade(), &local_type::instance());
        }
        {
            const station_type station(string_type{}, principal_type::instance(), false, false, string_type{});

            BOOST_CHECK_EQUAL(&station.grade(), &principal_type::instance());
        }
        {
            const station_type station(string_type{}, local_terminal_type::instance(), false, false, string_type{});

            BOOST_CHECK_EQUAL(&station.grade(), &local_terminal_type::instance());
        }
        {
            const station_type station(
                string_type{}, principal_terminal_type::instance(), false, false, string_type{}
            );

            BOOST_CHECK_EQUAL(&station.grade(), &principal_terminal_type::instance());
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(shows_down_arrival_times)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type{}, local_type::instance(), false, false, string_type{});

            BOOST_CHECK(!station.shows_down_arrival_times());
        }
        {
            const station_type station(string_type{}, local_type::instance(), true, false, string_type{});

            BOOST_CHECK(station.shows_down_arrival_times());
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(shows_up_arrival_times)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type{}, local_type::instance(), false, false, string_type{});

            BOOST_CHECK(!station.shows_up_arrival_times());
        }
        {
            const station_type station(string_type{}, local_type::instance(), false, true, string_type{});

            BOOST_CHECK(station.shows_up_arrival_times());
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type{}, local_type::instance(), false, false, string_type{});

            BOOST_CHECK(station.note() == string_type{});
        }
        {
            const station_type station(
                string_type{}, local_type::instance(), false, false, string_type{ TETENGO2_TEXT("N") }
            );

            BOOST_CHECK(station.note() == string_type{ TETENGO2_TEXT("N") });
        }
        {
            const station_type station(
                string_type{}, local_type::instance(), false, false, string_type{ TETENGO2_TEXT("NM") }
            );

            BOOST_CHECK(station.note() == string_type{ TETENGO2_TEXT("NM") });
        }
        {
            const station_type station(
                string_type{}, local_type::instance(), false, false, string_type(1024 * 1024, TETENGO2_TEXT('Y'))
            );

            BOOST_CHECK(station.note() == string_type(1024 * 1024, TETENGO2_TEXT('Y')));
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
