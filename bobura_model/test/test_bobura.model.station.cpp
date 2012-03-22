/*! \file
    \brief Test of class bobura::model::station.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::grade_type_set
        >::type
        grade_type_set_type;

    typedef grade_type_set_type::local_type local_type;

    typedef grade_type_set_type::principal_type principal_type;

    typedef grade_type_set_type::local_terminal_type local_terminal_type;

    typedef
        grade_type_set_type::principal_terminal_type principal_terminal_type;

    typedef
        boost::mpl::at<
            test_bobura::model::type_list, test_bobura::model::type::string
        >::type
        string_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::station
        >::type
        station_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(station)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance());
        }
        {
            const station_type station("A", local_type::instance());
        }
        {
            const station_type station("AB", local_type::instance());
        }
        {
            const station_type station(
                string_type(1024 * 1024, L'X'), local_type::instance()
            );
        }
        {
            const station_type station(string_type(), principal_type::instance());
        }
        {
            const station_type station("A", principal_type::instance());
        }
        {
            const station_type station("AB", principal_type::instance());
        }
        {
            const station_type station(
                string_type(1024 * 1024, L'X'), local_type::instance()
            );
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station1("A", local_type::instance());
            const station_type station2("A", local_type::instance());

            BOOST_CHECK(station1 == station2);
        }
        {
            const station_type station1("B", principal_type::instance());
            const station_type station2("B", principal_type::instance());

            BOOST_CHECK(station1 == station2);
        }
        {
            const station_type station1("A", local_type::instance());
            const station_type station2("B", principal_type::instance());

            BOOST_CHECK(station1 != station2);
        }
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance());

            BOOST_CHECK(station.name() == string_type());
        }
        {
            const station_type station("A", local_type::instance());

            BOOST_CHECK(station.name() == string_type("A"));
        }
        {
            const station_type station("AB", local_type::instance());

            BOOST_CHECK(station.name() == string_type("AB"));
        }
        {
            const station_type station(
                string_type(1024 * 1024, L'X'), local_type::instance()
            );

            BOOST_CHECK(station.name() == string_type(1024 * 1024, L'X'));
        }
    }

    BOOST_AUTO_TEST_CASE(grade)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance());

            BOOST_CHECK_EQUAL(&station.grade(), &local_type::instance());
        }
        {
            const station_type station(string_type(), principal_type::instance());

            BOOST_CHECK_EQUAL(&station.grade(), &principal_type::instance());
        }
        {
            const station_type station(string_type(), local_terminal_type::instance());

            BOOST_CHECK_EQUAL(
                &station.grade(), &local_terminal_type::instance()
            );
        }
        {
            const station_type station(
                string_type(), principal_terminal_type::instance()
            );

            BOOST_CHECK_EQUAL(
                &station.grade(), &principal_terminal_type::instance()
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
