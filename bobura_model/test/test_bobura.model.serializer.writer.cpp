/*! \file
    \brief Test of class bobura::model::serializer::writer.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <ostream>
#include <sstream>

#include <boost/core/ignore_unused.hpp>
#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/writer.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using timetable_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type;

    using output_stream_type =
        std::basic_ostream<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_string>::type::value_type
        >;

    using writer_type =
        bobura::model::serializer::writer<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::difference>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type,
            output_stream_type,
            boost::mpl::at<
                test_bobura::model::model_type_list, test_bobura::model::type::model::operating_distance
            >::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::speed>::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::font>::type
        >;

    class concrete_writer : public writer_type
    {
    public:
        virtual ~concrete_writer()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        virtual boost::filesystem::path extension_impl()
        const override
        {
            return boost::filesystem::path{ TETENGO2_TEXT("hoge") };
        }

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        override
        {
            boost::ignore_unused(timetable, output_stream);
        }


    };

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_writer writer{};
    }

    BOOST_AUTO_TEST_CASE(extension)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_writer writer{};

        BOOST_CHECK(writer.extension() == boost::filesystem::path{ TETENGO2_TEXT("hoge") });
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_writer writer{};

        BOOST_CHECK(writer.selects(boost::filesystem::path{ TETENGO2_TEXT("hoge") }));
        BOOST_CHECK(!writer.selects(boost::filesystem::path{ TETENGO2_TEXT("fuga") }));
        BOOST_CHECK(!writer.selects(boost::filesystem::path{}));
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        concrete_writer writer{};
        const timetable_type timetable{};
        std::ostringstream stream{};
        writer.write(timetable, stream);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
