/*! \file
    \brief Test of class bobura::command::vertically_zoom_in.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/command/vertically_zoom_in.h>
#include <bobura/diagram_view.h>
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

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            common_type_list_type::string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using diagram_view_traits_type = traits_type_list_type::diagram_view_type;

    using diagram_view_type = bobura::diagram_view<diagram_view_traits_type>;

    using vertically_zoom_in_command_type =
        bobura::command::vertically_zoom_in<
            traits_type_list_type::command_type,
            traits_type_list_type::command_set_type,
            traits_type_list_type::main_window_type,
            diagram_view_traits_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(vertically_zoom_in)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type diagram_view{ model, message_catalog };
        const vertically_zoom_in_command_type command{ diagram_view };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
