/*! \file
    \brief Test of class bobura::view_picture_box.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view_picture_box.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using mouse_capture_type = ui_type_list_type::mouse_capture_type;

    using view_picture_box_type = bobura::view_picture_box<picture_box_type, mouse_capture_type>;

    using dimension_type = view_picture_box_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using mouse_button_type = view_picture_box_type::mouse_button_type;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(view_picture_box)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            window_type                 window{};
            const view_picture_box_type picture_box{ window };
        }

        BOOST_AUTO_TEST_CASE(set_mouse_capture)
        {
            BOOST_TEST_PASSPOINT();

            window_type           window{};
            view_picture_box_type picture_box{ window };

            picture_box.set_mouse_capture(mouse_button_type::left);
            picture_box.release_mouse_capture(mouse_button_type::left);
        }

        BOOST_AUTO_TEST_CASE(release_mouse_capture)
        {
            BOOST_TEST_PASSPOINT();

            {
                window_type           window{};
                view_picture_box_type picture_box{ window };

                const auto captured = picture_box.release_mouse_capture(mouse_button_type::left);

                BOOST_TEST(!captured);
            }
            {
                window_type           window{};
                view_picture_box_type picture_box{ window };

                picture_box.set_mouse_capture(mouse_button_type::left);
                const auto captured = picture_box.release_mouse_capture(mouse_button_type::left);

                BOOST_TEST(captured);
            }
        }

        BOOST_AUTO_TEST_CASE(update_scroll_bars)
        {
            BOOST_TEST_PASSPOINT();

            window_type           window{};
            view_picture_box_type picture_box{ window };

            picture_box.update_scroll_bars(
                dimension_type{ dimension_unit_type{ 24 }, dimension_unit_type{ 24 } },
                dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 42 } });
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
