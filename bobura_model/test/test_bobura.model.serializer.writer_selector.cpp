/*! \file
    \brief Test of class bobura::model::serializer::writer_selector.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/writer_selector.h>

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

    using writer_selector_type =
        bobura::model::serializer::writer_selector<
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

    using writer_type = writer_selector_type::base_type;

    class concrete_writer : public writer_type
    {
    public:
        using output_string_type = std::basic_string<output_stream_type::char_type>;

        explicit concrete_writer(boost::filesystem::path extension)
        :
        writer_type(),
        m_extension(std::move(extension))
        {}

        virtual ~concrete_writer()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        const boost::filesystem::path m_extension;

        virtual boost::filesystem::path extension_impl()
        const override
        {
            return m_extension;
        }

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        override
        {
            boost::ignore_unused(timetable);

            output_stream << m_extension.string();
        }


    };


    // functions

    std::vector<std::unique_ptr<writer_type>> create_concrete_writers()
    {
        std::vector<std::unique_ptr<writer_type>> writers{};

        writers.push_back(
            tetengo2::stdalt::make_unique<concrete_writer>(boost::filesystem::path{ TETENGO2_TEXT(".hoge") })
        );
        writers.push_back(
            tetengo2::stdalt::make_unique<concrete_writer>(boost::filesystem::path{ TETENGO2_TEXT(".fuga") })
        );

        return std::move(writers);
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
            auto concrete_writers = create_concrete_writers();
            const writer_selector_type writer_selector{ std::move(concrete_writers), boost::filesystem::path{} };
        }
        {
            BOOST_CHECK_THROW(
                writer_selector_type(std::vector<std::unique_ptr<writer_type>>{}, boost::filesystem::path{}),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(extension)
    {
        BOOST_TEST_PASSPOINT();

        auto concrete_writers = create_concrete_writers();
        const writer_selector_type writer_selector{ std::move(concrete_writers), boost::filesystem::path{} };

        BOOST_CHECK_THROW(writer_selector.extension(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        auto concrete_writers = create_concrete_writers();
        const writer_selector_type writer_selector{ std::move(concrete_writers), boost::filesystem::path{} };

        BOOST_CHECK(writer_selector.selects(boost::filesystem::path{ TETENGO2_TEXT("piyo.hoge") }));
        BOOST_CHECK(!writer_selector.selects(boost::filesystem::path{ TETENGO2_TEXT("piyo.foo") }));
        BOOST_CHECK(!writer_selector.selects(boost::filesystem::path{}));
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto concrete_writers = create_concrete_writers();
            writer_selector_type writer_selector{
                std::move(concrete_writers), boost::filesystem::path{ TETENGO2_TEXT("piyo.hoge") }
            };
            const timetable_type timetable{};
            std::ostringstream stream{};
            writer_selector.write(timetable, stream);

            BOOST_CHECK(stream.str() == std::string{ ".hoge" });
        }
        {
            auto concrete_writers = create_concrete_writers();
            writer_selector_type writer_selector{
                std::move(concrete_writers), boost::filesystem::path{ TETENGO2_TEXT("piyo.fuga") }
            };
            const timetable_type timetable{};
            std::ostringstream stream{};
            writer_selector.write(timetable, stream);

            BOOST_CHECK(stream.str() == std::string{ ".fuga" });
        }
        {
            auto concrete_writers = create_concrete_writers();
            writer_selector_type writer_selector{
                std::move(concrete_writers), boost::filesystem::path{ TETENGO2_TEXT("piyo.foo") }
            };
            const timetable_type timetable{};
            std::ostringstream stream{};

            BOOST_CHECK_THROW(writer_selector.write(timetable, stream), std::logic_error);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
