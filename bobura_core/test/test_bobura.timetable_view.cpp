/*! \file
    \brief Test of class bobura::timetable_view.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/timetable_view.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/utility.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            common_type_list_type::string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using position_type = picture_box_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = picture_box_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using direction_type = bobura::view::timetable::direction_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using timetable_view_traits_type = traits_type_list_type::timetable_view_type;

    using timetable_view_type = bobura::timetable_view<timetable_view_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(timetable_view)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const timetable_view_type timetable_view{ direction_type::down, model, message_catalog };
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ direction_type::down, model, message_catalog };

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        timetable_view.draw_on(
            *p_canvas,
            dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
            position_type{ position_unit_type{ 2 }, position_unit_type{ 3 } }
        );
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const timetable_view_type timetable_view{ direction_type::down, model, message_catalog };

        timetable_view.dimension();
    }

    BOOST_AUTO_TEST_CASE(update_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ direction_type::down, model, message_catalog };

        timetable_view.update_dimension();
    }

    BOOST_AUTO_TEST_CASE(page_size)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const timetable_view_type timetable_view{ direction_type::down, model, message_catalog };

        timetable_view.page_size(dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } });
    }

    BOOST_AUTO_TEST_CASE(unselect_all_items)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        timetable_view_type timetable_view{ direction_type::down, model, message_catalog };

        timetable_view.unselect_all_items();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
