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

    using common_dialog_type_list_type = bobura::common_dialog_type_list<detail_type_list_type>;

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

    using dialog_type = boost::mpl::at<ui_type_list_type, bobura::type::ui::dialog>::type;

    struct oudia_diagram_dialog_type : public dialog_type
    {
        using base_type = dialog_type;

        using abstract_window_type = window_type::base_type;

        using message_catalog_type = message_catalog_type_;

        oudia_diagram_dialog_type(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        base_type(parent)
        {
            boost::ignore_unused(message_catalog);
        }

        virtual ~oudia_diagram_dialog_type()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;

        const string_type& file_name()
        const
        {
            static const string_type singleton{};
            return singleton;
        }

        void set_file_name(string_type file_name)
        {
            boost::ignore_unused(file_name);
        }

        const std::vector<string_type>& names()
        const
        {
            static const std::vector<string_type> singleton{};
            return singleton;
        }

        void set_names(std::vector<string_type> names)
        {
            boost::ignore_unused(names);
        }

        const boost::optional<size_type>& selected_index()
        const
        {
            static const boost::optional<size_type> singleton{};
            return singleton;
        }

        void set_selected_index(const size_type index)
        {
            boost::ignore_unused(index);
        }

    };

    using load_save_traits_type =
        bobura::load_save::traits<
            size_type,
            difference_type,
            string_type,
            boost::mpl::at<common_type_list_type, bobura::type::input_stream_iterator>::type,
            boost::mpl::at<common_type_list_type, bobura::type::output_stream>::type,
            operating_distance_type,
            speed_type,
            fast_font_type,
            boost::mpl::at<ui_type_list_type, bobura::type::ui::abstract_window>::type,
            boost::mpl::at<common_dialog_type_list_type, bobura::type::common_dialog::message_box>::type,
            boost::mpl::at<common_dialog_type_list_type, bobura::type::common_dialog::file_open>::type,
            boost::mpl::at<common_dialog_type_list_type, bobura::type::common_dialog::file_save>::type,
            oudia_diagram_dialog_type,
            message_catalog_type_,
            boost::mpl::at<locale_type_list_type, bobura::type::locale::timetable_file_encoder>::type,
            boost::mpl::at<locale_type_list_type, bobura::type::locale::windia_file_encoder>::type
        >;

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
