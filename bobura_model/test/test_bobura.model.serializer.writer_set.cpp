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

    using output_stream_type =
        std::basic_ostream<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_string>::type::value_type
        >;

    using writer_set_type =
        bobura::model::serializer::writer_set<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::difference>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type,
            output_stream_type,
            boost::mpl::at<
                test_bobura::model::model_type_list, test_bobura::model::type::model::operating_distance
            >::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::speed>::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::font>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_encoder>::type
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
