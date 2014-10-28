/*! \file
    \brief Test of class bobura::model::serializer::reader_selector.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/reader_selector.h>
#include <bobura/model/timetable.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using size_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type;

    using difference_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::difference>::type;

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using operating_distance_type =
        boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::operating_distance>::type;

    using speed_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::speed>::type;

    using font_type = boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::font>::type;

    using timetable_type =
        bobura::model::timetable<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<
            std::istreambuf_iterator<
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_string>::type::value_type
            >
        >;

    using reader_selector_type =
        bobura::model::serializer::reader_selector<
            size_type,
            difference_type,
            string_type,
            input_stream_iterator_type,
            operating_distance_type,
            speed_type,
            font_type

        >;

    using reader_type = reader_selector_type::base_type;

    using error_type = reader_type::error_type;

    class concrete_reader : public reader_type
    {
    public:
        concrete_reader(string_type line_name)
        :
        reader_type(),
        m_line_name(std::move(line_name))
        {}

        virtual ~concrete_reader()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        const string_type m_line_name;

        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            return string_type{ first, last } == m_line_name;
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            boost::ignore_unused(first, last, error);

            auto p_timetable = tetengo2::stdalt::make_unique<timetable_type>();

            p_timetable->set_line_name(m_line_name);

            return std::move(p_timetable);
        }


    };


    // functions

    std::vector<std::unique_ptr<reader_type>> create_concrete_readers()
    {
        std::vector<std::unique_ptr<reader_type>> readers{};

        readers.push_back(tetengo2::stdalt::make_unique<concrete_reader>(string_type{ TETENGO2_TEXT("hoge") }));
        readers.push_back(tetengo2::stdalt::make_unique<concrete_reader>(string_type{ TETENGO2_TEXT("fuga") }));

        return std::move(readers);
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader_selector)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto concrete_readers = create_concrete_readers();
            const reader_selector_type reader_selector{ std::move(concrete_readers) };
        }
        {
            std::vector<std::unique_ptr<reader_type>> concrete_readers{};
            BOOST_CHECK_THROW(reader_selector_type{ std::move(concrete_readers) }, std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        auto concrete_readers = create_concrete_readers();
        reader_selector_type reader_selector{ std::move(concrete_readers) };

        std::istringstream input_stream{ "hoge" };
        BOOST_CHECK_THROW(
            reader_selector.selects(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
            ),
            std::logic_error
        );
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto concrete_readers = create_concrete_readers();
            reader_selector_type reader_selector{ std::move(concrete_readers) };

            std::istringstream input_stream{ "hoge" };
            auto error = error_type::none;
            const auto p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            auto concrete_readers = create_concrete_readers();
            reader_selector_type reader_selector{ std::move(concrete_readers) };

            std::istringstream input_stream{ "fuga" };
            auto error = error_type::none;
            const auto p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(p_timetable->line_name() == string_type{ TETENGO2_TEXT("fuga") });
        }
        {
            auto concrete_readers = create_concrete_readers();
            reader_selector_type reader_selector{ std::move(concrete_readers) };

            std::istringstream input_stream{ "piyo" };
            auto error = error_type::none;
            const auto p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::unsupported);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
