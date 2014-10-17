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

#include <bobura/command/set_traits.h>
#include <bobura/command/traits.h>
#include <bobura/config_traits.h>
#include <bobura/detail_type_list.h>
#include <bobura/diagram_view.h>
#include <bobura/dialog_traits.h>
#include <bobura/load_save/confirm_file_save.h>
#include <bobura/load_save/load_from_file.h>
#include <bobura/load_save/new_file.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/load_save/traits.h>
#include <bobura/main_window_traits.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/oudia_diagram_dialog.h>
#include <bobura/settings.h>
#include <bobura/view/diagram/traits.h>
#include <bobura/view/scale_list.h>


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
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        using size_type = std::size_t;
        using string_type = std::wstring;
        using io_string_type = std::string;
        using input_stream_iterator_type =
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;
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
        tetengo2::meta::assoc_list_end
        >>>>>;


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
        using internal_encoding_type =
            tetengo2::text::encoding::locale<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >;
        using utf8_encoding_type =
            tetengo2::text::encoding::utf8<boost::mpl::at<detail_type_list, type::detail::encoding>::type>;
        using cp932_encoding_type =
            tetengo2::text::encoding::cp932<boost::mpl::at<detail_type_list, type::detail::encoding>::type>;
        using exception_encoding_type = utf8_encoding_type;
        using ui_encoding_type =
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::widget>::type::string_type,
                boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >;
        using config_encoding_type =
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::config>::type::string_type,
                boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >;
        using message_catalog_encoding_type = utf8_encoding_type;
        using message_catalog_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>;
        using locale_name_encoding_type =
            tetengo2::text::encoding::locale<
                std::string, boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >;
        using locale_name_encoder_type = tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type>;
        using message_catalog_type =
            tetengo2::message::message_catalog<
                boost::mpl::at<common_type_list, type::input_stream_iterator>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
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
        using unit_difference_type =
            tetengo2::gui::unit::em<
                boost::rational<boost::mpl::at<common_type_list, type::difference>::type>,
                boost::mpl::at<detail_type_list, type::detail::unit>::type
            >;
        using position_type = std::pair<unit_difference_type, unit_difference_type>;
        using unit_size_type =
            tetengo2::gui::unit::em<
                boost::rational<boost::mpl::at<common_type_list, type::size>::type>,
                boost::mpl::at<detail_type_list, type::detail::unit>::type
            >;
        using dimension_type = std::pair<unit_size_type, unit_size_type>;
        using fast_solid_background_type =
            tetengo2::gui::drawing::solid_background<
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using transparent_background_type =
            tetengo2::gui::drawing::transparent_background<
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using fast_font_type =
            tetengo2::gui::drawing::font<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using canvas_traits_type =
            tetengo2::gui::drawing::canvas_traits<
                boost::mpl::at<common_type_list, type::size>::type,
                unit_size_type,
                boost::mpl::at<common_type_list, type::string>::type,
                position_type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type
            >;
        using canvas_type =
            tetengo2::gui::drawing::canvas<
                canvas_traits_type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type,
                boost::mpl::at<detail_type_list, type::detail::icon>::type

            >;
        using fast_canvas_type =
            tetengo2::gui::drawing::canvas<
                canvas_traits_type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type,
                boost::mpl::at<detail_type_list, type::detail::icon>::type
            >;
        using mouse_observer_set_type =
            tetengo2::gui::message::mouse_observer_set<
                position_type, boost::mpl::at<common_type_list, type::difference>::type
            >;
        using widget_traits_type =
            tetengo2::gui::widget::widget_traits<
                boost::mpl::at<common_type_list, type::size>::type,
                unit_size_type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                position_type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                boost::mpl::at<locale_type_list, type::locale::exception_encoder>::type
            >;
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type,
                boost::mpl::at<detail_type_list, type::detail::icon>::type,
                boost::mpl::at<detail_type_list, type::detail::alert>::type,
                boost::mpl::at<detail_type_list, type::detail::cursor>::type,
                boost::mpl::at<detail_type_list, type::detail::scroll>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
            >;
        using widget_type = tetengo2::gui::widget::widget<widget_traits_type, widget_details_traits_type>;
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<
                widget_traits_type,
                widget_details_traits_type,
                boost::mpl::at<detail_type_list, type::detail::menu>::type
            >;
        using window_type =
            tetengo2::gui::widget::window<
                widget_traits_type,
                widget_details_traits_type,
                boost::mpl::at<detail_type_list,
                type::detail::menu>::type
            >;
        using dialog_type =
            tetengo2::gui::widget::dialog<
                widget_traits_type,
                widget_details_traits_type,
                boost::mpl::at<detail_type_list, type::detail::menu>::type,
                boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >;
        using color_type = tetengo2::gui::drawing::color;
        using button_type = tetengo2::gui::widget::button<widget_traits_type, widget_details_traits_type>;
        using dropdown_box_type = tetengo2::gui::widget::dropdown_box<widget_traits_type, widget_details_traits_type>;
        using image_type = tetengo2::gui::widget::image<widget_traits_type, widget_details_traits_type>;
        using label_type = tetengo2::gui::widget::label<widget_traits_type, widget_details_traits_type>;
        using link_label_type =
            tetengo2::gui::widget::link_label<
                widget_traits_type,
                widget_details_traits_type,
                boost::mpl::at<detail_type_list, type::detail::system_color>::type, 
                boost::mpl::at<detail_type_list, type::detail::shell>::type
            >;
        using list_box_type = tetengo2::gui::widget::list_box<widget_traits_type, widget_details_traits_type>;
        using mouse_capture_type =
            tetengo2::gui::mouse_capture<
                widget_type,
                mouse_observer_set_type::mouse_button_type,
                boost::mpl::at<detail_type_list, type::detail::mouse_capture>::type
            >;
        using map_box_type =
            tetengo2::gui::widget::map_box<
                widget_traits_type,
                widget_details_traits_type,
                boost::mpl::at<detail_type_list, type::detail::mouse_capture>::type,
                boost::mpl::at<detail_type_list, type::detail::system_color>::type
            >;
        using menu_bar_type =
            tetengo2::gui::menu::menu_bar<
                boost::mpl::at<common_type_list, type::string>::type,
                tetengo2::gui::menu::shortcut_key_table<
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type,
                    boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
                >,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                boost::mpl::at<detail_type_list, type::detail::menu>::type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
            >;
        using picture_box_type =
            tetengo2::gui::widget::picture_box<
                widget_traits_type,
                widget_details_traits_type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using shell_type =
            tetengo2::gui::shell<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                boost::mpl::at<detail_type_list, type::detail::shell>::type
            >;
        using side_bar_type =
            tetengo2::gui::widget::side_bar<
                widget_traits_type,
                widget_details_traits_type,
                boost::mpl::at<detail_type_list, type::detail::mouse_capture>::type,
                boost::mpl::at<detail_type_list, type::detail::system_color>::type,
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
                tetengo2::gui::unit::point<
                    boost::rational<boost::mpl::at<common_type_list, type::size>::type>,
                    boost::mpl::at<detail_type_list, type::detail::unit>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::popup_menu,
                tetengo2::gui::menu::popup<
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type,
                    boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
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


    /**** Setting ***********************************************************/

    namespace type { namespace setting
    {
        struct config_traits;  //!< The config traits type.
        struct settings;       //!< The settings type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace setting
    {
        using config_traits_type =
            config_traits<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<locale_type_list, type::locale::config_encoder>::type,
                boost::mpl::at<detail_type_list, type::detail::config>::type
            >;
        using settings_type =
            settings<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                config_traits_type
            >;
    }}
#endif

    //! The type list for the settings.
    using setting_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::setting::config_traits, detail::setting::config_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::setting::settings, detail::setting::settings_type>,
        tetengo2::meta::assoc_list_end
        >>;


    /**** Common Dialog *****************************************************/

    namespace type { namespace common_dialog
    {
        struct color;          //!< The color dialog type.
        struct file_open_dialog; //!< The file open dialog type.
        struct file_save_dialog; //!< The file save dialog type.
        struct font;           //!< The font dialog type.
        struct message_box;    //!< The message box type.
    }}

    //! The type list for the commong dialogs.
    using common_dialog_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::color,
                tetengo2::gui::common_dialog::color<
                    boost::mpl::at<ui_type_list, type::ui::color>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_details_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_open_dialog,
                tetengo2::gui::common_dialog::file_open<
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_details_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_save_dialog,
                tetengo2::gui::common_dialog::file_save<
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_details_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::font,
                tetengo2::gui::common_dialog::font<
                    boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_details_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::message_box,
                tetengo2::gui::common_dialog::message_box<
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type,
                    boost::mpl::at<ui_type_list, type::ui::widget_details_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>;


    /**** Model *************************************************************/

    namespace type { namespace model
    {
        struct operating_distance; //!< The operating distance type.
        struct speed;          //!< The speed type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace model
    {
        using operating_distance_type = boost::rational<boost::mpl::at<common_type_list, type::size>::type>;
        using speed_type = boost::rational<boost::mpl::at<common_type_list, type::size>::type>;
    }}
#endif

    //! The model type list.
    using model_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::operating_distance, detail::model::operating_distance_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::speed, detail::model::speed_type>,
        tetengo2::meta::assoc_list_end
        >>;


    /**** View **************************************************************/

    namespace type { namespace view
    {
        struct traits;         //!< The traits type.
        struct scale;          //!< The scale type.
        struct scale_list;     //!< The scale list type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace view
    {
        using scale_type = boost::rational<boost::mpl::at<common_type_list, type::size>::type>;
        using traits_type =
            bobura::view::diagram::traits<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                boost::mpl::at<model_type_list, type::model::speed>::type,
                scale_type,
                boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_solid_background>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;
    }}
#endif

    //! The view type list.
    using view_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::view::traits, detail::view::traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::view::scale, detail::view::scale_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::view::scale_list,
                view::scale_list<
                    boost::mpl::at<common_type_list, type::size>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    detail::view::scale_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>;


    /**** Loading and Saving ************************************************/

    namespace type { namespace load_save
    {
        struct traits;         //!< The traits.
        struct new_file;       //!< The file initialization.
        struct load_from_file; //!< The file loading.
        struct save_to_file;   //!< The file saving.
        struct confirm_file_save; //!< The file save confirmation.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace load_save
    {
        using dialog_traits_type =
            dialog_traits<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<ui_type_list, type::ui::label>::type,
                boost::mpl::at<ui_type_list, type::ui::link_label>::type,
                boost::mpl::at<ui_type_list, type::ui::image>::type,
                boost::mpl::at<ui_type_list, type::ui::button>::type,
                boost::mpl::at<ui_type_list, type::ui::text_box>::type,
                boost::mpl::at<ui_type_list, type::ui::list_box>::type,
                boost::mpl::at<ui_type_list, type::ui::dropdown_box>::type,
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<ui_type_list, type::ui::transparent_background>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;
        using oudia_diagram_dialog_type =
            oudia_diagram_dialog<dialog_traits_type, boost::mpl::at<common_type_list, type::size>::type>;
        using traits_type =
            bobura::load_save::traits<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::input_stream_iterator>::type,
                boost::mpl::at<common_type_list, type::output_stream>::type,
                boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                boost::mpl::at<model_type_list, type::model::speed>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_open_dialog>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
                oudia_diagram_dialog_type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type,
                boost::mpl::at<locale_type_list, type::locale::windia_file_encoder>::type
            >;
    }}
#endif

    //! The loading and saving processing type list.
    using load_save_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::load_save::traits, detail::load_save::traits_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::load_save::new_file, load_save::new_file<detail::load_save::traits_type>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::load_save::load_from_file, load_save::load_from_file<detail::load_save::traits_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::load_save::save_to_file, load_save::save_to_file<detail::load_save::traits_type>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::load_save::confirm_file_save, load_save::confirm_file_save<detail::load_save::traits_type>
            >,
        tetengo2::meta::assoc_list_end
        >>>>>;


    /**** Traits *************************************************************/

    namespace type { namespace traits
    {
        struct dialog;         //!< The dialog traits.
        struct main_window;    //!< The main window traits.
        struct command;        //!< The command traits.
        struct command_set;    //!< The command set traits.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace traits
    {
        using dialog_traits_type =
            dialog_traits<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<ui_type_list, type::ui::label>::type,
                boost::mpl::at<ui_type_list, type::ui::link_label>::type,
                boost::mpl::at<ui_type_list, type::ui::image>::type,
                boost::mpl::at<ui_type_list, type::ui::button>::type,
                boost::mpl::at<ui_type_list, type::ui::text_box>::type,
                boost::mpl::at<ui_type_list, type::ui::list_box>::type,
                boost::mpl::at<ui_type_list, type::ui::dropdown_box>::type,
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<ui_type_list, type::ui::transparent_background>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;
        using main_window_traits_type =
            main_window_traits<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                boost::mpl::at<model_type_list, type::model::speed>::type,
                boost::mpl::at<ui_type_list, type::ui::window>::type,
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<ui_type_list, type::ui::map_box>::type,
                boost::mpl::at<ui_type_list, type::ui::side_bar>::type,
                boost::mpl::at<ui_type_list, type::ui::popup_menu>::type,
                tetengo2::gui::message::message_loop_break<
                    boost::mpl::at<detail_type_list, type::detail::message_loop>::type
                >,
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                boost::mpl::at<view_type_list, type::view::traits>::type,
                boost::mpl::at<load_save_type_list, type::load_save::traits>::type,
                boost::mpl::at<setting_type_list, type::setting::config_traits>::type
            >;
        using command_traits_type =
            command::traits<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                boost::mpl::at<model_type_list, type::model::speed>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type
            >;
        using command_set_traits_type =
            command::set_traits<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                boost::mpl::at<ui_type_list, type::ui::color>::type,
                boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                boost::mpl::at<view_type_list, type::view::scale>::type,
                boost::mpl::at<ui_type_list, type::ui::shell>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::font>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::color>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                command_traits_type,
                main_window_traits_type,
                boost::mpl::at<view_type_list, type::view::traits>::type,
                boost::mpl::at<load_save_type_list, type::load_save::traits>::type,
                dialog_traits_type,
                boost::mpl::at<setting_type_list, type::setting::config_traits>::type
            >;
    }}
#endif

    //! The traits type list.
    using traits_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::dialog, detail::traits::dialog_traits_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::main_window, detail::traits::main_window_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::command, detail::traits::command_traits_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::command_set, detail::traits::command_set_traits_type>,
        tetengo2::meta::assoc_list_end
        >>>>;


}


#endif
