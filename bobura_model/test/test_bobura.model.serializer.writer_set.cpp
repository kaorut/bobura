/*! \file
    \brief Test of class bobura::model::serializer::writer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <ostream>

#include <boost/test/unit_test.hpp>

#include <bobura/model/serializer/writer_set.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common<detail_type_list_type>;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using output_stream_type = std::basic_ostream<common_type_list_type::io_string_type::value_type>;

    using writer_set_type =
        bobura::model::serializer::writer_set<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            common_type_list_type::string_type,
            output_stream_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::font_type,
            common_type_list_type::io_encoder_type
        >;

}


#if 0 // until writer_set implementation is moved to .cpp.
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
#endif
