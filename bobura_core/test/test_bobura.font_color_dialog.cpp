/*! \file
    \brief Test of class bobura::font_color_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/font_color_dialog.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using common_dialog_type_list_type = bobura::type_list::common_dialog<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using font_type = ui_type_list_type::font_type;

    using color_type = ui_type_list_type::color_type;

    using window_type = ui_type_list_type::window_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using font_color_dialog_type = bobura::font_color_dialog<
        traits_type_list_type::dialog_type,
        common_type_list_type::size_type,
        font_type,
        ui_type_list_type::point_dimension_unit_type,
        color_type,
        ui_type_list_type::canvas_type,
        common_dialog_type_list_type::font_type,
        common_dialog_type_list_type::color_type>;

    using font_color_type = font_color_dialog_type::font_color_type;


    // functions

    font_color_type make_font_color(const bool has_font, const bool has_color)
    {
        const auto font = boost::make_optional(
            has_font, font_type{ string_type{ TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false });
        const auto color = boost::make_optional(has_color, color_type{ 12, 34, 56 });
        return font_color_type{ font, color, font, color };
    }
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(font_color_dialog)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };
        }

        BOOST_AUTO_TEST_CASE(background)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.background();
        }

        BOOST_AUTO_TEST_CASE(set_background)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_background(make_font_color(false, true));

            BOOST_CHECK(font_color_dialog.background() == make_font_color(false, true));
        }

        BOOST_AUTO_TEST_CASE(general)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.general();
        }

        BOOST_AUTO_TEST_CASE(set_general)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_general(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.general() == make_font_color(true, true));
        }

        BOOST_AUTO_TEST_CASE(company_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.company_name();
        }

        BOOST_AUTO_TEST_CASE(set_company_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_company_name(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.company_name() == make_font_color(true, true));
        }

        BOOST_AUTO_TEST_CASE(line_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.line_name();
        }

        BOOST_AUTO_TEST_CASE(set_line_name)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_line_name(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.line_name() == make_font_color(true, true));
        }

        BOOST_AUTO_TEST_CASE(note)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.note();
        }

        BOOST_AUTO_TEST_CASE(set_note)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_note(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.note() == make_font_color(true, true));
        }

        BOOST_AUTO_TEST_CASE(local_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.local_station();
        }

        BOOST_AUTO_TEST_CASE(set_local_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_local_station(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.local_station() == make_font_color(true, true));
        }

        BOOST_AUTO_TEST_CASE(principal_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.principal_station();
        }

        BOOST_AUTO_TEST_CASE(set_principal_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_principal_station(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.principal_station() == make_font_color(true, true));
        }

        BOOST_AUTO_TEST_CASE(local_terminal_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.local_terminal_station();
        }

        BOOST_AUTO_TEST_CASE(set_local_terminal_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_local_terminal_station(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.local_terminal_station() == make_font_color(true, true));
        }

        BOOST_AUTO_TEST_CASE(principal_terminal_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                  parent{};
            const message_catalog_type   message_catalog{};
            const font_color_dialog_type font_color_dialog{ parent, message_catalog };

            font_color_dialog.principal_terminal_station();
        }

        BOOST_AUTO_TEST_CASE(set_principal_terminal_station)
        {
            BOOST_TEST_PASSPOINT();

            window_type                parent{};
            const message_catalog_type message_catalog{};
            font_color_dialog_type     font_color_dialog{ parent, message_catalog };

            font_color_dialog.set_principal_terminal_station(make_font_color(true, true));

            BOOST_CHECK(font_color_dialog.principal_terminal_station() == make_font_color(true, true));
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
