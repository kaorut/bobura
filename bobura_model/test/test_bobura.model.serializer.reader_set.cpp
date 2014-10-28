/*! \file
    \brief Test of class bobura::model::serializer::reader_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <algorithm>
#include <iterator>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/serializer/reader_set.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using size_type_ = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type;

    using string_type_ = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using widget_traits_type =
        boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_traits>::type;

    using widget_details_traits_type =
        boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_details_traits>::type;

    using menu_details_type =
        boost::mpl::at<test_bobura::model::detail_type_list, test_bobura::model::type::detail::menu>::type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<
            std::istreambuf_iterator<
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_string>::type::value_type
            >
        >;

    using encoder_type_ = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::encoder>::type;

    using message_catalog_type_ =
        tetengo2::message::message_catalog<
            input_stream_iterator_type, string_type_, size_type_, encoder_type_, encoder_type_
        >;

    using io_encoder_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::io_encoder>::type;

    struct select_oudia_diagram_type
    {
        using size_type = size_type_;

        using string_type = string_type_;

        using encoder_type = encoder_type_;

        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;

        using message_catalog_type = message_catalog_type_;

        string_type m_wanted;

        select_oudia_diagram_type(abstract_window_type&, string_type, const message_catalog_type&)
        :
        m_wanted()
        {}

        explicit select_oudia_diagram_type(string_type wanted)
        :
        m_wanted(std::move(wanted))
        {}

        template <typename Iterator>
        Iterator operator()(const Iterator first, const Iterator last)
        const
        {
            return std::find(first, last, m_wanted);
        }

    };

    using reader_set_type =
        bobura::model::serializer::reader_set<
            size_type_,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::difference>::type,
            string_type_,
            input_stream_iterator_type,
            boost::mpl::at<
                test_bobura::model::model_type_list, test_bobura::model::type::model::operating_distance
            >::type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::speed>::type,
            select_oudia_diagram_type,
            boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::font>::type,
            io_encoder_type,
            io_encoder_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader_set)
    // test cases

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(create_readers)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type_ file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type_ message_catalog{};
        const auto p_readers = reader_set_type::create_readers(parent, std::move(file_name), message_catalog);

        BOOST_REQUIRE(!p_readers.empty());
        BOOST_CHECK(p_readers[0]);
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
