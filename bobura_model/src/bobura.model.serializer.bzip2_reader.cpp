/*! \file
    \brief The definition of bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/predef.h>
#include <boost/range/iterator_range.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/bzip2_reader.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer
{
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    class bzip2_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::impl :
        private boost::noncopyable
    {
    public:
        // types

        using iterator = ForwardIterator;

        using base_type = typename bzip2_reader::base_type;

        using timetable_type = typename bzip2_reader::timetable_type;

        using error_type = typename bzip2_reader::error_type;


        // constructors and destructor

        explicit impl(std::unique_ptr<base_type> p_reader)
        :
        m_p_reader(std::move(p_reader))
        {}


        // functions

        bool selects_impl(const iterator first, const iterator last)
        {
            if (std::distance(first, last) < 2)
                return false;
            if (input_string_type{ first, std::next(first, 2) } != input_string_type(TETENGO2_TEXT("BZ")))
                return false;

            const input_string_type input_string{ first, last };
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(input_string) };
            boost::iostreams::filtering_istream filtering_input_stream{};
            filtering_input_stream.push(boost::iostreams::bzip2_decompressor());
            filtering_input_stream.push(input_stream);

            try
            {
                const auto observable_first =
                    tetengo2::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>{ filtering_input_stream }
                        )
                    );
                const auto observable_last =
                    tetengo2::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>{}
                        )
                    );
                return m_p_reader->selects(observable_first, observable_last);
            }
            catch (const boost::iostreams::bzip2_error&)
            {
                return false;
            }
            catch (...)
            {
                throw;
            }
        }

        std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        {
            const input_string_type input_string{ first, last };
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(input_string) };
            boost::iostreams::filtering_istream filtering_input_stream{};
            filtering_input_stream.push(boost::iostreams::bzip2_decompressor());
            filtering_input_stream.push(input_stream);

            try
            {
                const auto observable_first =
                    tetengo2::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>{ filtering_input_stream }
                        )
                    );
                const auto observable_last =
                    tetengo2::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>{}
                        )
                    );
                return m_p_reader->read(observable_first, observable_last, error);
            }
            catch (const boost::iostreams::bzip2_error&)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            catch (...)
            {
                throw;
            }
        }


    private:
        // types

        using input_string_type = std::basic_string<typename iterator::value_type>;


        // variables

        const std::unique_ptr<base_type> m_p_reader;


    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    bzip2_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::bzip2_reader(
        std::unique_ptr<base_type> p_reader
    )
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(p_reader)))
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    bzip2_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::~bzip2_reader()
    noexcept
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    bool bzip2_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::selects_impl(
        const iterator first,
        const iterator last
    )
    {
        return m_p_impl->selects_impl(first, last);
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    std::unique_ptr<
        typename bzip2_reader<
            Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font
        >::timetable_type
    >
    bzip2_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::read_impl(
        const iterator first,
        const iterator last,
        error_type&    error
    )
    {
        return m_p_impl->read_impl(first, last, error);
    }


    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class bzip2_reader<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::input_stream_iterator_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type
    >;
#endif

#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
    template class bzip2_reader<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type
    >;
#endif


}}}
