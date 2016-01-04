/*! \file
    \brief Test of class bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <iterator>
#include <string>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/windia_reader.h>
#include <bobura/model/timetable.h>
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

    using timetable_type =
        bobura::model::timetable<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using station_location_type = timetable_type::station_location_type;

    using train_kind_type = timetable_type::train_kind_type;

    using color_type = ui_type_list_type::color_type;

    using train_type = timetable_type::train_type;

    using stop_type = train_type::stop_type;

    using time_type = stop_type::time_type;

    using input_stream_iterator_type = common_type_list_type::input_stream_iterator_type;

    using windia_file_encoder_type = locale_type_list_type::windia_file_encoder_type;

    using reader_type =
        bobura::model::serializer::windia_reader<
            size_type,
            difference_type,
            string_type,
            input_stream_iterator_type,
            operating_distance_type,
            speed_type,
            font_type,
            windia_file_encoder_type
        >;

    using error_type = reader_type::error_type;

    using utf8_encoder_type =
        tetengo2::text::encoder<
            windia_file_encoder_type::internal_encoding_type,
            tetengo2::text::encoding::utf8<detail_type_list_type::encoding_type>
        >;


    // variables

    const std::string data0{};

    const std::string data1{
        "[WinDIA]\n"
        "\n"
        "\n"
        "[\x89\x77]\n" // eki
        "\n"
        "[\x89\xBA\x82\xE8]\n" // kudari
        "\n"
        "[\x8F\xE3\x82\xE8]\n" // nobori
    };

    const std::string data2{
        "[WinDIA]\n"
        "abc\n"
        "\n"
        "[\x89\x77]\n" // eki
        ",hoge\n"
        "u,fuga\n"
        "b,piyo\n"
        "pb,mnu\n"
        "u,iroha\n"
        "p,nihohe\n"
        "\n"
        "[\x90\xFC\x8E\xED]\n" // senshu
        "LINES=0,0,0,0,0,128,128,128,128,128,128,128,0,128,3,1,129,0,0,0,0,0,0,0\n"
        "Train04=junkaisoku,junk\n"
        "Train06=express,expr\n"
        "\n"
        "[\x89\xBA\x82\xE8]\n" // kudari
        ",121D,,,1000,1010,1020/1030,1040/1050,1100,1110/,\\\n"
        "\t%\n"
        "6,101D,foo,1,1100,-,-,1130/1140?,-,1150/,\\\n"
        "\t%\n"
        "(96),123D,,,1200,1210,1220/1230,1240/,,,\\\n"
        "\t%xyzw\n"
        "\n"
        "[\x8F\xE3\x82\xE8]\n" // nobori
        ",122D,,,1040/,1030/,1010/1020,1000,,\n"
        ",124D,,,1210/,1200/,1140?/1150,1120/1130,1110/,1100,\\\n"
        "\t%\n"
        "6(213),102D,bar,2,1230/,-,-,-,-,1200,\\\n"
        "\t%\n"
    };

    const std::string data3{
        "[hoge]\n"
    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(windia_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const reader_type reader{};
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        {
            reader_type reader{};

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data0) };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(!reader.selects(first, last));
        }
        {
            reader_type reader{};

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data1) };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(reader.selects(first, last));
        }
        {
            reader_type reader{};

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data3) };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_TEST(!reader.selects(first, last));
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            reader_type reader{};

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data0) };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            reader_type reader{};

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data1) };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_TEST(p_timetable->line_name().empty());
            BOOST_TEST(p_timetable->station_locations().empty());
            BOOST_TEST(p_timetable->train_kinds().empty());
            BOOST_TEST(p_timetable->down_trains().empty());
            BOOST_TEST(p_timetable->up_trains().empty());
        }
        {
            reader_type reader{};

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data2) };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(p_timetable.get());
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("abc") });

            BOOST_TEST_REQUIRE(p_timetable->station_locations().size() == 6U);
            {
                const auto& station_location = p_timetable->station_locations()[0];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("hoge") });
                BOOST_CHECK(station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local") });
                BOOST_TEST(station_location.operating_distance() == 0U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[2];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("piyo") });
                BOOST_CHECK(
                    station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local terminal") }
                );
                BOOST_TEST(station_location.operating_distance() == 2U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[4];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("iroha") });
                BOOST_CHECK(station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local") });
                BOOST_TEST(station_location.get_station().shows_up_arrival_times());
                BOOST_TEST_REQUIRE(station_location.operating_distance() == 4U);
            }

            BOOST_TEST_REQUIRE(p_timetable->train_kinds().size() == 4U);
            {
                const auto& train_kind = p_timetable->train_kinds()[0];

                static const utf8_encoder_type utf8_encoder;
                const std::string futsuu_in_utf8{ "\xE6\x99\xAE\xE9\x80\x9A" }; // futsuu
                const string_type futsuu = utf8_encoder.decode(futsuu_in_utf8);
                BOOST_CHECK(train_kind.name() == utf8_encoder.decode(futsuu_in_utf8));
                BOOST_CHECK((train_kind.color() == color_type{ 0, 0, 0 }));
                BOOST_CHECK(train_kind.weight() == train_kind_type::weight_type::normal);
            }
            {
                const auto& train_kind = p_timetable->train_kinds()[3];

                BOOST_CHECK(train_kind.name() == string_type{ TETENGO2_TEXT("express") });
                BOOST_CHECK((train_kind.color() == color_type{ 255, 0, 0 }));
                BOOST_CHECK(train_kind.weight() == train_kind_type::weight_type::bold);
            }

            BOOST_TEST_REQUIRE(p_timetable->down_trains().size() == 3U);
            {
                const auto& train = p_timetable->down_trains()[0];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("121D") });
                BOOST_TEST(train.name().empty());
                BOOST_TEST(train.kind_index() == 0U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[0];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 10, 0, 0 }));
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[2];

                    BOOST_CHECK((stop.arrival() == time_type{ 10, 20, 0 }));
                    BOOST_CHECK((stop.departure() == time_type{ 10, 30, 0 }));
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
            {
                const auto& train = p_timetable->down_trains()[1];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("101D") });
                BOOST_CHECK(train.name() == string_type{ TETENGO2_TEXT("foo") });
                BOOST_TEST(train.kind_index() == 1U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[0];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 11, 0, 0 }));
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[2];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[3];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 30, 0 }));
                    BOOST_CHECK((stop.departure() == time_type{ 11, 40, 0 }));
                    BOOST_TEST(stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }

            BOOST_TEST_REQUIRE(p_timetable->up_trains().size() == 3U);
            {
                const auto& train = p_timetable->up_trains()[1];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("124D") });
                BOOST_TEST(train.name().empty());
                BOOST_TEST(train.kind_index() == 0U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[2];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 40, 00 }));
                    BOOST_CHECK((stop.departure() == time_type{ 11, 50, 00 }));
                    BOOST_TEST(stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[4];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 10, 0 }));
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
            {
                const auto& train = p_timetable->up_trains()[2];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("102D") });
                BOOST_CHECK(train.name() == string_type{ TETENGO2_TEXT("bar") });
                BOOST_TEST(train.kind_index() == 3U);
                BOOST_TEST_REQUIRE(train.stops().size() == 6U);
                {
                    const auto& stop = train.stops()[4];

                    BOOST_TEST(!stop.arrival().initialized());
                    BOOST_TEST(!stop.departure().initialized());
                    BOOST_TEST(!stop.operational());
                    BOOST_TEST(stop.platform().empty());
                }
            }
        }
        {
            reader_type reader{};

            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(data3) };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            auto error = error_type::none;
            const auto p_timetable = reader.read(first, last, error);

            BOOST_TEST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
