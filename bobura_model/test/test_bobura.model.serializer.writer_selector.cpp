/*! \file
    \brief Test of class bobura::model::serializer::writer_selector.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/writer.h>
#include <bobura/model/serializer/writer_selector.h>
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

    using path_type = tetengo2::stdalt::filesystem::path;

    using path_string_type = path_type::string_type;

    using output_stream_type = common_type_list_type::output_stream_type;

    using writer_selector_type = bobura::model::serializer::writer_selector<
        size_type,
        difference_type,
        string_type,
        output_stream_type,
        operating_distance_type,
        speed_type,
        font_type>;

    using writer_type = writer_selector_type::base_type;

    class concrete_writer : public writer_type
    {
    public:
        using output_string_type = std::basic_string<output_stream_type::char_type>;

        explicit concrete_writer(path_type extension) : writer_type{}, m_extension{ std::move(extension) } {}

        virtual ~concrete_writer() = default;


    private:
        const path_type m_extension;

        virtual path_type extension_impl() const override
        {
            return m_extension;
        }

        virtual void write_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const timetable_type& timetable,
            output_stream_type&                                output_stream) override
        {
            output_stream << m_extension.string();
        }
    };


    // functions

    std::vector<std::unique_ptr<writer_type>> create_concrete_writers()
    {
        std::vector<std::unique_ptr<writer_type>> writers{};

        writers.push_back(std::make_unique<concrete_writer>(path_type{ path_string_type{ TETENGO2_TEXT(".hoge") } }));
        writers.push_back(std::make_unique<concrete_writer>(path_type{ path_string_type{ TETENGO2_TEXT(".fuga") } }));

        return writers;
    }
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(model)
        BOOST_AUTO_TEST_SUITE(serializer)
            BOOST_AUTO_TEST_SUITE(writer_selector)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        auto                       concrete_writers = create_concrete_writers();
                        const writer_selector_type writer_selector{ std::move(concrete_writers), path_type{} };
                    }
                    {
                        BOOST_CHECK_THROW(
                            writer_selector_type(std::vector<std::unique_ptr<writer_type>>{}, path_type{}),
                            std::invalid_argument);
                    }
                }

                BOOST_AUTO_TEST_CASE(extension)
                {
                    BOOST_TEST_PASSPOINT();

                    auto                       concrete_writers = create_concrete_writers();
                    const writer_selector_type writer_selector{ std::move(concrete_writers), path_type{} };

                    BOOST_CHECK_THROW(writer_selector.extension(), std::logic_error);
                }

                BOOST_AUTO_TEST_CASE(selects)
                {
                    BOOST_TEST_PASSPOINT();

                    auto                       concrete_writers = create_concrete_writers();
                    const writer_selector_type writer_selector{ std::move(concrete_writers), path_type{} };

                    BOOST_TEST(writer_selector.selects(path_type{ path_string_type{ TETENGO2_TEXT("piyo.hoge") } }));
                    BOOST_TEST(!writer_selector.selects(path_type{ path_string_type{ TETENGO2_TEXT("piyo.foo") } }));
                    BOOST_TEST(!writer_selector.selects(path_type{}));
                }

                BOOST_AUTO_TEST_CASE(write)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        auto                 concrete_writers = create_concrete_writers();
                        writer_selector_type writer_selector{
                            std::move(concrete_writers), path_type{ path_string_type{ TETENGO2_TEXT("piyo.hoge") } }
                        };
                        const timetable_type timetable{};
                        std::ostringstream   stream{};
                        writer_selector.write(timetable, stream);

                        BOOST_CHECK(stream.str() == std::string{ ".hoge" });
                    }
                    {
                        auto                 concrete_writers = create_concrete_writers();
                        writer_selector_type writer_selector{
                            std::move(concrete_writers), path_type{ path_string_type{ TETENGO2_TEXT("piyo.fuga") } }
                        };
                        const timetable_type timetable{};
                        std::ostringstream   stream{};
                        writer_selector.write(timetable, stream);

                        BOOST_CHECK(stream.str() == std::string{ ".fuga" });
                    }
                    {
                        auto                 concrete_writers = create_concrete_writers();
                        writer_selector_type writer_selector{
                            std::move(concrete_writers), path_type{ path_string_type{ TETENGO2_TEXT("piyo.foo") } }
                        };
                        const timetable_type timetable{};
                        std::ostringstream   stream{};

                        BOOST_CHECK_THROW(writer_selector.write(timetable, stream), std::logic_error);
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
