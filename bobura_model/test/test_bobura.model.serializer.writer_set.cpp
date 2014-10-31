/*! \file
    \brief Test of class bobura::model::serializer::writer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <ostream>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/model/serializer/writer_set.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::detail_type_list_for_test;

    using common_type_list_type = test_bobura::model::common_type_list<detail_type_list_type>;

    using ui_type_list_type = test_bobura::model::ui_type_list<detail_type_list_type>;

    using output_stream_type =
        std::basic_ostream<
            boost::mpl::at<common_type_list_type, test_bobura::model::type::io_string>::type::value_type
        >;

    using writer_set_type =
        bobura::model::serializer::writer_set<
            boost::mpl::at<common_type_list_type, test_bobura::model::type::size>::type,
            boost::mpl::at<common_type_list_type, test_bobura::model::type::difference>::type,
            boost::mpl::at<common_type_list_type, test_bobura::model::type::string>::type,
            output_stream_type,
            boost::mpl::at<common_type_list_type, test_bobura::model::type::operating_distance>::type,
            boost::mpl::at<common_type_list_type, test_bobura::model::type::speed>::type,
            boost::mpl::at<ui_type_list_type, test_bobura::model::type::ui::font>::type,
            boost::mpl::at<common_type_list_type, test_bobura::model::type::io_encoder>::type
        >;

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(create_writers)
    {
        BOOST_TEST_PASSPOINT();

        const auto p_writers = writer_set_type::create_writers();

        BOOST_CHECK(!p_writers.empty());
        BOOST_CHECK(p_writers[0]);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
