/*! \file
    \brief Test of class bobura::command::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.common_dialog.h>

#include "test_bobura.types.h"

#include "bobura.command.save_to_file.h"


namespace
{
    // types

    typedef
        bobura::command::save_to_file<
            model_type,
            abstract_window_type,
            message_box_type,
            file_save_type,
            writer_type,
            message_catalog_type
        >
        save_to_file_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(save_to_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        const message_catalog_type message_catalog;
        writer_type writer;
        const save_to_file_type save_to_file(
            false, parent, model, writer, message_catalog
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            model_type model;
            const message_catalog_type message_catalog;
            writer_type writer;
            const save_to_file_type save_to_file(
                false, parent, model, writer, message_catalog
            );

            save_to_file(model, parent);
        }
        {
            window_type parent;
            model_type model;
            const message_catalog_type message_catalog;
            writer_type writer;
            const save_to_file_type save_to_file(
                true, parent, model, writer, message_catalog
            );

            save_to_file(model, parent);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
