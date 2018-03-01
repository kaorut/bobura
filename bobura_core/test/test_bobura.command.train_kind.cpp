/*! \file
    \brief Test of class bobura::command::train_kind.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/command/train_kind.h>
#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using common_dialog_type_list_type = bobura::type_list::common_dialog<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using train_kind_command_type = bobura::command::train_kind<
        traits_type_list_type::command_type,
        ui_type_list_type::dialog_type,
        ui_type_list_type::point_dimension_unit_type,
        ui_type_list_type::color_type,
        ui_type_list_type::fast_canvas_type,
        common_dialog_type_list_type::font_type,
        common_dialog_type_list_type::color_type,
        message_catalog_type,
        traits_type_list_type::dialog_type>;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(command)
        BOOST_AUTO_TEST_SUITE(train_kind)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                const message_catalog_type    message_catalog{};
                const train_kind_command_type command{ message_catalog };
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
