/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/station.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>
#include <bobura/model/train_kind.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using station_type = bobura::model::station<string_type>;

    using grade_type_set_type = bobura::model::station_info::grade_type_set<string_type>;

    using local_type = grade_type_set_type::local_type;

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

    using train_kinds_type = timetable_type::train_kinds_type;

    using train_kind_index_type = timetable_type::size_type;

    using font_color_set_type = timetable_type::font_color_set_type;

    using font_color_type = font_color_set_type::font_color_type;

    using color_type = ui_type_list_type::color_type;



}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable)
    // test cases

   BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable{};
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable1{};

            const timetable_type timetable2{};

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type timetable1{};
            timetable1.set_line_name(string_type{ TETENGO2_TEXT("hoge") });

            timetable_type timetable2{};
            timetable2.set_line_name(string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type timetable1{};
            timetable1.set_line_name(string_type{ TETENGO2_TEXT("hoge") });

            timetable_type timetable2{};
            timetable2.set_line_name(string_type{ TETENGO2_TEXT("fuga") });

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type timetable1{};
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );

            timetable_type timetable2{};
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type timetable1{};
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );

            timetable_type timetable2{};
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type timetable1{};
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );

            timetable_type timetable2{};
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type timetable1{};
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            timetable_type timetable2{};
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            BOOST_CHECK(timetable1 == timetable2);
        }
    }

    BOOST_AUTO_TEST_CASE(company_name)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable{};

        BOOST_TEST(timetable.company_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_company_name)
    {
        BOOST_TEST_PASSPOINT();

        timetable_type timetable{};

        timetable.set_company_name(string_type{ TETENGO2_TEXT("hoge") });

        BOOST_CHECK(timetable.company_name() == string_type{ TETENGO2_TEXT("hoge") });
    }

    BOOST_AUTO_TEST_CASE(line_name)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable{};

        BOOST_TEST(timetable.line_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_line_name)
    {
        BOOST_TEST_PASSPOINT();

        timetable_type timetable{};

        timetable.set_line_name(string_type{ TETENGO2_TEXT("hoge") });

        BOOST_CHECK(timetable.line_name() == string_type{ TETENGO2_TEXT("hoge") });
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable{};

        BOOST_TEST(timetable.note().empty());
    }

    BOOST_AUTO_TEST_CASE(set_note)
    {
        BOOST_TEST_PASSPOINT();

        timetable_type timetable{};

        timetable.set_note(string_type{ TETENGO2_TEXT("hoge") });

        BOOST_CHECK(timetable.note() == string_type{ TETENGO2_TEXT("hoge") });
    }

    BOOST_AUTO_TEST_CASE(station_locations)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable{};

            const auto& station_locations = timetable.station_locations();

            BOOST_TEST(station_locations.empty());
        }
        {
            timetable_type timetable{};

            const timetable_type::station_locations_type station_locations{
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                },
            };
            timetable.insert_station_location(timetable.station_locations().end(), station_locations[0]);

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type timetable{};

            const timetable_type::station_locations_type station_locations{
                    station_location_type{
                        station_type{
                            string_type{ TETENGO2_TEXT("A") },
                            local_type::instance(),
                            false,
                            false,
                            string_type{ TETENGO2_TEXT("N") }
                        },
                        1
                    },
                    station_location_type{
                        station_type{
                            string_type{ TETENGO2_TEXT("B") },
                            local_type::instance(),
                            false,
                            false,
                            string_type{ TETENGO2_TEXT("N") }
                        },
                        2
                    },
            };
            timetable.insert_station_location(timetable.station_locations().end(), station_locations[0]);
            timetable.insert_station_location(timetable.station_locations().end(), station_locations[1]);

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(insert_station_location)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};

            const timetable_type::station_locations_type station_locations{
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                },
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                },
            };
            timetable.insert_station_location(timetable.station_locations().end(), station_locations[0]);
            timetable.insert_station_location(timetable.station_locations().end(), station_locations[1]);

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );

            const auto& station_locations = timetable.station_locations();

            BOOST_TEST_REQUIRE(station_locations.size() == 1U);
            BOOST_CHECK(station_locations[0].get_station().name() == string_type{ TETENGO2_TEXT("A") });
            BOOST_TEST(station_locations[0].operating_distance() == 1U);
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            const auto& station_locations = timetable.station_locations();

            BOOST_TEST_REQUIRE(station_locations.size() == 2U);
            BOOST_CHECK(station_locations[0].get_station().name() == string_type{ TETENGO2_TEXT("A") });
            BOOST_TEST(station_locations[0].operating_distance() == 1U);
            BOOST_CHECK(station_locations[1].get_station().name() == string_type{ TETENGO2_TEXT("B") });
            BOOST_TEST(station_locations[1].operating_distance() == 2U);
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );
            BOOST_CHECK_THROW(
                timetable.insert_station_location(
                    timetable.station_locations().end(),
                    station_location_type{
                        station_type{
                            string_type{ TETENGO2_TEXT("A") },
                            local_type::instance(),
                            false,
                            false,
                            string_type{ TETENGO2_TEXT("N") }
                        },
                        1
                    }
                ),
                std::invalid_argument
            );

            const auto& station_locations = timetable.station_locations();

            BOOST_TEST_REQUIRE(station_locations.size() == 1U);
            BOOST_CHECK(station_locations[0].get_station().name() == string_type{ TETENGO2_TEXT("B") });
            BOOST_TEST(station_locations[0].operating_distance() == 2U);
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("D") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    4
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().begin(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().begin() + 2,
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("C") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    3
                }
            );

            const auto& station_locations = timetable.station_locations();

            BOOST_TEST_REQUIRE(station_locations.size() == 4U);
            BOOST_CHECK(station_locations[0].get_station().name() == string_type{ TETENGO2_TEXT("A") });
            BOOST_TEST(station_locations[0].operating_distance() == 1U);
            BOOST_CHECK(station_locations[1].get_station().name() == string_type{ TETENGO2_TEXT("B") });
            BOOST_TEST(station_locations[1].operating_distance() == 2U);
            BOOST_CHECK(station_locations[2].get_station().name() == string_type{ TETENGO2_TEXT("C") });
            BOOST_TEST(station_locations[2].operating_distance() == 3U);
            BOOST_CHECK(station_locations[3].get_station().name() == string_type{ TETENGO2_TEXT("D") });
            BOOST_TEST(station_locations[3].operating_distance() == 4U);
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );

            BOOST_TEST_REQUIRE(timetable.down_trains()[0].stops().size() == timetable.station_locations().size());
            BOOST_TEST(!timetable.down_trains()[0].stops()[0].arrival().initialized());
            BOOST_TEST(!timetable.down_trains()[0].stops()[0].departure().initialized());
            BOOST_TEST(timetable.down_trains()[0].stops()[0].platform().empty());

            const train_type::stops_type stops{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") },
                    stops.begin(),
                    stops.begin() + 1
                }
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("C") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    3
                }
            );

            BOOST_TEST_REQUIRE(timetable.down_trains()[1].stops().size() == timetable.station_locations().size());
            BOOST_TEST(!timetable.down_trains()[1].stops()[1].arrival().initialized());
            BOOST_TEST(!timetable.down_trains()[1].stops()[1].departure().initialized());
            BOOST_TEST(timetable.down_trains()[1].stops()[1].platform().empty());

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("3") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") },
                    stops.begin(),
                    stops.end()
                }
            );

            timetable.insert_station_location(
                timetable.station_locations().begin() + 1,
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            BOOST_TEST_REQUIRE(timetable.down_trains()[2].stops().size() == timetable.station_locations().size());
            BOOST_TEST(!timetable.down_trains()[2].stops()[1].arrival().initialized());
            BOOST_TEST(!timetable.down_trains()[2].stops()[1].departure().initialized());
            BOOST_TEST(timetable.down_trains()[2].stops()[1].platform().empty());
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );

            BOOST_TEST_REQUIRE(timetable.up_trains()[0].stops().size() == timetable.station_locations().size());
            BOOST_TEST(!timetable.up_trains()[0].stops()[0].arrival().initialized());
            BOOST_TEST(!timetable.up_trains()[0].stops()[0].departure().initialized());
            BOOST_TEST(timetable.up_trains()[0].stops()[0].platform().empty());

            const train_type::stops_type stops{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") },
                    stops.begin(),
                    stops.begin() + 1
                }
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("C") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    3
                }
            );

            BOOST_TEST_REQUIRE(timetable.up_trains()[1].stops().size() == timetable.station_locations().size());
            BOOST_TEST(!timetable.up_trains()[1].stops()[1].arrival().initialized());
            BOOST_TEST(!timetable.up_trains()[1].stops()[1].departure().initialized());
            BOOST_TEST(timetable.up_trains()[1].stops()[1].platform().empty());

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("3") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") },
                    stops.begin(),
                    stops.end()
                }
            );

            timetable.insert_station_location(
                timetable.station_locations().begin() + 1,
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("C") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            BOOST_TEST_REQUIRE(timetable.up_trains()[2].stops().size() == timetable.station_locations().size());
            BOOST_TEST(!timetable.up_trains()[2].stops()[1].arrival().initialized());
            BOOST_TEST(!timetable.up_trains()[2].stops()[1].departure().initialized());
            BOOST_TEST(timetable.up_trains()[2].stops()[1].platform().empty());
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(erase_station_locations)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().end()
            );

            BOOST_TEST(timetable.station_locations().empty());
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin() + 1
            );

            BOOST_TEST_REQUIRE(timetable.station_locations().size() == 1U);
            BOOST_CHECK(timetable.station_locations()[0].get_station().name() == string_type{ TETENGO2_TEXT("B") });
            BOOST_TEST(timetable.station_locations()[0].operating_distance() == 2U);
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin()
            );

            BOOST_TEST_REQUIRE(timetable.station_locations().size() == 2U);
            BOOST_CHECK(timetable.station_locations()[0].get_station().name() == string_type{ TETENGO2_TEXT("A") });
            BOOST_TEST(timetable.station_locations()[0].operating_distance() == 1U);
            BOOST_CHECK(timetable.station_locations()[1].get_station().name() == string_type{ TETENGO2_TEXT("B") });
            BOOST_TEST(timetable.station_locations()[1].operating_distance() == 2U);
        }
        {
            const timetable_type::station_locations_type station_locations{
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                },
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                },
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("C") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    3
                },
            };
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("C") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    3
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin() + 1, timetable.station_locations().begin() + 2
            );

            BOOST_TEST_REQUIRE(timetable.station_locations().size() == 2U);
            BOOST_CHECK(timetable.station_locations()[0].get_station().name() == string_type{ TETENGO2_TEXT("A") });
            BOOST_TEST(timetable.station_locations()[0].operating_distance() == 1U);
            BOOST_CHECK(timetable.station_locations()[1].get_station().name() == string_type{ TETENGO2_TEXT("C") });
            BOOST_TEST(timetable.station_locations()[1].operating_distance() == 3U);
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") },
                    stops.begin(),
                    stops.end()
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().end()
            );

            BOOST_TEST(timetable.down_trains()[0].stops().size() == timetable.station_locations().size());
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") },
                    stops.begin(),
                    stops.end()
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().end()
            );

            BOOST_TEST(timetable.up_trains()[0].stops().size() == timetable.station_locations().size());
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") },
                    stops.begin(),
                    stops.end()
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin() + 1
            );

            BOOST_TEST(timetable.down_trains()[0].stops().size() == timetable.station_locations().size());
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("B") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    2
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") },
                    stops.begin(),
                    stops.end()
                }
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin() + 1
            );

            BOOST_TEST(timetable.up_trains()[0].stops().size() == timetable.station_locations().size());
        }
    }

    BOOST_AUTO_TEST_CASE(station_intervals)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable{};
        timetable.station_intervals();
    }

    BOOST_AUTO_TEST_CASE(train_kinds)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable{};

        BOOST_TEST(timetable.train_kinds().empty());
    }

    BOOST_AUTO_TEST_CASE(train_kind_referred)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("3") },
                    1,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") }
                }
            );

            BOOST_TEST(timetable.train_kind_referred(timetable.train_kinds().begin()));
            BOOST_TEST(timetable.train_kind_referred(std::next(timetable.train_kinds().begin(), 1)));
            BOOST_TEST(!timetable.train_kind_referred(std::next(timetable.train_kinds().begin(), 2)));
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("3") },
                    1,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") }
                }
            );

            BOOST_TEST(timetable.train_kind_referred(0));
            BOOST_TEST(timetable.train_kind_referred(1));
            BOOST_TEST(!timetable.train_kind_referred(2));
        }
    }

    BOOST_AUTO_TEST_CASE(insert_train_kind)
    {
        BOOST_TEST_PASSPOINT();

        timetable_type timetable{};

        const train_kind_type kind0{
            string_type{ TETENGO2_TEXT("Rapid") },
            string_type{ TETENGO2_TEXT("Rapid") },
            color_type{ 0, 128, 0 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };
        timetable.insert_train_kind(timetable.train_kinds().end(), kind0);
       
        BOOST_TEST(timetable.train_kinds().size() == 1U);

        const train_kind_type kind2{
            string_type{ TETENGO2_TEXT("Express") },
            string_type{ TETENGO2_TEXT("Exp.") },
            color_type{ 255, 0, 0 },
            train_kind_type::weight_type::bold,
            train_kind_type::line_style_type::solid
        };
        timetable.insert_train_kind(timetable.train_kinds().end(), kind2);
       
        BOOST_TEST(timetable.train_kinds().size() == 2U);

        timetable.insert_down_train(
            timetable.down_trains().end(),
            train_type{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            }
        );
        timetable.insert_down_train(
            timetable.down_trains().end(),
            train_type{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("2") },
                1,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("y") }
            }
        );

        const train_kind_type kind1{
            string_type{ TETENGO2_TEXT("Local") },
            string_type{ TETENGO2_TEXT("Local") },
            color_type{ 0, 0, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };
        timetable.insert_train_kind(std::next(timetable.train_kinds().begin(), 1), kind1);
        
        BOOST_TEST_REQUIRE(timetable.train_kinds().size() == 3U);
        BOOST_CHECK(timetable.train_kinds()[0].name() == string_type{ TETENGO2_TEXT("Rapid") });
        BOOST_CHECK(timetable.train_kinds()[1].name() == string_type{ TETENGO2_TEXT("Local") });
        BOOST_CHECK(timetable.train_kinds()[2].name() == string_type{ TETENGO2_TEXT("Express") });

        BOOST_TEST(timetable.down_trains()[0].kind_index() == 0U);
        BOOST_TEST(timetable.down_trains()[0].kind_index() < timetable.train_kinds().size());
        BOOST_CHECK(
            timetable.train_kinds()[timetable.down_trains()[0].kind_index()].name() ==
            string_type{ TETENGO2_TEXT("Rapid") }
        );
        BOOST_TEST(timetable.down_trains()[1].kind_index() == 2U);
        BOOST_TEST(timetable.down_trains()[1].kind_index() < timetable.train_kinds().size());
        BOOST_CHECK(
            timetable.train_kinds()[timetable.down_trains()[1].kind_index()].name() ==
            string_type{ TETENGO2_TEXT("Express") }
        );
    }

    BOOST_AUTO_TEST_CASE(set_train_kind)
    {
        BOOST_TEST_PASSPOINT();

        timetable_type timetable{};
        timetable.insert_train_kind(
            timetable.train_kinds().end(),
            train_kind_type{
                string_type{ TETENGO2_TEXT("Local") },
                string_type{ TETENGO2_TEXT("Local") },
                color_type{ 0, 0, 255 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid
            }
        );
        timetable.insert_train_kind(
            timetable.train_kinds().end(),
            train_kind_type{
                string_type{ TETENGO2_TEXT("Rapid") },
                string_type{ TETENGO2_TEXT("Rapid") },
                color_type{ 0, 128, 0 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid
            }
        );

        timetable.set_train_kind(
            timetable.train_kinds().begin(),
            train_kind_type{
                string_type{ TETENGO2_TEXT("Limited Express") },
                string_type{ TETENGO2_TEXT("Ltd.Exp.") },
                color_type{ 255, 0, 0 },
                train_kind_type::weight_type::bold,
                train_kind_type::line_style_type::solid
            }
        );

        BOOST_TEST_REQUIRE(timetable.train_kinds().size() == 2U);
        BOOST_CHECK(timetable.train_kinds()[0].name() == string_type{ TETENGO2_TEXT("Limited Express") });
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(erase_train_kind)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );

            timetable.erase_train_kind(timetable.train_kinds().begin());

            BOOST_TEST_REQUIRE(timetable.train_kinds().size() == 1U);
            BOOST_CHECK(timetable.train_kinds()[0].name() == string_type{ TETENGO2_TEXT("Rapid") });

            timetable.erase_train_kind(timetable.train_kinds().begin());

            BOOST_TEST(timetable.train_kinds().empty());
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Limited Express") },
                    string_type{ TETENGO2_TEXT("Ltd.Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    2,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            timetable.erase_train_kind(std::next(timetable.train_kinds().begin(), 1));

            BOOST_TEST(timetable.down_trains()[0].kind_index() == 0U);
            BOOST_TEST(timetable.down_trains()[0].kind_index() < timetable.train_kinds().size());
            BOOST_CHECK(
                timetable.train_kinds()[timetable.down_trains()[0].kind_index()].name() ==
                string_type{ TETENGO2_TEXT("Local") }
            );
            BOOST_TEST(timetable.down_trains()[1].kind_index() == 1U);
            BOOST_TEST(timetable.down_trains()[1].kind_index() < timetable.train_kinds().size());
            BOOST_CHECK(
                timetable.train_kinds()[timetable.down_trains()[1].kind_index()].name() ==
                string_type{ TETENGO2_TEXT("Limited Express") }
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            BOOST_CHECK_THROW(
                timetable.erase_train_kind(timetable.train_kinds().begin()),
                std::invalid_argument
            );
        }
    }
#endif

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(assign_train_kinds)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};

            const train_kinds_type train_kinds{
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
            };

            timetable.assign_train_kinds(std::move(train_kinds), std::vector<train_kind_index_type>());

            BOOST_TEST_REQUIRE(timetable.train_kinds().size() == 2U);
            BOOST_CHECK(timetable.train_kinds()[0].name() == string_type{ TETENGO2_TEXT("Local") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            const train_kinds_type train_kinds{
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
            };

            const std::vector<train_kind_index_type> train_kind_index_map{ 1 };

            timetable.assign_train_kinds(std::move(train_kinds), train_kind_index_map);

            BOOST_TEST_REQUIRE(timetable.train_kinds().size() == 2U);
            BOOST_CHECK(timetable.train_kinds()[0].name() == string_type{ TETENGO2_TEXT("Local") });

            BOOST_TEST(timetable.down_trains()[0].kind_index() == 1U);
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            const train_kinds_type train_kinds{
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
            };

            std::vector<train_kind_index_type> train_kind_index_map{};

            BOOST_CHECK_THROW(
                timetable.assign_train_kinds(std::move(train_kinds), train_kind_index_map), std::out_of_range
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            const train_kinds_type train_kinds{
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Local") },
                    string_type{ TETENGO2_TEXT("Local") },
                    color_type{ 0, 0, 255 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Rapid") },
                    string_type{ TETENGO2_TEXT("Rapid") },
                    color_type{ 0, 128, 0 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
            };

            const std::vector<train_kind_index_type> train_kind_index_map{ 2 };

            BOOST_CHECK_THROW(
                timetable.assign_train_kinds(std::move(train_kinds), train_kind_index_map), std::out_of_range
            );
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(down_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable{};

            const auto& trains = timetable.down_trains();

            BOOST_TEST(trains.empty());
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 1U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
        }
    }

    BOOST_AUTO_TEST_CASE(up_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable{};

            const auto& trains = timetable.up_trains();

            BOOST_TEST(trains.empty());
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 1U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
        }
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(insert_down_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 1U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("4") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("w") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().begin(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().begin() + 2,
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("3") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") }
                }
            );

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 4U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
            BOOST_CHECK(trains[2].number() == string_type{ TETENGO2_TEXT("3") });
            BOOST_CHECK(trains[2].note() == string_type{ TETENGO2_TEXT("z") });
            BOOST_CHECK(trains[3].number() == string_type{ TETENGO2_TEXT("4") });
            BOOST_CHECK(trains[3].note() == string_type{ TETENGO2_TEXT("w") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(),
                    train_type{
                        train_type::direction_type::up,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") }
                    }
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };

            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(),
                    train_type{
                        train_type::direction_type::down,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") },
                        stops.begin(),
                        stops.end()
                    }
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(),
                    train_type{
                        train_type::direction_type::down,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") }
                    }
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };

            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(),
                    train_type{
                        train_type::direction_type::down,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") },
                        stops.begin(),
                        stops.end()
                    }
                ),
                std::invalid_argument
            );
        }
    }
#endif

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(insert_up_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 1U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("4") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("w") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().begin(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().begin() + 2,
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("3") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") }
                }
            );

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 4U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
            BOOST_CHECK(trains[2].number() == string_type{ TETENGO2_TEXT("3") });
            BOOST_CHECK(trains[2].note() == string_type{ TETENGO2_TEXT("z") });
            BOOST_CHECK(trains[3].number() == string_type{ TETENGO2_TEXT("4") });
            BOOST_CHECK(trains[3].note() == string_type{ TETENGO2_TEXT("w") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.down_trains().end(),
                    train_type{
                        train_type::direction_type::down,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") }
                    }
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };

            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.up_trains().end(),
                    train_type{
                        train_type::direction_type::up,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") },
                        stops.begin(),
                        stops.end()
                    }
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type{
                    station_type{
                        string_type{ TETENGO2_TEXT("A") },
                        local_type::instance(),
                        false,
                        false,
                        string_type{ TETENGO2_TEXT("N") }
                    },
                    1
                }
            );
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );

            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.up_trains().end(),
                    train_type{
                        train_type::direction_type::up,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") }
                    }
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };

            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.up_trains().end(),
                    train_type{
                        train_type::direction_type::up,
                        string_type{ TETENGO2_TEXT("1") },
                        0,
                        string_type{ TETENGO2_TEXT("a") },
                        string_type{ TETENGO2_TEXT("42") },
                        string_type{ TETENGO2_TEXT("x") },
                        stops.begin(),
                        stops.end()
                    }
                ),
                std::invalid_argument
            );
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(erase_down_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            timetable.erase_down_trains(timetable.down_trains().begin(), timetable.down_trains().end());

            const auto& trains = timetable.down_trains();

            BOOST_TEST(trains.empty());
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            timetable.erase_down_trains(timetable.down_trains().begin(), timetable.down_trains().begin() + 1);

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 1U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("y") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            timetable.erase_down_trains(timetable.down_trains().begin(), timetable.down_trains().begin());

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("3") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") }
                }
            );

            timetable.erase_down_trains(timetable.down_trains().begin() + 1, timetable.down_trains().begin() + 2);

            const auto& trains = timetable.down_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("3") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("z") });
        }
    }

    BOOST_AUTO_TEST_CASE(erase_up_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            timetable.erase_up_trains(timetable.up_trains().begin(), timetable.up_trains().end());

            const auto& trains = timetable.up_trains();

            BOOST_TEST(trains.empty());
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            timetable.erase_up_trains(timetable.up_trains().begin(), timetable.up_trains().begin() + 1);

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 1U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("y") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                   string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );

            timetable.erase_up_trains(timetable.up_trains().begin(), timetable.up_trains().begin());

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("2") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("y") });
        }
        {
            timetable_type timetable{};
            timetable.insert_train_kind(
                timetable.train_kinds().end(),
                train_kind_type{
                    string_type{ TETENGO2_TEXT("Express") },
                    string_type{ TETENGO2_TEXT("Exp.") },
                    color_type{ 255, 0, 0 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                }
            );
            
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("3") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("z") }
                }
            );

            timetable.erase_up_trains(timetable.up_trains().begin() + 1, timetable.up_trains().begin() + 2);

            const auto& trains = timetable.up_trains();

            BOOST_TEST_REQUIRE(trains.size() == 2U);
            BOOST_CHECK(trains[0].number() == string_type{ TETENGO2_TEXT("1") });
            BOOST_CHECK(trains[0].note() == string_type{ TETENGO2_TEXT("x") });
            BOOST_CHECK(trains[1].number() == string_type{ TETENGO2_TEXT("3") });
            BOOST_CHECK(trains[1].note() == string_type{ TETENGO2_TEXT("z") });
        }
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(scheduled_speed)
    {
        BOOST_TEST_PASSPOINT();

        timetable_type timetable{};

        const timetable_type::station_locations_type station_locations{
            station_location_type{
                station_type{
                string_type{ TETENGO2_TEXT("A") },
                local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("N") }
                },
                0
            },
            station_location_type{
                station_type{
                    string_type{ TETENGO2_TEXT("B") },
                    local_type::instance(),
                    false,
                    false,
                    string_type{ TETENGO2_TEXT("N") }
                },
                1
            },
            station_location_type{
                station_type{
                    string_type{ TETENGO2_TEXT("C") },
                    local_type::instance(),
                    false,
                    false,
                    string_type{ TETENGO2_TEXT("N") }
                },
                13
            },
            station_location_type{
                station_type{
                    string_type{ TETENGO2_TEXT("D") },
                    local_type::instance(),
                    false,
                    false,
                    string_type{ TETENGO2_TEXT("N") }
                },
                14
            },
        };
        timetable.insert_station_location(timetable.station_locations().end(), station_locations[0]);
        timetable.insert_station_location(timetable.station_locations().end(), station_locations[1]);
        timetable.insert_station_location(timetable.station_locations().end(), station_locations[2]);
        timetable.insert_station_location(timetable.station_locations().end(), station_locations[3]);

        timetable.insert_train_kind(
            timetable.train_kinds().end(),
            train_kind_type{
                string_type{ TETENGO2_TEXT("Express") },
                string_type{ TETENGO2_TEXT("Exp.") },
                color_type{ 255, 0, 0 },
                train_kind_type::weight_type::bold,
                train_kind_type::line_style_type::solid
            }
        );
            
        {
            train_type train{
                train_type{
                    train_type::direction_type::down,
                    string_type{ TETENGO2_TEXT("1") },
                    0,
                    string_type{ TETENGO2_TEXT("a") },
                    string_type{ TETENGO2_TEXT("42") },
                    string_type{ TETENGO2_TEXT("x") }
                }
            };
            train.insert_stop(
                train.stops().end(),
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), true, string_type{ TETENGO2_TEXT("0") }
                }
            );
            train.insert_stop(
                train.stops().end(),
                stop_type(time_type{ 0 * 60 * 60 }, time_type{ 1 * 60 * 60 }, true, string_type{ TETENGO2_TEXT("1") })
            );
            train.insert_stop(
                train.stops().end(),
                stop_type(time_type{ 5 * 60 * 60 }, time_type{ 6 * 60 * 60 }, true, string_type{ TETENGO2_TEXT("2") })
            );
            train.insert_stop(
                train.stops().end(),
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), true, string_type{ TETENGO2_TEXT("3") }
                }
            );

            timetable.insert_down_train(timetable.down_trains().end(), std::move(train));
        }
        {
            train_type train{
                train_type{
                    train_type::direction_type::up,
                    string_type{ TETENGO2_TEXT("2") },
                    0,
                    string_type{ TETENGO2_TEXT("b") },
                    string_type{ TETENGO2_TEXT("24") },
                    string_type{ TETENGO2_TEXT("y") }
                }
            };
            train.insert_stop(
                train.stops().end(),
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), true, string_type{ TETENGO2_TEXT("0") }
                }
            );
            train.insert_stop(
                train.stops().end(),
                stop_type(time_type{ 4 * 60 * 60 }, time_type{ 5 * 60 * 60 }, true, string_type{ TETENGO2_TEXT("1") })
            );
            train.insert_stop(
                train.stops().end(),
                stop_type(time_type{ 0 * 60 * 60 }, time_type{ 1 * 60 * 60 }, true, string_type{ TETENGO2_TEXT("2") })
            );
            train.insert_stop(
                train.stops().end(),
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), true, string_type{ TETENGO2_TEXT("3") }
                }
            );

            timetable.insert_up_train(timetable.up_trains().end(), std::move(train));
        }

        {
            const auto speed =
                timetable.scheduled_speed(
                    timetable.down_trains()[0],
                    std::next(timetable.down_trains()[0].stops().begin(), 1),
                    std::next(timetable.down_trains()[0].stops().begin(), 2)
                );
            BOOST_TEST(speed == 3U);
        }
        {
            const auto speed =
                timetable.scheduled_speed(
                    timetable.up_trains()[0],
                    std::next(timetable.up_trains()[0].stops().begin(), 2),
                    std::next(timetable.up_trains()[0].stops().begin(), 1)
                );
            BOOST_TEST(speed == 4U);
        }
        {
            const train_type unknown_train = timetable.down_trains()[0];
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    unknown_train,
                    std::next(unknown_train.stops().begin(), 1),
                    std::next(unknown_train.stops().begin(), 2)
                ),
                std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    timetable.down_trains()[0],
                    timetable.down_trains()[0].stops().end(),
                    std::next(timetable.down_trains()[0].stops().begin(), 2)
                ),
                std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    timetable.down_trains()[0],
                    std::next(timetable.down_trains()[0].stops().begin(), 1),
                    timetable.down_trains()[0].stops().end()
                ),
                std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    timetable.down_trains()[0],
                    std::next(timetable.down_trains()[0].stops().begin(), 1),
                    std::next(timetable.down_trains()[0].stops().begin(), 1)
                ),
                std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    timetable.down_trains()[0],
                    std::next(timetable.down_trains()[0].stops().begin(), 2),
                    std::next(timetable.down_trains()[0].stops().begin(), 1)
                ),
                std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    timetable.up_trains()[0],
                    std::next(timetable.up_trains()[0].stops().begin(), 1),
                    std::next(timetable.up_trains()[0].stops().begin(), 2)
                ),
                std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    timetable.down_trains()[0],
                    std::next(timetable.down_trains()[0].stops().begin(), 0),
                    std::next(timetable.down_trains()[0].stops().begin(), 1)
                ),
                std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                timetable.scheduled_speed(
                    timetable.down_trains()[0],
                    std::next(timetable.down_trains()[0].stops().begin(), 2),
                    std::next(timetable.down_trains()[0].stops().begin(), 3)
                ),
                std::invalid_argument
            );
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(font_color_set)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable{};

        timetable.font_color_set();
    }

    BOOST_AUTO_TEST_CASE(set_font_color_set)
    {
        BOOST_TEST_PASSPOINT();

        timetable_type timetable{};

        font_type diagram_font{ string_type{ TETENGO2_TEXT("hoge") }, 42, false, true, false, true };
        color_type diagram_color{ 12, 34, 56 };
        font_type timetable_font{ string_type{ TETENGO2_TEXT("hoge") }, 42, false, true, false, true };
        color_type timetable_color{ 12, 34, 56 };
        const font_color_type font_color{
            std::move(diagram_font), std::move(diagram_color), std::move(timetable_font), std::move(timetable_color)
        };
        const font_color_set_type font_color_set{
            font_color,
            font_color,
            font_color,
            font_color,
            font_color,
            font_color,
            font_color,
            font_color,
            font_color,
            font_color
        };
        timetable.set_font_color_set(font_color_set);

        BOOST_CHECK(timetable.font_color_set() == font_color_set);
    }

    BOOST_AUTO_TEST_CASE(observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable{};

            timetable.observer_set();
        }
        {
            timetable_type timetable{};

            timetable.observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
