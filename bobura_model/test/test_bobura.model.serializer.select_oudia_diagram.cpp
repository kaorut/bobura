/*! \file
    \brief Test of class bobura::model::serializer::select_oudia_diagram.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <iterator>
#include <utility>
#include <vector>

#include <boost/test/unit_test.hpp>

#include <bobura/model/serializer/oudia_diagram_dialog.h>
#include <bobura/model/serializer/select_oudia_diagram.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using string_type = common_type_list_type::string_type;

    using window_type = ui_type_list_type::window_type;

    using input_stream_iterator_type = common_type_list_type::input_stream_iterator_type;

    using message_catalog_type_ = locale_type_list_type::message_catalog_type;

    using oudia_diagram_dialog_type =
        bobura::model::serializer::oudia_diagram_dialog<typename traits_type_list_type::dialog_type, size_type>;

    using select_oudia_diagram_type = bobura::model::serializer::select_oudia_diagram<oudia_diagram_dialog_type>;

    using select_oudia_diagram_for_test_type = bobura::model::serializer::select_oudia_diagram_for_test<string_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(select_oudia_diagram)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type_ message_catalog{};
        const select_oudia_diagram_type select_oudia_diagram{ parent, std::move(file_name), message_catalog };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type_ message_catalog{};
        const select_oudia_diagram_type select_oudia_diagram{ parent, std::move(file_name), message_catalog };

        std::vector<string_type> diagram_names{};
        const auto selected = select_oudia_diagram(diagram_names.begin(), diagram_names.end());

        BOOST_CHECK(selected == diagram_names.end());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(select_oudia_diagram_for_test)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        string_type name{ TETENGO2_TEXT("hoge") };
        const select_oudia_diagram_for_test_type select_oudia_diagram_for_test{ std::move(name) };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        string_type name{ TETENGO2_TEXT("hoge") };
        const select_oudia_diagram_for_test_type select_oudia_diagram_for_test{ std::move(name) };

        std::vector<string_type> diagram_names{
            string_type{ TETENGO2_TEXT("fuga") }, string_type{ TETENGO2_TEXT("hoge") }
        };
        const auto selected = select_oudia_diagram_for_test(diagram_names.begin(), diagram_names.end());

        BOOST_CHECK(selected == std::next(diagram_names.begin()));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
