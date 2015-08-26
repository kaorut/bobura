/*! \file
    \brief Test of class bobura::train_kind_dialog.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/train_kind.h>
#include <bobura/train_kind_dialog.h>
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

    using size_type = common_type_list_type::size_type;

    using string_type = common_type_list_type::string_type;

    using font_type = ui_type_list_type::font_type;

    using color_type = ui_type_list_type::color_type;

    using window_type = ui_type_list_type::window_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using train_kind_type = bobura::model::train_kind<string_type>;

    using train_kind_dialog_type =
        bobura::train_kind_dialog<
            traits_type_list_type::dialog_type,
            size_type,
            string_type,
            font_type,
            color_type,
            ui_type_list_type::fast_canvas_type,
            common_dialog_type_list_type::color_type
        >;

    using info_set_type = train_kind_dialog_type::info_set_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(train_kind_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const font_type font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type background_color{ 12, 34, 56 };
        const message_catalog_type message_catalog{};
        const train_kind_dialog_type train_kind_dialog{ parent, font, background_color, message_catalog };
    }

    BOOST_AUTO_TEST_CASE(info_sets)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const font_type font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type background_color{ 12, 34, 56 };
        const message_catalog_type message_catalog{};
        const train_kind_dialog_type train_kind_dialog{ parent, font, background_color, message_catalog };

        BOOST_TEST(train_kind_dialog.info_sets().empty());
    }

    BOOST_AUTO_TEST_CASE(set_info_sets)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const font_type font{ string_type{TETENGO2_TEXT("Tetengo2 Font") }, 42, false, false, false, false };
        const color_type background_color{ 12, 34, 56 };
        const message_catalog_type message_catalog{};
        train_kind_dialog_type train_kind_dialog{ parent, font, background_color, message_catalog };

        std::vector<info_set_type> info_sets{
            info_set_type{
                boost::make_optional<size_type>(0),
                false,
                train_kind_type{
                    string_type{ TETENGO2_TEXT("name0") },
                    string_type{ TETENGO2_TEXT("abbreviation0") },
                    color_type{ 0, 10, 20 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            },
            info_set_type{
                boost::make_optional<size_type>(1),
                true,
                train_kind_type{
                    string_type{ TETENGO2_TEXT("name1") },
                    string_type{ TETENGO2_TEXT("abbreviation1") },
                    color_type{ 1, 11, 21 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::dashed
                }
            }
        };
        train_kind_dialog.set_info_sets(std::move(info_sets));

        const std::vector<info_set_type> expected{
            info_set_type{
                boost::make_optional<size_type>(0),
                false,
                train_kind_type{
                    string_type{ TETENGO2_TEXT("name0") },
                    string_type{ TETENGO2_TEXT("abbreviation0") },
                    color_type{ 0, 10, 20 },
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                }
            },
            info_set_type{
                boost::make_optional<size_type>(1),
                true,
                train_kind_type{
                    string_type{ TETENGO2_TEXT("name1") },
                    string_type{ TETENGO2_TEXT("abbreviation1") },
                    color_type{ 1, 11, 21 },
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::dashed
                }
            }
        };
        BOOST_TEST(train_kind_dialog.info_sets().size() == expected.size());
        BOOST_CHECK(train_kind_dialog.info_sets()[0].original_index() == expected[0].original_index());
        BOOST_TEST(train_kind_dialog.info_sets()[0].referred() == expected[0].referred());
        BOOST_CHECK(train_kind_dialog.info_sets()[0].train_kind() == expected[0].train_kind());
        BOOST_CHECK(train_kind_dialog.info_sets()[1].original_index() == expected[1].original_index());
        BOOST_TEST(train_kind_dialog.info_sets()[1].referred() == expected[1].referred());
        BOOST_CHECK(train_kind_dialog.info_sets()[1].train_kind() == expected[1].train_kind());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
