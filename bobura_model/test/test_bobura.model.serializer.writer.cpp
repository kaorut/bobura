/*! \file
    \brief Test of class bobura::model::serializer::writer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/writer.h>
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

    using timetable_type = bobura::model::
        timetable<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

    using output_stream_type = common_type_list_type::output_stream_type;

    using writer_type = bobura::model::serializer::writer<
        size_type,
        difference_type,
        string_type,
        output_stream_type,
        operating_distance_type,
        speed_type,
        font_type>;

    class concrete_writer : public writer_type
    {
    public:
        virtual ~concrete_writer() = default;


    private:
        virtual boost::filesystem::path extension_impl() const override
        {
            return boost::filesystem::path{ TETENGO2_TEXT("hoge") };
        }

        virtual void write_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const timetable_type& timetable,
            TETENGO2_STDALT_MAYBE_UNUSED output_stream_type& output_stream) override
        {}
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

                    BOOST_TEST(writer.selects(boost::filesystem::path{ TETENGO2_TEXT("hoge") }));
                    BOOST_TEST(!writer.selects(boost::filesystem::path{ TETENGO2_TEXT("fuga") }));
                    BOOST_TEST(!writer.selects(boost::filesystem::path{}));
                }

                BOOST_AUTO_TEST_CASE(write)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_writer      writer{};
                    const timetable_type timetable{};
                    std::ostringstream   stream{};
                    writer.write(timetable, stream);
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
