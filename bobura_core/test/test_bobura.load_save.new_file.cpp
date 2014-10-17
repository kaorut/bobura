/*! \file
    \brief Test of class bobura::load_save::new_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using model_type =
        bobura::timetable_model<
            boost::mpl::at<bobura::common_type_list, bobura::type::size>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::difference>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::string>::type,
            boost::mpl::at<bobura::model_type_list, bobura::type::model::operating_distance>::type,
            boost::mpl::at<bobura::model_type_list, bobura::type::model::speed>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::fast_font>::type
        >;

    using message_catalog_type = boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using save_to_file_type = boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type;

    using confirm_file_save_type =
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    using new_file_type = boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::new_file>::type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(new_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const new_file_type new_file{ confirm_file_save };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const new_file_type new_file{ confirm_file_save };

        window_type parent{};
        new_file(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
