/*! \file
    \brief Test of class bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using reader_type =
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::reader
        >::type;

    using error_type = reader_type::error_type;

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using timetable_type =
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type;

    using bzip2_reader_type =
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::bzip2_reader
        >::type;

    class concrete_reader : public reader_type
    {
    public:
        virtual ~concrete_reader()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            tetengo2::suppress_unused_variable_warning(first, last);

            return true;
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            tetengo2::suppress_unused_variable_warning(first, last, error);

            return tetengo2::stdalt::make_unique<timetable_type>();
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(bzip2_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
        const bzip2_reader_type bzip2_reader{ std::move(p_reader) };
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
            bzip2_reader_type bzip2_reader{ std::move(p_reader) };

            std::istringstream input_stream{ "BZ" };
            BOOST_CHECK(
                bzip2_reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
            bzip2_reader_type bzip2_reader{ std::move(p_reader) };

            std::istringstream input_stream{ "AZ" };
            BOOST_CHECK(
                !bzip2_reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
        bzip2_reader_type bzip2_reader{ std::move(p_reader) };

        std::istringstream input_stream{ "BZ" };
        auto error = error_type::none;
        const auto p_timetable =
            bzip2_reader.read(
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
