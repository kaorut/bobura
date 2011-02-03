/*! \file
    \brief Test of class tetengo2::gui::drawing::font.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <cstddef>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.text.h"

#include "tetengo2.gui.drawing.font.h"


namespace
{
    // types

    typedef
        tetengo2::gui::drawing::font<
            std::string, std::size_t, tetengo2::detail::stub::drawing
        >
        font_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(font)
    // test cases

    BOOST_AUTO_TEST_CASE(dialog_font)
    {
        BOOST_TEST_PASSPOINT();

        const font_type& font = font_type::dialog_font();

        BOOST_CHECK(
            font ==
            font_type(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            )
        );
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const font_type font(
            TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
        );
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const font_type font1(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
            const font_type font2(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );

            BOOST_CHECK(font1 == font2);
        }
        {
            const font_type font1(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
            const font_type font2(
                TETENGO2_TEXT("TetengoFont2"), 12, false, false, false, false
            );

            BOOST_CHECK(font1 != font2);
        }
        {
            const font_type font1(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
            const font_type font2(
                TETENGO2_TEXT("TetengoFont"), 42, false, false, false, false
            );

            BOOST_CHECK(font1 != font2);
        }
        {
            const font_type font1(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
            const font_type font2(
                TETENGO2_TEXT("TetengoFont"), 12, true, false, false, false
            );

            BOOST_CHECK(font1 != font2);
        }
        {
            const font_type font1(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
            const font_type font2(
                TETENGO2_TEXT("TetengoFont"), 12, false, true, false, false
            );

            BOOST_CHECK(font1 != font2);
        }
        {
            const font_type font1(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
            const font_type font2(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, true, false
            );

            BOOST_CHECK(font1 != font2);
        }
        {
            const font_type font1(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
            const font_type font2(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, true
            );

            BOOST_CHECK(font1 != font2);
        }
    }

    BOOST_AUTO_TEST_CASE(family)
    {
        BOOST_TEST_PASSPOINT();

        const font_type font(
            TETENGO2_TEXT("TetengoFont"), 12, false, true, false, true
        );

        BOOST_CHECK(
            font.family() ==
            font_type::string_type(TETENGO2_TEXT("TetengoFont"))
        );
    }

    BOOST_AUTO_TEST_CASE(size)
    {
        BOOST_TEST_PASSPOINT();

        const font_type font(
            TETENGO2_TEXT("TetengoFont"), 12, false, true, false, true
        );

        BOOST_CHECK_EQUAL(font.size(), 12U);
    }

    BOOST_AUTO_TEST_CASE(bold)
    {
        BOOST_TEST_PASSPOINT();

        const font_type font(
            TETENGO2_TEXT("TetengoFont"), 12, false, true, false, true
        );

        BOOST_CHECK(!font.bold());
    }

    BOOST_AUTO_TEST_CASE(italic)
    {
        BOOST_TEST_PASSPOINT();

        const font_type font(
            TETENGO2_TEXT("TetengoFont"), 12, false, true, false, true
        );

        BOOST_CHECK(font.italic());
    }

    BOOST_AUTO_TEST_CASE(underline)
    {
        BOOST_TEST_PASSPOINT();

        const font_type font(
            TETENGO2_TEXT("TetengoFont"), 12, false, true, false, true
        );

        BOOST_CHECK(!font.underline());
    }

    BOOST_AUTO_TEST_CASE(strikeout)
    {
        BOOST_TEST_PASSPOINT();

        const font_type font(
            TETENGO2_TEXT("TetengoFont"), 12, false, true, false, true
        );

        BOOST_CHECK(font.strikeout());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
