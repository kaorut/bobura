/*! \file
    \brief Test of class bobura::view::diagram::selection.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/none.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using string_type = common_type_list_type::string_type;

    using model_type =
        bobura::timetable_model<
            size_type,
            common_type_list_type::difference_type,
            string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using station_location_type = model_type::timetable_type::station_location_type;

    using station_type = station_location_type::station_type;

    using station_grade_type_set_type = bobura::model::station_info::grade_type_set<string_type>;
    
    using train_type = model_type::timetable_type::train_type;

    using traits_type = traits_type_list_type::diagram_view_type;

    using selection_type = bobura::view::diagram::selection<traits_type>;


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

        BOOST_TEST(!selection.selected(station_location));
    }

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

        BOOST_TEST(!selection.selected(train, boost::none));
    }

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

        BOOST_TEST(selection.selected(station_location));
        BOOST_TEST(!selection.selected(train, boost::none));
        BOOST_TEST(!selection.selected(train, boost::make_optional<size_type>(42)));
        BOOST_TEST(p_selected_station_location == &station_location);
    }

    BOOST_AUTO_TEST_CASE(select_O_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            selection_type selection{};

            const train_type* p_selected_train = nullptr;
            boost::optional<size_type> selected_departure_stop_index{};
            selection.selection_observer_set().train_selected().connect(
                [&p_selected_train, &selected_departure_stop_index](
                    const train_type&                 train,
                    const boost::optional<size_type>& departure_stop_index
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
        
            BOOST_TEST(!selection.selected(station_location));
            BOOST_TEST(selection.selected(train, boost::none));
            BOOST_TEST(!selection.selected(train, boost::make_optional<size_type>(42)));
            BOOST_TEST(p_selected_train == &train);
            BOOST_CHECK(selected_departure_stop_index == boost::none);
        }
        {
            selection_type selection{};

            const train_type* p_selected_train = nullptr;
            boost::optional<size_type> selected_departure_stop_index{};
            selection.selection_observer_set().train_selected().connect(
                [&p_selected_train, &selected_departure_stop_index](
                    const train_type&                 train,
                    const boost::optional<size_type>& departure_stop_index
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
        
            selection.select(train, boost::make_optional<size_type>(42));
        
            BOOST_TEST(!selection.selected(station_location));
            BOOST_TEST(!selection.selected(train, boost::none));
            BOOST_TEST(selection.selected(train, boost::make_optional<size_type>(42)));
            BOOST_TEST(p_selected_train == &train);
            BOOST_CHECK(selected_departure_stop_index == boost::make_optional<size_type>(42));
        }
        {
            selection_type selection{};

            const train_type* p_selected_train = nullptr;
            boost::optional<size_type> selected_departure_stop_index{};
            selection.selection_observer_set().train_selected().connect(
                [&p_selected_train, &selected_departure_stop_index](
                    const train_type&                 train,
                    const boost::optional<size_type>& departure_stop_index
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
        
            selection.select(train, boost::make_optional<size_type>(42));
        
            BOOST_TEST(!selection.selected(station_location));
            BOOST_TEST(!selection.selected(train, boost::none));
            BOOST_TEST(selection.selected(train, boost::make_optional<size_type>(42)));
            BOOST_TEST(p_selected_train == &train);
            BOOST_CHECK(selected_departure_stop_index == boost::make_optional<size_type>(42));
        }
    }

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

            BOOST_TEST(!selection.selected(station_location));
            BOOST_TEST(all_unselected_called);
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

            BOOST_TEST(!selection.selected(train, boost::none));
            BOOST_TEST(all_unselected_called);
        }
    }

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
