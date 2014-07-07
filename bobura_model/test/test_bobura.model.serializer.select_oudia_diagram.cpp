/*! \file
    \brief Test of class bobura::model::serializer::select_oudia_diagram.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cstddef>
#include <utility>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/serializer/select_oudia_diagram.h>
#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using window_type =
        tetengo2::gui::widget::window<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_traits>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_details_traits>::type,
            boost::mpl::at<test_bobura::model::detail_type_list, test_bobura::model::type::detail::menu>::type
        >;

    using io_string_type = std::string;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;

    using message_catalog_type =
        tetengo2::message::message_catalog<
            input_stream_iterator_type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::encoder>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::encoder>::type
        >;

    struct oudia_diagram_dialog
    {
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_traits>::type,
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_details_traits>::type,
                boost::mpl::at<test_bobura::model::detail_type_list, test_bobura::model::type::detail::menu>::type
            >;

        using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

        using message_catalog_type =
            tetengo2::message::message_catalog<
                input_stream_iterator_type,
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type,
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type,
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::encoder>::type,
                boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::encoder>::type
            >;

        enum class result_type
        {
            undecided,
            accepted,
            canceled,
        };

        using int_size_type = std::size_t;

        oudia_diagram_dialog(abstract_window_type&, const message_catalog_type&)
        {}

        result_type result()
        const
        {
            return result_type::undecided;
        }

        void do_modal()
        {}

        const string_type& file_name()
        const
        {
            static const string_type singleton{};
            return singleton;
        }

        void set_file_name(string_type)
        {}

        const std::vector<string_type>& names()
        const
        {
            static const std::vector<string_type> singleton{};
            return singleton;
        }

        void set_names(std::vector<string_type>)
        {}

        boost::optional<int_size_type> selected_index()
        const
        {
            return boost::none;
        }

        void set_selected_index(int_size_type)
        {}

        
    };

    using select_oudia_diagram_type = bobura::model::serializer::select_oudia_diagram<oudia_diagram_dialog>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(select_oudia_diagram)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type message_catalog{};
        const select_oudia_diagram_type select_oudia_diagram{ parent, std::move(file_name), message_catalog };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type message_catalog{};
        const select_oudia_diagram_type select_oudia_diagram{ parent, std::move(file_name), message_catalog };

        std::vector<string_type> diagram_names{};
        const auto selected = select_oudia_diagram(diagram_names.begin(), diagram_names.end());

        BOOST_CHECK(selected == diagram_names.end());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
