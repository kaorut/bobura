/*! \file
    \brief Test of class bobura::model::serializer::json_writer.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/json_writer.h>
#include <bobura/model/station.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>
#include <bobura/model/train_kind.h>
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

    using station_type = bobura::model::station<string_type>;

    using grade_type_set_type = bobura::model::station_info::grade_type_set<string_type>;

    using local_type = grade_type_set_type::local_type;

    using principal_type = grade_type_set_type::principal_type;

    using station_location_type =
        bobura::model::timetable_info::station_location<string_type, operating_distance_type>;

    using time_type = bobura::model::train_info::time<size_type, difference_type>;

    using stop_type = bobura::model::train_info::stop<size_type, difference_type, string_type>;

    using train_kind_type = bobura::model::train_kind<string_type>;

    using train_type = bobura::model::train<size_type, difference_type, string_type>;

    using timetable_type =
        bobura::model::timetable<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using font_color_set_type = timetable_type::font_color_set_type;

    using font_color_type = font_color_set_type::font_color_type;

    using color_type = ui_type_list_type::color_type;

    using output_stream_type = common_type_list_type::output_stream_type;

    using writer_type =
        bobura::model::serializer::json_writer<
            size_type,
            difference_type,
            string_type,
            output_stream_type,
            operating_distance_type,
            speed_type,
            font_type,
            locale_type_list_type::timetable_file_encoder_type
        >;


    // variables

    const std::string json0{
        "[\n"
        "    {\n"
        "        \"company_name\": \"\",\n"
        "        \"line_name\": \"\",\n"
        "        \"note\": \"\"\n"
        "    },\n"
        "    {},\n"
        "    [],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    };

    const std::string json1{
        "[\n"
        "    {\n"
        "        \"company_name\": \"hoge\",\n"
        "        \"line_name\": \"fuga\",\n"
        "        \"note\": \"piyo\"\n"
        "    },\n"
        "    {\n"
        "        \"background\": \"ABCDEF\",\n"
        "        \"company_line_name\": [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"train_name\": [\"hogefont\", 42, false, true, false, true]\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\": \"stationA\",\n"
        "            \"grade\": \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\": true,\n"
        "            \"note\": \"noteA\",\n"
        "            \"operating_distance\": 420\n"
        "        },\n"
        "        {\n"
        "            \"name\": \"stationB\",\n"
        "            \"grade\": \"principal\",\n"
        "            \"show_down_arrival_times\": true,\n"
        "            \"show_up_arrival_times\": false,\n"
        "            \"note\": \"noteB\",\n"
        "            \"operating_distance\": 42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\": \"nameA\",\n"
        "            \"abbreviation\": \"abbrA\",\n"
        "            \"diagram_line_color\": \"0080FF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\": 0\n"
        "        },\n"
        "        {\n"
        "            \"name\": \"nameB\",\n"
        "            \"abbreviation\": \"abbrB\",\n"
        "            \"diagram_line_color\": \"FF8000\",\n"
        "            \"diagram_line_weight\": 1,\n"
        "            \"diagram_line_style\": 2\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"101D\",\n"
        "            \"kind_index\": 0,\n"
        "            \"name\": \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\": \"fuga\",\n"
        "            \"stops\": [\n"
        "                [    -1,     -1, false, \"\"],\n"
        "                [    -1,     -1, false, \"\"]\n"
        "            ]\n"
        "        },\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"kind_index\": 1,\n"
        "            \"name\": \"baz\",\n"
        "            \"name_number\": \"bazz\",\n"
        "            \"note\": \"\",\n"
        "            \"stops\": [\n"
        "                [    -1,  60030,  true, \"1\"],\n"
        "                [100545,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"9324M\",\n"
        "            \"kind_index\": 0,\n"
        "            \"name\": \"abc\",\n"
        "            \"name_number\": \"def\",\n"
        "            \"note\": \"piyo\",\n"
        "            \"stops\": [\n"
        "                [    -1,  62000, false, \"0A\"],\n"
        "                [    -1,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ]\n"
        "]\n"
    };


    // functions

    std::unique_ptr<const timetable_type> create_timetable1()
    {
        auto p_timetable = tetengo2::stdalt::make_unique<timetable_type>();

        p_timetable->set_company_name(string_type{ TETENGO2_TEXT("hoge") });
        p_timetable->set_line_name(string_type{ TETENGO2_TEXT("fuga") });
        p_timetable->set_note(string_type{ TETENGO2_TEXT("piyo") });
        {
            font_type font{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true };
            color_type color{ 0xAB, 0xCD, 0xEF };
            const font_color_type font_color{ font, color };

            const font_color_set_type font_color_set{
                font_color,
                font_color,
                font_color,
                font_color_set_type::default_().note(),
                font_color_set_type::default_().time_line(),
                font_color_set_type::default_().local_station(),
                font_color_set_type::default_().principal_station(),
                font_color_set_type::default_().local_terminal_station(),
                font_color_set_type::default_().principal_terminal_station(),
                font_color
            };

            p_timetable->set_font_color_set(font_color_set);
        }
        {
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("stationA") },
                        local_type::instance(),
                        false,
                        true,
                        string_type{ TETENGO2_TEXT("noteA") }
                    },
                    42
                }
            );
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("stationB") },
                        principal_type::instance(),
                        true,
                        false,
                        string_type{ TETENGO2_TEXT("noteB") }
                    },
                    4242
                }
            );
        }
        {
            p_timetable->insert_train_kind(
                p_timetable->train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("nameA") },
                    string_type{ TETENGO2_TEXT("abbrA") },
                    color_type{ 0, 128, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            p_timetable->insert_train_kind(
                p_timetable->train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("nameB") },
                    string_type{ TETENGO2_TEXT("abbrB") },
                    color_type{ 255, 128, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::dotted
                }
            );
        }
        {
            {
                train_type train{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("101D") },
                    0,
                    string_type{ TETENGO2_TEXT("foo") },
                    string_type{ TETENGO2_TEXT("bar") },
                    string_type{ TETENGO2_TEXT("fuga") }
                };
                train.insert_stop(
                    train.stops().end(),
                    stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{})
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{})
                );
                p_timetable->insert_down_train(p_timetable->down_trains().end(), train);
            }
            {
                train_type train{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("123D") },
                    1,
                    string_type{ TETENGO2_TEXT("baz") },
                    string_type{ TETENGO2_TEXT("bazz") },
                    string_type{}
                };
                train.insert_stop(
                    train.stops().end(),
                    stop_type{
                        time_type::uninitialized(), time_type{ 6, 0, 30 }, true, string_type{ TETENGO2_TEXT("1") }
                    }
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(time_type{ 10, 5, 45 }, time_type::uninitialized(), false, string_type{})
                );
                p_timetable->insert_down_train(p_timetable->down_trains().end(), train);
            }
        }
        {
            {
                train_type train{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("9324M") },
                    0,
                    string_type{ TETENGO2_TEXT("abc") },
                    string_type{ TETENGO2_TEXT("def") },
                    string_type{ TETENGO2_TEXT("piyo") }
                };
                train.insert_stop(
                    train.stops().end(),
                    stop_type{
                        time_type::uninitialized(), time_type{ 6, 20, 0 }, false, string_type{ TETENGO2_TEXT("0A") }
                    }
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{})
                );
                p_timetable->insert_up_train(p_timetable->up_trains().end(), train);
            }
        }
        return std::move(p_timetable);
    }


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(json_writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const writer_type json_writer{};
    }

    BOOST_AUTO_TEST_CASE(extension)
    {
        BOOST_TEST_PASSPOINT();

        const writer_type json_writer{};

        BOOST_CHECK(json_writer.extension() == boost::filesystem::path{ TETENGO2_TEXT(".btt") });
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        const writer_type json_writer{};

        BOOST_TEST(json_writer.selects(boost::filesystem::path{ TETENGO2_TEXT(".btt") }));
        BOOST_TEST(!json_writer.selects(boost::filesystem::path{ TETENGO2_TEXT(".hoge") }));
        BOOST_TEST(!json_writer.selects(boost::filesystem::path{}));
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        {
            writer_type json_writer{};

            const timetable_type timetable{};
            std::ostringstream stream{};

            json_writer.write(timetable, stream);

            const auto result = stream.str();
            BOOST_CHECK(result == json0);
        }
        {
            writer_type json_writer{};

            const auto p_timetable = create_timetable1();
            std::ostringstream stream{};

            json_writer.write(*p_timetable, stream);

            const auto result = stream.str();
            BOOST_CHECK(result == json1);
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
