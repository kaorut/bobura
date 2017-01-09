/*! \file
    \brief The definition of bobura::model::serializer::reader.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>

#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>
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
    reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::~reader()
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
    bool reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::selects(
        const iterator first,
        const iterator last
    )
    {
        return selects_impl(first, last);
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
        typename reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::timetable_type
    >
    reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::read(
        const iterator first,
        const iterator last,
        error_type&    error
    )
    {
        return read_impl(first, last, error);
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
    reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>::reader()
    {}


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
    template class reader<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::input_stream_iterator_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type
    >;
#endif

    template class reader<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type
    >;


}}}
