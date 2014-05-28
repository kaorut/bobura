/*! \file
    \brief Test of class bobura::model::serializer::reader_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using abstract_window_type =
        boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::abstract_window>::type;

    using message_catalog_type =
        boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::message_catalog>::type;

    using reader_type =
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::reader
        >::type;

    using reader_set_type =
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::reader_set
        >::type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader_set)
    // test cases

    BOOST_AUTO_TEST_CASE(create_readers)
    {
        BOOST_TEST_PASSPOINT();

        abstract_window_type parent;
        string_type file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type message_catalog;
        const auto p_readers = reader_set_type::create_readers(parent, std::move(file_name), message_catalog);

        BOOST_REQUIRE(!p_readers.empty());
        BOOST_CHECK(p_readers[0]);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
