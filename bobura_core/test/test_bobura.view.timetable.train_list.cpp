/*! \file
    \brief Test of class bobura::view::timetable::train_list.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/em.h>

#include <bobura/detail_type_list.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/train_list.h>
#include <bobura/view/timetable/utility.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using model_type = bobura::timetable_model<
        common_type_list_type::size_type,
        common_type_list_type::difference_type,
        string_type,
        common_type_list_type::operating_distance_type,
        common_type_list_type::speed_type,
        ui_type_list_type::fast_font_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using dimension_type = picture_box_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using direction_type = bobura::view::timetable::direction_type;

    using traits_type = traits_type_list_type::timetable_view_type;

    using train_list_type = bobura::view::timetable::train_list<traits_type>;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(view)
        BOOST_AUTO_TEST_SUITE(timetable)
            BOOST_AUTO_TEST_SUITE(train_list)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const model_type           model{};
                    const message_catalog_type message_catalog{};
                    window_type                window{};
                    const picture_box_type     picture_box{ window, picture_box_type::scroll_bar_style_type::both };
                    const auto                 p_canvas = picture_box.create_canvas();
                    train_list_type            header1{ direction_type::down,
                                             model,
                                             message_catalog,
                                             *p_canvas,
                                             dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } } };
                    const train_list_type      header2{ std::move(header1) };
                }

                BOOST_AUTO_TEST_CASE(operator_assign)
                {
                    BOOST_TEST_PASSPOINT();

                    const model_type           model{};
                    const message_catalog_type message_catalog{};
                    window_type                window{};
                    const picture_box_type     picture_box{ window, picture_box_type::scroll_bar_style_type::both };
                    const auto                 p_canvas = picture_box.create_canvas();
                    train_list_type            header1{ direction_type::down,
                                             model,
                                             message_catalog,
                                             *p_canvas,
                                             dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } } };
                    train_list_type            header2{ direction_type::down,
                                             model,
                                             message_catalog,
                                             *p_canvas,
                                             dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } } };

                    header1 = std::move(header2);
                }

                BOOST_AUTO_TEST_CASE(draw_on)
                {
                    BOOST_TEST_PASSPOINT();

                    const model_type           model{};
                    const message_catalog_type message_catalog{};
                    window_type                window{};
                    const picture_box_type     picture_box{ window, picture_box_type::scroll_bar_style_type::both };
                    const auto                 p_canvas = picture_box.create_canvas();
                    const train_list_type      train_list{ direction_type::down,
                                                      model,
                                                      message_catalog,
                                                      *p_canvas,
                                                      dimension_type{ dimension_unit_type{ 42 },
                                                                      dimension_unit_type{ 24 } } };

                    train_list.draw_on(*p_canvas);
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
