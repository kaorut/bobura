/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "bobura.settings.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(settings)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        const std::vector<std::wstring> arguments;
        const bobura::settings<std::wstring> settings(
            arguments.begin(), arguments.end()
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
