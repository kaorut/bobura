/*! \file
    \brief Test of class bobura::model::timetable_info::station_interval_calculator.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using station_interval_calculator_type =
        boost::mpl::at<
            test_bobura::model::model_type_list, test_bobura::model::type::model::station_interval_calculator
        >::type;

    using station_location_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station_location>::type;

    using operating_distance_type = station_location_type::operating_distance_type;

    using train_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::train>::type;

    using stop_type = train_type::stop_type;

    using time_type = stop_type::time_type;

    using time_tick_type = time_type::tick_type;

    using time_span_type = time_type::time_span_type;

    using station_intervals_type = station_interval_calculator_type::station_intervals_type;

    using station_interval_type = station_intervals_type::value_type;

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using station_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station>::type;

    using grade_type_set_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::grade_type_set>::type;


    // functions

    station_location_type make_station_location(string_type name, operating_distance_type operating_distance)
    {
        return
            station_location_type{
                station_type{
                    std::move(name), grade_type_set_type::local_type::instance(), false, false, string_type{}
                },
                std::move(operating_distance)
            };
    }

    std::vector<station_location_type> make_station_locations()
    {
        return
            {
                make_station_location(string_type{ TETENGO2_TEXT("AAA") }, 0),
                make_station_location(string_type{ TETENGO2_TEXT("BBB") }, 10),
                make_station_location(string_type{ TETENGO2_TEXT("CCC") }, 20),
                make_station_location(string_type{ TETENGO2_TEXT("DDD") }, 30),
            };
    }

    template <typename InputIterator>
    train_type make_train(const InputIterator stop_first, const InputIterator stop_last)
    {
        return
            train_type{
                train_type::direction_type::down,
                train_type::string_type{},
                0,
                train_type::string_type{},
                train_type::string_type{},
                train_type::string_type{},
                stop_first,
                stop_last
            };
    }

    stop_type make_stop(
        const time_tick_type arrival_hours,
        const time_tick_type arrival_minutes,
        const time_tick_type departure_hours,
        const time_tick_type departure_minutes
    )
    {
        return
            stop_type{
                time_type{ arrival_hours, arrival_minutes, 0 },
                time_type{ departure_hours, departure_minutes, 0 },
                false,
                string_type{}
            };
    }

    stop_type make_stop(const bool arrival, const time_tick_type hours, const time_tick_type minutes)
    {
        time_type time{ hours, minutes, 0 };
        return
            stop_type{
                arrival ? std::move(time) : time_type::uninitialized(),
                arrival ? time_type::uninitialized() : std::move(time),
                false,
                string_type{}
            };
    }

    stop_type make_stop()
    {
        return stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{});
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable_info)
BOOST_AUTO_TEST_SUITE(station_interval_calculator)
    // test cases

    BOOST_AUTO_TEST_CASE(default_interval)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(station_interval_calculator_type::default_interval().seconds() > 0);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<station_location_type> station_locations{};
        const std::vector<train_type> down_trains{};
        const std::vector<train_type> up_trains{};
        const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };
    }

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(calculate)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<station_location_type> station_locations{};
            const std::vector<train_type> down_trains{};
            const std::vector<train_type> up_trains{};
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            BOOST_CHECK(intervals.empty());
        }
        {
            // |DOWN|   | UP |
            // +----+---+----+
            // |    |AAA|    |
            // |    |BBB|    |
            // |    |CCC|    |
            // |    |DDD|    |
            // +----+---+----+
            const auto station_locations = make_station_locations();
            const std::vector<train_type> down_trains{};
            const std::vector<train_type> up_trains{};
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_locations.size(), station_interval_calculator_type::default_interval()
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|   | UP |
            // +----+---+----+
            // |  v |AAA|    |
            // |  v |BBB|    |
            // |  v |CCC|    |
            // |  v |DDD|    |
            // +----+---+----+
            const auto station_locations = make_station_locations();
            std::vector<train_type> down_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(),
                    make_stop(),
                    make_stop(),
                    make_stop(),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const std::vector<train_type> up_trains{};
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_locations.size(), station_interval_calculator_type::default_interval()
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|   | UP |
            // +----+---+----+
            // |    |AAA|  ^ |
            // |    |BBB|  ^ |
            // |    |CCC|  ^ |
            // |    |DDD|  ^ |
            // +----+---+----+
            const auto station_locations = make_station_locations();
            const std::vector<train_type> down_trains{};
            std::vector<train_type> up_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(),
                    make_stop(),
                    make_stop(),
                    make_stop(),
                };
                up_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_locations.size(), station_interval_calculator_type::default_interval()
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|   | UP |
            // +----+---+----+
            // |1000|AAA|    |
            // |1001|BBB|    |
            // |1003|CCC|    |
            // |1006|DDD|    |
            // +----+---+----+
            const auto station_locations = make_station_locations();
            std::vector<train_type> down_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 10, 0),
                    make_stop(true, 10, 1),
                    make_stop(true, 10, 3),
                    make_stop(true, 10, 6),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const std::vector<train_type> up_trains{};
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_interval_type{ 1 * 60 },
                station_interval_type{ 2 * 60 },
                station_interval_type{ 3 * 60 },
                station_interval_calculator_type::default_interval(),
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|DOWN|   | UP |
            // +----+----+---+----+
            // |1000|1200|AAA|    |
            // |1001|1201|BBB|    |
            // |1003|1202|CCC|    |
            // |1006|1203|DDD|    |
            // +----+----+---+----+
            const auto station_locations = make_station_locations();
            std::vector<train_type> down_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 10, 0),
                    make_stop(true, 10, 1),
                    make_stop(true, 10, 3),
                    make_stop(true, 10, 6),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 12, 0),
                    make_stop(true, 12, 1),
                    make_stop(true, 12, 2),
                    make_stop(true, 12, 3),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const std::vector<train_type> up_trains{};
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_interval_type{ 1 * 60 },
                station_interval_type{ 1 * 60 },
                station_interval_type{ 1 * 60 },
                station_interval_calculator_type::default_interval(),
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|   | UP |
            // +----+---+----+
            // |1000|AAA|1106|
            // |1001|BBB|1104|
            // |1003|CCC|1102|
            // |1006|DDD|1100|
            // +----+---+----+
            const auto station_locations = make_station_locations();
            std::vector<train_type> down_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 10, 0),
                    make_stop(true, 10, 1),
                    make_stop(true, 10, 3),
                    make_stop(true, 10, 6),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            std::vector<train_type> up_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(true, 11, 6),
                    make_stop(true, 11, 4),
                    make_stop(true, 11, 2),
                    make_stop(false, 11, 0),
                };
                up_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            station_intervals_type expected{
                station_interval_type{ 1 * 60 },
                station_interval_type{ 2 * 60 },
                station_interval_type{ 2 * 60 },
                station_interval_calculator_type::default_interval(),
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|   | UP |
            // +----+---+----+
            // |1000|AAA|    |
            // |  v |BBB|    |
            // |  v |CCC|    |
            // |1012|DDD|    |
            // +----+---+----+
            const auto station_locations = make_station_locations();
            std::vector<train_type> down_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 10, 0),
                    make_stop(),
                    make_stop(),
                    make_stop(true, 10, 12),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const std::vector<train_type> up_trains{};
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_interval_type{ 4 * 60 },
                station_interval_type{ 4 * 60 },
                station_interval_type{ 4 * 60 },
                station_interval_calculator_type::default_interval(),
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|DOWN|   | UP |
            // +----+----+---+----+
            // |1000|1200|AAA|    |
            // |  v |1203|BBB|    |
            // |1004|  v |CCC|    |
            // |1006|1209|DDD|    |
            // +----+----+---+----+
            const auto station_locations = make_station_locations();
            std::vector<train_type> down_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 10, 0),
                    make_stop(),
                    make_stop(true, 10, 4),
                    make_stop(true, 10, 6),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 12, 0),
                    make_stop(true, 12, 3),
                    make_stop(),
                    make_stop(true, 12, 9),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const std::vector<train_type> up_trains{};
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_interval_type{ 3 * 60 },
                station_interval_type{ 2 * 60 },
                station_interval_type{ 2 * 60 },
                station_interval_calculator_type::default_interval(),
            };
            BOOST_CHECK(intervals == expected);
        }
        {
            // |DOWN|   | UP |
            // +----+---+----+
            // |1000|AAA|====|
            // |  v |BBB|1108|
            // |1010|CCC|  ^ |
            // |====|DDD|1100|
            // +----+---+----+
            const auto station_locations = make_station_locations();
            std::vector<train_type> down_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(false, 10, 0),
                    make_stop(),
                    make_stop(true, 10, 10),
                    make_stop(),
                };
                down_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            std::vector<train_type> up_trains{};
            {
                const std::vector<stop_type> stops{
                    make_stop(),
                    make_stop(true, 11, 8),
                    make_stop(),
                    make_stop(false, 11, 0),
                };
                up_trains.push_back(make_train(stops.begin(), stops.end()));
            }
            const station_interval_calculator_type calculator{ station_locations, down_trains, up_trains };

            const auto intervals = calculator.calculate();

            const station_intervals_type expected{
                station_interval_type{ 5 * 60 },
                station_interval_type{ 4 * 60 },
                station_interval_type{ 4 * 60 },
                station_interval_calculator_type::default_interval(),
            };
            BOOST_CHECK(intervals == expected);
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
