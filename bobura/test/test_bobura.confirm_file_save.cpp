/*! \file
    \brief Test of class bobura::confirm_file_save.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(confirm_file_save)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        const confirm_file_save_type confirm_file_save(
            model, message_catalog
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        const confirm_file_save_type confirm_file_save(
            model, message_catalog
        );

        window_type window;
        confirm_file_save(window);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()