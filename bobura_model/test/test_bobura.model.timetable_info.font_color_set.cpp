/*! \file
    \brief Test of class bobura::model::timetable_info::font_color_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <utility>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/model/timetable_info/font_color_set.h>

#include "test_bobura.model.detail_type_list.h"
#include "test_bobura.model.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using font_type = ui_type_list_type::font_type;

    using color_type = ui_type_list_type::color_type;

    using font_color_set_type = bobura::model::timetable_info::font_color_set<font_type>;

    using font_color_type = font_color_set_type::font_color_type;


    // functions

    font_color_type make_font_color(const string_type& font_name, const bool has_color)
    {
        const auto font = !font_name.empty() ?
                              tetengo2::stdalt::make_optional(font_type{ font_name, 42, false, true, false, true }) :
                              TETENGO2_STDALT_NULLOPT;
        const auto color =
            has_color ? tetengo2::stdalt::make_optional(color_type{ 12, 34, 56 }) : TETENGO2_STDALT_NULLOPT;
        return font_color_type{ font, color, font, color };
    }

    font_color_set_type make_font_color_set1()
    {
        auto background_font_color = make_font_color(string_type{}, true);
        auto general_font_color = make_font_color(string_type{ TETENGO2_TEXT("general") }, true);
        auto company_name_font_color = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);
        auto line_name_font_color = make_font_color(string_type{ TETENGO2_TEXT("line_name") }, true);
        auto note_font_color = make_font_color(string_type{ TETENGO2_TEXT("note") }, true);
        auto local_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("local_station") }, true);
        auto principal_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("principal_station") }, true);
        auto local_terminal_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("local_terminal") }, true);
        auto principal_terminal_station_font_color =
            make_font_color(string_type{ TETENGO2_TEXT("principal_terminal") }, true);

        return font_color_set_type{ std::move(background_font_color),
                                    std::move(general_font_color),
                                    std::move(company_name_font_color),
                                    std::move(line_name_font_color),
                                    std::move(note_font_color),
                                    std::move(local_station_font_color),
                                    std::move(principal_station_font_color),
                                    std::move(local_terminal_station_font_color),
                                    std::move(principal_terminal_station_font_color) };
    }

    font_color_set_type make_font_color_set2()
    {
        auto background_font_color = make_font_color(string_type{}, true);
        auto general_font_color = make_font_color(string_type{ TETENGO2_TEXT("general") }, true);
        auto company_name_font_color = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);
        auto line_name_font_color = make_font_color(string_type{ TETENGO2_TEXT("line_name") }, true);
        auto note_font_color = make_font_color(string_type{ TETENGO2_TEXT("note") }, true);
        auto local_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("local_station") }, true);
        auto principal_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("principal_station") }, true);
        auto local_terminal_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("local_terminal") }, true);
        auto principal_terminal_station_font_color =
            make_font_color(string_type{ TETENGO2_TEXT("principal_terminal") }, true);

        return font_color_set_type{ std::move(background_font_color),
                                    std::move(general_font_color),
                                    std::move(company_name_font_color),
                                    std::move(line_name_font_color),
                                    std::move(note_font_color),
                                    std::move(local_station_font_color),
                                    std::move(principal_station_font_color),
                                    std::move(local_terminal_station_font_color),
                                    std::move(principal_terminal_station_font_color) };
    }

    font_color_set_type make_font_color_set3()
    {
        auto background_font_color = make_font_color(string_type{}, true);
        auto general_font_color = make_font_color(string_type{ TETENGO2_TEXT("GENERAL") }, true);
        auto company_name_font_color = make_font_color(string_type{ TETENGO2_TEXT("COMPANY_NAME") }, true);
        auto line_name_font_color = make_font_color(string_type{ TETENGO2_TEXT("LINE_NAME") }, true);
        auto note_font_color = make_font_color(string_type{ TETENGO2_TEXT("NOTE") }, true);
        auto local_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("LOCAL_STATION") }, true);
        auto principal_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("PRINCIPAL_STATION") }, true);
        auto local_terminal_station_font_color = make_font_color(string_type{ TETENGO2_TEXT("LOCAL_TERMINAL") }, true);
        auto principal_terminal_station_font_color =
            make_font_color(string_type{ TETENGO2_TEXT("PRINCIPAL_TERMINAL") }, true);
        return font_color_set_type{ std::move(background_font_color),
                                    std::move(general_font_color),
                                    std::move(company_name_font_color),
                                    std::move(line_name_font_color),
                                    std::move(note_font_color),
                                    std::move(local_station_font_color),
                                    std::move(principal_station_font_color),
                                    std::move(local_terminal_station_font_color),
                                    std::move(principal_terminal_station_font_color) };
    }
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(model)
        BOOST_AUTO_TEST_SUITE(timetable_info)
            BOOST_AUTO_TEST_SUITE(font_color)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto font_color = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);
                }

                BOOST_AUTO_TEST_CASE(operator_equal)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const auto font_color1 = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);
                        const auto font_color2 = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);

                        BOOST_CHECK(font_color1 == font_color2);
                    }
                    {
                        const auto font_color1 = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);
                        const auto font_color2 = make_font_color(string_type{ TETENGO2_TEXT("ABC") }, true);

                        BOOST_CHECK(font_color1 != font_color2);
                    }
                }

                BOOST_AUTO_TEST_CASE(diagram_font)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto font_color = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);

                    const auto expected = tetengo2::stdalt::make_optional(
                        font_type{ string_type{ TETENGO2_TEXT("company_name") }, 42, false, true, false, true });
                    BOOST_CHECK(font_color.diagram_font() == expected);
                }

                BOOST_AUTO_TEST_CASE(diagram_color)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto font_color = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);

                    BOOST_CHECK(
                        (font_color.diagram_color() == tetengo2::stdalt::make_optional(color_type{ 12, 34, 56 })));
                }

                BOOST_AUTO_TEST_CASE(timetable_font)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto font_color = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);

                    const auto expected = tetengo2::stdalt::make_optional(
                        font_type{ string_type{ TETENGO2_TEXT("company_name") }, 42, false, true, false, true });
                    BOOST_CHECK(font_color.timetable_font() == expected);
                }

                BOOST_AUTO_TEST_CASE(timetable_color)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto font_color = make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true);

                    BOOST_CHECK(
                        (font_color.timetable_color() == tetengo2::stdalt::make_optional(color_type{ 12, 34, 56 })));
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(font_color_set)
                // test cases

                BOOST_AUTO_TEST_CASE(default_)
                {
                    BOOST_TEST_PASSPOINT();

                    font_color_set_type::default_();
                }

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    make_font_color_set1();
                }

                BOOST_AUTO_TEST_CASE(operator_equal)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const font_color_set_type font_color_set1 = make_font_color_set1();
                        const font_color_set_type font_color_set2 = make_font_color_set2();


                        BOOST_CHECK(font_color_set1 == font_color_set2);
                    }
                    {
                        const font_color_set_type font_color_set1 = make_font_color_set1();
                        const font_color_set_type font_color_set3 = make_font_color_set3();

                        BOOST_CHECK(font_color_set1 != font_color_set3);
                    }
                }

                BOOST_AUTO_TEST_CASE(background)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(font_color_set.background() == make_font_color(string_type{}, true));
                }

                BOOST_AUTO_TEST_CASE(general)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(
                        font_color_set.general() == make_font_color(string_type{ TETENGO2_TEXT("general") }, true));
                }

                BOOST_AUTO_TEST_CASE(company_name)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(
                        font_color_set.company_name() ==
                        make_font_color(string_type{ TETENGO2_TEXT("company_name") }, true));
                }

                BOOST_AUTO_TEST_CASE(line_name)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(
                        font_color_set.line_name() == make_font_color(string_type{ TETENGO2_TEXT("line_name") }, true));
                }

                BOOST_AUTO_TEST_CASE(note)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(font_color_set.note() == make_font_color(string_type{ TETENGO2_TEXT("note") }, true));
                }

                BOOST_AUTO_TEST_CASE(local_station)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(
                        font_color_set.local_station() ==
                        make_font_color(string_type{ TETENGO2_TEXT("local_station") }, true));
                }

                BOOST_AUTO_TEST_CASE(principal_station)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(
                        font_color_set.principal_station() ==
                        make_font_color(string_type{ TETENGO2_TEXT("principal_station") }, true));
                }

                BOOST_AUTO_TEST_CASE(local_terminal_station)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(
                        font_color_set.local_terminal_station() ==
                        make_font_color(string_type{ TETENGO2_TEXT("local_terminal") }, true));
                }

                BOOST_AUTO_TEST_CASE(principal_terminal_station)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_color_set_type font_color_set = make_font_color_set1();

                    BOOST_CHECK(
                        font_color_set.principal_terminal_station() ==
                        make_font_color(string_type{ TETENGO2_TEXT("principal_terminal") }, true));
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
