/*! \file
    \brief Test of class bobura::model::serializer::json_reader.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/exec_json_reading_task.h>
#include <bobura/model/serializer/json_reader.h>
#include <bobura/model/station.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable.h>
#include <bobura/model/timetable_info/font_color_set.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using time_type = bobura::model::train_info::time<size_type, difference_type>;

    using timetable_type =
        bobura::model::timetable<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using font_color_set_type = timetable_type::font_color_set_type;
    
    using font_color_type = font_color_set_type::font_color_type;

    using color_type = ui_type_list_type::color_type;

    using input_stream_iterator_type = common_type_list_type::input_stream_iterator_type;

    using dialog_type = ui_type_list_type::dialog_type;

    using timer_type = ui_type_list_type::timer_type;

    using system_color_set_type = ui_type_list_type::system_color_set_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

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

    using reader_type =
        bobura::model::serializer::json_reader<
            size_type,
            difference_type,
            string_type,
            input_stream_iterator_type,
            int,
            double,
            operating_distance_type,
            speed_type,
            exec_json_reading_task_type,
            font_type,
            locale_type_list_type::timetable_file_encoder_type
        >;

    using error_type = reader_type::error_type;

    using window_type = ui_type_list_type::window_type;


    // variables

    const std::string json_empty0{};

    const std::string json_empty1{
        "[]"
    };

    const std::string json_empty2{
        "[\n"
        "    {\n"
        "    },\n"
        "    {},\n"
        "    [],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_line_name_only{
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_station_only{
        "[\n"
        "    {\n"
        "        \"piyo\":      \"piyopiyo\",\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   true,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": true,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_invalid_station_grade{
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"hoge\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_full_content{
        "[\n"
        "    {\n"
        "        \"company_name\": \"hoge\",\n"
        "        \"line_name\": \"fuga\",\n"
        "        \"note\": \"piyo\"\n"
        "    },\n"
        "    {\n"
        "        \"background\":                 [\n"
        "                                            null,\n"
        "                                            \"ABCDEF\",\n"
        "                                            null,\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"general\"  :                  [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"company_name\":               [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"line_name\":                  [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"note\":                       [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"local_station\":              [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"principal_station\":          [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"local_terminal_station\":     [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ],\n"
        "        \"principal_terminal_station\": [\n"
        "                                            [\"hogefont\", 42, false, true, false, true],\n"
        "                                            \"ABCDEF\",\n"
        "                                            [\"fugafont\", 42, false, true, false, true],\n"
        "                                            \"FEDCBA\"\n"
        "                                        ]\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":                \"nameA\",\n"
        "            \"abbreviation\":        \"abbrA\",\n"
        "            \"diagram_font\":        [\"hogefont\", 42, false, true, false, true],\n"
        "            \"diagram_color\":       \"ABCDEF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\":  1,\n"
        "            \"timetable_font\":      [\"fugafont\", 42, false, true, false, true],\n"
        "            \"timetable_color\":     \"EFABCD\"\n"
        "        },\n"
        "        {\n"
        "            \"name\":                \"nameB\",\n"
        "            \"abbreviation\":        \"abbrB\",\n"
        "            \"diagram_font\":        [\"foofont\", 42, false, true, false, true],\n"
        "            \"diagram_color\":       \"ABCDEF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\":  1,\n"
        "            \"timetable_font\":      [\"barfont\", 42, false, true, false, true],\n"
        "            \"timetable_color\":     \"EFABCD\"\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"101D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"fuga\",\n"
        "            \"stops\":       []\n"
        "        },\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  1,\n"
        "            \"name\":        \"baz\",\n"
        "            \"name_number\": \"bazz\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1,  60030,  true, \"1\"],\n"
        "                [ 60545,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"9324M\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"abc\",\n"
        "            \"name_number\": \"def\",\n"
        "            \"note\":        \"piyo\",\n"
        "            \"stops\":       [\n"
        "                [  -1,  62000, false, \"0A\"]\n"
        "            ]\n"
        "        }\n"
        "    ]\n"
        "]\n"
    };

    const std::string json_invalid_stop_time{
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":                \"nameA\",\n"
        "            \"abbreviation\":        \"abbrA\",\n"
        "            \"diagram_font\":        [\"hogefont\", 42, false, true, false, true],\n"
        "            \"diagram_color\":       \"ABCDEF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\":  1,\n"
        "            \"timetable_font\":      [\"fugafont\", 42, false, true, false, true],\n"
        "            \"timetable_color\":     \"EFABCD\"\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1,  66030,  true, \"1\"],\n"
        "                [ 60545,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_too_many_stops{
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":                \"nameA\",\n"
        "            \"abbreviation\":        \"abbrA\",\n"
        "            \"diagram_font\":        [\"hogefont\", 42, false, true, false, true],\n"
        "            \"diagram_color\":       \"ABCDEF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\":  1,\n"
        "            \"timetable_font\":      [\"fugafont\", 42, false, true, false, true],\n"
        "            \"timetable_color\":     \"EFABCD\"\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1,  60030,  true, \"1\"],\n"
        "                [ 60230,  60315, false, \"\"],\n"
        "                [ 60545,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_white_space_before_start_element{
        "    \t    \n    []\n"
    };

    const std::string json_not_json{
        "hoge\n"
    };

    const std::string json_invalid_time_format{
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":                \"nameA\",\n"
        "            \"abbreviation\":        \"abbrA\",\n"
        "            \"diagram_font\":        [\"hogefont\", 42, false, true, false, true],\n"
        "            \"diagram_color\":       \"ABCDEF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\":  1,\n"
        "            \"timetable_font\":      [\"fugafont\", 42, false, true, false, true],\n"
        "            \"timetable_color\":     \"EFABCD\"\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1, 235000,  true, \"1\"],\n"
        "                [ 01000,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_train_with_no_stop{
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":                \"nameA\",\n"
        "            \"abbreviation\":        \"abbrA\",\n"
        "            \"diagram_font\":        [\"hogefont\", 42, false, true, false, true],\n"
        "            \"diagram_color\":       \"ABCDEF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\":  1,\n"
        "            \"timetable_font\":      [\"fugafont\", 42, false, true, false, true],\n"
        "            \"timetable_color\":     \"EFABCD\"\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"101D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name_number\": \"bar\",\n"
        "            \"name\":        \"foo\",\n"
        "            \"note\":        \"fuga\",\n"
        "            \"stops\":       []\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    };

    const std::string json_invalid_kind_index{
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":                \"nameA\",\n"
        "            \"abbreviation\":        \"abbrA\",\n"
        "            \"diagram_font\":        [\"hogefont\", 42, false, true, false, true],\n"
        "            \"diagram_color\":       \"ABCDEF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\":  1,\n"
        "            \"timetable_font\":      [\"fugafont\", 42, false, true, false, true],\n"
        "            \"timetable_color\":     \"EFABCD\"\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"101D\",\n"
        "            \"kind_index\":  1,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"fuga\",\n"
        "            \"stops\":       []\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    };

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(json_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type window;
            const message_catalog_type message_catalog;
            auto p_exec_json_reading_task =
                tetengo2::stdalt::make_unique<exec_json_reading_task_type>(window, message_catalog);
            reader_type json_reader{ std::move(p_exec_json_reading_task) };
        }
        {
            std::unique_ptr<exec_json_reading_task_type> p_exec_json_reading_task{};
            BOOST_CHECK_THROW(reader_type json_reader{ std::move(p_exec_json_reading_task) }, std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        auto p_exec_json_reading_task =
            tetengo2::stdalt::make_unique<exec_json_reading_task_type>(window, message_catalog);
        reader_type json_reader{ std::move(p_exec_json_reading_task) };
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_empty0) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(!json_reader.selects(first, last));
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_empty1) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(json_reader.selects(first, last));
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_empty2) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(json_reader.selects(first, last));
        }
        {
            boost::iostreams::filtering_istream input_stream{
                boost::make_iterator_range(json_white_space_before_start_element)
            };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(json_reader.selects(first, last));
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_not_json) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(!json_reader.selects(first, last));
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        auto p_exec_json_reading_task =
            tetengo2::stdalt::make_unique<exec_json_reading_task_type>(window, message_catalog);
        reader_type json_reader{ std::move(p_exec_json_reading_task) };
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_not_json) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_empty1) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_empty2) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_TEST(p_timetable->line_name().empty());
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_line_name_only) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_station_only) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("hoge") });
            BOOST_TEST_REQUIRE(p_timetable->station_locations().size() == 2U);
            {
                const auto& station_location = p_timetable->station_locations()[0];
                const auto& station = station_location.get_station();
                BOOST_CHECK(station.name() == string_type{ TETENGO2_TEXT("stationA") });
                BOOST_CHECK(station.grade().name() == string_type{ TETENGO2_TEXT("local") });
                BOOST_TEST(!station.shows_down_arrival_times());
                BOOST_TEST(station.shows_up_arrival_times());
                BOOST_CHECK(station.note() == string_type{ TETENGO2_TEXT("noteA") });
                BOOST_TEST(station_location.operating_distance() == 42U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[1];
                const auto& station = station_location.get_station();
                BOOST_CHECK(station.name() == string_type{ TETENGO2_TEXT("stationB") });
                BOOST_CHECK(station.grade().name() == string_type{ TETENGO2_TEXT("principal") });
                BOOST_TEST(station.shows_down_arrival_times());
                BOOST_TEST(!station.shows_up_arrival_times());
                BOOST_CHECK(station.note() == string_type{ TETENGO2_TEXT("noteB") });
                BOOST_TEST(station_location.operating_distance() == 4242U);
            }
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_invalid_station_grade) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_full_content) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);

            BOOST_CHECK(p_timetable->company_name() == string_type{ TETENGO2_TEXT("hoge") });
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("fuga") });
            BOOST_CHECK(p_timetable->note() == string_type{ TETENGO2_TEXT("piyo") });

            {
                const auto& font_color_set = p_timetable->font_color_set();

                BOOST_TEST_REQUIRE(!!font_color_set.background().diagram_color());
                BOOST_CHECK((*font_color_set.background().diagram_color() == color_type{ 0xAB, 0xCD, 0xEF }));
                BOOST_CHECK((
                    font_color_set.company_name() ==
                    font_color_type{
                        boost::make_optional(
                            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true }
                        ),
                        boost::make_optional(color_type{ 0xAB, 0xCD, 0xEF }),
                        boost::make_optional(
                            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true }
                        ),
                        boost::make_optional(color_type{ 0xFE, 0xDC, 0xBA })
                    }
                ));
            }

            BOOST_TEST_REQUIRE(p_timetable->down_trains().size() == 2U);
            {
                const auto& train = p_timetable->down_trains()[0];
                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("101D") });
                BOOST_CHECK(train.note() == string_type{ TETENGO2_TEXT("fuga") });
                const auto& stops = train.stops();
                BOOST_TEST_REQUIRE(train.stops().size() == 2U);
                {
                    const auto& stop = stops[0];
                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = stops[1];
                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
            {
                const auto& train = p_timetable->down_trains()[1];
                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("123D") });
                BOOST_TEST(train.note().empty());
                const auto& stops = train.stops();
                BOOST_TEST_REQUIRE(train.stops().size() == 2U);
                {
                    const auto& stop = stops[0];
                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 6, 0, 30 }));
                    BOOST_TEST(stop.operational());
                    BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("1") });
                }
                {
                    const auto& stop = stops[1];
                    BOOST_CHECK((stop.arrival() == time_type{ 6, 5, 45 }));
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
            BOOST_TEST_REQUIRE(p_timetable->up_trains().size() == 1U);
            {
                const auto& train = p_timetable->up_trains()[0];
                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("9324M") });
                BOOST_CHECK(train.note() == string_type{ TETENGO2_TEXT("piyo") });
                const auto& stops = train.stops();
                BOOST_TEST_REQUIRE(train.stops().size() == 2U);
                {
                    const auto& stop = stops[0];
                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 6, 20, 0 }));
                    BOOST_TEST(!stop.operational());
                    BOOST_CHECK(stop.platform() == string_type{ TETENGO2_TEXT("0A") });
                }
                {
                    const auto& stop = stops[1];
                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_invalid_stop_time) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_too_many_stops) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_invalid_time_format) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_train_with_no_stop) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(json_invalid_kind_index) };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = json_reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
