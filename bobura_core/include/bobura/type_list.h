/*! \file
    \brief The definition of type lists for bobura.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

#include <cstddef>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/rational.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/application_traits.h>
#include <bobura/command/set_traits.h>
#include <bobura/command/traits.h>
#include <bobura/config_traits.h>
#include <bobura/detail_type_list.h>
#include <bobura/dialog_traits.h>
#include <bobura/load_save/traits.h>
#include <bobura/main_window_traits.h>
#include <bobura/oudia_diagram_dialog.h>
#include <bobura/view/diagram/traits.h>


namespace bobura
{
    /**** Common ************************************************************/

    namespace type
    {
        struct difference;     //!< The difference type.
        struct size;           //!< The size type.
        struct string;         //!< The string type.
        struct input_stream_iterator; //!< The input stream iterator type.
        struct output_stream;  //!< The output stream type.
        struct operating_distance; //!< The operating distance type.
        struct speed;          //!< The speed type.
        struct scale;          //!< The scale type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        using size_type = std::size_t;
        using string_type = std::wstring;
        using io_string_type = std::string;
        using input_stream_iterator_type =
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;
        using operating_distance_type = boost::rational<size_type>;
        using speed_type = boost::rational<size_type>;
        using scale_type = boost::rational<size_type>;
    }
#endif

    //! The common type list.
    using common_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::input_stream_iterator, detail::input_stream_iterator_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::output_stream, std::basic_ostream<detail::io_string_type::value_type>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::operating_distance, detail::operating_distance_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::speed, detail::speed_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::scale, detail::scale_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>;


    /**** Locale ************************************************************/

    namespace type { namespace locale
    {
        struct exception_encoder; //!< The encoder type for exceptions.
        struct ui_encoder;     //!< The encoder type for the user interface.
        struct config_encoder; //!< The encoder type for the user interface.
        struct message_catalog_encoder; //!< The message catalog encoder type.
        struct locale_name_encoder; //!< The locale name encoder type.
        struct message_catalog; //!< The message catalog type.
        struct timetable_file_encoder; //!< The encoder type for the timetable file.
        struct windia_file_encoder; //!< The encoder type for the WinDIA file.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace locale
    {
        using string_type = boost::mpl::at<common_type_list, type::string>::type;
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using utf8_encoding_type = tetengo2::text::encoding::utf8<encoding_details_type>;
        using cp932_encoding_type = tetengo2::text::encoding::cp932<encoding_details_type>;
        using exception_encoding_type = utf8_encoding_type;
        using ui_encoding_type =
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::widget>::type::string_type, encoding_details_type
            >;
        using config_encoding_type =
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::config>::type::string_type, encoding_details_type
            >;
        using message_catalog_encoding_type = utf8_encoding_type;
        using message_catalog_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>;
        using locale_name_encoding_type = tetengo2::text::encoding::locale<std::string, encoding_details_type>;
        using locale_name_encoder_type = tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type>;
        using message_catalog_type =
            tetengo2::message::message_catalog<
                boost::mpl::at<common_type_list, type::input_stream_iterator>::type,
                string_type,
                size_type,
                message_catalog_encoder_type,
                locale_name_encoder_type
            >;
        using timetable_file_encoding_type = utf8_encoding_type;
        using timetable_file_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, timetable_file_encoding_type>;
        using windia_file_encoding_type = cp932_encoding_type;
        using windia_file_encoder_type = tetengo2::text::encoder<internal_encoding_type, windia_file_encoding_type>;
    }}
#endif

    //! The type list for the locale.
    using locale_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::exception_encoder,
                tetengo2::text::encoder<
                    detail::locale::internal_encoding_type, detail::locale::exception_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::config_encoder,
                tetengo2::text::encoder<detail::locale::internal_encoding_type, detail::locale::config_encoding_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::ui_encoder,
                tetengo2::text::encoder<detail::locale::internal_encoding_type, detail::locale::ui_encoding_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::message_catalog_encoder, detail::locale::message_catalog_encoder_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::locale_name_encoder, detail::locale::locale_name_encoder_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::message_catalog, detail::locale::message_catalog_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::timetable_file_encoder, detail::locale::timetable_file_encoder_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::windia_file_encoder, detail::locale::windia_file_encoder_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>;


    /**** User Interface ****************************************************/

    namespace type { namespace ui
    {
        struct abstract_window; //!< The abstract window type.
        struct button;         //!< The button type.
        struct canvas;         //!< The canvas type.
        struct color;          //!< The color type.
        struct dialog;         //!< The dialog type.
        struct dimension;      //!< The dimension type.
        struct dropdown_box;   //!< The dropdown box type.
        struct fast_canvas;    //!< The fast canvas type.
        struct fast_font;      //!< The fast font type.
        struct fast_solid_background; //!< The fast solid background type.
        struct image;          //!< The image type.
        struct label;          //!< The label type.
        struct link_label;     //!< The link label type.
        struct list_box;       //!< The list box type.
        struct map_box;        //!< The map box type.
        struct menu_bar;       //!< The menu bar type.
        struct mouse_capture;  //!< The mouse capture type.
        struct picture_box;    //!< The picture box type.
        struct point_unit_size; //!< The point unit size type.
        struct popup_menu;     //!< The popup menu type.
        struct position;       //!< The position type.
        struct shell;          //!< The shell type.
        struct side_bar;       //!< The side bar type.
        struct text_box;       //!< The text box type.
        struct transparent_background; //!< The transparent background type.
        struct widget;         //!< The widget type.
        struct widget_details_traits; //!< The widget details traits type.
        struct widget_traits;  //!< The widget traits type.
        struct window;         //!< The window type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        using size_type = boost::mpl::at<common_type_list, type::size>::type;
        using difference_type = boost::mpl::at<common_type_list, type::difference>::type;
        using string_type = boost::mpl::at<common_type_list, type::string>::type;
        using ui_encoder_type = boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type;
        using unit_details_type = boost::mpl::at<detail_type_list, type::detail::unit>::type;
        using drawing_details_type = boost::mpl::at<detail_type_list, type::detail::drawing>::type;
        using fast_drawing_details_type = boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type;
        using icon_details_type = boost::mpl::at<detail_type_list, type::detail::icon>::type;
        using virtual_key_details_type = boost::mpl::at<detail_type_list, type::detail::virtual_key>::type;
        using menu_details_type = boost::mpl::at<detail_type_list, type::detail::menu>::type;
        using shell_details_type = boost::mpl::at<detail_type_list, type::detail::shell>::type;
        using system_color_details_type = boost::mpl::at<detail_type_list, type::detail::system_color>::type;
        using mouse_capture_details_type = boost::mpl::at<detail_type_list, type::detail::mouse_capture>::type;
        using unit_difference_type = tetengo2::gui::unit::em<boost::rational<difference_type>, unit_details_type>;
        using position_type = std::pair<unit_difference_type, unit_difference_type>;
        using unit_size_type = tetengo2::gui::unit::em<boost::rational<size_type>, unit_details_type>;
        using dimension_type = std::pair<unit_size_type, unit_size_type>;
        using fast_solid_background_type = tetengo2::gui::drawing::solid_background<fast_drawing_details_type>;
        using transparent_background_type = tetengo2::gui::drawing::transparent_background<drawing_details_type>;
        using fast_font_type = tetengo2::gui::drawing::font<string_type, size_type, fast_drawing_details_type>;
        using canvas_traits_type =
            tetengo2::gui::drawing::canvas_traits<
                size_type, unit_size_type, string_type, position_type, dimension_type, ui_encoder_type
            >;
        using canvas_type =
            tetengo2::gui::drawing::canvas<canvas_traits_type, drawing_details_type, icon_details_type>;
        using fast_canvas_type =
            tetengo2::gui::drawing::canvas<canvas_traits_type, fast_drawing_details_type, icon_details_type>;
        using mouse_observer_set_type = tetengo2::gui::message::mouse_observer_set<position_type, difference_type>;
        using widget_traits_type =
            tetengo2::gui::widget::widget_traits<
                size_type,
                unit_size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                ui_encoder_type,
                boost::mpl::at<locale_type_list, type::locale::exception_encoder>::type
            >;
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                drawing_details_type,
                icon_details_type,
                boost::mpl::at<detail_type_list, type::detail::alert>::type,
                boost::mpl::at<detail_type_list, type::detail::cursor>::type,
                boost::mpl::at<detail_type_list, type::detail::scroll>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type,
                virtual_key_details_type
            >;
        using widget_type = tetengo2::gui::widget::widget<widget_traits_type, widget_details_traits_type>;
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;
        using window_type =
            tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;
        using dialog_type =
            tetengo2::gui::widget::dialog<
                widget_traits_type,
                widget_details_traits_type,
                menu_details_type,
                boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >;
        using color_type = tetengo2::gui::drawing::color;
        using button_type = tetengo2::gui::widget::button<widget_traits_type, widget_details_traits_type>;
        using dropdown_box_type = tetengo2::gui::widget::dropdown_box<widget_traits_type, widget_details_traits_type>;
        using image_type = tetengo2::gui::widget::image<widget_traits_type, widget_details_traits_type>;
        using label_type = tetengo2::gui::widget::label<widget_traits_type, widget_details_traits_type>;
        using link_label_type =
            tetengo2::gui::widget::link_label<
                widget_traits_type, widget_details_traits_type, system_color_details_type, shell_details_type
            >;
        using list_box_type = tetengo2::gui::widget::list_box<widget_traits_type, widget_details_traits_type>;
        using mouse_capture_type =
            tetengo2::gui::mouse_capture<
                widget_type, mouse_observer_set_type::mouse_button_type, mouse_capture_details_type
            >;
        using map_box_type =
            tetengo2::gui::widget::map_box<
                widget_traits_type, widget_details_traits_type, mouse_capture_details_type, system_color_details_type
            >;
        using menu_bar_type =
            tetengo2::gui::menu::menu_bar<
                string_type,
                tetengo2::gui::menu::shortcut_key_table<
                    string_type, ui_encoder_type, menu_details_type, virtual_key_details_type
                >,
                ui_encoder_type,
                menu_details_type,
                virtual_key_details_type
            >;
        using picture_box_type =
            tetengo2::gui::widget::picture_box<
                widget_traits_type, widget_details_traits_type, fast_drawing_details_type
            >;
        using shell_type = tetengo2::gui::shell<string_type, ui_encoder_type, shell_details_type>;
        using side_bar_type =
            tetengo2::gui::widget::side_bar<
                widget_traits_type,
                widget_details_traits_type,
                mouse_capture_details_type,
                system_color_details_type,
                boost::mpl::at<detail_type_list, type::detail::timer>::type
            >;
        using text_box_type = tetengo2::gui::widget::text_box<widget_traits_type, widget_details_traits_type>;
    }}
#endif

    //! The type list for the user interface.
    using ui_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::abstract_window, detail::ui::abstract_window_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::button, detail::ui::button_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::canvas, detail::ui::canvas_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::color, detail::ui::color_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dialog, detail::ui::dialog_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dimension, detail::ui::dimension_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dropdown_box, detail::ui::dropdown_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::fast_canvas, detail::ui::fast_canvas_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::fast_font, detail::ui::fast_font_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::fast_solid_background, detail::ui::fast_solid_background_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::image, detail::ui::image_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::label, detail::ui::label_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::link_label, detail::ui::link_label_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::list_box, detail::ui::list_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::map_box, detail::ui::map_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::menu_bar, detail::ui::menu_bar_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::mouse_capture, detail::ui::mouse_capture_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::picture_box, detail::ui::picture_box_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::point_unit_size,
                tetengo2::gui::unit::point<boost::rational<detail::ui::size_type>, detail::ui::unit_details_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::popup_menu,
                tetengo2::gui::menu::popup<
                    detail::ui::string_type,
                    detail::ui::ui_encoder_type,
                    detail::ui::menu_details_type,
                    detail::ui::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::position, detail::ui::position_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::shell, detail::ui::shell_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::side_bar, detail::ui::side_bar_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::text_box, detail::ui::text_box_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::transparent_background, detail::ui::transparent_background_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::widget, detail::ui::widget_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::widget_details_traits, detail::ui::widget_details_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::widget_traits, detail::ui::widget_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::window, detail::ui::window_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>;


    /**** Common Dialog *****************************************************/

    namespace type { namespace common_dialog
    {
        struct color;          //!< The color dialog type.
        struct file_open_dialog; //!< The file open dialog type.
        struct file_save_dialog; //!< The file save dialog type.
        struct font;           //!< The font dialog type.
        struct message_box;    //!< The message box type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace common_dialog
    {
        using string_type = boost::mpl::at<common_type_list, type::string>::type;
        using widget_traits_type = boost::mpl::at<ui_type_list, type::ui::widget_traits>::type;
        using common_dialog_details_type = boost::mpl::at<detail_type_list, type::detail::common_dialog>::type;
        using widget_details_traits_type = boost::mpl::at<ui_type_list, type::ui::widget_details_traits>::type;
        using menu_details_type = boost::mpl::at<detail_type_list, type::detail::menu>::type;
    }}
#endif

    //! The type list for the commong dialogs.
    using common_dialog_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::color,
                tetengo2::gui::common_dialog::color<
                    boost::mpl::at<ui_type_list, type::ui::color>::type,
                    detail::common_dialog::widget_traits_type,
                    detail::common_dialog::common_dialog_details_type,
                    detail::common_dialog::widget_details_traits_type,
                    detail::common_dialog::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_open_dialog,
                tetengo2::gui::common_dialog::file_open<
                    detail::common_dialog::string_type,
                    detail::common_dialog::widget_traits_type,
                    detail::common_dialog::common_dialog_details_type,
                    detail::common_dialog::widget_details_traits_type,
                    detail::common_dialog::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_save_dialog,
                tetengo2::gui::common_dialog::file_save<
                    detail::common_dialog::string_type,
                    detail::common_dialog::widget_traits_type,
                    detail::common_dialog::common_dialog_details_type,
                    detail::common_dialog::widget_details_traits_type,
                    detail::common_dialog::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::font,
                tetengo2::gui::common_dialog::font<
                    boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                    detail::common_dialog::widget_traits_type,
                    detail::common_dialog::common_dialog_details_type,
                    detail::common_dialog::widget_details_traits_type,
                    detail::common_dialog::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::message_box,
                tetengo2::gui::common_dialog::message_box<
                    detail::common_dialog::string_type,
                    detail::common_dialog::widget_traits_type,
                    detail::common_dialog::common_dialog_details_type,
                    detail::common_dialog::widget_details_traits_type,
                    detail::common_dialog::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>;


    /**** Traits *************************************************************/

    namespace type { namespace traits
    {
        struct dialog;         //!< The dialog traits.
        struct load_save;      //!< The loading and saving processing traits.
        struct view;           //!< The view traits.
        struct config;         //!< The config traits.
        struct main_window;    //!< The main window traits.
        struct command;        //!< The command traits.
        struct command_set;    //!< The command set traits.
        struct application;    //!< The application traits.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace traits
    {
        using size_type = boost::mpl::at<common_type_list, type::size>::type;
        using difference_type = boost::mpl::at<common_type_list, type::difference>::type;
        using string_type = boost::mpl::at<common_type_list, type::string>::type;
        using position_type = boost::mpl::at<ui_type_list, type::ui::position>::type;
        using dimension_type = boost::mpl::at<ui_type_list, type::ui::dimension>::type;
        using operating_distance_type = boost::mpl::at<common_type_list, type::operating_distance>::type;
        using speed_type = boost::mpl::at<common_type_list, type::speed>::type;
        using scale_type = boost::mpl::at<common_type_list, type::scale>::type;
        using fast_canvas_type = boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type;
        using fast_font_type = boost::mpl::at<ui_type_list, type::ui::fast_font>::type;
        using dialog_type = boost::mpl::at<ui_type_list, type::ui::dialog>::type;
        using abstract_window_type = boost::mpl::at<ui_type_list, type::ui::abstract_window>::type;
        using picture_box_type = boost::mpl::at<ui_type_list, type::ui::picture_box>::type;
        using mouse_capture_type = boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type;
        using message_catalog_type = boost::mpl::at<locale_type_list, type::locale::message_catalog>::type;
        using dialog_traits_type =
            dialog_traits<
                string_type,
                position_type,
                dimension_type,
                dialog_type,
                abstract_window_type,
                boost::mpl::at<ui_type_list, type::ui::label>::type,
                boost::mpl::at<ui_type_list, type::ui::link_label>::type,
                boost::mpl::at<ui_type_list, type::ui::image>::type,
                boost::mpl::at<ui_type_list, type::ui::button>::type,
                boost::mpl::at<ui_type_list, type::ui::text_box>::type,
                boost::mpl::at<ui_type_list, type::ui::list_box>::type,
                boost::mpl::at<ui_type_list, type::ui::dropdown_box>::type,
                picture_box_type,
                boost::mpl::at<ui_type_list, type::ui::transparent_background>::type,
                message_catalog_type
            >;
        using load_save_traits_type =
            bobura::load_save::traits<
                size_type,
                difference_type,
                string_type,
                boost::mpl::at<common_type_list, type::input_stream_iterator>::type,
                boost::mpl::at<common_type_list, type::output_stream>::type,
                operating_distance_type,
                speed_type,
                fast_font_type,
                abstract_window_type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_open_dialog>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
                oudia_diagram_dialog<dialog_traits_type, size_type>,
                message_catalog_type,
                boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type,
                boost::mpl::at<locale_type_list, type::locale::windia_file_encoder>::type
            >;
        using view_traits_type =
            bobura::view::diagram::traits<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                scale_type,
                fast_canvas_type,
                boost::mpl::at<ui_type_list, type::ui::fast_solid_background>::type,
                message_catalog_type
            >;
        using config_traits_type =
            config_traits<
                string_type,
                size_type,
                boost::mpl::at<locale_type_list, type::locale::config_encoder>::type,
                boost::mpl::at<detail_type_list, type::detail::config>::type
            >;
        using main_window_traits_type =
            main_window_traits<
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                operating_distance_type,
                speed_type,
                boost::mpl::at<ui_type_list, type::ui::window>::type,
                picture_box_type,
                boost::mpl::at<ui_type_list, type::ui::map_box>::type,
                boost::mpl::at<ui_type_list, type::ui::side_bar>::type,
                boost::mpl::at<ui_type_list, type::ui::popup_menu>::type,
                tetengo2::gui::message::message_loop_break<
                    boost::mpl::at<detail_type_list, type::detail::message_loop>::type
                >,
                fast_font_type,
                mouse_capture_type,
                message_catalog_type,
                view_traits_type,
                load_save_traits_type,
                config_traits_type
            >;
        using command_traits_type =
            command::traits<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                fast_font_type,
                abstract_window_type,
                mouse_capture_type
            >;
        using command_set_traits_type =
            command::set_traits<
                size_type,
                string_type,
                position_type,
                dimension_type,
                dialog_type,
                boost::mpl::at<ui_type_list, type::ui::color>::type,
                boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
                fast_canvas_type,
                scale_type,
                boost::mpl::at<ui_type_list, type::ui::shell>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::font>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::color>::type,
                message_catalog_type,
                command_traits_type,
                main_window_traits_type,
                view_traits_type,
                load_save_traits_type,
                dialog_traits_type,
                config_traits_type
            >;
        using application_traits_type =
            application_traits<string_type, position_type, dimension_type, config_traits_type>;
    }}
#endif

    //! The traits type list.
    using traits_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::dialog, detail::traits::dialog_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::load_save, detail::traits::load_save_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::view, detail::traits::view_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::config, detail::traits::config_traits_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::main_window, detail::traits::main_window_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::command, detail::traits::command_traits_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::command_set, detail::traits::command_set_traits_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::application, detail::traits::application_traits_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>;


}


#endif
