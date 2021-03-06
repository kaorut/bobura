/*! \file
    \brief Test of class bobura::model::serializer::reader.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <string>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/preprocessor.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/reader.h>
#include <bobura/model/timetable.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using timetable_type = bobura::model::timetable;

    using input_stream_iterator_type = common_type_list_type::input_stream_iterator_type;

    using reader_type = bobura::model::serializer::reader<
        size_type,
        difference_type,
        string_type,
        input_stream_iterator_type,
        operating_distance_type,
        speed_type,
        font_type>;

    using error_type = reader_type::error_type;

    class concrete_reader : public reader_type
    {
    public:
        virtual ~concrete_reader() = default;


    private:
        virtual bool selects_impl(const iterator first, const iterator last) override
        {
            return string_type{ first, last } == string_type{ TETENGO2_TEXT("hoge") };
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const iterator first,
            TETENGO2_STDALT_MAYBE_UNUSED const iterator last,
            TETENGO2_STDALT_MAYBE_UNUSED error_type& error) override
        {
            return std::make_unique<timetable_type>();
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

                BOOST_AUTO_TEST_CASE(selects)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_reader reader{};

                    {
                        std::istringstream input_stream{ "hoge" };
                        const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)));
                        const auto last = tetengo2::iterator::make_observable_forward_iterator(
                            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()));
                        BOOST_TEST(reader.selects(first, last));
                    }
                    {
                        std::istringstream input_stream{ "fuga" };
                        const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)));
                        const auto last = tetengo2::iterator::make_observable_forward_iterator(
                            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()));
                        BOOST_TEST(!reader.selects(first, last));
                    }
                }

                BOOST_AUTO_TEST_CASE(read)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_reader    reader{};
                    std::istringstream input_stream{ "hoge" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()));
                    auto       error = error_type::none;
                    const auto p_timetable = reader.read(first, last, error);

                    BOOST_TEST_REQUIRE(p_timetable.get());
                    BOOST_CHECK(error == error_type::none);
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
