/*! \file
    \brief Test of class bobura::view::diagram::item.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/type_list.h>
#include <bobura/view/diagram/item.h>
#include <bobura/view/diagram/selection.h>


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

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using traits_type = traits_type_list_type::diagram_view_type;

    using selection_type = bobura::view::diagram::selection<traits_type>;

    using item_type = bobura::view::diagram::item<traits_type>;

    class concrete_item : public item_type
    {
    public:
        explicit concrete_item(selection_type& selection)
        :
        item_type(selection),
        m_selected(false)
        {}

        concrete_item& operator=(concrete_item&& item)
        {
            item_type::operator=(std::move(item));
            return *this;
        }


    private:
        bool m_selected;

        virtual bool selected_impl()
        const override
        {
            return m_selected;
        }

        virtual void select_impl(const bool switch_selection_style)
        override
        {
            boost::ignore_unused(switch_selection_style);

            m_selected = true;
        }

    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(item)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const concrete_item item{ selection };
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection1{};
        concrete_item item1{ selection1 };
        selection_type selection2{};
        concrete_item item2{ selection2 };

        item1 = std::move(item2);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const concrete_item item{ selection };

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();
        item.draw_on(*p_canvas);
    }

    BOOST_AUTO_TEST_CASE(p_item_by_position)
    {
        BOOST_TEST_PASSPOINT();

        {
            selection_type selection{};
            const concrete_item item{ selection };

            item.p_item_by_position(position_type{ left_type{ 42 }, top_type{ 24 } });
        }
        {
            selection_type selection{};
            concrete_item item{ selection };

            item.p_item_by_position(position_type{ left_type{ 42 }, top_type{ 24 } });
        }
    }

    BOOST_AUTO_TEST_CASE(get_selection)
    {
        BOOST_TEST_PASSPOINT();

        {
            selection_type selection{};
            const concrete_item item{ selection };

            BOOST_TEST(&item.get_selection() == &selection);
        }
        {
            selection_type selection{};
            concrete_item item{ selection };

            BOOST_TEST(&item.get_selection() == &selection);
        }
    }

    BOOST_AUTO_TEST_CASE(selected)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        const concrete_item item{ selection };

        BOOST_TEST(!item.selected());
    }

    BOOST_AUTO_TEST_CASE(select)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection{};
        concrete_item item{ selection };

        item.select(false);

        BOOST_TEST(item.selected());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
