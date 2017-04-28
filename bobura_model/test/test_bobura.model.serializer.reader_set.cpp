/*! \file
    \brief Test of class bobura::model::serializer::reader_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/exec_json_reading_task.h>
#include <bobura/model/serializer/oudia_diagram_dialog.h>
#include <bobura/model/serializer/reader_set.h>
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

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using window_type = ui_type_list_type::window_type;

    using dialog_type = ui_type_list_type::dialog_type;

    using timer_type = ui_type_list_type::timer_type;

    using system_color_set_type = ui_type_list_type::system_color_set_type;

    using input_stream_iterator_type = common_type_list_type::input_stream_iterator_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using abstract_window_type = ui_type_list_type::abstract_window_type;

    using exec_json_reading_task_type =
        bobura::model::serializer::exec_json_reading_task<
            size_type,
            difference_type,
            string_type,
            operating_distance_type,
            speed_type,
            font_type,
            dialog_type,
            timer_type,
            system_color_set_type,
            message_catalog_type
        >;

    using oudia_diagram_dialog_type =
        bobura::model::serializer::oudia_diagram_dialog<traits_type_list_type::dialog_type, size_type>;

    using select_oudia_diagram_type = bobura::model::serializer::select_oudia_diagram<oudia_diagram_dialog_type>;

    using reader_set_type =
        bobura::model::serializer::reader_set<
            size_type,
            difference_type,
            string_type,
            input_stream_iterator_type,
            operating_distance_type,
            speed_type,
            exec_json_reading_task_type,
            select_oudia_diagram_type,
            font_type,
            locale_type_list_type::timetable_file_encoder_type,
            locale_type_list_type::windia_file_encoder_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader_set)
    // test cases

    BOOST_AUTO_TEST_CASE(create_readers)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type message_catalog{};
        const auto p_readers = reader_set_type::create_readers(parent, std::move(file_name), message_catalog);

        BOOST_TEST_REQUIRE(!p_readers.empty());
        BOOST_TEST(p_readers[0].get());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
