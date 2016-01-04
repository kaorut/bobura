/*! \file
    \brief Test of class bobura::model::train.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <iterator>
#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using common_type_list_type = test_bobura::model::type_list::common;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using time_type = bobura::model::train_info::time<size_type, difference_type>;

    using stop_type = bobura::model::train_info::stop<size_type, difference_type, string_type>;

    using train_type = bobura::model::train<size_type, difference_type, string_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            BOOST_TEST(train.stops().empty());
        }
        {
            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            BOOST_TEST(train.stops().empty());
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };
            train_type::stops_type stops2{ stops };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                std::move(stops2)
            };

            BOOST_CHECK(train.stops() == stops);
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops
            };

            BOOST_CHECK(train.stops() == stops);
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.stops() == stops);
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.stops() == stops);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type train1{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            const train_type train2{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            BOOST_CHECK(train1 == train2);
        }
        {
            const train_type::stops_type stops1{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };
            const train_type train1{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops1.begin(),
                stops1.end()
            };

            const train_type::stops_type stops2{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };
            const train_type train2{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops2.begin(),
                stops2.end()
            };

            BOOST_CHECK(train1 == train2);
        }
        {
            const train_type::stops_type stops1{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };
            const train_type train1{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops1.begin(),
                stops1.end()
            };

            const train_type::stops_type stops2{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };
            const train_type train2{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops2.begin(),
                stops2.end()
            };

            BOOST_CHECK(train1 == train2);
        }
        {
            const train_type train1{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            const train_type train2{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            BOOST_CHECK(train1 != train2);
        }
        {
            const train_type train1{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            const train_type::stops_type stops2{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };
            const train_type train2{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("2") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("y") },
                stops2.begin(),
                stops2.end()
            };

            BOOST_CHECK(train1 != train2);
        }
        {
            const train_type::stops_type stops1{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };
            const train_type train1{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops1.begin(),
                stops1.end()
            };

            const train_type train2{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("2") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("y") }
            };

            BOOST_CHECK(train1 != train2);
        }
        {
            const train_type::stops_type stops1{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };
            const train_type train1{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops1.begin(),
                stops1.end()
            };

            const train_type::stops_type stops2{
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, true, string_type{ TETENGO2_TEXT("b") } },
            };
            const train_type train2{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("2") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("y") },
                stops2.begin(),
                stops2.end()
            };

            BOOST_CHECK(train1 != train2);
        }
    }

    BOOST_AUTO_TEST_CASE(direction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            BOOST_CHECK(train.direction() == train_type::direction_type::down);
        }
        {
            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };

            BOOST_CHECK(train.direction() == train_type::direction_type::up);
        }
    }

    BOOST_AUTO_TEST_CASE(number)
    {
        BOOST_TEST_PASSPOINT();

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("1") },
            0,
            string_type{ TETENGO2_TEXT("a") },
            string_type{ TETENGO2_TEXT("42") },
            string_type{ TETENGO2_TEXT("x") }
        };

        BOOST_CHECK(train.number() == string_type{ TETENGO2_TEXT("1") });
    }

    BOOST_AUTO_TEST_CASE(kind_index)
    {
        BOOST_TEST_PASSPOINT();

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("1") },
            42,
            string_type{ TETENGO2_TEXT("a") },
            string_type{ TETENGO2_TEXT("42") },
            string_type{ TETENGO2_TEXT("x") }
        };

        BOOST_TEST(train.kind_index() == 42U);
    }

    BOOST_AUTO_TEST_CASE(set_kind_index)
    {
        BOOST_TEST_PASSPOINT();

        train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("1") },
            42,
            string_type{ TETENGO2_TEXT("a") },
            string_type{ TETENGO2_TEXT("42") },
            string_type{ TETENGO2_TEXT("x") }
        };

        train.set_kind_index(24);

        BOOST_TEST(train.kind_index() == 24U);
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("1") },
            0,
            string_type{ TETENGO2_TEXT("a") },
            string_type{ TETENGO2_TEXT("42") },
            string_type{ TETENGO2_TEXT("x") }
        };

        BOOST_CHECK(train.name() == string_type{ TETENGO2_TEXT("a") });
    }

    BOOST_AUTO_TEST_CASE(name_number)
    {
        BOOST_TEST_PASSPOINT();

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("1") },
            0,
            string_type{ TETENGO2_TEXT("a") },
            string_type{ TETENGO2_TEXT("42") },
            string_type{ TETENGO2_TEXT("x") }
        };

        BOOST_CHECK(train.name_number() == string_type{ TETENGO2_TEXT("42") });
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("1") },
            0,
            string_type{ TETENGO2_TEXT("a") },
            string_type{ TETENGO2_TEXT("42") },
            string_type{ TETENGO2_TEXT("x") }
        };

        BOOST_CHECK(train.note() == string_type{ TETENGO2_TEXT("x") });
    }

    BOOST_AUTO_TEST_CASE(stops)
    {
        BOOST_TEST_PASSPOINT();

        const train_type::stops_type stops{
            stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
        };

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("1") },
            0,
            string_type{ TETENGO2_TEXT("a") },
            string_type{ TETENGO2_TEXT("42") },
            string_type{ TETENGO2_TEXT("x") },
            stops.begin(),
            stops.end()
        };

        BOOST_CHECK(train.stops() == stops);
    }

    BOOST_AUTO_TEST_CASE(insert_stop)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };
            train.insert_stop(train.stops().end(), stops[0]);

            BOOST_CHECK(train.stops() == stops);
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };
            train.insert_stop(train.stops().end(), stops[0]);
            train.insert_stop(train.stops().end(), stops[1]);

            BOOST_CHECK(train.stops() == stops);
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.begin() + 1
            };
            train.insert_stop(train.stops().end(), stops[1]);

            BOOST_CHECK(train.stops() == stops);
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin() + 1,
                stops.end()
            };
            train.insert_stop(train.stops().begin(), stops[0]);

            BOOST_CHECK(train.stops() == stops);
        }
    }

    BOOST_AUTO_TEST_CASE(erase_stops)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }, 
                stops.begin(),
                stops.end()
            };

            train.erase_stops(train.stops().begin(), train.stops().end());

            BOOST_TEST(train.stops().empty());
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") }
            };
            train.insert_stop(train.stops().end(), stops[0]);
            train.insert_stop(train.stops().end(), stops[1]);

            train.erase_stops(train.stops().begin(), train.stops().end());

            BOOST_TEST(train.stops().empty());
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.begin() + 1
            };
            train.insert_stop(train.stops().end(), stops[1]);

            train.erase_stops(train.stops().begin(), train.stops().end());

            BOOST_TEST(train.stops().empty());
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            train.erase_stops(train.stops().begin(), train.stops().begin());

            BOOST_TEST_REQUIRE(train.stops().size() == 2U);
            BOOST_CHECK(train.stops()[0].arrival() == time_type{ 0 });
            BOOST_CHECK(train.stops()[0].departure() == time_type{ 0 });
            BOOST_TEST(!train.stops()[0].operational());
            BOOST_CHECK(train.stops()[0].platform() == string_type{});
            BOOST_CHECK(train.stops()[1].arrival() == time_type{ 1 });
            BOOST_CHECK(train.stops()[1].departure() == time_type{ 2 });
            BOOST_TEST(train.stops()[1].operational());
            BOOST_CHECK(train.stops()[1].platform() == string_type{ TETENGO2_TEXT("a") });
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 0 }, time_type{ 0 }, false, string_type{} },
                stop_type{ time_type{ 1 }, time_type{ 2 }, true, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, false, string_type{ TETENGO2_TEXT("b") } },
            };

            train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            train.erase_stops(train.stops().begin() + 1, train.stops().begin() + 2);

            BOOST_TEST_REQUIRE(train.stops().size() == 2U);
            BOOST_CHECK(train.stops()[0].arrival() == time_type{ 0 });
            BOOST_CHECK(train.stops()[0].departure() == time_type{ 0 });
            BOOST_TEST(!train.stops()[0].operational());
            BOOST_CHECK(train.stops()[0].platform() == string_type{});
            BOOST_CHECK(train.stops()[1].arrival() == time_type{ 3 });
            BOOST_CHECK(train.stops()[1].departure() == time_type{ 4 });
            BOOST_TEST(!train.stops()[1].operational());
            BOOST_CHECK(train.stops()[1].platform() == string_type{ TETENGO2_TEXT("b") });
        }
    }


    BOOST_AUTO_TEST_CASE(previous_stop)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.previous_stop(std::next(train.stops().begin(), 0)) == train.stops().end());
            BOOST_CHECK(train.previous_stop(std::next(train.stops().begin(), 1)) == train.stops().end());
            BOOST_CHECK(
                train.previous_stop(std::next(train.stops().begin(), 2)) == std::next(train.stops().begin(), 1)
            );
            BOOST_CHECK(
                train.previous_stop(std::next(train.stops().begin(), 3)) == std::next(train.stops().begin(), 2)
            );
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
            };

            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(
                train.previous_stop(std::next(train.stops().begin(), 0)) == std::next(train.stops().begin(), 1)
            );
            BOOST_CHECK(
                train.previous_stop(std::next(train.stops().begin(), 1)) == std::next(train.stops().begin(), 2)
            );
            BOOST_CHECK(train.previous_stop(std::next(train.stops().begin(), 2)) == train.stops().end());
            BOOST_CHECK(train.previous_stop(std::next(train.stops().begin(), 3)) == train.stops().end());
        }
    }


    BOOST_AUTO_TEST_CASE(next_stop)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(
                train.next_stop(std::next(train.stops().begin(), 0)) == std::next(train.stops().begin(), 1)
            );
            BOOST_CHECK(
                train.next_stop(std::next(train.stops().begin(), 1)) == std::next(train.stops().begin(), 2)
            );
            BOOST_CHECK(train.next_stop(std::next(train.stops().begin(), 2)) == train.stops().end());
            BOOST_CHECK(train.next_stop(std::next(train.stops().begin(), 3)) == train.stops().end());
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
            };

            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.next_stop(std::next(train.stops().begin(), 0)) == train.stops().end());
            BOOST_CHECK(train.next_stop(std::next(train.stops().begin(), 1)) == train.stops().end());
            BOOST_CHECK(
                train.next_stop(std::next(train.stops().begin(), 2)) == std::next(train.stops().begin(), 1)
            );
            BOOST_CHECK(
                train.next_stop(std::next(train.stops().begin(), 3)) == std::next(train.stops().begin(), 2)
            );
        }
    }


    BOOST_AUTO_TEST_CASE(origin_stop)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type::stops_type stops{
                stop_type{ time_type::uninitialized(), time_type{ 0 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type{ 5 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") } },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.origin_stop() == std::next(train.stops().begin(), 0));
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.origin_stop() == std::next(train.stops().begin(), 1));
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 5 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type::uninitialized(), time_type{ 0 }, false, string_type{ TETENGO2_TEXT("a") } },
            };

            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.origin_stop() == std::next(train.stops().begin(), 3));
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
            };

            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.origin_stop() == std::next(train.stops().begin(), 2));
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("b") }
                },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.origin_stop() == train.stops().end());
        }
    }


    BOOST_AUTO_TEST_CASE(destination_stop)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_type::stops_type stops{
                stop_type{ time_type::uninitialized(), time_type{ 0 }, false, string_type{ TETENGO2_TEXT("a") } },
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type{ 5 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") } },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.destination_stop() == std::next(train.stops().begin(), 3));
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.destination_stop() == std::next(train.stops().begin(), 2));
        }
        {
            const train_type::stops_type stops{
                stop_type{ time_type{ 5 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") } },
                stop_type{ time_type{ 3 }, time_type{ 4 }, false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type{ 1 }, time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{ time_type::uninitialized(), time_type{ 0 }, false, string_type{ TETENGO2_TEXT("a") } },
            };

            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.destination_stop() == std::next(train.stops().begin(), 0));
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("d") }
                },
                stop_type{ time_type{ 3 }, time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("c") } },
                stop_type{ time_type::uninitialized(), time_type{ 2 }, false, string_type{ TETENGO2_TEXT("b") } },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
            };

            const train_type train{
                train_type::direction_type::up,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.destination_stop() == std::next(train.stops().begin(), 1));
        }
        {
            const train_type::stops_type stops{
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("a") }
                },
                stop_type{
                    time_type::uninitialized(), time_type::uninitialized(), false, string_type{ TETENGO2_TEXT("b") }
                },
            };

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("1") },
                0,
                string_type{ TETENGO2_TEXT("a") },
                string_type{ TETENGO2_TEXT("42") },
                string_type{ TETENGO2_TEXT("x") },
                stops.begin(),
                stops.end()
            };

            BOOST_CHECK(train.destination_stop() == train.stops().end());
        }
    }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
