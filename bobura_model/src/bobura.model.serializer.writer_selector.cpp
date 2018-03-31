/*! \file
    \brief The definition of bobura::model::serializer::writer_selector.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>


#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/writer_selector.h>
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
    class writer_selector<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::impl
    : private boost::noncopyable
    {
    public:
        // types

        using output_stream_type = OutputStream;

        using base_type = typename writer_selector::base_type;

        using timetable_type = typename writer_selector::timetable_type;


        // constructors and destructor

        impl(std::vector<std::unique_ptr<base_type>> p_writers, boost::filesystem::path path)
        : m_p_writers{ std::move(p_writers) }, m_path{ std::move(path) }
        {
            if (m_p_writers.empty())
                BOOST_THROW_EXCEPTION(std::invalid_argument("No writer is specified."));
        }


        // functions

        bool selects_impl(const boost::filesystem::path& path) const
        {
            return std::find_if(
                       m_p_writers.begin(), m_p_writers.end(), [&path](const std::unique_ptr<base_type>& p_writer) {
                           return p_writer->selects(path);
                       }) != m_p_writers.end();
        }

#if BOOST_COMP_GNUC
#pragma GCC diagnostic ignored "-Wreturn-type"
#endif
        boost::filesystem::path extension_impl() const
        {
            BOOST_THROW_EXCEPTION(std::logic_error("No extension."));
        }
#if BOOST_COMP_GNUC
#pragma GCC diagnostic warning "-Wreturn-type"
#endif

        void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        {
            const auto found = std::find_if(
                m_p_writers.begin(), m_p_writers.end(), [this](const std::unique_ptr<base_type>& p_writer) {
                    return p_writer->selects(this->m_path);
                });
            if (found == m_p_writers.end())
                BOOST_THROW_EXCEPTION(std::logic_error("No writer selects this file type."));

            (*found)->write(timetable, output_stream);
        }


    private:
        // variables

        const std::vector<std::unique_ptr<base_type>> m_p_writers;

        const boost::filesystem::path m_path;
    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    writer_selector<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::writer_selector(
        std::vector<std::unique_ptr<base_type>> p_writers,
        boost::filesystem::path                 path)
    : base_type{}, m_p_impl{ tetengo2::stdalt::make_unique<impl>(std::move(p_writers), std::move(path)) }
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    writer_selector<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::~writer_selector() noexcept
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    bool writer_selector<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::selects_impl(
        const boost::filesystem::path& path) const
    {
        return m_p_impl->selects_impl(path);
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    boost::filesystem::path
    writer_selector<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::extension_impl() const
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
    void writer_selector<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::write_impl(
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
    template class writer_selector<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::output_stream_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type>;
#endif

    template class writer_selector<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::output_stream_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type>;
}
