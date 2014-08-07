/*! \file
    \brief Test of class bobura::diagram_view.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/diagram_view.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using size_type = boost::mpl::at<bobura::common_type_list, bobura::type::size>::type;

    using difference_type = boost::mpl::at<bobura::common_type_list, bobura::type::difference>::type;

    using string_type = boost::mpl::at<bobura::common_type_list, bobura::type::string>::type;

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using speed_type = model_type::speed_type;

    using operating_distance_type = model_type::timetable_type::station_location_type::operating_distance_type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    using picture_box_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type;

    using position_type = picture_box_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = picture_box_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using canvas_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type;

    using solid_background_type =
        tetengo2::gui::drawing::solid_background<
            boost::mpl::at<bobura::detail_type_list, bobura::type::detail::drawing>::type
        >;

    using message_catalog_type =
        boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using view_type =
        bobura::diagram_view<
            size_type,
            difference_type,
            string_type,
            operating_distance_type,
            speed_type,
            canvas_type,
            solid_background_type,
            message_catalog_type
        >;

    using horizontal_scale_type = view_type::horizontal_scale_type;

    using vertical_scale_type = view_type::vertical_scale_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(diagram_view)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const view_type view{ model, message_catalog };
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        view.draw_on(
            *p_canvas,
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            position_type{ left_type{ 2 }, top_type{ 3 } }
        );
    }

    BOOST_AUTO_TEST_CASE(horizontal_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const view_type view{ model, message_catalog };

        view.horizontal_scale();
    }

    BOOST_AUTO_TEST_CASE(set_horizontal_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };

        view.set_horizontal_scale(42);

        BOOST_CHECK(view.horizontal_scale() == horizontal_scale_type{ 42 });

        view.set_horizontal_scale(24);

        BOOST_CHECK(view.horizontal_scale() == horizontal_scale_type{ 24 });
    }

    BOOST_AUTO_TEST_CASE(vertical_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const view_type view{ model, message_catalog };

        view.vertical_scale();
    }

    BOOST_AUTO_TEST_CASE(set_vertical_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };

        view.set_vertical_scale(42);

        BOOST_CHECK(view.vertical_scale() == vertical_scale_type{ 42 });

        view.set_vertical_scale(24);

        BOOST_CHECK(view.vertical_scale() == vertical_scale_type{ 24 });
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const view_type view{ model, message_catalog };

        view.dimension();
    }

    BOOST_AUTO_TEST_CASE(update_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };

        view.update_dimension();
    }

    BOOST_AUTO_TEST_CASE(page_size)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        const view_type view{ model, message_catalog };

        view.page_size(dimension_type{ width_type{ 42 }, height_type{ 24 } });
    }

    BOOST_AUTO_TEST_CASE(p_item_by_position)
    {
        BOOST_TEST_PASSPOINT();

        {
            const model_type model{};
            const message_catalog_type message_catalog{};
            const view_type view{ model, message_catalog };

            view.p_item_by_position(position_type{ left_type{ 42 }, top_type{ 24 } });
        }
        {
            const model_type model{};
            const message_catalog_type message_catalog{};
            view_type view{ model, message_catalog };

            view.p_item_by_position(position_type{ left_type{ 42 }, top_type{ 24 } });
        }
    }

    BOOST_AUTO_TEST_CASE(unselect_all_items)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };

        view.unselect_all_items();
    }

    BOOST_AUTO_TEST_CASE(selection_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const model_type model{};
            const message_catalog_type message_catalog{};
            const view_type view{ model, message_catalog };

            view.selection_observer_set();
        }
        {
            const model_type model{};
            const message_catalog_type message_catalog{};
            view_type view{ model, message_catalog };

            view.selection_observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
