/*! \file
    \brief Test of class bobura::message::font_color_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>
#include <vector>

#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/message/font_color_dialog.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using common_dialog_type_list_type = bobura::type_list::common_dialog<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using string_type = common_type_list_type::string_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using window_type = ui_type_list_type::window_type;

    using dialog_type = ui_type_list_type::dialog_type;

    class concrete_dialog : public dialog_type
    {
    public:
        explicit concrete_dialog(window_type::base_type& parent) : dialog_type{ parent } {}
    };

    using list_box_type = ui_type_list_type::list_box_type;

    using dimension_type = window_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using font_type = canvas_type::font_type;

    using color_type = canvas_type::color_type;

    using font_dialog_type = common_dialog_type_list_type::font_type;

    using color_dialog_type = common_dialog_type_list_type::color_type;

    class font_color_type
    {
    public:
        // constructors and destructors

        font_color_type() : m_diagram_font{}, m_diagram_color{}, m_timetable_font{}, m_timetable_color{} {}

        font_color_type(
            boost::optional<font_type>  diagram_font,
            boost::optional<color_type> diagram_color,
            boost::optional<font_type>  timetable_font,
            boost::optional<color_type> timetable_color)
        : m_diagram_font{ diagram_font }, m_diagram_color{ diagram_color }, m_timetable_font{ timetable_font },
          m_timetable_color{ timetable_color }
        {}


        // functions

        const boost::optional<font_type>& diagram_font() const
        {
            return m_diagram_font;
        }

        void set_diagram_font(boost::optional<font_type> diagram_font)
        {
            m_diagram_font = std::move(diagram_font);
        }

        const boost::optional<color_type>& diagram_color() const
        {
            return m_diagram_color;
        }

        void set_diagram_color(boost::optional<color_type> diagram_color)
        {
            m_diagram_color = std::move(diagram_color);
        }

        const boost::optional<font_type>& timetable_font() const
        {
            return m_timetable_font;
        }

        void set_timetable_font(boost::optional<font_type> timetable_font)
        {
            m_timetable_font = std::move(timetable_font);
        }

        const boost::optional<color_type>& timetable_color() const
        {
            return m_timetable_color;
        }

        void set_timetable_color(boost::optional<color_type> timetable_color)
        {
            m_timetable_color = std::move(timetable_color);
        }


    private:
        // variables

        boost::optional<font_type> m_diagram_font;

        boost::optional<color_type> m_diagram_color;

        boost::optional<font_type> m_timetable_font;

        boost::optional<color_type> m_timetable_color;
    };


    // functions

    font_color_type make_font_color(const bool has_font, const bool has_color)
    {
        const auto font = boost::make_optional(
            has_font, font_type{ string_type{ TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false });
        const auto color = boost::make_optional(has_color, color_type{ 12, 34, 56 });
        return font_color_type{ font, color, font, color };
    }


    void update() {}
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
                    window_type                parent{};
                    list_box_type              list_box{ parent, list_box_type::scroll_bar_style_type::none };
                    const bobura::message::font_color_dialog::
                        category_list_box_selection_changed<size_type, list_box_type>
                            observer(current_category_index, list_box, update);
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    boost::optional<size_type> current_category_index{};
                    window_type                parent{};
                    list_box_type              list_box{ parent, list_box_type::scroll_bar_style_type::none };
                    const bobura::message::font_color_dialog::
                        category_list_box_selection_changed<size_type, list_box_type>
                            observer(current_category_index, list_box, update);

                    observer();
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(sample_picture_box_paint)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type         message_catalog{};
                    const bobura::message::font_color_dialog::
                        sample_picture_box_paint<size_type, canvas_type, font_color_type, message_catalog_type>
                            observer{ font_color_list,
                                      boost::make_optional<size_type>(1),
                                      dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                                      message_catalog };
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    const std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type         message_catalog{};
                    const bobura::message::font_color_dialog::
                        sample_picture_box_paint<size_type, canvas_type, font_color_type, message_catalog_type>
                            observer{ font_color_list,
                                      boost::make_optional<size_type>(1),
                                      dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } },
                                      message_catalog };

                    window_type window{};
                    const auto  p_canvas = window.create_canvas();
                    observer(*p_canvas);
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(diagram_font_button_mouse_clicked)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    const bobura::message::font_color_dialog::diagram_font_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        font_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };
                }

#if !( \
    BOOST_OS_LINUX && \
        (BOOST_COMP_CLANG >= BOOST_VERSION_NUMBER(5, 0, 0) && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(5, 1, 0)) || \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(6, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(6, 4, 0))\
)
                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    bobura::message::font_color_dialog::diagram_font_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        font_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };

                    observer();
                }
#endif


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(diagram_color_button_mouse_clicked)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    const bobura::message::font_color_dialog::diagram_color_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        color_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    bobura::message::font_color_dialog::diagram_color_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        color_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };

                    observer();
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(timetable_font_button_mouse_clicked)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    const bobura::message::font_color_dialog::timetable_font_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        font_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };
                }

#if !( \
    BOOST_OS_LINUX && \
    ((BOOST_COMP_CLANG >= BOOST_VERSION_NUMBER(5, 0, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 1, 0)) || \
     (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(6, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(6, 4, 0)))\
)
                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    bobura::message::font_color_dialog::timetable_font_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        font_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };

                    observer();
                }
#endif


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(timetable_color_button_mouse_clicked)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    const bobura::message::font_color_dialog::timetable_color_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        color_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                  parent{};
                    concrete_dialog              dialog{ parent };
                    std::vector<font_color_type> font_color_list{ 2, make_font_color(true, true) };
                    const message_catalog_type   message_catalog{};
                    bobura::message::font_color_dialog::timetable_color_button_mouse_clicked<
                        size_type,
                        dialog_type,
                        color_dialog_type,
                        canvas_type,
                        font_color_type,
                        message_catalog_type>
                        observer{
                            dialog, font_color_list, boost::make_optional<size_type>(1), update, message_catalog
                        };

                    observer();
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(ok_button_mouse_clicked)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                                                                    parent{};
                    concrete_dialog                                                                dialog{ parent };
                    const bobura::message::font_color_dialog::ok_button_mouse_clicked<dialog_type> observer{ dialog };
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                                                                    parent{};
                    concrete_dialog                                                                dialog{ parent };
                    const bobura::message::font_color_dialog::ok_button_mouse_clicked<dialog_type> observer{ dialog };

                    observer();
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(cancel_button_mouse_clicked)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                                                                        parent{};
                    concrete_dialog                                                                    dialog{ parent };
                    const bobura::message::font_color_dialog::cancel_button_mouse_clicked<dialog_type> observer{
                        dialog
                    };
                }

                BOOST_AUTO_TEST_CASE(operator_paren)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type                                                                        parent{};
                    concrete_dialog                                                                    dialog{ parent };
                    const bobura::message::font_color_dialog::cancel_button_mouse_clicked<dialog_type> observer{
                        dialog
                    };

                    observer();
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
