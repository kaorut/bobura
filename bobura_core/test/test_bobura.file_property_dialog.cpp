/*! \file
    \brief Test of class bobura::file_property_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/dialog_traits.h>
#include <bobura/file_property_dialog.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using window_type = ui_type_list_type::window_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using file_property_dialog_type = bobura::file_property_dialog<traits_type_list_type::dialog_type>;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(file_property_dialog)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            window_type                     parent{};
            const message_catalog_type      message_catalog{};
            const file_property_dialog_type file_property_dialog{ parent, message_catalog };
        }

        BOOST_AUTO_TEST_CASE(company_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                     parent{};
            const message_catalog_type      message_catalog{};
            const file_property_dialog_type file_property_dialog{ parent, message_catalog };

            BOOST_TEST(file_property_dialog.company_name().empty());
        }

        BOOST_AUTO_TEST_CASE(set_company_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            file_property_dialog_type  file_property_dialog{ parent, message_catalog };

            file_property_dialog.set_company_name(string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(file_property_dialog.company_name() == string_type{ TETENGO2_TEXT("hoge") });
        }

        BOOST_AUTO_TEST_CASE(line_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                     parent{};
            const message_catalog_type      message_catalog{};
            const file_property_dialog_type file_property_dialog{ parent, message_catalog };

            BOOST_TEST(file_property_dialog.line_name().empty());
        }

        BOOST_AUTO_TEST_CASE(set_line_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            file_property_dialog_type  file_property_dialog{ parent, message_catalog };

            file_property_dialog.set_line_name(string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(file_property_dialog.line_name() == string_type{ TETENGO2_TEXT("hoge") });
        }

        BOOST_AUTO_TEST_CASE(note)
        {
            BOOST_TEST_PASSPOINT();

            window_type                     parent{};
            const message_catalog_type      message_catalog{};
            const file_property_dialog_type file_property_dialog{ parent, message_catalog };

            BOOST_TEST(file_property_dialog.note().empty());
        }

        BOOST_AUTO_TEST_CASE(set_note)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            file_property_dialog_type  file_property_dialog{ parent, message_catalog };

            file_property_dialog.set_note(string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(file_property_dialog.note() == string_type{ TETENGO2_TEXT("hoge") });
        }

        BOOST_AUTO_TEST_CASE(file_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                     parent{};
            const message_catalog_type      message_catalog{};
            const file_property_dialog_type file_property_dialog{ parent, message_catalog };

            BOOST_TEST(file_property_dialog.file_name().empty());
        }

        BOOST_AUTO_TEST_CASE(set_file_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            file_property_dialog_type  file_property_dialog{ parent, message_catalog };

            file_property_dialog.set_file_name(string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(file_property_dialog.file_name() == string_type{ TETENGO2_TEXT("hoge") });
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
