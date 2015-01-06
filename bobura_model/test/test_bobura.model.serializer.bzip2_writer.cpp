/*! \file
    \brief Test of class bobura::model::serializer::bzip2_writer.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <ostream>
#include <sstream>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/bzip2_writer.h>
#include <bobura/model/timetable.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common<detail_type_list_type>;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using timetable_type =
        bobura::model::timetable<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using output_stream_type = std::basic_ostream<common_type_list_type::io_string_type::value_type>;

    using bzip2_writer_type =
        bobura::model::serializer::bzip2_writer<
            size_type,
            difference_type,
            string_type,
            output_stream_type,
            operating_distance_type,
            speed_type,
            font_type
        >;

    using writer_type = bzip2_writer_type::base_type;

    class concrete_writer : public writer_type
    {
    public:
        virtual ~concrete_writer()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        virtual boost::filesystem::path extension_impl()
        const override
        {
            return boost::filesystem::path{ TETENGO2_TEXT("hoge.ext") };
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
BOOST_AUTO_TEST_SUITE(bzip2_writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        auto p_writer = tetengo2::stdalt::make_unique<concrete_writer>();
        const bzip2_writer_type bzip2_writer{ std::move(p_writer) };
    }

    BOOST_AUTO_TEST_CASE(extension)
    {
        BOOST_TEST_PASSPOINT();

        auto p_writer = tetengo2::stdalt::make_unique<concrete_writer>();
        const bzip2_writer_type bzip2_writer{ std::move(p_writer) };

        BOOST_CHECK(bzip2_writer.extension() == boost::filesystem::path{ TETENGO2_TEXT("hoge.ext_bz2") });
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        auto p_writer = tetengo2::stdalt::make_unique<concrete_writer>();
        const bzip2_writer_type bzip2_writer{ std::move(p_writer) };

        BOOST_CHECK(bzip2_writer.selects(boost::filesystem::path{ TETENGO2_TEXT("hoge.ext_bz2") }));
        BOOST_CHECK(!bzip2_writer.selects(boost::filesystem::path{ TETENGO2_TEXT("hoge.ext") }));
        BOOST_CHECK(!bzip2_writer.selects(boost::filesystem::path{}));
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        auto p_writer = tetengo2::stdalt::make_unique<concrete_writer>();
        bzip2_writer_type bzip2_writer{ std::move(p_writer) };
        const timetable_type timetable{};
        std::ostringstream stream{};
        bzip2_writer.write(timetable, stream);

        const auto result = stream.str();
        BOOST_CHECK(result.substr(0, 2) == "BZ");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
