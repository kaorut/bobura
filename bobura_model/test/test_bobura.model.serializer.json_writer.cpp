/*! \file
    \brief Test of class bobura::model::serializer::json_writer.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/json_writer.h>
#include <bobura/model/station.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable.h>
#include <bobura/model/timetable_info/font_color_set.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>
#include <bobura/model/train_kind.h>
#include <bobura/type_list.h>


namespace {
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

    using station_type = bobura::model::station;

    using grade_type_set_type = bobura::model::station_info::grade_type_set;

    using local_type = grade_type_set_type::local_type;

    using principal_type = grade_type_set_type::principal_type;

    using station_location_type = bobura::model::timetable_info::station_location;

    using time_type = bobura::model::train_info::time;

    using stop_type = bobura::model::train_info::stop;

    using train_kind_type = bobura::model::train_kind;

    using train_type = bobura::model::train;

    using timetable_type = bobura::model::timetable;

    using font_color_set_type = timetable_type::font_color_set_type;

    using font_color_type = font_color_set_type::font_color_type;

    using color_type = ui_type_list_type::color_type;

    using path_type = tetengo2::stdalt::filesystem::path;

    using path_string_type = path_type::string_type;

    using output_stream_type = common_type_list_type::output_stream_type;

    using writer_type = bobura::model::serializer::json_writer<
        size_type,
        difference_type,
        string_type,
        output_stream_type,
        operating_distance_type,
        speed_type,
        font_type,
        locale_type_list_type::timetable_file_encoder_type>;


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
        "        \"background\": [null, \"ABCDEF\", null, \"FEDCBA\"],\n"
        "        \"company_name\": [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\", [\"fugafont\", 42, false, true, false, true], \"FEDCBA\"]\n"
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
        "            \"diagram_font\": [\"hogefont\", 42, false, true, false, true],\n"
        "            \"diagram_color\": \"0080FF\",\n"
        "            \"diagram_line_weight\": 0,\n"
        "            \"diagram_line_style\": 0,\n"
        "            \"timetable_font\": [\"fugafont\", 42, false, true, false, true],\n"
        "            \"timetable_color\": \"00FF80\"\n"
        "        },\n"
        "        {\n"
        "            \"name\": \"nameB\",\n"
        "            \"abbreviation\": \"abbrB\",\n"
        "            \"diagram_font\": [\"foofont\", 42, false, true, false, true],\n"
        "            \"diagram_color\": \"FF8000\",\n"
        "            \"diagram_line_weight\": 1,\n"
        "            \"diagram_line_style\": 2,\n"
        "            \"timetable_font\": [\"barfont\", 42, false, true, false, true],\n"
        "            \"timetable_color\": \"80FF00\"\n"
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
        auto p_timetable = std::make_unique<timetable_type>();

        p_timetable->set_company_name(string_type{ TETENGO2_TEXT("hoge") });
        p_timetable->set_line_name(string_type{ TETENGO2_TEXT("fuga") });
        p_timetable->set_note(string_type{ TETENGO2_TEXT("piyo") });
        {
            color_type            diagram_background_color{ 0xAB, 0xCD, 0xEF };
            color_type            timetable_background_color{ 0xFE, 0xDC, 0xBA };
            const font_color_type background_font_color{
                TETENGO2_STDALT_NULLOPT,
                tetengo2::stdalt::make_optional(std::move(diagram_background_color)),
                TETENGO2_STDALT_NULLOPT,
                tetengo2::stdalt::make_optional(std::move(timetable_background_color))
            };

            font_type diagram_company_name_font{
                string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true
            };
            color_type diagram_company_name_color{ 0xAB, 0xCD, 0xEF };
            font_type  timetable_company_name_font{
                string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true
            };
            color_type            timetable_company_name_color{ 0xFE, 0xDC, 0xBA };
            const font_color_type company_name_font_color{
                tetengo2::stdalt::make_optional(std::move(diagram_company_name_font)),
                tetengo2::stdalt::make_optional(std::move(diagram_company_name_color)),
                tetengo2::stdalt::make_optional(std::move(timetable_company_name_font)),
                tetengo2::stdalt::make_optional(std::move(timetable_company_name_color))
            };

            const font_color_set_type font_color_set{ background_font_color,
                                                      font_color_set_type::default_().general(),
                                                      company_name_font_color,
                                                      font_color_set_type::default_().line_name(),
                                                      font_color_set_type::default_().note(),
                                                      font_color_set_type::default_().local_station(),
                                                      font_color_set_type::default_().principal_station(),
                                                      font_color_set_type::default_().local_terminal_station(),
                                                      font_color_set_type::default_().principal_terminal_station() };

            p_timetable->set_font_color_set(font_color_set);
        }
        {
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type{ station_type{ string_type{ TETENGO2_TEXT("stationA") },
                                                     local_type::instance(),
                                                     false,
                                                     true,
                                                     string_type{ TETENGO2_TEXT("noteA") } },
                                       42 });
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type{ station_type{ string_type{ TETENGO2_TEXT("stationB") },
                                                     principal_type::instance(),
                                                     true,
                                                     false,
                                                     string_type{ TETENGO2_TEXT("noteB") } },
                                       4242 });
        }
        {
            p_timetable->insert_train_kind(
                p_timetable->train_kinds().end(),
                train_kind_type{ string_type{ TETENGO2_TEXT("nameA") },
                                 string_type{ TETENGO2_TEXT("abbrA") },
                                 font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
                                 color_type{ 0, 128, 255 },
                                 train_kind_type::weight_type::normal,
                                 train_kind_type::line_style_type::solid,
                                 font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
                                 color_type{ 0, 255, 128 } });
            p_timetable->insert_train_kind(
                p_timetable->train_kinds().end(),
                train_kind_type{ string_type{ TETENGO2_TEXT("nameB") },
                                 string_type{ TETENGO2_TEXT("abbrB") },
                                 font_type{ string_type{ TETENGO2_TEXT("foofont") }, 42, false, true, false, true },
                                 color_type{ 255, 128, 0 },
                                 train_kind_type::weight_type::bold,
                                 train_kind_type::line_style_type::dotted,
                                 font_type{ string_type{ TETENGO2_TEXT("barfont") }, 42, false, true, false, true },
                                 color_type{ 128, 255, 0 } });
        }
        { { train_type train{ train_type::direction_type::down,
                              string_type{ TETENGO2_TEXT("101D") },
                              0,
                              string_type{ TETENGO2_TEXT("foo") },
                              string_type{ TETENGO2_TEXT("bar") },
                              string_type{ TETENGO2_TEXT("fuga") } };
        train.insert_stop(
            train.stops().end(),
            stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{}));
        train.insert_stop(
            train.stops().end(),
            stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{}));
        p_timetable->insert_down_train(p_timetable->down_trains().end(), train);
    }
    {
        train_type train{ train_type::direction_type::down,    string_type{ TETENGO2_TEXT("123D") }, 1,
                          string_type{ TETENGO2_TEXT("baz") }, string_type{ TETENGO2_TEXT("bazz") }, string_type{} };
        train.insert_stop(
            train.stops().end(),
            stop_type{ time_type::uninitialized(), time_type{ 6, 0, 30 }, true, string_type{ TETENGO2_TEXT("1") } });
        train.insert_stop(
            train.stops().end(), stop_type(time_type{ 10, 5, 45 }, time_type::uninitialized(), false, string_type{}));
        p_timetable->insert_down_train(p_timetable->down_trains().end(), train);
    }
}
{
    {
        train_type train{ train_type::direction_type::up,
                          string_type{ TETENGO2_TEXT("9324M") },
                          0,
                          string_type{ TETENGO2_TEXT("abc") },
                          string_type{ TETENGO2_TEXT("def") },
                          string_type{ TETENGO2_TEXT("piyo") } };
        train.insert_stop(
            train.stops().end(),
            stop_type{ time_type::uninitialized(), time_type{ 6, 20, 0 }, false, string_type{ TETENGO2_TEXT("0A") } });
        train.insert_stop(
            train.stops().end(),
            stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{}));
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

                    BOOST_CHECK(
                        json_writer.extension() ==
                        tetengo2::stdalt::filesystem::path{ path_string_type{ TETENGO2_TEXT(".btt") } });
                }

                BOOST_AUTO_TEST_CASE(selects)
                {
                    BOOST_TEST_PASSPOINT();

                    const writer_type json_writer{};

                    BOOST_TEST(json_writer.selects(
                        tetengo2::stdalt::filesystem::path{ path_string_type{ TETENGO2_TEXT(".btt") } }));
                    BOOST_TEST(!json_writer.selects(
                        tetengo2::stdalt::filesystem::path{ path_string_type{ TETENGO2_TEXT(".hoge") } }));
                    BOOST_TEST(!json_writer.selects(tetengo2::stdalt::filesystem::path{}));
                }

                BOOST_AUTO_TEST_CASE(write)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        writer_type json_writer{};

                        const timetable_type timetable{};
                        std::ostringstream   stream{};

                        json_writer.write(timetable, stream);

                        const auto result = stream.str();
                        BOOST_CHECK(result == json0);
                    }
                    {
                        writer_type json_writer{};

                        const auto         p_timetable = create_timetable1();
                        std::ostringstream stream{};

                        json_writer.write(*p_timetable, stream);

                        const auto result = stream.str();
                        BOOST_CHECK(result == json1);
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
