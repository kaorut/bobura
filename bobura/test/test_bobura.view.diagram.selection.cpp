/*! \file
    \brief Test of class bobura::view::diagram::selection.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/view/diagram/selection.h>
#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using string_type = boost::mpl::at<bobura::common_type_list, bobura::type::string>::type;

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using station_location_type = model_type::timetable_type::station_location_type;

    using station_type = station_location_type::station_type;

    using station_grade_type_set_type =
        boost::mpl::at<bobura::model_type_list, bobura::type::model::station_grade_type_set>::type;
    
    using train_type = model_type::timetable_type::train_type;

    using stop_index_type = train_type::stops_type::size_type;

    using diagram_selection_observer_set_type =
        bobura::message::diagram_selection_observer_set<station_location_type, train_type>;

    using selection_type =
        bobura::view::diagram::selection<station_location_type, train_type, diagram_selection_observer_set_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(selection)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const selection_type selection{};
        }
        {
            selection_type selection1{};
            const selection_type selection2{ std::move(selection1) };
        }
    }

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(selected_O_station)
    {
        BOOST_TEST_PASSPOINT();

        const selection_type selection{};

        station_type station{
            string_type{ TETENGO2_TEXT("name") },
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type{ TETENGO2_TEXT("note") }
        };
        const station_location_type station_location{ std::move(station), 42 };

        BOOST_CHECK(!selection.selected(station_location));
    }
#endif

    BOOST_AUTO_TEST_CASE(selected_O_train)
    {
        BOOST_TEST_PASSPOINT();

        const selection_type selection{};

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("number") },
            0,
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("name_number") },
            string_type{ TETENGO2_TEXT("note") }
        };

        BOOST_CHECK(!selection.selected(train, boost::none));
    }

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(select_O_station)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};

        const station_location_type* p_selected_station_location = nullptr;
        selection.selection_observer_set().station_selected().connect(
            [&p_selected_station_location](const station_location_type& station_location)
            {
                p_selected_station_location = &station_location;
            }
        );

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("number") },
            0,
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("name_number") },
            string_type{ TETENGO2_TEXT("note") }
        };
        
        selection.select(train, boost::none);
        
        station_type station{
            string_type{ TETENGO2_TEXT("name") },
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type{ TETENGO2_TEXT("note") }
        };
        const station_location_type station_location{ std::move(station), 42 };

        selection.select(station_location);

        BOOST_CHECK(selection.selected(station_location));
        BOOST_CHECK(!selection.selected(train, boost::none));
        BOOST_CHECK(!selection.selected(train, boost::make_optional<stop_index_type>(42)));
        BOOST_CHECK_EQUAL(p_selected_station_location, &station_location);
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(select_O_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            selection_type selection{};

            const train_type* p_selected_train = nullptr;
            boost::optional<stop_index_type> selected_departure_stop_index{};
            selection.selection_observer_set().train_selected().connect(
                [&p_selected_train, &selected_departure_stop_index](
                    const train_type&                       train,
                    const boost::optional<stop_index_type>& departure_stop_index
                )
                {
                    p_selected_train = &train;
                    selected_departure_stop_index = departure_stop_index;
                }
            );

            station_type station{
                string_type{ TETENGO2_TEXT("name") },
                station_grade_type_set_type::local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("note") }
            };
            const station_location_type station_location{ std::move(station), 42 };
            selection.select(station_location);

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("number") },
                0,
                string_type{ TETENGO2_TEXT("name") },
                string_type{ TETENGO2_TEXT("name_number") },
                string_type{ TETENGO2_TEXT("note") }
            };
        
            selection.select(train, boost::none);
        
            BOOST_CHECK(!selection.selected(station_location));
            BOOST_CHECK(selection.selected(train, boost::none));
            BOOST_CHECK(!selection.selected(train, boost::make_optional<stop_index_type>(42)));
            BOOST_CHECK_EQUAL(p_selected_train, &train);
            BOOST_CHECK(selected_departure_stop_index == boost::none);
        }
        {
            selection_type selection{};

            const train_type* p_selected_train = nullptr;
            boost::optional<stop_index_type> selected_departure_stop_index{};
            selection.selection_observer_set().train_selected().connect(
                [&p_selected_train, &selected_departure_stop_index](
                    const train_type&                       train,
                    const boost::optional<stop_index_type>& departure_stop_index
                )
                {
                    p_selected_train = &train;
                    selected_departure_stop_index = departure_stop_index;
                }
            );

            station_type station{
                string_type{ TETENGO2_TEXT("name") },
                station_grade_type_set_type::local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("note") }
            };
            const station_location_type station_location{ std::move(station), 42 };
            selection.select(station_location);

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("number") },
                0,
                string_type{ TETENGO2_TEXT("name") },
                string_type{ TETENGO2_TEXT("name_number") },
                string_type{ TETENGO2_TEXT("note") }
            };
        
            selection.select(train, boost::make_optional<stop_index_type>(42));
        
            BOOST_CHECK(!selection.selected(station_location));
            BOOST_CHECK(!selection.selected(train, boost::none));
            BOOST_CHECK(selection.selected(train, boost::make_optional<stop_index_type>(42)));
            BOOST_CHECK_EQUAL(p_selected_train, &train);
            BOOST_CHECK(selected_departure_stop_index == boost::make_optional<stop_index_type>(42));
        }
        {
            selection_type selection{};

            const train_type* p_selected_train = nullptr;
            boost::optional<stop_index_type> selected_departure_stop_index{};
            selection.selection_observer_set().train_selected().connect(
                [&p_selected_train, &selected_departure_stop_index](
                    const train_type&                       train,
                    const boost::optional<stop_index_type>& departure_stop_index
                )
                {
                    p_selected_train = &train;
                    selected_departure_stop_index = departure_stop_index;
                }
            );

            station_type station{
                string_type{ TETENGO2_TEXT("name") },
                station_grade_type_set_type::local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("note") }
            };
            const station_location_type station_location{ std::move(station), 42 };
            selection.select(station_location);

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("number") },
                0,
                string_type{ TETENGO2_TEXT("name") },
                string_type{ TETENGO2_TEXT("name_number") },
                string_type{ TETENGO2_TEXT("note") }
            };
        
            selection.select(train, boost::make_optional<stop_index_type>(42));
        
            BOOST_CHECK(!selection.selected(station_location));
            BOOST_CHECK(!selection.selected(train, boost::none));
            BOOST_CHECK(selection.selected(train, boost::make_optional<stop_index_type>(42)));
            BOOST_CHECK_EQUAL(p_selected_train, &train);
            BOOST_CHECK(selected_departure_stop_index == boost::make_optional<stop_index_type>(42));
        }
    }
#endif

// This test case causes a segmentation fault on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(unselect_all)
    {
        BOOST_TEST_PASSPOINT();

        {
            selection_type selection{};

            bool all_unselected_called = false;
            selection.selection_observer_set().all_unselected().connect(
                [&all_unselected_called]()
                {
                    all_unselected_called = true;
                }
            );

            station_type station{
                string_type{ TETENGO2_TEXT("name") },
                station_grade_type_set_type::local_type::instance(),
                false,
                false,
                string_type{ TETENGO2_TEXT("note") }
            };
            const station_location_type station_location{ std::move(station), 42 };
            selection.select(station_location);

            selection.unselect_all();

            BOOST_CHECK(!selection.selected(station_location));
            BOOST_CHECK(all_unselected_called);
        }
        {
            selection_type selection{};

            bool all_unselected_called = false;
            selection.selection_observer_set().all_unselected().connect(
                [&all_unselected_called]()
                {
                    all_unselected_called = true;
                }
            );

            const train_type train{
                train_type::direction_type::down,
                string_type{ TETENGO2_TEXT("number") },
                0,
                string_type{ TETENGO2_TEXT("name") },
                string_type{ TETENGO2_TEXT("name_number") },
                string_type{ TETENGO2_TEXT("note") }
            };
            selection.select(train, boost::none);

            selection.unselect_all();

            BOOST_CHECK(!selection.selected(train, boost::none));
            BOOST_CHECK(all_unselected_called);
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(selection_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const selection_type selection{};

            selection.selection_observer_set();
        }
        {
            selection_type selection{};

            selection.selection_observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
