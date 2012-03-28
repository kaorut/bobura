/*! \file
    \brief Test of class tetengo2::gui::widget::label.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::window
        >::type
        window_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list,
            test_tetengo2::gui::type::drawing::dimension
        >::type
        dimension_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::label
        >::type
        label_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(label)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const label_type label(parent);
    }

    BOOST_AUTO_TEST_CASE(fit_to_content)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        label_type label(parent);
        label.set_text("Tetengo");

        label.fit_to_content();

        const dimension_type dimension = label.dimension();

        const dimension_type answer_dimension =
            label.create_canvas()->calc_text_dimension("Tetengo");
        BOOST_CHECK(dimension == answer_dimension);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
