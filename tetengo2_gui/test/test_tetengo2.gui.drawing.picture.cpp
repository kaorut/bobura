/*! \file
    \brief Test of class tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <stdexcept>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type dimension_type;

    typedef int canvas_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture>::type
        picture_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(picture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const canvas_type canvas(42);
            const picture_type picture(dimension_type(123, 456), canvas);
        }
        {
            const canvas_type canvas(42);
            picture_type::details_ptr_type p_details(
                tetengo2::detail::stub::drawing::create_picture(dimension_type(123, 456), canvas)
            );
            const picture_type picture2(std::move(p_details));
        }
        {
            picture_type::details_ptr_type p_details;

            BOOST_CHECK_THROW(picture_type picture(std::move(p_details)), std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const canvas_type canvas(42);
        const picture_type picture(dimension_type(123, 456), canvas);

        BOOST_CHECK(picture.dimension() == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const canvas_type canvas(42);
            const picture_type picture(dimension_type(123, 456), canvas);

            picture.details();
        }
        {
            const canvas_type canvas(42);
            picture_type picture(dimension_type(123, 456), canvas);

            picture.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
