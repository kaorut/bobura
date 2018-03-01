/*! \file
    \brief Test of class bobura::load_save::save_to_file.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/filesystem.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/detail_type_list.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using model_type = bobura::timetable_model<
        common_type_list_type::size_type,
        common_type_list_type::difference_type,
        common_type_list_type::string_type,
        common_type_list_type::operating_distance_type,
        common_type_list_type::speed_type,
        ui_type_list_type::fast_font_type>;

    using window_type = ui_type_list_type::window_type;

    using save_to_file_type = bobura::load_save::save_to_file<traits_type_list_type::load_save_type>;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(load_save)
        BOOST_AUTO_TEST_SUITE(save_to_file)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                const message_catalog_type message_catalog{};
                const save_to_file_type    save_to_file{ false, message_catalog };
            }

            BOOST_AUTO_TEST_CASE(operator_paren)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const message_catalog_type message_catalog{};
                    const save_to_file_type    save_to_file{ false, message_catalog };

                    model_type  model{};
                    window_type parent{};
                    const auto  result = save_to_file(model, parent);

                    BOOST_TEST(!result);
                }
                {
                    const message_catalog_type message_catalog{};
                    const save_to_file_type    save_to_file{ false, message_catalog };

                    model_type model{};
                    model.set_path(boost::filesystem::path("test"));
                    window_type parent{};
                    const auto  result = save_to_file(model, parent);

                    BOOST_TEST(!result);
                }
                {
                    const message_catalog_type message_catalog{};
                    const save_to_file_type    save_to_file{ false, message_catalog };

                    model_type model{};
                    model.set_changed(true);
                    window_type parent{};
                    const auto  result = save_to_file(model, parent);

                    BOOST_TEST(!result);
                }
                {
                    const message_catalog_type message_catalog{};
                    const save_to_file_type    save_to_file{ true, message_catalog };

                    model_type  model{};
                    window_type parent{};
                    const auto  result = save_to_file(model, parent);

                    BOOST_TEST(!result);
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
