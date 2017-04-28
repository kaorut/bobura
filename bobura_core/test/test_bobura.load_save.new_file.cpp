/*! \file
    \brief Test of class bobura::load_save::new_file.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/new_file.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            common_type_list_type::string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using load_save_traits_type = traits_type_list_type::load_save_type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using confirm_file_save_type = bobura::load_save::confirm_file_save<load_save_traits_type>;

    using window_type = ui_type_list_type::window_type;

    using new_file_type = bobura::load_save::new_file<load_save_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(new_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const new_file_type new_file{ confirm_file_save };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const new_file_type new_file{ confirm_file_save };

        window_type parent{};
        new_file(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
