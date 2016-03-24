/*! \file
    \brief Test of class bobura::message::diagram_view.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/message/diagram_view.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/property_bar.h>
#include <bobura/settings.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using position_type = ui_type_list_type::position_type;

    using dimension_type = ui_type_list_type::dimension_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using fast_font_type = ui_type_list_type::fast_font_type;

    using abstract_window_type = ui_type_list_type::abstract_window_type;

    using side_bar_type = ui_type_list_type::side_bar_type;

    using map_box_type = ui_type_list_type::map_box_type;

    using config_traits_type = traits_type_list_type::config_type;

    using window_type = ui_type_list_type::window_type;

    using settings_type = bobura::settings<string_type, position_type, dimension_type, config_traits_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using property_bar_type =
        bobura::property_bar<
            string_type,
            position_type,
            dimension_type,
            abstract_window_type,
            side_bar_type,
            map_box_type,
            message_catalog_type,
            config_traits_type
        >;

    using model_type =
        bobura::timetable_model<
            size_type, difference_type, string_type, operating_distance_type, speed_type, fast_font_type
        >;

    using timetable_type = model_type::timetable_type;

    using station_location_type = timetable_type::station_location_type;

    using station_type = station_location_type::station_type;

    using station_grade_type_set_type = bobura::model::station_info::grade_type_set<string_type>;
    
    using station_selected_type =
        bobura::message::diagram_view::station_selected<
            size_type,
            difference_type,
            string_type,
            position_type,
            dimension_type,
            operating_distance_type,
            speed_type,
            fast_font_type,
            abstract_window_type,
            side_bar_type,
            map_box_type,
            message_catalog_type,
            config_traits_type
        >;

    using train_type = model_type::timetable_type::train_type;

    using train_kind_type = model_type::timetable_type::train_kind_type;

    using color_type = train_kind_type::color_type;

    using train_selected_type =
        bobura::message::diagram_view::train_selected<
            size_type,
            difference_type,
            string_type,
            position_type,
            dimension_type,
            operating_distance_type,
            speed_type,
            fast_font_type,
            abstract_window_type,
            side_bar_type,
            map_box_type,
            message_catalog_type,
            config_traits_type
        >;

    using all_unselected_type =
        bobura::message::diagram_view::all_unselected<
            string_type,
            position_type,
            dimension_type,
            abstract_window_type,
            side_bar_type,
            map_box_type,
            message_catalog_type,
            config_traits_type
        >;


}


#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(diagram_view)
BOOST_AUTO_TEST_SUITE(station_selected)
    // test cases

// This test case causes a segmentation fault with GCC.
#if !( \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 8, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const message_catalog_type message_catalog{};
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        property_bar_type property_bar{ window, settings, message_catalog };
        const model_type model{};
        const station_selected_type station_selected{ property_bar, model, message_catalog };

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const message_catalog_type message_catalog{};
        property_bar_type property_bar{ window, settings, message_catalog };
        const model_type model{};
        station_selected_type station_selected{ property_bar, model, message_catalog };

        station_type station{
            string_type{ TETENGO2_TEXT("name") },
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type{ TETENGO2_TEXT("note") }
        };
        station_location_type station_location{ std::move(station), 42 };
        station_selected(station_location);

        settings.clear_config();
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_selected)
    // test cases

// This test case causes a segmentation fault with GCC.
#if !( \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 8, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const message_catalog_type message_catalog{};
        property_bar_type property_bar{ window, settings, message_catalog };
        const model_type model{};
        const train_selected_type train_selected{ property_bar, model, message_catalog };

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const message_catalog_type message_catalog{};
        property_bar_type property_bar{ window, settings, message_catalog };
        model_type model{};
        model.timetable().insert_train_kind(
            model.timetable().train_kinds().end(),
            train_kind_type{
                string_type{ TETENGO2_TEXT("Express") },
                string_type{ TETENGO2_TEXT("Exp.") },
                fast_font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, false, false, true },
                color_type{ 255, 0, 0 },
                train_kind_type::weight_type::bold,
                train_kind_type::line_style_type::solid,
                fast_font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, false, false, true },
                color_type{ 255, 0, 0 },
            }
        );
        train_selected_type train_selected{ property_bar, model, message_catalog };

        const train_type train{
            train_type::direction_type::down,
            string_type{ TETENGO2_TEXT("number") },
            0,
            string_type{ TETENGO2_TEXT("name") },
            string_type{ TETENGO2_TEXT("name_number") },
            string_type{ TETENGO2_TEXT("note") }
        };
        train_selected(train, boost::none);

        settings.clear_config();
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(all_unselected)
    // test cases

// This test case causes a segmentation fault with GCC.
#if !( \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 8, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const message_catalog_type message_catalog{};
        property_bar_type property_bar{ window, settings, message_catalog };
        const all_unselected_type all_unselected{ property_bar };

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const message_catalog_type message_catalog{};
        property_bar_type property_bar{ window, settings, message_catalog };
        all_unselected_type all_unselected{ property_bar };

        all_unselected();

        settings.clear_config();
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
