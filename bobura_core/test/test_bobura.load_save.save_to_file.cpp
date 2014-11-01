/*! \file
    \brief Test of class bobura::load_save::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/load_save/save_to_file.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::detail_type_list;

    using common_type_list_type = bobura::common_type_list;

    using locale_type_list_type = bobura::locale_type_list<detail_type_list_type>;

    using ui_type_list_type = bobura::ui_type_list<detail_type_list_type>;

    using traits_type_list_type = bobura::traits_type_list<detail_type_list_type>;

    using message_catalog_type = boost::mpl::at<locale_type_list_type, bobura::type::locale::message_catalog>::type;

    using model_type =
        bobura::timetable_model<
            boost::mpl::at<common_type_list_type, bobura::type::size>::type,
            boost::mpl::at<common_type_list_type, bobura::type::difference>::type,
            boost::mpl::at<common_type_list_type, bobura::type::string>::type,
            boost::mpl::at<common_type_list_type, bobura::type::operating_distance>::type,
            boost::mpl::at<common_type_list_type, bobura::type::speed>::type,
            boost::mpl::at<ui_type_list_type, bobura::type::ui::fast_font>::type
        >;

    using window_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::window>::type;

    using save_to_file_type =
        bobura::load_save::save_to_file<
            boost::mpl::at<traits_type_list_type, bobura::type::traits::load_save>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(save_to_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        {
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };

            model_type model{};
            window_type parent{};
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
        {
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };

            model_type model{};
            model.set_path(boost::filesystem::path("test"));
            window_type parent{};
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
        {
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };

            model_type model{};
            model.set_changed(true);
            window_type parent{};
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
        {
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ true, message_catalog };

            model_type model{};
            window_type parent{};
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
