/*! \file
    \brief The definition of bobura::model::serializer::writer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/bzip2_writer.h>
#include <bobura/model/serializer/json_writer.h>
#include <bobura/model/serializer/writer_set.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer
{
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    class writer_set<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder>::impl :
        private boost::noncopyable
    {
    public:
        // types

        using size_type = Size;

        using difference_type = Difference;

        using string_type = String;

        using output_stream_type = OutputStream;

        using operating_distance_type = OperatingDistance;

        using speed_type = Speed;

        using font_type = Font;

        using encoder_type = Encoder;

        using writer_type = typename writer_set::writer_type;

        using bzip2_writer_type =
            bzip2_writer<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                font_type
            >;

        using json_writer_type =
            json_writer<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                font_type,
                encoder_type
            >;


        // static functions

        static std::vector<std::unique_ptr<writer_type>> create_writers()
        {
            std::vector<std::unique_ptr<writer_type>> writers{};

            writers.push_back(tetengo2::stdalt::make_unique<json_writer_type>());
            writers.push_back(
                tetengo2::stdalt::make_unique<bzip2_writer_type>(tetengo2::stdalt::make_unique<json_writer_type>())
            );

            return std::move(writers);
        }


    private:
        // forbidden operations

        impl()
        = delete;


    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    std::vector<
        std::unique_ptr<
            typename writer_set<
                Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder
            >::writer_type
        >
    >
    writer_set<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder>::create_writers()
    {
        return impl::create_writers();
    }


    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class writer_set<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::output_stream_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::locale_type_list_type::timetable_file_encoder_type
    >;
#endif

    template class writer_set<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::output_stream_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type,
        typename test::locale_type_list_type::timetable_file_encoder_type
    >;


}}}
