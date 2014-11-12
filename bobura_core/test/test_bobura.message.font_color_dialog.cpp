/*! \file
    \brief Test of class bobura::message::font_color_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.h>

#include <bobura/message/font_color_dialog.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list_temp::detail_for_test;

    using common_type_list_type = bobura::type_list_temp::common;

    using locale_type_list_type = bobura::type_list_temp::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list_temp::ui<detail_type_list_type>;

    using common_dialog_type_list_type = bobura::type_list_temp::common_dialog<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using window_type = ui_type_list_type::window_type;

    using dialog_type = ui_type_list_type::dialog_type;

    class concrete_dialog : public dialog_type
    {
    public:
        explicit concrete_dialog(window_type::base_type& parent)
        :
        dialog_type(parent)
        {}

    };

    using list_box_type = ui_type_list_type::list_box_type;

    using dimension_type = window_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using font_dialog_type = common_dialog_type_list_type::font_type;

    using color_dialog_type = common_dialog_type_list_type::color_type;


    // functions

    void update()
    {}


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(font_color_dialog)
BOOST_AUTO_TEST_SUITE(category_list_box_selection_changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        boost::optional<size_type> current_category_index{};
        window_type parent{};
        list_box_type list_box{ parent, list_box_type::scroll_bar_style_type::none };
        const bobura::message::font_color_dialog::category_list_box_selection_changed<size_type, list_box_type>
        observer(current_category_index, list_box, update);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        boost::optional<size_type> current_category_index{};
        window_type parent{};
        list_box_type list_box{ parent, list_box_type::scroll_bar_style_type::none };
        const bobura::message::font_color_dialog::category_list_box_selection_changed<size_type, list_box_type>
        observer(current_category_index, list_box, update);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(sample_picture_box_paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::pair<boost::optional<font_type>, boost::optional<color_type>>> font_color_list(
            2,
            std::pair<boost::optional<font_type>, boost::optional<color_type>>(
                boost::make_optional<font_type>(font_type::dialog_font()),
                boost::make_optional<color_type>(color_type{ 0x12, 0x34, 0x56 })
            )
        );
        const message_catalog_type message_catalog{};
        const bobura::message::font_color_dialog::sample_picture_box_paint<
            size_type, canvas_type, message_catalog_type
        > observer{
            font_color_list,
            boost::make_optional<size_type>(1),
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            message_catalog
        };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::pair<boost::optional<font_type>, boost::optional<color_type>>> font_color_list(
            2,
            std::pair<boost::optional<font_type>, boost::optional<color_type>>(
                boost::make_optional<font_type>(font_type::dialog_font()),
                boost::make_optional<color_type>(color_type{ 0x12, 0x34, 0x56 })
            )
        );
        const message_catalog_type message_catalog{};
        const bobura::message::font_color_dialog::sample_picture_box_paint<
            size_type, canvas_type, message_catalog_type
        > observer{
            font_color_list,
            boost::make_optional<size_type>(1), 
            dimension_type{ width_type{ 42 }, height_type{ 24 } },
            message_catalog
        };

        window_type window{};
        const auto p_canvas = window.create_canvas();
        observer(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(font_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        std::vector<std::pair<boost::optional<font_type>, boost::optional<color_type>>> font_color_list(
            2,
            std::pair<boost::optional<font_type>, boost::optional<color_type>>(
                boost::make_optional<font_type>(font_type::dialog_font()),
                boost::make_optional<color_type>(color_type{ 0x12, 0x34, 0x56 })
            )
        );
        const message_catalog_type message_catalog{};
        const bobura::message::font_color_dialog::font_button_mouse_clicked<
            size_type, dialog_type, font_dialog_type, canvas_type, message_catalog_type
        > observer{
            dialog,
            font_color_list,
            boost::make_optional<size_type>(1),
            update,
            message_catalog
        };
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 8, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 9, 0)) \
)
    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        std::vector<std::pair<boost::optional<font_type>, boost::optional<color_type>>> font_color_list(
            2,
            std::pair<boost::optional<font_type>, boost::optional<color_type>>(
                boost::make_optional<font_type>(font_type::dialog_font()),
                boost::make_optional<color_type>(color_type{ 0x12, 0x34, 0x56 })
            )
        );
        const message_catalog_type message_catalog{};
        const bobura::message::font_color_dialog::font_button_mouse_clicked<
            size_type, dialog_type, font_dialog_type, canvas_type, message_catalog_type
        > observer{
            dialog,
            font_color_list,
            boost::make_optional<size_type>(1),
            update,
            message_catalog
        };

        observer();
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(color_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        std::vector<std::pair<boost::optional<font_type>, boost::optional<color_type>>> font_color_list(
            2,
            std::pair<boost::optional<font_type>, boost::optional<color_type>>(
                boost::make_optional<font_type>(font_type::dialog_font()),
                boost::make_optional<color_type>(color_type{ 0x12, 0x34, 0x56 })
            )
        );
        const message_catalog_type message_catalog{};
        const bobura::message::font_color_dialog::color_button_mouse_clicked<
            size_type, dialog_type, color_dialog_type, canvas_type, message_catalog_type
        > observer{
            dialog,
            font_color_list,
            boost::make_optional<size_type>(1),
            update,
            message_catalog
        };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        std::vector<std::pair<boost::optional<font_type>, boost::optional<color_type>>> font_color_list(
            2,
            std::pair<boost::optional<font_type>, boost::optional<color_type>>(
                boost::make_optional<font_type>(font_type::dialog_font()),
                boost::make_optional<color_type>(color_type{ 0x12, 0x34, 0x56 })
            )
        );
        const message_catalog_type message_catalog{};
        const bobura::message::font_color_dialog::color_button_mouse_clicked<
            size_type, dialog_type, color_dialog_type, canvas_type, message_catalog_type
        > observer{
            dialog,
            font_color_list,
            boost::make_optional<size_type>(1),
            update,
            message_catalog
        };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(ok_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        const bobura::message::font_color_dialog::ok_button_mouse_clicked<dialog_type> observer{ dialog };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        const bobura::message::font_color_dialog::ok_button_mouse_clicked<dialog_type> observer{ dialog };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(cancel_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        const bobura::message::font_color_dialog::cancel_button_mouse_clicked<dialog_type> observer{ dialog };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog{ parent };
        const bobura::message::font_color_dialog::cancel_button_mouse_clicked<dialog_type> observer{ dialog };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
