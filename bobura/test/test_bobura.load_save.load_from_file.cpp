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
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/load_save/load_from_file.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using message_catalog_type = boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using save_to_file_type = boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type;

    using confirm_file_save_type =
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    struct oudia_diagram_dialog_type : public boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dialog>::type
    {
        using base_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dialog>::type;

        using abstract_window_type = window_type::base_type;

        using string_type = abstract_window_type::string_type;

        using message_catalog_type =
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

        using int_size_type = boost::mpl::at<bobura::common_type_list, bobura::type::size>::type;

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

        const boost::optional<int_size_type>& selected_index()
        const
        {
            static const boost::optional<int_size_type> singleton{};
            return singleton;
        }

        void set_selected_index(const int_size_type index)
        {
            boost::ignore_unused(index);
        }

    };

    using load_from_file_type =
        bobura::load_save::load_from_file<
            boost::mpl::at<bobura::common_type_list, bobura::type::size>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::difference>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::string>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::input_stream_iterator>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::output_stream>::type,
            boost::mpl::at<bobura::model_type_list, bobura::type::model::operating_distance>::type,
            boost::mpl::at<bobura::model_type_list, bobura::type::model::speed>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::fast_font>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window>::type,
            boost::mpl::at<bobura::common_dialog_type_list, bobura::type::common_dialog::message_box>::type,
            boost::mpl::at<bobura::common_dialog_type_list, bobura::type::common_dialog::file_open_dialog>::type,
            boost::mpl::at<bobura::common_dialog_type_list, bobura::type::common_dialog::file_save_dialog>::type,
            oudia_diagram_dialog_type,
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type,
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::timetable_file_encoder>::type,
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::windia_file_encoder>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model{};
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };
        }
        {
            model_type model{};
            const message_catalog_type message_catalog{};
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
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};

            BOOST_CHECK(!load_from_file.reloadable(model, path));
        }
        {
            model_type model{};
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ true, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};

            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
        {
            model_type model{};
            model.set_path(boost::filesystem::path{ TETENGO2_TEXT("file_path") });
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};
            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
        {
            model_type model{};
            const message_catalog_type message_catalog{};
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
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ false, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};
            window_type parent{};
            load_from_file(model, path, parent);
        }
        {
            model_type model{};
            const message_catalog_type message_catalog{};
            const save_to_file_type save_to_file{ false, message_catalog };
            const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
            const load_from_file_type load_from_file{ true, confirm_file_save, message_catalog };

            const boost::optional<boost::filesystem::path> path{};
            window_type parent{};
            load_from_file(model, path, parent);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
