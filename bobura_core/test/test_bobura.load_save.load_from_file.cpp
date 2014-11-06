/*! \file
    \brief Test of class bobura::load_save::load_from_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/load_save/load_from_file.h>
#include <bobura/load_save/traits.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::detail_type_list_for_test;

    using common_type_list_type = bobura::common_type_list;

    using locale_type_list_type = bobura::locale_type_list<detail_type_list_type>;

    using ui_type_list_type = bobura::ui_type_list<detail_type_list_type>;

    using traits_type_list_type = bobura::traits_type_list<detail_type_list_type>;

    using size_type = boost::mpl::at<common_type_list_type, bobura::type::size>::type;

    using difference_type = boost::mpl::at<common_type_list_type, bobura::type::difference>::type;

    using string_type = boost::mpl::at<common_type_list_type, bobura::type::string>::type;

    using operating_distance_type = boost::mpl::at<common_type_list_type, bobura::type::operating_distance>::type;

    using speed_type = boost::mpl::at<common_type_list_type, bobura::type::speed>::type;

    using fast_font_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::fast_font>::type;

    using model_type =
        bobura::timetable_model<
            size_type, difference_type, string_type, operating_distance_type, speed_type, fast_font_type
        >;

    using message_catalog_type_ =
        boost::mpl::at<locale_type_list_type, bobura::type::locale::message_catalog>::type;

    using window_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::window>::type;

    using load_save_traits_type = boost::mpl::at<traits_type_list_type, bobura::type::traits::load_save>::type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using confirm_file_save_type = bobura::load_save::confirm_file_save<load_save_traits_type>;

    using load_from_file_type = bobura::load_save::load_from_file<load_save_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model{};
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };
        }
        {
            model_type model{};
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ true, confirm_file_save, message_catalog };
        }
    }

    BOOST_AUTO_TEST_CASE(reloadable)
    {
        BOOST_TEST_PASSPOINT();
    
        {
            model_type model{};
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};

            BOOST_CHECK(!load_from_file.reloadable(model, path));
        }
        {
            model_type model{};
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ true, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};

            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
        {
            model_type model{};
            model.set_path(boost::filesystem::path{ TETENGO2_TEXT("file_path") });
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};
            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
        {
            model_type model{};
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{
                boost::filesystem::path{ TETENGO2_TEXT("file_path") }
            };
            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model{};
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};
            window_type parent{};
            load_from_file(model, path, parent);
        }
        {
            model_type model{};
            const message_catalog_type_ message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ true, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};
            window_type parent{};
            load_from_file(model, path, parent);
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
