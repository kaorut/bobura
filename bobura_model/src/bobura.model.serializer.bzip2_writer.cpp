/*! \file
    \brief The definition of bobura::model::serializer::bzip2_writer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <ios>
#include <memory>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/predef.h>

#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/bzip2_writer.h>
#include <bobura/type_list.h>


namespace bobura::model::serializer {
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    class bzip2_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::impl
    : private boost::noncopyable
    {
    public:
        // types

        using output_stream_type = OutputStream;

        using base_type = typename bzip2_writer::base_type;

        using timetable_type = typename bzip2_writer::timetable_type;


        // constructors and destructor

        explicit impl(std::unique_ptr<base_type> p_writer) : m_p_writer{ std::move(p_writer) } {}


        // functions

        boost::filesystem::path extension_impl() const
        {
            return boost::filesystem::path(
                m_p_writer->extension().native() +
                typename boost::filesystem::path::string_type{ TETENGO2_TEXT("_bz2") });
        }

        void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        {
            boost::iostreams::filtering_ostream filtering_output_stream{};
            filtering_output_stream.push(boost::iostreams::bzip2_compressor{});
            filtering_output_stream.push(output_stream);

            m_p_writer->write(timetable, filtering_output_stream);
        }


    private:
        // variables

        const std::unique_ptr<base_type> m_p_writer;
    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    bzip2_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::bzip2_writer(
        std::unique_ptr<base_type> p_writer)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(p_writer)) }
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    bzip2_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::~bzip2_writer() noexcept
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    boost::filesystem::path
    bzip2_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::extension_impl() const
    {
        return m_p_impl->extension_impl();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    void bzip2_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::write_impl(
        const timetable_type& timetable,
        output_stream_type&   output_stream)
    {
        m_p_impl->write_impl(timetable, output_stream);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class bzip2_writer<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::output_stream_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type>;
#endif

    template class bzip2_writer<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::output_stream_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type>;
}
