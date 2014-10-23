/*! \file
    \brief Test of class bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <sstream>
#include <string>

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/model/serializer/windia_reader.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using timetable_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type;

    using station_location_type = timetable_type::station_location_type;

    using train_kind_type = timetable_type::train_kind_type;

    using color_type = train_kind_type::color_type;

    using train_type = timetable_type::train_type;

    using stop_type = train_type::stop_type;

    using time_type = stop_type::time_type;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<
            std::istreambuf_iterator<
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_string>::type::value_type
            >
        >;

    using reader_type =
        bobura::model::serializer::windia_reader<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::difference>::type,
            string_type,
            input_stream_iterator_type,
            boost::mpl::at<
                test_bobura::model::model_type_list, test_bobura::model::type::model::operating_distance
            >::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::speed>::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::font>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_encoder>::type
        >;

    using error_type = reader_type::error_type;


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

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        {
            reader_type reader{};

            std::istringstream input_stream{ data0 };
            BOOST_CHECK(
                !reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            reader_type reader{};

            std::istringstream input_stream{ data1 };
            BOOST_CHECK(
                reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            reader_type reader{};

            std::istringstream input_stream{ data3 };
            BOOST_CHECK(
                !reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
    }

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            reader_type reader{};

            std::istringstream input_stream{ data0 };
            auto error = error_type::none;
            const auto p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            reader_type reader{};

            std::istringstream input_stream{ data1 };
            auto error = error_type::none;
            const auto p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name().empty());
            BOOST_CHECK(p_timetable->station_locations().empty());
            BOOST_CHECK(p_timetable->train_kinds().empty());
            BOOST_CHECK(p_timetable->down_trains().empty());
            BOOST_CHECK(p_timetable->up_trains().empty());
        }
        {
            reader_type reader{};

            std::istringstream input_stream{ data2 };
            auto error = error_type::none;
            const auto p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("abc") });

            BOOST_REQUIRE_EQUAL(p_timetable->station_locations().size(), 6U);
            {
                const auto& station_location = p_timetable->station_locations()[0];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("hoge") });
                BOOST_CHECK(station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local") });
                BOOST_CHECK_EQUAL(station_location.operating_distance(), 0U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[2];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("piyo") });
                BOOST_CHECK(
                    station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local terminal") }
                );
                BOOST_CHECK_EQUAL(station_location.operating_distance(), 2U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[4];
                BOOST_CHECK(station_location.get_station().name() == string_type{ TETENGO2_TEXT("iroha") });
                BOOST_CHECK(station_location.get_station().grade().name() == string_type{ TETENGO2_TEXT("local") });
                BOOST_CHECK(station_location.get_station().shows_up_arrival_times());
                BOOST_REQUIRE_EQUAL(station_location.operating_distance(), 4U);
            }

            BOOST_REQUIRE_EQUAL(p_timetable->train_kinds().size(), 4U);
            {
                const auto& train_kind = p_timetable->train_kinds()[0];

                BOOST_CHECK(train_kind.name() == string_type{ TETENGO2_TEXT("\x95\x81\x92\xCA") }); // futsuu
                BOOST_CHECK((train_kind.color() == color_type{ 0, 0, 0 }));
                BOOST_CHECK(train_kind.weight() == train_kind_type::weight_type::normal);
            }
            {
                const auto& train_kind = p_timetable->train_kinds()[3];

                BOOST_CHECK(train_kind.name() == string_type{ TETENGO2_TEXT("express") });
                BOOST_CHECK((train_kind.color() == color_type{ 255, 0, 0 }));
                BOOST_CHECK(train_kind.weight() == train_kind_type::weight_type::bold);
            }

            BOOST_REQUIRE_EQUAL(p_timetable->down_trains().size(), 3U);
            {
                const auto& train = p_timetable->down_trains()[0];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("121D") });
                BOOST_CHECK(train.name().empty());
                BOOST_CHECK_EQUAL(train.kind_index(), 0U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const auto& stop = train.stops()[0];

                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 10, 0, 0 }));
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[2];

                    BOOST_CHECK((stop.arrival() == time_type{ 10, 20, 0 }));
                    BOOST_CHECK((stop.departure() == time_type{ 10, 30, 0 }));
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            {
                const auto& train = p_timetable->down_trains()[1];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("101D") });
                BOOST_CHECK(train.name() == string_type{ TETENGO2_TEXT("foo") });
                BOOST_CHECK_EQUAL(train.kind_index(), 1U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const auto& stop = train.stops()[0];

                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK((stop.departure() == time_type{ 11, 0, 0 }));
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[2];

                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK(!stop.departure().initialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[3];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 30, 0 }));
                    BOOST_CHECK((stop.departure() == time_type{ 11, 40, 0 }));
                    BOOST_CHECK(stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }

            BOOST_REQUIRE_EQUAL(p_timetable->up_trains().size(), 3U);
            {
                const auto& train = p_timetable->up_trains()[1];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("124D") });
                BOOST_CHECK(train.name().empty());
                BOOST_CHECK_EQUAL(train.kind_index(), 0U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const auto& stop = train.stops()[2];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 40, 00 }));
                    BOOST_CHECK((stop.departure() == time_type{ 11, 50, 00 }));
                    BOOST_CHECK(stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const auto& stop = train.stops()[4];

                    BOOST_CHECK((stop.arrival() == time_type{ 11, 10, 0 }));
                    BOOST_CHECK(!stop.departure().initialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            {
                const auto& train = p_timetable->up_trains()[2];

                BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("102D") });
                BOOST_CHECK(train.name() == string_type{ TETENGO2_TEXT("bar") });
                BOOST_CHECK_EQUAL(train.kind_index(), 3U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const auto& stop = train.stops()[4];

                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK(!stop.departure().initialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
        }
        {
            reader_type reader{};

            std::istringstream input_stream{ data3 };
            auto error = error_type::none;
            const auto p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
