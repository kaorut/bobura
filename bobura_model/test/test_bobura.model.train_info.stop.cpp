/*! \file
    \brief Test of class bobura::model::train_info::stop.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text.h>

#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using common_type_list_type = test_bobura::model::type_list::common;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using time_type = bobura::model::train_info::time<size_type, difference_type>;

    using stop_type = bobura::model::train_info::stop<size_type, difference_type, string_type>;


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
            const stop_type stop{ time_type{ 0 }, time_type{ 0 }, false, string_type{} };

            BOOST_CHECK(stop.arrival() == time_type{ 0 });
            BOOST_CHECK(stop.departure() == time_type{ 0 });
            BOOST_TEST(!stop.operational());
            BOOST_CHECK(stop.platform() == string_type{});
        }
        {
            const stop_type stop{ time_type{ 0 }, time_type{ 1 }, true, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop.arrival() == time_type{ 0 });
            BOOST_CHECK(stop.departure() == time_type{ 1 });
            BOOST_TEST(stop.operational());
            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("1") });
        }
        {
            const stop_type stop{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("ZZZ") } };

            BOOST_CHECK(stop.arrival() == time_type{ 1 });
            BOOST_CHECK(stop.departure() == time_type{ 2 });
            BOOST_TEST(stop.operational());
            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("ZZZ") });
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop1{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };
            const stop_type stop2{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop1 == stop2);
        }
        {
            const stop_type stop1{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };
            const stop_type stop2{ time_type{ 3 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };
            const stop_type stop2{ time_type{ 1 }, time_type{ 4 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };
            const stop_type stop2{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };
            const stop_type stop2{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("2") } };

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };
            const stop_type stop2{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("2") } };

            BOOST_CHECK(stop1 != stop2);
        }
    }

    BOOST_AUTO_TEST_CASE(arrival)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop.arrival() == time_type{ 1 });
        }
        {
            const stop_type stop{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("2") } };

            BOOST_CHECK(stop.arrival() == time_type{ 3 });
        }
    }

    BOOST_AUTO_TEST_CASE(departure)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop.departure() == time_type{ 2 });
        }
        {
            const stop_type stop{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("2") } };

            BOOST_CHECK(stop.departure() == time_type{ 4 });
        }
    }

    BOOST_AUTO_TEST_CASE(passing)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_TEST(!stop.passing());
        }
        {
            const stop_type stop{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_TEST(!stop.passing());
        }
        {
            const stop_type stop{ time_type{ 1 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_TEST(!stop.passing());
        }
        {
            const stop_type stop{
                time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("1") }
            };

            BOOST_TEST(stop.passing());
        }
    }

    BOOST_AUTO_TEST_CASE(operational)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_TEST(!stop.operational());
        }
        {
            const stop_type stop{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("2") } };

            BOOST_TEST(stop.operational());
        }
    }

    BOOST_AUTO_TEST_CASE(platform)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("1") } };

            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("1") });
        }
        {
            const stop_type stop{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("2") } };

            BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("2") });
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
