/*! \file
    \brief The definition of bobura::model::serializer::reader_selector.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <bobura/model/serializer/reader_selector.h>
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
    class reader_selector<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::impl :
        private boost::noncopyable
    {
    public:
        // types

        using iterator = ForwardIterator;

        using base_type = typename reader_selector::base_type;

        using timetable_type = typename reader_selector::timetable_type;

        using error_type = typename reader_selector::error_type;


        // constructors and destructor

        explicit impl(std::vector<std::unique_ptr<base_type>> p_readers)
        :
        m_p_readers(std::move(p_readers))
        {
            if (m_p_readers.empty())
                BOOST_THROW_EXCEPTION(std::invalid_argument("No reader is specified."));
        }


        // functions

#if BOOST_COMP_GNUC
#   pragma GCC diagnostic ignored "-Wreturn-type"
#endif
        bool selects_impl(const iterator first, const iterator last)
        {
            boost::ignore_unused(first, last);

            BOOST_THROW_EXCEPTION(std::logic_error("This function cannot be called."));
        }
#if BOOST_COMP_GNUC
#   pragma GCC diagnostic warning "-Wreturn-type"
#endif

        std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        {
            const auto found =
                std::find_if(
                    m_p_readers.begin(),
                    m_p_readers.end(),
                    [first, last](const std::unique_ptr<base_type>& p_reader)
                    {
                        return p_reader->selects(first, last);
                    }
                );
            if (found == m_p_readers.end())
            {
                error = error_type::unsupported;
                return std::unique_ptr<timetable_type>{};
            }

            return (*found)->read(first, last, error);
        }


    private:
        // variables

        const std::vector<std::unique_ptr<base_type>> m_p_readers;


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
    reader_selector<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::reader_selector(
        std::vector<std::unique_ptr<base_type>> p_readers
    )
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(p_readers)))
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
    reader_selector<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::~reader_selector()
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
    bool reader_selector<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::selects_impl(
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
        typename reader_selector<
            Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font
        >::timetable_type
    >
    reader_selector<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::read_impl(
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
    template class reader_selector<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::input_stream_iterator_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type
    >;
#endif

    template class reader_selector<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type
    >;


}}}
