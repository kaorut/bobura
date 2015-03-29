/*! \file
    \brief Test of class bobura::model::serializer::oudia_diagram_dialog.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/oudia_diagram_dialog.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using window_type = ui_type_list_type::window_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using oudia_diagram_dialog_type =
        bobura::model::serializer::oudia_diagram_dialog<
            traits_type_list_type::dialog_type, common_type_list_type::size_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(oudia_diagram_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const oudia_diagram_dialog_type oudia_diagram_dialog{ parent, message_catalog };
    }

    BOOST_AUTO_TEST_CASE(file_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const oudia_diagram_dialog_type oudia_diagram_dialog{ parent, message_catalog };

        BOOST_CHECK(oudia_diagram_dialog.file_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_file_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        oudia_diagram_dialog_type oudia_diagram_dialog{ parent, message_catalog };

        oudia_diagram_dialog.set_file_name(string_type{ TETENGO2_TEXT("hoge") });

        const string_type expected{ TETENGO2_TEXT("hoge") };
        BOOST_CHECK(oudia_diagram_dialog.file_name() == expected);
    }

    BOOST_AUTO_TEST_CASE(names)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const oudia_diagram_dialog_type oudia_diagram_dialog{ parent, message_catalog };

        BOOST_CHECK(oudia_diagram_dialog.names().empty());
    }

    BOOST_AUTO_TEST_CASE(set_names)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        oudia_diagram_dialog_type oudia_diagram_dialog{ parent, message_catalog };

        std::vector<string_type> names{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            string_type{ TETENGO2_TEXT("piyo") }
        };
        oudia_diagram_dialog.set_names(std::move(names));

        const std::vector<string_type> expected{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            string_type{ TETENGO2_TEXT("piyo") }
        };
        BOOST_CHECK(oudia_diagram_dialog.names() == expected);
    }

    BOOST_AUTO_TEST_CASE(selected_index)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const oudia_diagram_dialog_type oudia_diagram_dialog{ parent, message_catalog };

        BOOST_CHECK(!oudia_diagram_dialog.selected_index());
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 8, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(set_selected_index)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        oudia_diagram_dialog_type oudia_diagram_dialog{ parent, message_catalog };

        std::vector<string_type> names{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            string_type{ TETENGO2_TEXT("piyo") }
        };
        oudia_diagram_dialog.set_names(std::move(names));

        BOOST_CHECK_THROW(oudia_diagram_dialog.set_selected_index(3), std::out_of_range);

        oudia_diagram_dialog.set_selected_index(1);

        BOOST_CHECK(oudia_diagram_dialog.selected_index());
        BOOST_CHECK(*oudia_diagram_dialog.selected_index() == 1);

        oudia_diagram_dialog.set_names(std::vector<string_type>{});

        BOOST_CHECK(!oudia_diagram_dialog.selected_index());
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
