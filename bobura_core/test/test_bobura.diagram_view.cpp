/*! \file
    \brief Test of class bobura::diagram_view.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/detail_type_list.h>
#include <bobura/diagram_view.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using model_type = bobura::timetable_model<
        common_type_list_type::size_type,
        common_type_list_type::difference_type,
        common_type_list_type::string_type,
        common_type_list_type::operating_distance_type,
        common_type_list_type::speed_type,
        ui_type_list_type::fast_font_type>;

    using speed_type = model_type::speed_type;

    using scale_type = common_type_list_type::scale_type;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using position_type = picture_box_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = picture_box_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using diagram_view_traits_type = traits_type_list_type::diagram_view_type;

    using diagram_view_type = bobura::diagram_view<diagram_view_traits_type>;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(diagram_view)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            const diagram_view_type    diagram_view{ model, message_catalog };
        }

        BOOST_AUTO_TEST_CASE(draw_on)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            diagram_view_type          diagram_view{ model, message_catalog };

            window_type            window{};
            const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
            const auto             p_canvas = picture_box.create_canvas();
            diagram_view.draw_on(
                *p_canvas,
                dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                position_type{ position_unit_type{ 2 }, position_unit_type{ 3 } });
        }

        BOOST_AUTO_TEST_CASE(horizontal_scale)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            const diagram_view_type    diagram_view{ model, message_catalog };

            diagram_view.horizontal_scale();
        }

        BOOST_AUTO_TEST_CASE(set_horizontal_scale)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            diagram_view_type          diagram_view{ model, message_catalog };

            diagram_view.set_horizontal_scale(42);

            BOOST_CHECK(diagram_view.horizontal_scale() == scale_type{ 42 });

            diagram_view.set_horizontal_scale(24);

            BOOST_CHECK(diagram_view.horizontal_scale() == scale_type{ 24 });
        }

        BOOST_AUTO_TEST_CASE(vertical_scale)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            const diagram_view_type    diagram_view{ model, message_catalog };

            diagram_view.vertical_scale();
        }

        BOOST_AUTO_TEST_CASE(set_vertical_scale)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            diagram_view_type          diagram_view{ model, message_catalog };

            diagram_view.set_vertical_scale(42);

            BOOST_CHECK(diagram_view.vertical_scale() == scale_type{ 42 });

            diagram_view.set_vertical_scale(24);

            BOOST_CHECK(diagram_view.vertical_scale() == scale_type{ 24 });
        }

        BOOST_AUTO_TEST_CASE(dimension)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            const diagram_view_type    diagram_view{ model, message_catalog };

            diagram_view.dimension();
        }

        BOOST_AUTO_TEST_CASE(update_dimension)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            diagram_view_type          diagram_view{ model, message_catalog };

            diagram_view.update_dimension();
        }

        BOOST_AUTO_TEST_CASE(page_size)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            const diagram_view_type    diagram_view{ model, message_catalog };

            diagram_view.page_size(dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } });
        }

        BOOST_AUTO_TEST_CASE(p_item_by_position)
        {
            BOOST_TEST_PASSPOINT();

            {
                const model_type           model{};
                const message_catalog_type message_catalog{};
                const diagram_view_type    diagram_view{ model, message_catalog };

                diagram_view.p_item_by_position(position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } });
            }
            {
                const model_type           model{};
                const message_catalog_type message_catalog{};
                diagram_view_type          diagram_view{ model, message_catalog };

                diagram_view.p_item_by_position(position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } });
            }
        }

        BOOST_AUTO_TEST_CASE(unselect_all_items)
        {
            BOOST_TEST_PASSPOINT();

            const model_type           model{};
            const message_catalog_type message_catalog{};
            diagram_view_type          diagram_view{ model, message_catalog };

            diagram_view.unselect_all_items();
        }

        BOOST_AUTO_TEST_CASE(selection_observer_set)
        {
            BOOST_TEST_PASSPOINT();

            {
                const model_type           model{};
                const message_catalog_type message_catalog{};
                const diagram_view_type    diagram_view{ model, message_catalog };

                diagram_view.selection_observer_set();
            }
            {
                const model_type           model{};
                const message_catalog_type message_catalog{};
                diagram_view_type          diagram_view{ model, message_catalog };

                diagram_view.selection_observer_set();
            }
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
