/*! \file
    \brief Test of class bobura::view::diagram::zoom.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/diagram_view.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/zoom.h>
#include <bobura/view_picture_box.h>


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

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using window_type = ui_type_list_type::window_type;

    using abstract_window_type = ui_type_list_type::abstract_window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using mouse_capture_type = ui_type_list_type::mouse_capture_type;

    using view_picture_box_type = bobura::view_picture_box<picture_box_type, abstract_window_type, mouse_capture_type>;

    using view_traits_type = traits_type_list_type::diagram_view_type;

    using font_type = ui_type_list_type::fast_font_type;

    using timetable_model_type =
        bobura::timetable_model<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using diagram_view_type = bobura::diagram_view<view_traits_type>;

    using zoom_type =
        bobura::view::diagram::zoom<view_traits_type, abstract_window_type, picture_box_type, mouse_capture_type>;

    using scale_type = zoom_type::scale_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(zoom)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        view_picture_box_type picture_box{ parent };
        const timetable_model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type view{ model, message_catalog };
        const zoom_type zoom{ picture_box, view };
    }

    BOOST_AUTO_TEST_CASE(set_horizontal_scale)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        view_picture_box_type picture_box{ parent };
        const timetable_model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type view{ model, message_catalog };
        zoom_type zoom{ picture_box, view };

        zoom.set_horizontal_scale(scale_type{ 42 });
    }

    BOOST_AUTO_TEST_CASE(horizontally_zoom_in)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        view_picture_box_type picture_box{ parent };
        const timetable_model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type view{ model, message_catalog };
        zoom_type zoom{ picture_box, view };

        zoom.horizontally_zoom_in(false);
        zoom.horizontally_zoom_in(true);
    }

    BOOST_AUTO_TEST_CASE(horizontally_zoom_out)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        view_picture_box_type picture_box{ parent };
        const timetable_model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type view{ model, message_catalog };
        zoom_type zoom{ picture_box, view };

        zoom.horizontally_zoom_out(false);
        zoom.horizontally_zoom_out(true);
    }

    BOOST_AUTO_TEST_CASE(set_vertical_scale)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        view_picture_box_type picture_box{ parent };
        const timetable_model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type view{ model, message_catalog };
        zoom_type zoom{ picture_box, view };

        zoom.set_vertical_scale(scale_type{ 42 });
    }

    BOOST_AUTO_TEST_CASE(vertically_zoom_in)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        view_picture_box_type picture_box{ parent };
        const timetable_model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type view{ model, message_catalog };
        zoom_type zoom{ picture_box, view };

        zoom.vertically_zoom_in(false);
        zoom.vertically_zoom_in(true);
    }

    BOOST_AUTO_TEST_CASE(vertically_zoom_out)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        view_picture_box_type picture_box{ parent };
        const timetable_model_type model{};
        const message_catalog_type message_catalog{};
        diagram_view_type view{ model, message_catalog };
        zoom_type zoom{ picture_box, view };

        zoom.vertically_zoom_out(false);
        zoom.vertically_zoom_out(true);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
