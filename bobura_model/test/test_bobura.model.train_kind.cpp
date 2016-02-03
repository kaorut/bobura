/*! \file
    \brief Test of class bobura::model::train_kind.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/train_kind.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using font_type = ui_type_list_type::font_type;

    using color_type = ui_type_list_type::color_type;

    using train_kind_type = bobura::model::train_kind<string_type, font_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train_kind)
    // test cases

    BOOST_AUTO_TEST_CASE(default_)
    {
        BOOST_TEST_PASSPOINT();

        train_kind_type::default_();
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_kind_type kind1{
                string_type{ TETENGO2_TEXT("hoge") },
                string_type{ TETENGO2_TEXT("fuga") },
                font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
                color_type{ 0, 128, 255 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid,
                font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
                color_type{ 0, 255, 128 }
            };
            const train_kind_type kind2{
                string_type{ TETENGO2_TEXT("hoge") },
                string_type{ TETENGO2_TEXT("fuga") },
                font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
                color_type{ 0, 128, 255 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid,
                font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
                color_type{ 0, 255, 128 }
            };

            BOOST_CHECK(kind1 == kind2);
        }
        {
            const train_kind_type kind1{
                string_type{ TETENGO2_TEXT("hoge") },
                string_type{ TETENGO2_TEXT("fuga") },
                font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
                color_type{ 0, 128, 255 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid,
                font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
                color_type{ 0, 255, 128 }
            };
            const train_kind_type kind2{
                string_type{ TETENGO2_TEXT("foo") },
                string_type{ TETENGO2_TEXT("bar") },
                font_type{ string_type{ TETENGO2_TEXT("foofont") }, 42, false, true, false, true },
                color_type{ 255, 128, 0 },
                train_kind_type::weight_type::bold,
                train_kind_type::line_style_type::dashed,
                font_type{ string_type{ TETENGO2_TEXT("barfont") }, 42, false, true, false, true },
                color_type{ 128, 255, 0 }
            };

            BOOST_CHECK(kind1 != kind2);
        }
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK(kind.name() == string_type{ TETENGO2_TEXT("hoge") });
    }

    BOOST_AUTO_TEST_CASE(abbreviation)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK(kind.abbreviation() == string_type{ TETENGO2_TEXT("fuga") });
    }

    BOOST_AUTO_TEST_CASE(diagram_font)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK((
            kind.diagram_font() == font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true }
        ));
    }

    BOOST_AUTO_TEST_CASE(diagram_color)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK((kind.diagram_color() == color_type{ 0, 128, 255 }));
    }

    BOOST_AUTO_TEST_CASE(diagram_line_weight)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK(kind.diagram_line_weight() == train_kind_type::weight_type::normal);
    }

    BOOST_AUTO_TEST_CASE(diagram_line_style)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK(kind.diagram_line_style() == train_kind_type::line_style_type::solid);
    }

    BOOST_AUTO_TEST_CASE(timetable_font)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK((
            kind.timetable_font() ==
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true }
        ));
    }

    BOOST_AUTO_TEST_CASE(timetable_color)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            font_type{ string_type{ TETENGO2_TEXT("hogefont") }, 42, false, true, false, true },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid,
            font_type{ string_type{ TETENGO2_TEXT("fugafont") }, 42, false, true, false, true },
            color_type{ 0, 255, 128 }
        };

        BOOST_CHECK((kind.timetable_color() == color_type{ 0, 255, 128 }));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
