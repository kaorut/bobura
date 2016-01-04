/*! \file
    \brief Test of class bobura::view::timetable::item.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <boost/test/unit_test.hpp>

#include <bobura/type_list.h>
#include <bobura/view/timetable/item.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using position_type = canvas_type::position_type;

    using traits_type = traits_type_list_type::timetable_view_type;

    using item_type = bobura::view::timetable::item<traits_type>;

    class concrete_item : public item_type
    {
    public:
        concrete_item()
        :
        item_type()
        {}

        concrete_item& operator=(concrete_item&& item)
        {
            item_type::operator=(std::move(item));
            return *this;
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(timetable)
BOOST_AUTO_TEST_SUITE(item)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_item item{};
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        concrete_item item1{};
        concrete_item item2{};

        item1 = std::move(item2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_item item{};

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        item.draw_on(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
