/*! \file
    \brief Test of class bobura::message::main_window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/diagram_picture_box.h>
#include <bobura/message/main_window.h>
#include <bobura/message/type_list.h>
#include <bobura/message/type_list_impl.h>
#include <bobura/property_bar.h>


namespace
{
    // types

    using string_type = boost::mpl::at<bobura::common_type_list, bobura::type::string>::type;

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using popup_menu_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::popup_menu>::type;

    using abstract_window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window>::type;

    struct command_type
    {
    public:
        enum class state_type
        {
            default_,
            checked,
            selected,
        };

        virtual bool enabled(const model_type& model)
        const
        {
            boost::ignore_unused(model);

            return true;
        }

        virtual state_type state()
        const
        {
            return state_type::default_;
        }

        virtual void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model, parent);
        }

    };

    using message_catalog_type = boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using save_to_file_type = boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type;

    using confirm_file_save_type =
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type;

    using settings_type = boost::mpl::at<bobura::setting_type_list, bobura::type::setting::settings>::type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    using view_type = boost::mpl::at<bobura::view_type_list, bobura::type::view::view>::type;

    using picture_box_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type;

    using diagram_picture_box_message_type_list =
        bobura::message::diagram_picture_box::type_list<
            picture_box_type,
            abstract_window_type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::mouse_capture>::type,
            boost::mpl::at<bobura::view_type_list, bobura::type::view::traits>::type
        >;

    using diagram_picture_box_type =
        bobura::diagram_picture_box<
            picture_box_type,
            abstract_window_type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::mouse_capture>::type,
            diagram_picture_box_message_type_list
        >;

    using property_bar_type =
        bobura::property_bar<
            string_type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dimension>::type,
            abstract_window_type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::side_bar>::type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::map_box>::type,
            message_catalog_type,
            boost::mpl::at<bobura::setting_type_list, bobura::type::setting::config_traits>::type
        >;

    using popup_menu_selected_type =
        bobura::message::main_window::popup_menu_selected<popup_menu_type, command_type, model_type>;

    using menu_command_selected_type =
        bobura::message::main_window::menu_command_selected<command_type, model_type, abstract_window_type>;

    using window_resized_type =
        bobura::message::main_window::window_resized<
            view_type, abstract_window_type, diagram_picture_box_type, property_bar_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(main_window)
BOOST_AUTO_TEST_SUITE(popup_menu_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("popup") } };
        std::vector<const command_type*> commands;
        const model_type model{};
        const popup_menu_selected_type observer{ popup_menu, std::move(commands), model };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("popup") } };
        std::vector<const command_type*> commands;
        const model_type model{};
        const popup_menu_selected_type observer{ popup_menu, std::move(commands), model };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(menu_command_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type menu{ command, model, window };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type observer{ command, model, window };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(file_dropped)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type menu{ command, model, window };
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command{};
        model_type model{};
        window_type window{};
        const menu_command_selected_type observer{ command, model, window };

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(window_resized)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        window_type window{};
        diagram_picture_box_type diagram_picture_box{ window };
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        property_bar_type property_bar{ window, settings, message_catalog };
        const window_resized_type observer{ view, window, diagram_picture_box, property_bar };

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model{};
        const message_catalog_type message_catalog{};
        view_type view{ model, message_catalog };
        window_type window{};
        diagram_picture_box_type diagram_picture_box{ window };
        const std::vector<string_type> settings_arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ settings_arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        property_bar_type property_bar{ window, settings, message_catalog };
        const window_resized_type observer{ view, window, diagram_picture_box, property_bar };

        observer();

        settings.clear_config();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(window_closing)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const std::vector<string_type> command_line_arguments{ 1, string_type{ TETENGO2_TEXT("path/to/exe") } };
        const bobura::message::main_window::window_closing<abstract_window_type, confirm_file_save_type> observer(
            parent, confirm_file_save, []() {}
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        model_type model{};
        const message_catalog_type message_catalog{};
        const save_to_file_type save_to_file{ false, message_catalog };
        const confirm_file_save_type confirm_file_save{ model, save_to_file, message_catalog };
        const bobura::message::main_window::window_closing<abstract_window_type, confirm_file_save_type> observer(
            parent, confirm_file_save, []() {}
        );

        auto cancel = false;
        observer(cancel);

        BOOST_CHECK(!cancel);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
