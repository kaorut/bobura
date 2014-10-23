/*! \file
    \brief Test of class bobura::message::timetable_model.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/diagram_picture_box.h>
#include <bobura/diagram_view.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/message/timetable_model.h>
#include <bobura/message/type_list_impl.h>
#include <bobura/settings.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using string_type = boost::mpl::at<bobura::common_type_list, bobura::type::string>::type;

    using model_type =
        bobura::timetable_model<
            boost::mpl::at<bobura::common_type_list, bobura::type::size>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::difference>::type,
            string_type,
            boost::mpl::at<bobura::common_type_list, bobura::type::operating_distance>::type,
            boost::mpl::at<bobura::common_type_list, bobura::type::speed>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::fast_font>::type
        >;

    using view_traits_type = boost::mpl::at<bobura::traits_type_list, bobura::type::traits::view>::type;

    using view_type = bobura::diagram_view<view_traits_type>;

    using message_catalog_type = boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using settings_type =
        bobura::settings<
            string_type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dimension>::type,
            boost::mpl::at<bobura::traits_type_list, bobura::type::traits::config>::type
        >;

    using load_save_traits_type = boost::mpl::at<bobura::traits_type_list, bobura::type::traits::load_save>::type;

    using save_to_file_type = bobura::load_save::save_to_file<load_save_traits_type>;

    using confirm_file_save_type = bobura::load_save::confirm_file_save<load_save_traits_type>;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    class main_window_type : public window_type
    {
    public:
        using base_type = window_type;

        using picture_box_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type;

        using abstract_window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window>::type;

        using mouse_capture_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::mouse_capture>::type;

        using diagram_picture_box_message_type_list =
            bobura::message::diagram_picture_box::type_list<
                picture_box_type, abstract_window_type, mouse_capture_type, view_traits_type
            >;

        using diagram_picture_box_type =
            bobura::diagram_picture_box<
                picture_box_type, abstract_window_type, mouse_capture_type, diagram_picture_box_message_type_list
            >;

        main_window_type(
            const message_catalog_type&   message_catalog,
            const settings_type&          settings,
            const confirm_file_save_type& confirm_file_save
        )
        :
        base_type(),
        m_diagram_picture_box(*this)
        {
            boost::ignore_unused(message_catalog, settings, confirm_file_save);
        }

        virtual ~main_window_type()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;

        void set_title(const boost::optional<string_type>& document_name, const bool changed)
        {
            boost::ignore_unused(document_name, changed);
        }

        const diagram_picture_box_type& get_diagram_picture_box()
        const
        {
            return m_diagram_picture_box;
        }

        diagram_picture_box_type& get_diagram_picture_box()
        {
            return m_diagram_picture_box;
        }

    private:
        diagram_picture_box_type m_diagram_picture_box;

    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(timetable_model)
BOOST_AUTO_TEST_SUITE(reset)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::reset<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::reset<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        observer();

        settings.clear_config();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::changed<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        main_window_type main_window{ message_catalog, settings, confirm_file_save };
        const bobura::message::timetable_model::changed<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        observer();

        settings.clear_config();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
