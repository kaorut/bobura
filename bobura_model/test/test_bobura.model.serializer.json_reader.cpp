/*! \file
    \brief Test of class bobura::model::serializer::json_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <string>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::station
        >::type
        station_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::station_location
        >::type
        station_location_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::time
        >::type
        time_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::stop
        >::type
        stop_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::train
        >::type
        train_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::timetable
        >::type
        timetable_type;

    typedef
        boost::mpl::at<
            test_bobura::model::type_list, test_bobura::model::type::string
        >::type
        string_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::json_reader
        >::type
        reader_type;


    // variables

    const std::string json0;

    const std::string json1 =
        "[]";

    const std::string json2 =
        "[\n"
        "    {\n"
        "    },\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json3 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json4 =
        "[\n"
        "    {\n"
        "        \"piyo\":  \"piyopiyo\",\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json5 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"hoge\",\n"
        "            \"meterage\": 42\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json6 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"101D\",\n"
        "            \"note\":   \"fuga\",\n"
        "            \"stops\":  []\n"
        "        },\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\":   \"\",\n"
        "            \"stops\":  [\n"
        "                [    -1,  60030, \"1\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"9324M\",\n"
        "            \"note\":   \"piyo\",\n"
        "            \"stops\":  [\n"
        "                [  -1,  62000, \"0A\"]\n"
        "            ]\n"
        "        }\n"
        "    ]\n"
        "]\n";

    const std::string json7 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\":   \"\",\n"
        "            \"stops\":  [\n"
        "                [    -1,  66030, \"1\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n";

    const std::string json8 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\":   \"\",\n"
        "            \"stops\":  [\n"
        "                [    -1,  60030, \"1\"],\n"
        "                [ 60230,  60315, \"\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n";


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(json_reader)
    // test cases

#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const reader_type json_reader;
    }
#endif

#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        reader_type json_reader;
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json0.begin(), json0.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json1.begin(), json1.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json2.begin(), json2.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK(p_timetable->title().empty());
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json3.begin(), json3.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK(
                p_timetable->title() == string_type(TETENGO2_TEXT("hoge"))
            );
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json4.begin(), json4.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK(
                p_timetable->title() == string_type(TETENGO2_TEXT("hoge"))
            );
            BOOST_CHECK_EQUAL(p_timetable->station_locations().size(), 2U);
            {
                const station_location_type& station_location =
                    p_timetable->station_locations()[0];
                const station_type& station = station_location.station();
                BOOST_CHECK(
                    station.name() == string_type(TETENGO2_TEXT("stationA"))
                );
                BOOST_CHECK(
                    station.grade().name() ==
                    string_type(TETENGO2_TEXT("local"))
                );
                BOOST_CHECK_EQUAL(station_location.meterage(), 42U);
            }
            {
                const station_location_type& station_location =
                    p_timetable->station_locations()[1];
                const station_type& station = station_location.station();
                BOOST_CHECK(
                    station.name() == string_type(TETENGO2_TEXT("stationB"))
                );
                BOOST_CHECK(
                    station.grade().name() ==
                    string_type(TETENGO2_TEXT("principal"))
                );
                BOOST_CHECK_EQUAL(station_location.meterage(), 4242U);
            }
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json5.begin(), json5.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json6.begin(), json6.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK_EQUAL(p_timetable->down_trains().size(), 2U);
            {
                const train_type& train = p_timetable->down_trains()[0];
                BOOST_CHECK(
                    train.number() == string_type(TETENGO2_TEXT("101D"))
                );
                BOOST_CHECK(
                    train.note() == string_type(TETENGO2_TEXT("fuga"))
                );
                const train_type::stops_type& stops = train.stops();
                BOOST_CHECK_EQUAL(train.stops().size(), 2U);
                {
                    const stop_type& stop = stops[0];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const stop_type& stop = stops[1];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            {
                const train_type& train = p_timetable->down_trains()[1];
                BOOST_CHECK(
                    train.number() == string_type(TETENGO2_TEXT("123D"))
                );
                BOOST_CHECK(train.note().empty());
                const train_type::stops_type& stops = train.stops();
                BOOST_CHECK_EQUAL(train.stops().size(), 2U);
                {
                    const stop_type& stop = stops[0];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type(6, 0, 30));
                    BOOST_CHECK(
                        stop.platform() == string_type(TETENGO2_TEXT("1"))
                    );
                }
                {
                    const stop_type& stop = stops[1];
                    BOOST_CHECK(stop.arrival() == time_type(6, 5, 45));
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            BOOST_CHECK_EQUAL(p_timetable->up_trains().size(), 1U);
            {
                const train_type& train = p_timetable->up_trains()[0];
                BOOST_CHECK(
                    train.number() == string_type(TETENGO2_TEXT("9324M"))
                );
                BOOST_CHECK(
                    train.note() == string_type(TETENGO2_TEXT("piyo"))
                );
                const train_type::stops_type& stops = train.stops();
                BOOST_CHECK_EQUAL(train.stops().size(), 2U);
                {
                    const stop_type& stop = stops[0];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type(6, 20, 0));
                    BOOST_CHECK(
                        stop.platform() == string_type(TETENGO2_TEXT("0A"))
                    );
                }
                {
                    const stop_type& stop = stops[1];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
            }
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json7.begin(), json7.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json8.begin(), json8.end());

            BOOST_CHECK(!p_timetable);
        }
    }
#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
