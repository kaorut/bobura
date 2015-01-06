/*! \file
    \brief Test of class bobura::model::train_info::time_span.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include <bobura/model/train_info/time_span.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common<detail_type_list_type>;

    using difference_type = common_type_list_type::difference_type;

    using time_span_type = bobura::model::train_info::time_span<difference_type>;

    using hours_minutes_seconds_type_ = time_span_type::hours_minutes_seconds_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train_info)
BOOST_AUTO_TEST_SUITE(time_span)
BOOST_AUTO_TEST_SUITE(hours_minutes_seconds_type)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds(12, 34, 56);
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const hours_minutes_seconds_type_ hours_minutes_seconds1(12, 34, 56);
            const hours_minutes_seconds_type_ hours_minutes_seconds2(12, 34, 56);

            BOOST_CHECK(hours_minutes_seconds1 == hours_minutes_seconds2);
        }
        {
            const hours_minutes_seconds_type_ hours_minutes_seconds1(12, 34, 56);
            const hours_minutes_seconds_type_ hours_minutes_seconds2(56, 34, 12);

            BOOST_CHECK(hours_minutes_seconds1 != hours_minutes_seconds2);
        }
    }

    BOOST_AUTO_TEST_CASE(hours)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds(12, 34, 56);

        BOOST_CHECK_EQUAL(hours_minutes_seconds.hours(), 12);
    }

    BOOST_AUTO_TEST_CASE(minutes)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds(12, 34, 56);

        BOOST_CHECK_EQUAL(hours_minutes_seconds.minutes(), 34);
    }

    BOOST_AUTO_TEST_CASE(seconds)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds(12, 34, 56);

        BOOST_CHECK_EQUAL(hours_minutes_seconds.seconds(), 56);
    }


BOOST_AUTO_TEST_SUITE_END()
    // test cases

    BOOST_AUTO_TEST_CASE(seconds_of_whole_day)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK_EQUAL(time_span_type::seconds_of_whole_day(), 24 * 60 * 60);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_span_type time_span(0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);
        }
        {
            const time_span_type time_span(1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);
        }
        {
            const time_span_type time_span(2);

            BOOST_CHECK_EQUAL(time_span.seconds(), 2);
        }
        {
            const time_span_type time_span(-1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -1);
        }
        {
            const time_span_type time_span(-2);

            BOOST_CHECK_EQUAL(time_span.seconds(), -2);
        }
        {
            const time_span_type time_span(0, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);
        }
        {
            const time_span_type time_span(1, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3600);
        }
        {
            const time_span_type time_span(-1, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), -3600);
        }
        {
            const time_span_type time_span(0, 1, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 60);
        }
        {
            const time_span_type time_span(0, 59, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3540);
        }
        {
            const time_span_type time_span(0, -1, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), -60);
        }
        {
            const time_span_type time_span(0, -59, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), -3540);
        }
        {
            const time_span_type time_span(0, 0, 1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);
        }
        {
            const time_span_type time_span(0, 0, 59);

            BOOST_CHECK_EQUAL(time_span.seconds(), 59);
        }
        {
            const time_span_type time_span(0, 0, -1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -1);
        }
        {
            const time_span_type time_span(0, 0, -59);

            BOOST_CHECK_EQUAL(time_span.seconds(), -59);
        }
        {
            const time_span_type time_span(1, 1, 1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3661);
        }
        {
            const time_span_type time_span(1, 59, 59);

            BOOST_CHECK_EQUAL(time_span.seconds(), 7199);
        }
        {
            const time_span_type time_span(-1, -1, -1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -3661);
        }
        {
            const time_span_type time_span(-1, -59, -59);

            BOOST_CHECK_EQUAL(time_span.seconds(), -7199);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ 0, 60, 0 }), std::out_of_range);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ 0, 0, 60 }), std::out_of_range);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ 0, 60, 60 }), std::out_of_range);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ -1, 1, 1 }), std::invalid_argument);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ -1, -1, 1 }), std::invalid_argument);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ 1, -1, 1 }), std::invalid_argument);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ 1, -1, -1 }), std::invalid_argument);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ 1, 1, -1 }), std::invalid_argument);
        }
        {
            BOOST_CHECK_THROW((time_span_type{ -1, 1, -1 }), std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_plus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            time_span_type time_span1(1);
            const time_span_type time_span2(2);

            time_span1 += time_span2;

            BOOST_CHECK_EQUAL(time_span1.seconds(), 3);
        }
        {
            time_span_type time_span1(0, 0, 59);
            const time_span_type time_span2(0, 0, 1);

            time_span1 += time_span2;

            BOOST_CHECK(time_span1.hours_minutes_seconds() == hours_minutes_seconds_type_(0, 1, 0));
        }
        {
            time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(0, 0, -1);

            time_span1 += time_span2;

            BOOST_CHECK(time_span1.hours_minutes_seconds() == hours_minutes_seconds_type_(0, 0, 59));
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(2);

            const auto time_span3 = time_span1 + time_span2;

            BOOST_CHECK_EQUAL(time_span3.seconds(), 3);
        }
        {
            const time_span_type time_span1(0, 59, 59);
            const time_span_type time_span2(0, 0, 1);

            const auto time_span3 = time_span1 + time_span2;

            BOOST_CHECK(time_span3.hours_minutes_seconds() == hours_minutes_seconds_type_(1, 0, 0));
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 0, -1);

            const auto time_span3 = time_span1 + time_span2;

            BOOST_CHECK(time_span3.hours_minutes_seconds() == hours_minutes_seconds_type_(0, 59, 59));
        }
    }

    BOOST_AUTO_TEST_CASE(operator_minus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            time_span_type time_span1(1);
            const time_span_type time_span2(2);

            time_span1 -= time_span2;

            BOOST_CHECK_EQUAL(time_span1.seconds(), -1);
        }
        {
            time_span_type time_span1(0, 0, 59);
            const time_span_type time_span2(0, 0, -1);

            time_span1 -= time_span2;

            BOOST_CHECK(time_span1.hours_minutes_seconds() == hours_minutes_seconds_type_(0, 1, 0));
        }
        {
            time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(0, 0, 1);

            time_span1 -= time_span2;

            BOOST_CHECK(time_span1.hours_minutes_seconds() == hours_minutes_seconds_type_(0, 0, 59));
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(2);

            const auto time_span3 = time_span1 - time_span2;

            BOOST_CHECK_EQUAL(time_span3.seconds(), -1);
        }
        {
            const time_span_type time_span1(0, 59, 59);
            const time_span_type time_span2(0, 0, -1);

            const auto time_span3 = time_span1 - time_span2;

            BOOST_CHECK(time_span3.hours_minutes_seconds() == hours_minutes_seconds_type_(1, 0, 0));
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 0, 1);

            const auto time_span3 = time_span1 - time_span2;

            BOOST_CHECK(time_span3.hours_minutes_seconds() == hours_minutes_seconds_type_(0, 59, 59));
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(1);

            BOOST_CHECK(time_span1 == time_span2);
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(2);

            BOOST_CHECK(time_span1 != time_span2);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_span_type time_span1(0);
            const time_span_type time_span2(0);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(0);
            const time_span_type time_span2(1);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(0);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(0, 0, 1);
            const time_span_type time_span2(0, 1, 0);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(0, 0, 1);
            const time_span_type time_span2(1, 0, 0);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(1, 0, 0);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(0, 0, 1);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 0, 1);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 1, 0);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
    }

    BOOST_AUTO_TEST_CASE(seconds)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_span_type time_span(0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);
        }
        {
            const time_span_type time_span(1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);
        }
        {
            const time_span_type time_span(2);

            BOOST_CHECK_EQUAL(time_span.seconds(), 2);
        }
        {
            const time_span_type time_span(-1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -1);
        }
        {
            const time_span_type time_span(-2);

            BOOST_CHECK_EQUAL(time_span.seconds(), -2);
        }
    }

    BOOST_AUTO_TEST_CASE(hours_minutes_seconds)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_span_type time_span(0, 0, 0);

            BOOST_CHECK(time_span.hours_minutes_seconds() == hours_minutes_seconds_type_(0, 0, 0));
        }
        {
            const time_span_type time_span(1, 1, 1);

            BOOST_CHECK(time_span.hours_minutes_seconds() == hours_minutes_seconds_type_(1, 1, 1));
        }
        {
            const time_span_type time_span(1, 2, 3);

            BOOST_CHECK(time_span.hours_minutes_seconds() == hours_minutes_seconds_type_(1, 2, 3));
        }
        {
            const time_span_type time_span(-1, -1, -1);

            BOOST_CHECK(time_span.hours_minutes_seconds() == hours_minutes_seconds_type_(-1, -1, -1));
        }
        {
            const time_span_type time_span(-1, -2, -3);

            BOOST_CHECK(time_span.hours_minutes_seconds() == hours_minutes_seconds_type_(-1, -2, -3));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
