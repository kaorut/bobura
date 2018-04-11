/*! \file
    \brief Test of class bobura::view::diagram::station_line.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/model/timetable_info/font_color_set.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/view/diagram/station_line.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

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

    using station_location_type = model_type::timetable_type::station_location_type;

    using station_type = station_location_type::station_type;

    using font_color_type = model_type::timetable_type::font_color_set_type::font_color_type;

    using train_type = model_type::timetable_type::train_type;

    using time_type = model_type::timetable_type::train_type::stop_type::time_type;

    using time_span_type = time_type::time_span_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using position_type = picture_box_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = picture_box_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using scale_type = common_type_list_type::scale_type;

    using window_type = ui_type_list_type::window_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using traits_type = traits_type_list_type::diagram_view_type;

    using selection_type = bobura::view::diagram::selection<traits_type>;

    using station_line_type = bobura::view::diagram::station_line<traits_type>;

    using station_line_list_type = bobura::view::diagram::station_line_list<traits_type>;

    using station_grade_type_set_type = bobura::model::station_info::grade_type_set<string_type>;


    // functions

    font_color_type make_font_color(const bool has_font, const bool has_color)
    {
        const auto font =
            has_font ? tetengo2::stdalt::make_optional(
                           font_type{ string_type{ TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false }) :
                       TETENGO2_STDALT_NULLOPT;
        const auto color =
            has_color ? tetengo2::stdalt::make_optional(color_type{ 12, 34, 56 }) : TETENGO2_STDALT_NULLOPT;
        return font_color_type{ font, color, font, color };
    }
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(view)
        BOOST_AUTO_TEST_SUITE(diagram)
            BOOST_AUTO_TEST_SUITE(station_line)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    station_type                station{ string_type{ TETENGO2_TEXT("name") },
                                          station_grade_type_set_type::local_type::instance(),
                                          false,
                                          false,
                                          string_type{ TETENGO2_TEXT("note") } };
                    const station_location_type station_location{ std::move(station), 42 };
                    selection_type              selection{};
                    station_line_type           station_line1{ station_location,         selection,
                                                     position_unit_type{ 42 }, position_unit_type{ 12 },
                                                     position_unit_type{ 24 }, make_font_color(true, true) };
                    const station_line_type     station_line2{ std::move(station_line1) };
                }

                BOOST_AUTO_TEST_CASE(operator_assign)
                {
                    BOOST_TEST_PASSPOINT();

                    station_type                station1{ string_type{ TETENGO2_TEXT("name1") },
                                           station_grade_type_set_type::local_type::instance(),
                                           false,
                                           false,
                                           string_type{ TETENGO2_TEXT("note1") } };
                    const station_location_type station_location1{ std::move(station1), 42 };
                    selection_type              selection{};
                    station_line_type           station_line1{ station_location1,        selection,
                                                     position_unit_type{ 42 }, position_unit_type{ 12 },
                                                     position_unit_type{ 24 }, make_font_color(true, true) };
                    station_type                station2{ string_type{ TETENGO2_TEXT("name2") },
                                           station_grade_type_set_type::local_type::instance(),
                                           false,
                                           false,
                                           string_type{ TETENGO2_TEXT("note2") } };
                    const station_location_type station_location2{ std::move(station2), 4242 };
                    station_line_type           station_line2{ station_location2,        selection,
                                                     position_unit_type{ 42 }, position_unit_type{ 12 },
                                                     position_unit_type{ 24 }, make_font_color(true, true) };
                    station_line1 = std::move(station_line2);
                }

                BOOST_AUTO_TEST_CASE(draw_on)
                {
                    BOOST_TEST_PASSPOINT();

                    station_type                station{ string_type{ TETENGO2_TEXT("name") },
                                          station_grade_type_set_type::local_type::instance(),
                                          false,
                                          false,
                                          string_type{ TETENGO2_TEXT("note") } };
                    const station_location_type station_location{ std::move(station), 42 };
                    selection_type              selection{};
                    const auto                  font_color = make_font_color(true, true);
                    const station_line_type     station_line{ station_location,         selection,
                                                          position_unit_type{ 42 }, position_unit_type{ 12 },
                                                          position_unit_type{ 24 }, font_color };

                    window_type window{};
                    const auto  p_canvas = window.create_canvas();
                    station_line.draw_on(*p_canvas);
                }

                BOOST_AUTO_TEST_CASE(p_item_by_position)
                {
                    BOOST_TEST_PASSPOINT();

                    station_type                station{ string_type{ TETENGO2_TEXT("name") },
                                          station_grade_type_set_type::local_type::instance(),
                                          false,
                                          false,
                                          string_type{ TETENGO2_TEXT("note") } };
                    const station_location_type station_location{ std::move(station), 42 };
                    selection_type              selection{};
                    station_line_type           station_line{ station_location,         selection,
                                                    position_unit_type{ 42 }, position_unit_type{ 12 },
                                                    position_unit_type{ 24 }, make_font_color(true, true) };

                    {
                        const position_type position{ position_unit_type{ 6 }, position_unit_type{ 24 } };
                        BOOST_TEST(station_line.p_item_by_position(position) == &station_line);
                    }
                    {
                        const position_type position{ position_unit_type{ 24 }, position_unit_type{ 24 } };
                        BOOST_TEST(!station_line.p_item_by_position(position));
                    }
                    {
                        const position_type position{ position_unit_type{ 6 }, position_unit_type{ 48 } };
                        BOOST_TEST(!station_line.p_item_by_position(position));
                    }
                }

                BOOST_AUTO_TEST_CASE(selected)
                {
                    BOOST_TEST_PASSPOINT();

                    station_type                station{ string_type{ TETENGO2_TEXT("name") },
                                          station_grade_type_set_type::local_type::instance(),
                                          false,
                                          false,
                                          string_type{ TETENGO2_TEXT("note") } };
                    const station_location_type station_location{ std::move(station), 42 };
                    selection_type              selection{};
                    const station_line_type     station_line{ station_location,         selection,
                                                          position_unit_type{ 42 }, position_unit_type{ 12 },
                                                          position_unit_type{ 24 }, make_font_color(true, true) };

                    BOOST_TEST(!station_line.selected());
                }


                BOOST_AUTO_TEST_CASE(select)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        station_type                station{ string_type{ TETENGO2_TEXT("name") },
                                              station_grade_type_set_type::local_type::instance(),
                                              false,
                                              false,
                                              string_type{ TETENGO2_TEXT("note") } };
                        const station_location_type station_location{ std::move(station), 42 };
                        selection_type              selection{};
                        station_line_type           station_line{ station_location,         selection,
                                                        position_unit_type{ 42 }, position_unit_type{ 12 },
                                                        position_unit_type{ 24 }, make_font_color(true, true) };

                        station_line.select(false);

                        BOOST_TEST(station_line.selected());
                    }
                    {
                        station_type                station{ string_type{ TETENGO2_TEXT("name") },
                                              station_grade_type_set_type::local_type::instance(),
                                              false,
                                              false,
                                              string_type{ TETENGO2_TEXT("note") } };
                        const station_location_type station_location{ std::move(station), 42 };
                        selection_type              selection{};
                        station_line_type           station_line{ station_location,         selection,
                                                        position_unit_type{ 42 }, position_unit_type{ 12 },
                                                        position_unit_type{ 24 }, make_font_color(true, true) };

                        station_line.select(true);

                        BOOST_TEST(station_line.selected());
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(station_line_list)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const model_type       model{};
                    selection_type         selection{};
                    station_line_list_type station_line_list1{
                        model,
                        time_span_type{ 42 * 60 },
                        selection,
                        dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                        position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
                        position_unit_type{ 24 },
                        position_unit_type{ 42 },
                        dimension_unit_type{ 24 },
                        scale_type{ 42 },
                        std::vector<position_unit_type>(2, position_unit_type{ 42 })
                    };
                    const station_line_list_type station_line_list2{ std::move(station_line_list1) };
                }

                BOOST_AUTO_TEST_CASE(operator_assign)
                {
                    BOOST_TEST_PASSPOINT();

                    const model_type       model{};
                    selection_type         selection{};
                    station_line_list_type station_line_list1{
                        model,
                        time_span_type{ 42 * 60 },
                        selection,
                        dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                        position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
                        position_unit_type{ 24 },
                        position_unit_type{ 42 },
                        dimension_unit_type{ 24 },
                        scale_type{ 42 },
                        std::vector<position_unit_type>(2, position_unit_type{ 42 })
                    };
                    station_line_list_type station_line_list2{
                        model,
                        time_span_type{ 42 * 60 },
                        selection,
                        dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                        position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
                        position_unit_type{ 24 },
                        position_unit_type{ 42 },
                        dimension_unit_type{ 24 },
                        scale_type{ 42 },
                        std::vector<position_unit_type>(2, position_unit_type{ 42 })
                    };

                    station_line_list1 = std::move(station_line_list2);
                }

                BOOST_AUTO_TEST_CASE(draw_on)
                {
                    BOOST_TEST_PASSPOINT();

                    const model_type             model{};
                    selection_type               selection{};
                    const station_line_list_type station_line_list{
                        model,
                        time_span_type{ 42 * 60 },
                        selection,
                        dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                        position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
                        position_unit_type{ 24 },
                        position_unit_type{ 42 },
                        dimension_unit_type{ 24 },
                        scale_type{ 42 },
                        std::vector<position_unit_type>(2, position_unit_type{ 42 })
                    };

                    window_type window{};
                    const auto  p_canvas = window.create_canvas();
                    station_line_list.draw_on(*p_canvas);
                }

                BOOST_AUTO_TEST_CASE(p_item_by_position)
                {
                    BOOST_TEST_PASSPOINT();

                    const model_type       model{};
                    selection_type         selection{};
                    station_line_list_type station_line_list{
                        model,
                        time_span_type{ 42 * 60 },
                        selection,
                        dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                        position_type{ position_unit_type{ 24 }, position_unit_type{ 42 } },
                        position_unit_type{ 24 },
                        position_unit_type{ 42 },
                        dimension_unit_type{ 24 },
                        scale_type{ 42 },
                        std::vector<position_unit_type>(2, position_unit_type{ 42 })
                    };

                    const position_type position{ position_unit_type{ 24 }, position_unit_type{ 42 } };
                    BOOST_TEST(!station_line_list.p_item_by_position(position));
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
