/*! \file
    \brief Test of class bobura::model::train_info::stop.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using time_type = boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::time>::type;

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using stop_type = boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::stop>::type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train_info)
BOOST_AUTO_TEST_SUITE(stop)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(0), time_type(0), false, string_type());

            BOOST_CHECK(stop.arrival() == time_type(0));
            BOOST_CHECK(stop.departure() == time_type(0));
            BOOST_CHECK(!stop.operational());
            BOOST_CHECK(stop.platform() == string_type());
        }
        {
            const stop_type stop(time_type(0), time_type(1), true, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop.arrival() == time_type(0));
            BOOST_CHECK(stop.departure() == time_type(1));
            BOOST_CHECK(stop.operational());
            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("1") });
        }
        {
            const stop_type stop(time_type(1), time_type(2), true, string_type{ TETENGO2_TEXT("ZZZ") });

            BOOST_CHECK(stop.arrival() == time_type(1));
            BOOST_CHECK(stop.departure() == time_type(2));
            BOOST_CHECK(stop.operational());
            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("ZZZ") });
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop1(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });
            const stop_type stop2(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop1 == stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });
            const stop_type stop2(time_type(3), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });
            const stop_type stop2(time_type(1), time_type(4), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });
            const stop_type stop2(time_type(1), time_type(2), true, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });
            const stop_type stop2(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("2") });

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });
            const stop_type stop2(time_type(3), time_type(4), true, string_type{ TETENGO2_TEXT("2") });

            BOOST_CHECK(stop1 != stop2);
        }
    }

    BOOST_AUTO_TEST_CASE(arrival)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop.arrival() == time_type(1));
        }
        {
            const stop_type stop(time_type(3), time_type(4), true, string_type{ TETENGO2_TEXT("2") });

            BOOST_CHECK(stop.arrival() == time_type(3));
        }
    }

    BOOST_AUTO_TEST_CASE(departure)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop.departure() == time_type(2));
        }
        {
            const stop_type stop(time_type(3), time_type(4), true, string_type{ TETENGO2_TEXT("2") });

            BOOST_CHECK(stop.departure() == time_type(4));
        }
    }

    BOOST_AUTO_TEST_CASE(passing)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(!stop.passing());
        }
        {
            const stop_type stop(time_type::uninitialized(), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(!stop.passing());
        }
        {
            const stop_type stop(time_type(1), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(!stop.passing());
        }
        {
            const stop_type stop(
                time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("1") }
            );

            BOOST_CHECK(stop.passing());
        }
    }

    BOOST_AUTO_TEST_CASE(operational)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(!stop.operational());
        }
        {
            const stop_type stop(time_type(3), time_type(4), true, string_type{ TETENGO2_TEXT("2") });

            BOOST_CHECK(stop.operational());
        }
    }

    BOOST_AUTO_TEST_CASE(platform)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), false, string_type{ TETENGO2_TEXT("1") });

            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("1") });
        }
        {
            const stop_type stop(time_type(3), time_type(4), true, string_type{ TETENGO2_TEXT("2") });

            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("2") });
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
