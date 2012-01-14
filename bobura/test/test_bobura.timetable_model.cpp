/*! \file
    \brief Test of class bobura::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.unique.h>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(timetable_model)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
    }

    BOOST_AUTO_TEST_CASE(reset_timetable)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;

        model.reset_timetable(tetengo2::make_unique<timetable_type>());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
