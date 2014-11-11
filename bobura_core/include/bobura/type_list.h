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
#include <bobura/main_window_menu_builder_traits.h>
#include <bobura/oudia_diagram_dialog.h>
#include <bobura/view/diagram/traits.h>


namespace bobura { namespace type_list_temp
{
    /**** Common *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace common
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

    }}
#endif

    /*!
        \brief The common type list.
    */
    struct common
    {
        //! The difference type.
        using difference_type = detail::common::difference_type;

        //! The size type.
        using size_type = detail::common::size_type;

        //! The string type.
        using string_type = detail::common::string_type;

        //! The input stream iterator type.
        using input_stream_iterator_type = detail::common::input_stream_iterator_type;

        //! The output stream type.
        using output_stream_type = detail::common::output_stream_type;

        //! The operating distance type.
        using operating_distance_type = detail::common::operating_distance_type;

        //! The speed type.
        using speed_type = detail::common::speed_type;

        //! The scale type.
        using scale_type = detail::common::scale_type;

    };


    /**** Locale *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace locale
    {
        using size_type = type_list_temp::detail::common::size_type;

        using string_type = type_list_temp::detail::common::string_type;

        template <typename DetailTypeList>
        using encoding_details_type = typename DetailTypeList::encoding_type;

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
                typename DetailTypeList::widget_type::string_type, encoding_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using ui_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, ui_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using config_encoding_type =
            tetengo2::text::encoding::locale<
                typename DetailTypeList::config_type::string_type, encoding_details_type<DetailTypeList>
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
                type_list_temp::detail::common::input_stream_iterator_type,
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
    struct locale
    {
        //! The encoder type for exceptions.
        using exception_encoder_type = detail::locale::exception_encoder_type<DetailTypeList>;

        //! The encoder type for the user interface.
        using ui_encoder_type = detail::locale::ui_encoder_type<DetailTypeList>;

        //! The encoder type for the user interface.
        using config_encoder_type = detail::locale::config_encoder_type<DetailTypeList>;

        //! The message catalog encoder type.
        using message_catalog_encoder_type = detail::locale::message_catalog_encoder_type<DetailTypeList>;

        //! The locale name encoder type.
        using locale_name_encoder_type = detail::locale::locale_name_encoder_type<DetailTypeList>;

        //! The message catalog type.
        using message_catalog_type = detail::locale::message_catalog_type<DetailTypeList>;

        //! The encoder type for the timetable file.
        using timetable_file_encoder_type = detail::locale::timetable_file_encoder_type<DetailTypeList>;

        //! The encoder type for the WinDIA file.
        using windia_file_encoder_type = detail::locale::windia_file_encoder_type<DetailTypeList>;

    };


    /**** User Interface *********************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        using size_type = type_list_temp::detail::common::size_type;

        using difference_type = type_list_temp::detail::common::difference_type;

        using string_type = type_list_temp::detail::common::string_type;

        template <typename DetailTypeList>
        using ui_encoder_type = type_list_temp::detail::locale::ui_encoder_type<DetailTypeList>;

        template <typename DetailTypeList>
        using unit_details_type = typename DetailTypeList::unit_type;

        template <typename DetailTypeList>
        using drawing_details_type = typename DetailTypeList::drawing_type;

        template <typename DetailTypeList>
        using fast_drawing_details_type = typename DetailTypeList::fast_drawing_type;

        template <typename DetailTypeList>
        using icon_details_type = typename DetailTypeList::icon_type;

        template <typename DetailTypeList>
        using virtual_key_details_type = typename DetailTypeList::virtual_key_type;

        template <typename DetailTypeList>
        using menu_details_type = typename DetailTypeList::menu_type;

        template <typename DetailTypeList>
        using shell_details_type = typename DetailTypeList::shell_type;

        template <typename DetailTypeList>
        using system_color_details_type = typename DetailTypeList::system_color_type;

        template <typename DetailTypeList>
        using mouse_capture_details_type = typename DetailTypeList::mouse_capture_type;

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
                type_list_temp::detail::locale::exception_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                typename DetailTypeList::widget_type,
                drawing_details_type<DetailTypeList>,
                icon_details_type<DetailTypeList>,
                typename DetailTypeList::alert_type,
                typename DetailTypeList::cursor_type,
                typename DetailTypeList::scroll_type,
                typename DetailTypeList::message_handler_type,
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
                typename DetailTypeList::message_loop_type
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
        using menu_command_type =
            tetengo2::gui::menu::command<
                string_type,
                ui_encoder_type<DetailTypeList>,
                menu_details_type<DetailTypeList>,
                virtual_key_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using menu_separator_type =
            tetengo2::gui::menu::separator<
                string_type,
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
                typename DetailTypeList::timer_type
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
    struct ui
    {
        //! The abstract window type.
        using abstract_window_type = detail::ui::abstract_window_type<DetailTypeList>;

        //! The button type.
        using button_type = detail::ui::button_type<DetailTypeList>;

        //! The canvas type.
        using canvas_type = detail::ui::canvas_type<DetailTypeList>;

        //! The color type.
        using color_type = detail::ui::color_type;

        //! The dialog type.
        using dialog_type = detail::ui::dialog_type<DetailTypeList>;

        //! The dimension type.
        using dimension_type = detail::ui::dimension_type<DetailTypeList>;

        //! The dropdown box type.
        using dropdown_box_type = detail::ui::dropdown_box_type<DetailTypeList>;

        //! The fast canvas type.
        using fast_canvas_type = detail::ui::fast_canvas_type<DetailTypeList>;

        //! The fast font type.
        using fast_font_type = detail::ui::fast_font_type<DetailTypeList>;

        //! The fast solid background type.
        using fast_solid_background_type = detail::ui::fast_solid_background_type<DetailTypeList>;

        //! The image type.
        using image_type = detail::ui::image_type<DetailTypeList>;

        //! The label type.
        using label_type = detail::ui::label_type<DetailTypeList>;

        //! The link label type.
        using link_label_type = detail::ui::link_label_type<DetailTypeList>;

        //! The list box type.
        using list_box_type = detail::ui::list_box_type<DetailTypeList>;

        //! The map box type.
        using map_box_type = detail::ui::map_box_type<DetailTypeList>;

        //! The menu bar type.
        using menu_bar_type = detail::ui::menu_bar_type<DetailTypeList>;

        //! The menu command type.
        using menu_command_type = detail::ui::menu_command_type<DetailTypeList>;

        //! The menu separator type.
        using menu_separator_type = detail::ui::menu_separator_type<DetailTypeList>;

        //! The mouse capture type.
        using mouse_capture_type = detail::ui::mouse_capture_type<DetailTypeList>;

        //! The picture box type.
        using picture_box_type = detail::ui::picture_box_type<DetailTypeList>;

        //! The point unit size type.
        using point_unit_size_type = detail::ui::point_unit_size_type<DetailTypeList>;

        //! The popup menu type.
        using popup_menu_type = detail::ui::popup_menu_type<DetailTypeList>;

        //! The position type.
        using position_type = detail::ui::position_type<DetailTypeList>;

        //! The shell type.
        using shell_type = detail::ui::shell_type<DetailTypeList>;

        //! The side bar type.
        using side_bar_type = detail::ui::side_bar_type<DetailTypeList>;

        //! The text box type.
        using text_box_type = detail::ui::text_box_type<DetailTypeList>;

        //! The transparent background type.
        using transparent_background_type = detail::ui::transparent_background_type<DetailTypeList>;

        //! The widget type.
        using widget_type = detail::ui::widget_type<DetailTypeList>;

        //! The widget details traits type.
        using widget_details_traits_type = detail::ui::widget_details_traits_type<DetailTypeList>;

        //! The widget traits type.
        using widget_traits_type = detail::ui::widget_traits_type<DetailTypeList>;

        //! The window type.
        using window_type = detail::ui::window_type<DetailTypeList>;


    };


    /**** Common Dialog **********************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace common_dialog
    {
        using string_type = type_list_temp::detail::common::string_type;

        template <typename DetailTypeList>
        using widget_traits_type = type_list_temp::detail::ui::widget_traits_type<DetailTypeList>;

        template <typename DetailTypeList>
        using common_dialog_details_type = typename DetailTypeList::common_dialog_type;

        template <typename DetailTypeList>
        using widget_details_traits_type = type_list_temp::detail::ui::widget_details_traits_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_details_type = typename DetailTypeList::menu_type;

        template <typename DetailTypeList>
        using color_type =
            tetengo2::gui::common_dialog::color<
                type_list_temp::detail::ui::color_type,
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
                type_list_temp::detail::ui::fast_font_type<DetailTypeList>,
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
    struct common_dialog
    {
        //! The color dialog type.
        using color_type = detail::common_dialog::color_type<DetailTypeList>;

        //! The file open dialog type.
        using file_open_type = detail::common_dialog::file_open_type<DetailTypeList>;

        //! The file save dialog type.
        using file_save_type = detail::common_dialog::file_save_type<DetailTypeList>;

        //! The font dialog type.
        using font_type = detail::common_dialog::font_type<DetailTypeList>;

        //! The message box type.
        using message_box_type = detail::common_dialog::message_box_type<DetailTypeList>;


    };


    /**** Traits *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace traits
    {
        using size_type = type_list_temp::detail::common::size_type;

        using difference_type = type_list_temp::detail::common::difference_type;

        using string_type = type_list_temp::detail::common::string_type;

        template <typename DetailTypeList>
        using position_type = type_list_temp::detail::ui::position_type<DetailTypeList>;

        template <typename DetailTypeList>
        using dimension_type = type_list_temp::detail::ui::dimension_type<DetailTypeList>;

        using operating_distance_type = type_list_temp::detail::common::operating_distance_type;

        using speed_type = type_list_temp::detail::common::speed_type;

        using scale_type = type_list_temp::detail::common::scale_type;

        template <typename DetailTypeList>
        using fast_canvas_type = type_list_temp::detail::ui::fast_canvas_type<DetailTypeList>;

        template <typename DetailTypeList>
        using fast_font_type = type_list_temp::detail::ui::fast_font_type<DetailTypeList>;

        template <typename DetailTypeList>
        using dialog_type = type_list_temp::detail::ui::dialog_type<DetailTypeList>;

        template <typename DetailTypeList>
        using abstract_window_type = type_list_temp::detail::ui::abstract_window_type<DetailTypeList>;

        template <typename DetailTypeList>
        using picture_box_type = type_list_temp::detail::ui::picture_box_type<DetailTypeList>;

        template <typename DetailTypeList>
        using mouse_capture_type = type_list_temp::detail::ui::mouse_capture_type<DetailTypeList>;

        template <typename DetailTypeList>
        using message_catalog_type = type_list_temp::detail::locale::message_catalog_type<DetailTypeList>;

        template <typename DetailTypeList>
        using dialog_traits_type =
            dialog_traits<
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                dialog_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                type_list_temp::detail::ui::label_type<DetailTypeList>,
                type_list_temp::detail::ui::link_label_type<DetailTypeList>,
                type_list_temp::detail::ui::image_type<DetailTypeList>,
                type_list_temp::detail::ui::button_type<DetailTypeList>,
                type_list_temp::detail::ui::text_box_type<DetailTypeList>,
                type_list_temp::detail::ui::list_box_type<DetailTypeList>,
                type_list_temp::detail::ui::dropdown_box_type<DetailTypeList>,
                picture_box_type<DetailTypeList>,
                type_list_temp::detail::ui::transparent_background_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using load_save_traits_type =
            bobura::load_save::traits<
                size_type,
                difference_type,
                string_type,
                type_list_temp::detail::common::input_stream_iterator_type,
                type_list_temp::detail::common::output_stream_type,
                operating_distance_type,
                speed_type,
                fast_font_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                type_list_temp::detail::common_dialog::message_box_type<DetailTypeList>,
                type_list_temp::detail::common_dialog::file_open_type<DetailTypeList>,
                type_list_temp::detail::common_dialog::file_save_type<DetailTypeList>,
                oudia_diagram_dialog<dialog_traits_type<DetailTypeList>, size_type>,
                message_catalog_type<DetailTypeList>,
                type_list_temp::detail::locale::timetable_file_encoder_type<DetailTypeList>,
                type_list_temp::detail::locale::windia_file_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using view_traits_type =
            bobura::view::diagram::traits<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                scale_type,
                fast_canvas_type<DetailTypeList>,
                type_list_temp::detail::ui::fast_solid_background_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using config_traits_type =
            config_traits<
                string_type,
                size_type,
                type_list_temp::detail::locale::config_encoder_type<DetailTypeList>,
                typename DetailTypeList::config_type
            >;

        template <typename DetailTypeList>
        using map_box_type = type_list_temp::detail::ui::map_box_type<DetailTypeList>;

        template <typename DetailTypeList>
        using side_bar_type = type_list_temp::detail::ui::side_bar_type<DetailTypeList>;

        template <typename DetailTypeList>
        using popup_menu_type = type_list_temp::detail::ui::popup_menu_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_command_type = type_list_temp::detail::ui::menu_command_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_separator_type = type_list_temp::detail::ui::menu_separator_type<DetailTypeList>;

        template <typename DetailTypeList>
        using message_loop_details_type = typename DetailTypeList::message_loop_type;

        template <typename DetailTypeList>
        using main_window_traits_type =
            main_window_traits<
                size_type,
                difference_type,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                operating_distance_type,
                speed_type,
                type_list_temp::detail::ui::window_type<DetailTypeList>,
                picture_box_type<DetailTypeList>,
                map_box_type<DetailTypeList>,
                side_bar_type<DetailTypeList>,
                popup_menu_type<DetailTypeList>,
                tetengo2::gui::message::message_loop_break<message_loop_details_type<DetailTypeList>>,
                fast_font_type<DetailTypeList>,
                mouse_capture_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>,
                view_traits_type<DetailTypeList>,
                load_save_traits_type<DetailTypeList>,
                config_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using command_traits_type =
            command::traits<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                fast_font_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                mouse_capture_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using command_set_traits_type =
            command::set_traits<
                size_type,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                dialog_type<DetailTypeList>,
                type_list_temp::detail::ui::color_type,
                type_list_temp::detail::ui::point_unit_size_type<DetailTypeList>,
                fast_canvas_type<DetailTypeList>,
                scale_type,
                type_list_temp::detail::ui::shell_type<DetailTypeList>,
                type_list_temp::detail::common_dialog::font_type<DetailTypeList>,
                type_list_temp::detail::common_dialog::color_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>,
                command_traits_type<DetailTypeList>,
                main_window_traits_type<DetailTypeList>,
                view_traits_type<DetailTypeList>,
                load_save_traits_type<DetailTypeList>,
                dialog_traits_type<DetailTypeList>,
                config_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using gui_fixture_type = tetengo2::gui::fixture<typename DetailTypeList::gui_fixture_type>;

        template <typename DetailTypeList>
        using message_loop_type =
            tetengo2::gui::message::message_loop<
                abstract_window_type<DetailTypeList>, message_loop_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using timer_type =
            tetengo2::gui::timer<
                type_list_temp::detail::ui::widget_type<DetailTypeList>, typename DetailTypeList::timer_type
            >;

        template <typename DetailTypeList>
        using application_traits_type =
            application_traits<
                size_type,
                difference_type,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                operating_distance_type,
                speed_type,
                scale_type,
                gui_fixture_type<DetailTypeList>,
                fast_font_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                picture_box_type<DetailTypeList>,
                map_box_type<DetailTypeList>,
                side_bar_type<DetailTypeList>,
                type_list_temp::detail::ui::menu_bar_type<DetailTypeList>,
                popup_menu_type<DetailTypeList>,
                menu_command_type<DetailTypeList>,
                menu_separator_type<DetailTypeList>,
                message_loop_type<DetailTypeList>,
                mouse_capture_type<DetailTypeList>,
                timer_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>,
                main_window_traits_type<DetailTypeList>,
                view_traits_type<DetailTypeList>,
                load_save_traits_type<DetailTypeList>,
                command_set_traits_type<DetailTypeList>,
                config_traits_type<DetailTypeList>
            >;

    }}
#endif

    /*!
        \brief The traits type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    struct traits
    {
        //! The dialog traits.
        using dialog_type = detail::traits::dialog_traits_type<DetailTypeList>;

        //! The loading and saving processing traits.
        using load_save_type = detail::traits::load_save_traits_type<DetailTypeList>;

        //! The view traits.
        using view_type = detail::traits::view_traits_type<DetailTypeList>;

        //! The config traits.
        using config_type = detail::traits::config_traits_type<DetailTypeList>;

        //! The main window traits.
        using main_window_type = detail::traits::main_window_traits_type<DetailTypeList>;

        //! The command traits.
        using command_type = detail::traits::command_traits_type<DetailTypeList>;

        //! The command set traits.
        using command_set_type = detail::traits::command_set_traits_type<DetailTypeList>;

        //! The application traits.
        using application_type = detail::traits::application_traits_type<DetailTypeList>;


    };


}}

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
        struct menu_command;   //!< The menu command type.
        struct menu_separator; //!< The menu separator type.
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
        using menu_command_type =
            tetengo2::gui::menu::command<
                string_type,
                ui_encoder_type<DetailTypeList>,
                menu_details_type<DetailTypeList>,
                virtual_key_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using menu_separator_type =
            tetengo2::gui::menu::separator<
                string_type,
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
            boost::mpl::pair<type::ui::menu_command, detail::ui::menu_command_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::menu_separator, detail::ui::menu_separator_type<DetailTypeList>>,
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
        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>;


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

        template <typename DetailTypeList>
        using position_type = bobura::detail::ui::position_type<DetailTypeList>;

        template <typename DetailTypeList>
        using dimension_type = bobura::detail::ui::dimension_type<DetailTypeList>;

        using operating_distance_type = bobura::detail::operating_distance_type;

        using speed_type = bobura::detail::speed_type;

        using scale_type = bobura::detail::scale_type;

        template <typename DetailTypeList>
        using fast_canvas_type = bobura::detail::ui::fast_canvas_type<DetailTypeList>;

        template <typename DetailTypeList>
        using fast_font_type = bobura::detail::ui::fast_font_type<DetailTypeList>;

        template <typename DetailTypeList>
        using dialog_type = bobura::detail::ui::dialog_type<DetailTypeList>;

        template <typename DetailTypeList>
        using abstract_window_type = bobura::detail::ui::abstract_window_type<DetailTypeList>;

        template <typename DetailTypeList>
        using picture_box_type = bobura::detail::ui::picture_box_type<DetailTypeList>;

        template <typename DetailTypeList>
        using mouse_capture_type = bobura::detail::ui::mouse_capture_type<DetailTypeList>;

        template <typename DetailTypeList>
        using message_catalog_type = bobura::detail::locale::message_catalog_type<DetailTypeList>;

        template <typename DetailTypeList>
        using dialog_traits_type =
            dialog_traits<
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                dialog_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                bobura::detail::ui::label_type<DetailTypeList>,
                bobura::detail::ui::link_label_type<DetailTypeList>,
                bobura::detail::ui::image_type<DetailTypeList>,
                bobura::detail::ui::button_type<DetailTypeList>,
                bobura::detail::ui::text_box_type<DetailTypeList>,
                bobura::detail::ui::list_box_type<DetailTypeList>,
                bobura::detail::ui::dropdown_box_type<DetailTypeList>,
                picture_box_type<DetailTypeList>,
                bobura::detail::ui::transparent_background_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using load_save_traits_type =
            bobura::load_save::traits<
                size_type,
                difference_type,
                string_type,
                bobura::detail::input_stream_iterator_type,
                bobura::detail::output_stream_type,
                operating_distance_type,
                speed_type,
                fast_font_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                bobura::detail::common_dialog::message_box_type<DetailTypeList>,
                bobura::detail::common_dialog::file_open_type<DetailTypeList>,
                bobura::detail::common_dialog::file_save_type<DetailTypeList>,
                oudia_diagram_dialog<dialog_traits_type<DetailTypeList>, size_type>,
                message_catalog_type<DetailTypeList>,
                bobura::detail::locale::timetable_file_encoder_type<DetailTypeList>,
                bobura::detail::locale::windia_file_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using view_traits_type =
            bobura::view::diagram::traits<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                scale_type,
                fast_canvas_type<DetailTypeList>,
                bobura::detail::ui::fast_solid_background_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using config_traits_type =
            config_traits<
                string_type,
                size_type,
                bobura::detail::locale::config_encoder_type<DetailTypeList>,
                typename boost::mpl::at<DetailTypeList, type::detail::config>::type
            >;

        template <typename DetailTypeList>
        using map_box_type = bobura::detail::ui::map_box_type<DetailTypeList>;

        template <typename DetailTypeList>
        using side_bar_type = bobura::detail::ui::side_bar_type<DetailTypeList>;

        template <typename DetailTypeList>
        using popup_menu_type = bobura::detail::ui::popup_menu_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_command_type = bobura::detail::ui::menu_command_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_separator_type = bobura::detail::ui::menu_separator_type<DetailTypeList>;

        template <typename DetailTypeList>
        using message_loop_details_type = typename boost::mpl::at<DetailTypeList, type::detail::message_loop>::type;

        template <typename DetailTypeList>
        using main_window_traits_type =
            main_window_traits<
                size_type,
                difference_type,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                operating_distance_type,
                speed_type,
                bobura::detail::ui::window_type<DetailTypeList>,
                picture_box_type<DetailTypeList>,
                map_box_type<DetailTypeList>,
                side_bar_type<DetailTypeList>,
                popup_menu_type<DetailTypeList>,
                tetengo2::gui::message::message_loop_break<message_loop_details_type<DetailTypeList>>,
                fast_font_type<DetailTypeList>,
                mouse_capture_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>,
                view_traits_type<DetailTypeList>,
                load_save_traits_type<DetailTypeList>,
                config_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using command_traits_type =
            command::traits<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                fast_font_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                mouse_capture_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using command_set_traits_type =
            command::set_traits<
                size_type,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                dialog_type<DetailTypeList>,
                bobura::detail::ui::color_type,
                bobura::detail::ui::point_unit_size_type<DetailTypeList>,
                fast_canvas_type<DetailTypeList>,
                scale_type,
                bobura::detail::ui::shell_type<DetailTypeList>,
                bobura::detail::common_dialog::font_type<DetailTypeList>,
                bobura::detail::common_dialog::color_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>,
                command_traits_type<DetailTypeList>,
                main_window_traits_type<DetailTypeList>,
                view_traits_type<DetailTypeList>,
                load_save_traits_type<DetailTypeList>,
                dialog_traits_type<DetailTypeList>,
                config_traits_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using gui_fixture_type =
            tetengo2::gui::fixture<typename boost::mpl::at<DetailTypeList, type::detail::gui_fixture>::type>;

        template <typename DetailTypeList>
        using message_loop_type =
            tetengo2::gui::message::message_loop<
                abstract_window_type<DetailTypeList>, message_loop_details_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using timer_type =
            tetengo2::gui::timer<
                bobura::detail::ui::widget_type<DetailTypeList>,
                typename boost::mpl::at<DetailTypeList, type::detail::timer>::type
            >;

        template <typename DetailTypeList>
        using application_traits_type =
            application_traits<
                size_type,
                difference_type,
                string_type,
                position_type<DetailTypeList>,
                dimension_type<DetailTypeList>,
                operating_distance_type,
                speed_type,
                scale_type,
                gui_fixture_type<DetailTypeList>,
                fast_font_type<DetailTypeList>,
                abstract_window_type<DetailTypeList>,
                picture_box_type<DetailTypeList>,
                map_box_type<DetailTypeList>,
                side_bar_type<DetailTypeList>,
                bobura::detail::ui::menu_bar_type<DetailTypeList>,
                popup_menu_type<DetailTypeList>,
                menu_command_type<DetailTypeList>,
                menu_separator_type<DetailTypeList>,
                message_loop_type<DetailTypeList>,
                mouse_capture_type<DetailTypeList>,
                timer_type<DetailTypeList>,
                message_catalog_type<DetailTypeList>,
                main_window_traits_type<DetailTypeList>,
                view_traits_type<DetailTypeList>,
                load_save_traits_type<DetailTypeList>,
                command_set_traits_type<DetailTypeList>,
                config_traits_type<DetailTypeList>
            >;

    }}
#endif

    /*!
        \brief The traits type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    using traits_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::dialog, detail::traits::dialog_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::load_save, detail::traits::load_save_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::view, detail::traits::view_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::config, detail::traits::config_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::main_window, detail::traits::main_window_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::traits::command, detail::traits::command_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::command_set, detail::traits::command_set_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::traits::application, detail::traits::application_traits_type<DetailTypeList>>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>;


}


#endif
