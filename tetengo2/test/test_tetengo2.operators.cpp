/*! \file
    \brief Test of class tetengo2::text.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.operators.h"


namespace
{
    // types

    template <typename T>
    struct addable_class : private tetengo2::addable<addable_class<T>>
    {
        T value;

        addable_class(T value) : value(value) {}

        addable_class& operator+=(const addable_class& another)
        {
            value += another.value;
            return *this;
        }
    

    };


};


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(addable)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_plus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const addable_class<int> tc1(123);
            const addable_class<int> tc2(456);

            const addable_class<int> tc3 = tc1 + tc2;

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
        {
            const addable_class<int> tc1(123);
            addable_class<int> tc2(456);

            const addable_class<int> tc3 = tc1 + std::move(tc2);

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
        {
            addable_class<int> tc1(123);
            const addable_class<int> tc2(456);

            const addable_class<int> tc3 = std::move(tc1) + tc2;

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
        {
            addable_class<int> tc1(123);
            addable_class<int> tc2(456);

            const addable_class<int> tc3 = std::move(tc1) + std::move(tc2);

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
    }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
