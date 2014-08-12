/*! \file
    \brief Test of class bobura::model::serializer::reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using timetable_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type;

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<
            std::istreambuf_iterator<
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_string>::type::value_type
            >
        >;

    using reader_type =
        bobura::model::serializer::reader<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::difference>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type,
            input_stream_iterator_type,
            boost::mpl::at<
                test_bobura::model::model_type_list, test_bobura::model::type::model::operating_distance
            >::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::speed>::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::font>::type
        >;

    using error_type = reader_type::error_type;

    class concrete_reader : public reader_type
    {
    public:
        virtual ~concrete_reader()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            boost::ignore_unused(first, last);

            return string_type{ first, last } == string_type{ TETENGO2_TEXT("hoge") };
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            boost::ignore_unused(first, last, error);

            return tetengo2::stdalt::make_unique<timetable_type>();
        }


    };

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_reader reader{};
    }

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        concrete_reader reader{};

        {
            std::istringstream input_stream{ "hoge" };
            BOOST_CHECK(
                reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            std::istringstream input_stream{ "fuga" };
            BOOST_CHECK(
                !reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        concrete_reader reader{};
        std::istringstream input_stream{ "hoge" };
        auto error = error_type::none;
        const auto p_timetable =
            reader.read(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                error
            );

        BOOST_REQUIRE(p_timetable);
        BOOST_CHECK(error == error_type::none);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
