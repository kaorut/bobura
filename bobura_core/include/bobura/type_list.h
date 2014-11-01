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
        using difference_type = std::ptrdiff_t;

        using size_type = std::size_t;

        using string_type = std::wstring;

        using io_string_type = std::string;

        using input_stream_iterator_type =
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;

        using output_stream_type = std::basic_ostream<io_string_type::value_type>;

        using operating_distance_type = boost::rational<size_type>;

        using speed_type = boost::rational<size_type>;

        using scale_type = boost::rational<size_type>;

    }
#endif

    /*!
        \brief The common type list.
    */
    using common_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, detail::difference_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, bobura::detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::input_stream_iterator, detail::input_stream_iterator_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::output_stream, detail::output_stream_type>,
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
        using string_type = bobura::detail::string_type;

        template <typename DetailTypeList>
        using encoding_details_type = typename boost::mpl::at<DetailTypeList, type::detail::encoding>::type;

        template <typename DetailTypeList>
        using internal_encoding_type =
            tetengo2::text::encoding::locale<string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using utf8_encoding_type = tetengo2::text::encoding::utf8<encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using cp932_encoding_type = tetengo2::text::encoding::cp932<encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using exception_encoding_type = utf8_encoding_type<DetailTypeList>;

        template <typename DetailTypeList>
        using exception_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, exception_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using ui_encoding_type =
            tetengo2::text::encoding::locale<
                typename boost::mpl::at<DetailTypeList, type::detail::widget>::type::string_type,
                encoding_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using ui_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, ui_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using config_encoding_type =
            tetengo2::text::encoding::locale<
                typename boost::mpl::at<DetailTypeList, type::detail::config>::type::string_type,
                encoding_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using config_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, config_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using message_catalog_encoding_type = utf8_encoding_type<DetailTypeList>;

        template <typename DetailTypeList>
        using message_catalog_encoder_type =
            tetengo2::text::encoder<
                internal_encoding_type<DetailTypeList>, message_catalog_encoding_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using locale_name_encoding_type =
            tetengo2::text::encoding::locale<std::string, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using locale_name_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, locale_name_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using message_catalog_type =
            tetengo2::message::message_catalog<
                bobura::detail::input_stream_iterator_type,
                string_type,
                size_type,
                message_catalog_encoder_type<DetailTypeList>,
                locale_name_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using timetable_file_encoding_type = utf8_encoding_type<DetailTypeList>;

        template <typename DetailTypeList>
        using timetable_file_encoder_type =
            tetengo2::text::encoder<
                internal_encoding_type<DetailTypeList>, timetable_file_encoding_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using windia_file_encoding_type = cp932_encoding_type<DetailTypeList>;

        template <typename DetailTypeList>
        using windia_file_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, windia_file_encoding_type<DetailTypeList>>;

    }}
#endif

    /*!
        \brief The locale type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    using locale_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::exception_encoder, detail::locale::exception_encoder_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::config_encoder, detail::locale::config_encoder_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::ui_encoder, detail::locale::ui_encoder_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::message_catalog_encoder, detail::locale::message_catalog_encoder_type<DetailTypeList>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::locale_name_encoder, detail::locale::locale_name_encoder_type<DetailTypeList>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::message_catalog, detail::locale::message_catalog_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::timetable_file_encoder, detail::locale::timetable_file_encoder_type<DetailTypeList>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::windia_file_encoder, detail::locale::windia_file_encoder_type<DetailTypeList>
            >,
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
        using size_type = bobura::detail::size_type;

        using difference_type = bobura::detail::difference_type;

        using string_type = bobura::detail::string_type;

        template <typename DetailTypeList>
        using ui_encoder_type = bobura::detail::locale::ui_encoder_type<DetailTypeList>;

        template <typename DetailTypeList>
        using unit_details_type = typename boost::mpl::at<DetailTypeList, type::detail::unit>::type;

        template <typename DetailTypeList>
        using drawing_details_type = typename boost::mpl::at<DetailTypeList, type::detail::drawing>::type;

        template <typename DetailTypeList>
        using fast_drawing_details_type = typename boost::mpl::at<DetailTypeList, type::detail::fast_drawing>::type;

        template <typename DetailTypeList>
        using icon_details_type = typename boost::mpl::at<DetailTypeList, type::detail::icon>::type;

        template <typename DetailTypeList>
        using virtual_key_details_type = typename boost::mpl::at<DetailTypeList, type::detail::virtual_key>::type;

        template <typename DetailTypeList>
        using menu_details_type = typename boost::mpl::at<DetailTypeList, type::detail::menu>::type;

        template <typename DetailTypeList>
        using shell_details_type = typename boost::mpl::at<DetailTypeList, type::detail::shell>::type;

        template <typename DetailTypeList>
        using system_color_details_type =
            typename boost::mpl::at<DetailTypeList, type::detail::system_color>::type;

        template <typename DetailTypeList>
        using mouse_capture_details_type = typename boost::mpl::at<DetailTypeList, type::detail::mouse_capture>::type;

        template <typename DetailTypeList>
        using unit_difference_type =
            tetengo2::gui::unit::em<boost::rational<difference_type>, unit_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using position_type = std::pair<unit_difference_type<DetailTypeList>, unit_difference_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using unit_size_type =
            tetengo2::gui::unit::em<boost::rational<size_type>, unit_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using dimension_type = std::pair<unit_size_type<DetailTypeList>, unit_size_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using fast_solid_background_type =
            tetengo2::gui::drawing::solid_background<fast_drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using transparent_background_type =
            tetengo2::gui::drawing::transparent_background<drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using fast_font_type =
            tetengo2::gui::drawing::font<string_type, size_type, fast_drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using canvas_traits_type =
            tetengo2::gui::drawing::canvas_traits<
                size_type,
                unit_size_type<DetailTypeList>,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                ui_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using canvas_type =
            tetengo2::gui::drawing::canvas<
                canvas_traits_type<DetailTypeList>,
                drawing_details_type<DetailTypeList>,
                icon_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using fast_canvas_type =
            tetengo2::gui::drawing::canvas<
                canvas_traits_type<DetailTypeList>,
                fast_drawing_details_type<DetailTypeList>,
                icon_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using mouse_observer_set_type = 
            tetengo2::gui::message::mouse_observer_set<position_type<DetailTypeList>, difference_type>;

        template <typename DetailTypeList>
        using widget_traits_type =
            tetengo2::gui::widget::widget_traits<
                size_type,
                unit_size_type<DetailTypeList>,
                difference_type,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                ui_encoder_type<DetailTypeList>,
                bobura::detail::locale::exception_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                typename boost::mpl::at<DetailTypeList, type::detail::widget>::type,
                drawing_details_type<DetailTypeList>,
                icon_details_type<DetailTypeList>,
                typename boost::mpl::at<DetailTypeList, type::detail::alert>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::cursor>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::scroll>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::message_handler>::type,
                virtual_key_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using widget_type =
            tetengo2::gui::widget::widget<
                widget_traits_type<DetailTypeList>, widget_details_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<
                widget_traits_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using window_type =
            tetengo2::gui::widget::window<
                widget_traits_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using dialog_type =
            tetengo2::gui::widget::dialog<
                widget_traits_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>,
                typename boost::mpl::at<DetailTypeList, type::detail::message_loop>::type
            >;

        using color_type = tetengo2::gui::drawing::color;

        template <typename DetailTypeList>
        using button_type =
            tetengo2::gui::widget::button<
                widget_traits_type<DetailTypeList>, widget_details_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using dropdown_box_type =
            tetengo2::gui::widget::dropdown_box<
                widget_traits_type<DetailTypeList>, widget_details_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using image_type =
            tetengo2::gui::widget::image<
                widget_traits_type<DetailTypeList>, widget_details_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using label_type =
            tetengo2::gui::widget::label<
                widget_traits_type<DetailTypeList>, widget_details_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using link_label_type =
            tetengo2::gui::widget::link_label<
                widget_traits_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                system_color_details_type<DetailTypeList>,
                shell_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using list_box_type =
            tetengo2::gui::widget::list_box<
                widget_traits_type<DetailTypeList>, widget_details_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using mouse_capture_type =
            tetengo2::gui::mouse_capture<
                widget_type<DetailTypeList>,
                typename mouse_observer_set_type<DetailTypeList>::mouse_button_type,
                mouse_capture_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using map_box_type =
            tetengo2::gui::widget::map_box<
                widget_traits_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                mouse_capture_details_type<DetailTypeList>,
                system_color_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using menu_bar_type =
            tetengo2::gui::menu::menu_bar<
                string_type,
                tetengo2::gui::menu::shortcut_key_table<
                    string_type,
                    ui_encoder_type<DetailTypeList>,
                    menu_details_type<DetailTypeList>,
                    virtual_key_details_type<DetailTypeList>
                >,
                ui_encoder_type<DetailTypeList>,
                menu_details_type<DetailTypeList>,
                virtual_key_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using picture_box_type =
            tetengo2::gui::widget::picture_box<
                widget_traits_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                fast_drawing_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using point_unit_size_type =
            tetengo2::gui::unit::point<boost::rational<size_type>, unit_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using popup_menu_type =
            tetengo2::gui::menu::popup<
                string_type,
                ui_encoder_type<DetailTypeList>,
                menu_details_type<DetailTypeList>,
                virtual_key_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using shell_type =
            tetengo2::gui::shell<string_type, ui_encoder_type<DetailTypeList>, shell_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using side_bar_type =
            tetengo2::gui::widget::side_bar<
                widget_traits_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                mouse_capture_details_type<DetailTypeList>,
                system_color_details_type<DetailTypeList>,
                typename boost::mpl::at<DetailTypeList, type::detail::timer>::type
            >;

        template <typename DetailTypeList>
        using text_box_type =
            tetengo2::gui::widget::text_box<
                widget_traits_type<DetailTypeList>, widget_details_traits_type<DetailTypeList>
            >;

    }}
#endif

    /*!
        \brief The locale type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    using ui_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::abstract_window, detail::ui::abstract_window_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::button, detail::ui::button_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::canvas, detail::ui::canvas_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::color, detail::ui::color_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dialog, detail::ui::dialog_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dimension, detail::ui::dimension_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::dropdown_box, detail::ui::dropdown_box_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::fast_canvas, detail::ui::fast_canvas_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::fast_font, detail::ui::fast_font_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::fast_solid_background, detail::ui::fast_solid_background_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::image, detail::ui::image_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::label, detail::ui::label_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::link_label, detail::ui::link_label_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::list_box, detail::ui::list_box_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::map_box, detail::ui::map_box_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::menu_bar, detail::ui::menu_bar_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::mouse_capture, detail::ui::mouse_capture_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::picture_box, detail::ui::picture_box_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::point_unit_size, detail::ui::point_unit_size_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::popup_menu, detail::ui::popup_menu_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::position, detail::ui::position_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::shell, detail::ui::shell_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::side_bar, detail::ui::side_bar_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::text_box, detail::ui::text_box_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::transparent_background, detail::ui::transparent_background_type<DetailTypeList>
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::widget, detail::ui::widget_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::widget_details_traits, detail::ui::widget_details_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::widget_traits, detail::ui::widget_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::window, detail::ui::window_type<DetailTypeList>>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>;


    /**** Common Dialog *****************************************************/

    namespace type { namespace common_dialog
    {
        struct color;          //!< The color dialog type.
        struct file_open;      //!< The file open dialog type.
        struct file_save;      //!< The file save dialog type.
        struct font;           //!< The font dialog type.
        struct message_box;    //!< The message box type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace common_dialog
    {
        using string_type = bobura::detail::string_type;

        template <typename DetailTypeList>
        using widget_traits_type = bobura::detail::ui::widget_traits_type<DetailTypeList>;

        template <typename DetailTypeList>
        using common_dialog_details_type = typename boost::mpl::at<DetailTypeList, type::detail::common_dialog>::type;

        template <typename DetailTypeList>
        using widget_details_traits_type = bobura::detail::ui::widget_details_traits_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_details_type = typename boost::mpl::at<DetailTypeList, type::detail::menu>::type;

        template <typename DetailTypeList>
        using color_type =
            tetengo2::gui::common_dialog::color<
                bobura::detail::ui::color_type,
                widget_traits_type<DetailTypeList>,
                common_dialog_details_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using file_open_type =
            tetengo2::gui::common_dialog::file_open<
                string_type,
                widget_traits_type<DetailTypeList>,
                common_dialog_details_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using file_save_type =
            tetengo2::gui::common_dialog::file_save<
                string_type,
                widget_traits_type<DetailTypeList>,
                common_dialog_details_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using font_type =
            tetengo2::gui::common_dialog::font<
                bobura::detail::ui::fast_font_type<DetailTypeList>,
                widget_traits_type<DetailTypeList>,
                common_dialog_details_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using message_box_type =
            tetengo2::gui::common_dialog::message_box<
                string_type,
                widget_traits_type<DetailTypeList>,
                common_dialog_details_type<DetailTypeList>,
                widget_details_traits_type<DetailTypeList>,
                menu_details_type<DetailTypeList>
            >;

    }}
#endif

    /*!
        \brief The common dialog type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    using common_dialog_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::common_dialog::color, detail::common_dialog::color_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::common_dialog::file_open, detail::common_dialog::file_open_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::common_dialog::file_save, detail::common_dialog::file_save_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::common_dialog::font,  detail::common_dialog::font_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::message_box,  detail::common_dialog::message_box_type<DetailTypeList>
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
        using size_type = bobura::detail::size_type;

        using difference_type = bobura::detail::difference_type;

        using string_type = bobura::detail::string_type;

        using position_type = bobura::detail::ui::position_type<detail_type_list>;

        using dimension_type = bobura::detail::ui::dimension_type<detail_type_list>;

        using operating_distance_type = bobura::detail::operating_distance_type;

        using speed_type = bobura::detail::speed_type;

        using scale_type = bobura::detail::scale_type;

        using fast_canvas_type = bobura::detail::ui::fast_canvas_type<detail_type_list>;

        using fast_font_type = bobura::detail::ui::fast_font_type<detail_type_list>;

        using dialog_type = bobura::detail::ui::dialog_type<detail_type_list>;

        using abstract_window_type = bobura::detail::ui::abstract_window_type<detail_type_list>;

        using picture_box_type = bobura::detail::ui::picture_box_type<detail_type_list>;

        using mouse_capture_type = bobura::detail::ui::mouse_capture_type<detail_type_list>;

        using message_catalog_type = bobura::detail::locale::message_catalog_type<detail_type_list>;

        using dialog_traits_type =
            dialog_traits<
                string_type,
                position_type,
                dimension_type,
                dialog_type,
                abstract_window_type,
                bobura::detail::ui::label_type<detail_type_list>,
                bobura::detail::ui::link_label_type<detail_type_list>,
                bobura::detail::ui::image_type<detail_type_list>,
                bobura::detail::ui::button_type<detail_type_list>,
                bobura::detail::ui::text_box_type<detail_type_list>,
                bobura::detail::ui::list_box_type<detail_type_list>,
                bobura::detail::ui::dropdown_box_type<detail_type_list>,
                picture_box_type,
                bobura::detail::ui::transparent_background_type<detail_type_list>,
                message_catalog_type
            >;

        using load_save_traits_type =
            bobura::load_save::traits<
                size_type,
                difference_type,
                string_type,
                bobura::detail::input_stream_iterator_type,
                bobura::detail::output_stream_type,
                operating_distance_type,
                speed_type,
                fast_font_type,
                abstract_window_type,
                bobura::detail::common_dialog::message_box_type<detail_type_list>,
                bobura::detail::common_dialog::file_open_type<detail_type_list>,
                bobura::detail::common_dialog::file_save_type<detail_type_list>,
                oudia_diagram_dialog<dialog_traits_type, size_type>,
                message_catalog_type,
                bobura::detail::locale::timetable_file_encoder_type<detail_type_list>,
                bobura::detail::locale::windia_file_encoder_type<detail_type_list>
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
                bobura::detail::ui::fast_solid_background_type<detail_type_list>,
                message_catalog_type
            >;

        using config_traits_type =
            config_traits<
                string_type,
                size_type,
                bobura::detail::locale::config_encoder_type<detail_type_list>,
                boost::mpl::at<detail_type_list, type::detail::config>::type
            >;

        using map_box_type = bobura::detail::ui::map_box_type<detail_type_list>;

        using side_bar_type = bobura::detail::ui::side_bar_type<detail_type_list>;

        using popup_menu_type = bobura::detail::ui::popup_menu_type<detail_type_list>;

        using message_loop_details_type = boost::mpl::at<detail_type_list, type::detail::message_loop>::type;

        using main_window_traits_type =
            main_window_traits<
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                operating_distance_type,
                speed_type,
                bobura::detail::ui::window_type<detail_type_list>,
                picture_box_type,
                map_box_type,
                side_bar_type,
                popup_menu_type,
                tetengo2::gui::message::message_loop_break<message_loop_details_type>,
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
                bobura::detail::ui::color_type,
                bobura::detail::ui::point_unit_size_type<detail_type_list>,
                fast_canvas_type,
                scale_type,
                bobura::detail::ui::shell_type<detail_type_list>,
                bobura::detail::common_dialog::font_type<detail_type_list>,
                bobura::detail::common_dialog::color_type<detail_type_list>,
                message_catalog_type,
                command_traits_type,
                main_window_traits_type,
                view_traits_type,
                load_save_traits_type,
                dialog_traits_type,
                config_traits_type
            >;

        using gui_fixture_type =
            tetengo2::gui::fixture<boost::mpl::at<detail_type_list, type::detail::gui_fixture>::type>;

        using message_loop_type =
            tetengo2::gui::message::message_loop<abstract_window_type, message_loop_details_type>;

        using timer_type =
            tetengo2::gui::timer<
                bobura::detail::ui::widget_type<detail_type_list>,
                boost::mpl::at<detail_type_list, type::detail::timer>::type
            >;

        using application_traits_type =
            application_traits<
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                operating_distance_type,
                speed_type,
                scale_type,
                gui_fixture_type,
                fast_font_type,
                abstract_window_type,
                picture_box_type,
                map_box_type,
                side_bar_type,
                bobura::detail::ui::menu_bar_type<detail_type_list>,
                popup_menu_type,
                message_loop_type,
                mouse_capture_type,
                timer_type,
                message_catalog_type,
                main_window_traits_type,
                view_traits_type,
                load_save_traits_type,
                command_set_traits_type,
                config_traits_type
            >;

    }}
#endif

    /*!
        \brief The traits type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
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
