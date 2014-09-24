/*! \file
    \brief The definition of type lists for bobura.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/command_base.h>
#include <bobura/command/set.h>
#include <bobura/diagram_picture_box.h>
#include <bobura/main_window.h>
#include <bobura/main_window_traits.h>
#include <bobura/message/type_list_impl.h>
#include <bobura/property_bar.h>


namespace bobura
{
    /**** Main Window *******************************************************/

    template <typename Traits>
    class main_window;

    namespace type { namespace main_window
    {
        struct command_set;    //!< The command set type.
        struct main_window;    //!< The main window type.
        struct message_type_list; //!< The main window message type list type.
        struct diagram_picture_box; //!< The diagram picture box type.
        struct diagram_picture_box_message_type_list; //!< The diagram picture box message type list type.
        struct property_bar;   //!< The property bar type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace main_window
    {
        using command_set_type = command::set;
        using diagram_picture_box_message_type_list =
            message::diagram_picture_box::type_list<
                boost::mpl::at<view_type_list, type::view::traits>::type,
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type
            >;
        using diagram_picture_box_type =
            diagram_picture_box<
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type,
                diagram_picture_box_message_type_list
            >;
        using property_bar_type =
            property_bar<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<ui_type_list, type::ui::side_bar>::type,
                boost::mpl::at<ui_type_list, type::ui::map_box>::type,
                boost::mpl::at<setting_type_list, type::setting::config_traits>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;
        using main_window_traits_type =
            main_window_traits<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                boost::mpl::at<common_type_list, type::output_stream>::type,
                boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                boost::mpl::at<model_type_list, type::model::speed>::type,
                boost::mpl::at<ui_type_list, type::ui::window>::type,
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<ui_type_list, type::ui::map_box>::type,
                boost::mpl::at<ui_type_list, type::ui::side_bar>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type,
                boost::mpl::at<setting_type_list, type::setting::config_traits>::type,
                diagram_picture_box_message_type_list,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type
            >;
        using main_window_message_type_list =
            message::main_window::type_list<
                boost::mpl::at<ui_type_list, type::ui::popup_menu>::type,
                command_set_type,
                command::command_base,
                boost::mpl::at<model_type_list, type::model::model>::type,
                boost::mpl::at<view_type_list, type::view::view>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                diagram_picture_box_type,
                property_bar_type,
                boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type
            >;
    }}
#endif

    //! The type list for the main window.
    using main_window_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::command_set, detail::main_window::command_set_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window::main_window, main_window<detail::main_window::main_window_traits_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::message_type_list, detail::main_window::main_window_message_type_list>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::diagram_picture_box, detail::main_window::diagram_picture_box_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window::diagram_picture_box_message_type_list,
                detail::main_window::diagram_picture_box_message_type_list
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::property_bar, detail::main_window::property_bar_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>;


}


#endif
