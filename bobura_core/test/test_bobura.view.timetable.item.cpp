/*! \file
    \brief Test of class bobura::view::timetable::item.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

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

    using position_unit_type = position_type::unit_type;

    using dimension_type = canvas_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

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

        void call_set_position(position_type position)
        {
            set_position(std::move(position));
        }

        void call_set_dimension(dimension_type dimension)
        {
            set_dimension(std::move(dimension));
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

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_item item{};

            item.position();
        }
        {
            concrete_item item{};

            item.position();
        }
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_item item{};

            item.dimension();
        }
        {
            concrete_item item{};

            item.dimension();
        }
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

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        concrete_item item{};

        const position_type position{ position_unit_type{ 42 }, position_unit_type{ 24 } };
        item.call_set_position(position);

        BOOST_CHECK(item.position() == position);
    }

    BOOST_AUTO_TEST_CASE(set_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_item item{};

        const dimension_type dimension{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } };
        item.call_set_dimension(dimension);

        BOOST_CHECK(item.dimension() == dimension);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
