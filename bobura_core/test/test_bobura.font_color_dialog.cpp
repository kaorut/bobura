/*! \file
    \brief Test of class bobura::font_color_dialog.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <bobura/font_color_dialog.h>
#include <bobura/type_list.h>


namespace
{
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

    using font_color_dialog_type =
        bobura::font_color_dialog<
            traits_type_list_type::dialog_type,
            common_type_list_type::size_type,
            font_type,
            ui_type_list_type::point_unit_size_type,
            color_type,
            ui_type_list_type::canvas_type,
            common_dialog_type_list_type::font_type,
            common_dialog_type_list_type::color_type
        >;

    using font_color_type = font_color_dialog_type::font_color_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(font_color_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.background(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_background(color_type{ 12, 34, 56 });

        const color_type expected{ 12, 34, 56 };
        BOOST_CHECK(font_color_dialog.background() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(company_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.company_name(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_company_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_company_name(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.company_name() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.line_name(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_line_name(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.line_name() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.note(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_note)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_note(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.note() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(time_line)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.time_line(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_time_line)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_time_line(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.time_line() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(local_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.local_station(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_local_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_local_station(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.local_station() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(principal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.principal_station(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_principal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_principal_station(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.principal_station() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(local_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.local_terminal_station(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_local_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_local_terminal_station(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.local_terminal_station() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(principal_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.principal_terminal_station(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_principal_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_principal_terminal_station(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false },
            color_type{ 12, 34, 56 }
        );

        const font_type expected_font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type expected_color{ 12, 34, 56 };
        const font_color_type expected{ expected_font, expected_color };
        BOOST_CHECK(font_color_dialog.principal_terminal_station() == expected);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(train_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const font_color_dialog_type font_color_dialog{ parent, message_catalog };

        BOOST_CHECK_THROW(font_color_dialog.train_name(), std::logic_error);
    }
#endif

    BOOST_AUTO_TEST_CASE(set_train_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        font_color_dialog_type font_color_dialog{ parent, message_catalog };

        font_color_dialog.set_train_name(
            font_type{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false }
        );

        const font_type expected{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        BOOST_CHECK(font_color_dialog.train_name() == expected);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
