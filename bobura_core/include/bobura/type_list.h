/*! \file
    \brief The definition of type lists for bobura.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

#include <cstddef>
#include <iterator>
#include <ostream>
#include <string>

#include <boost/rational.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2/gui/alert.h>
#include <tetengo2/gui/common_dialog/color.h>
#include <tetengo2/gui/common_dialog/file_open.h>
#include <tetengo2/gui/common_dialog/file_save.h>
#include <tetengo2/gui/common_dialog/font.h>
#include <tetengo2/gui/common_dialog/message_box.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/drawing/transparent_background.h>
#include <tetengo2/gui/fixture.h>
#include <tetengo2/gui/menu/command.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/menu/popup.h>
#include <tetengo2/gui/menu/separator.h>
#include <tetengo2/gui/message/message_loop.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/shell.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/gui/widget/dropdown_box.h>
#include <tetengo2/gui/widget/image.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/link_label.h>
#include <tetengo2/gui/widget/list_box.h>
#include <tetengo2/gui/widget/map_box.h>
#include <tetengo2/gui/widget/picture_box.h>
#include <tetengo2/gui/widget/side_bar.h>
#include <tetengo2/gui/widget/tab_frame.h>
#include <tetengo2/gui/widget/text_box.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/message/message_catalog.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/cp932.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/text/encoding/utf8.h>

#include <bobura/application_traits.h>
#include <bobura/command/set_traits.h>
#include <bobura/command/traits.h>
#include <bobura/detail_type_list.h> // IWYU pragma: keep
#include <bobura/dialog_traits.h>
#include <bobura/load_save/traits.h>
#include <bobura/main_window_menu_builder_traits.h>
#include <bobura/main_window_traits.h>
#include <bobura/model/serializer/oudia_diagram_dialog.h> // IWYU pragma: keep
#include <bobura/view/diagram/traits.h>
#include <bobura/view/timetable/traits.h>

namespace tetengo2::gui::message {
    template <typename MessageLoopDetails>
    class message_loop_break;
}


namespace bobura::type_list {
/**** Common *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail::common {
        using difference_type = std::ptrdiff_t;

        using size_type = std::size_t;

        using string_type = std::wstring;

        using io_string_type = std::string;

        using input_stream_iterator_type = tetengo2::iterator::observable_forward_iterator<
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>>;

        using output_stream_type = std::basic_ostream<io_string_type::value_type>;

        using operating_distance_type = boost::rational<size_type>;

        using speed_type = boost::rational<size_type>;

        using scale_type = boost::rational<size_type>;
    }
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


    /**** Locale *************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail::locale {
        using string_type = type_list::detail::common::string_type;

        using internal_encoding_type = tetengo2::text::encoding::locale<string_type>;

        using utf8_encoding_type = tetengo2::text::encoding::utf8;

        using cp932_encoding_type = tetengo2::text::encoding::cp932;

        using message_catalog_encoding_type = utf8_encoding_type;

        using message_catalog_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>;

        using message_catalog_type = tetengo2::message::message_catalog;

        using timetable_file_encoding_type = utf8_encoding_type;

        using timetable_file_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, timetable_file_encoding_type>;

        using windia_file_encoding_type = cp932_encoding_type;

        using windia_file_encoder_type = tetengo2::text::encoder<internal_encoding_type, windia_file_encoding_type>;
    }
#endif

    /*!
        \brief The locale type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    struct locale
    {
        //! The message catalog type.
        using message_catalog_type = detail::locale::message_catalog_type;

        //! The encoder type for the timetable file.
        using timetable_file_encoder_type = detail::locale::timetable_file_encoder_type;

        //! The encoder type for the WinDIA file.
        using windia_file_encoder_type = detail::locale::windia_file_encoder_type;
    };


    /**** User Interface *****************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail::ui {
        using size_type = type_list::detail::common::size_type;

        using difference_type = type_list::detail::common::difference_type;

        using string_type = type_list::detail::common::string_type;

        using alert_type = tetengo2::gui::alert;

        template <typename DetailTypeList>
        using widget_details_type = typename DetailTypeList::widget_type;

        template <typename DetailTypeList>
        using drawing_details_type = typename DetailTypeList::drawing_type;

        template <typename DetailTypeList>
        using fast_drawing_details_type = typename DetailTypeList::fast_drawing_type;

        template <typename DetailTypeList>
        using scroll_details_type = typename DetailTypeList::scroll_type;

        template <typename DetailTypeList>
        using message_handler_details_type = typename DetailTypeList::message_handler_type;

        template <typename DetailTypeList>
        using menu_details_type = typename DetailTypeList::menu_type;

        template <typename DetailTypeList>
        using mouse_capture_details_type = typename DetailTypeList::mouse_capture_type;

        using position_type = tetengo2::gui::em_position;

        using dimension_type = tetengo2::gui::em_dimension;

        template <typename DetailTypeList>
        using fast_solid_background_type =
            tetengo2::gui::drawing::solid_background<fast_drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using transparent_background_type =
            tetengo2::gui::drawing::transparent_background<drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using font_type = tetengo2::gui::drawing::font<drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using fast_font_type = tetengo2::gui::drawing::font<fast_drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using canvas_type = tetengo2::gui::drawing::canvas<drawing_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using fast_canvas_type = tetengo2::gui::drawing::canvas<fast_drawing_details_type<DetailTypeList>>;

        using mouse_observer_set_type = tetengo2::gui::message::mouse_observer_set;

        using widget_type = tetengo2::gui::widget::widget;

        using abstract_window_type = tetengo2::gui::widget::abstract_window;

        using window_type = tetengo2::gui::widget::window;

        using dialog_type = tetengo2::gui::widget::dialog;

        using color_type = tetengo2::gui::drawing::color;

        using button_type = tetengo2::gui::widget::button;

        using dropdown_box_type = tetengo2::gui::widget::dropdown_box;

        using image_type = tetengo2::gui::widget::image;

        using label_type = tetengo2::gui::widget::label;

        using link_label_type = tetengo2::gui::widget::link_label;

        using list_box_type = tetengo2::gui::widget::list_box;

        template <typename DetailTypeList>
        using mouse_capture_type = tetengo2::gui::mouse_capture<
            widget_details_type<DetailTypeList>,
            drawing_details_type<DetailTypeList>,
            scroll_details_type<DetailTypeList>,
            message_handler_details_type<DetailTypeList>,
            mouse_capture_details_type<DetailTypeList>>;

        using map_box_type = tetengo2::gui::widget::map_box;

        template <typename DetailTypeList>
        using menu_bar_type = tetengo2::gui::menu::menu_bar<menu_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using menu_command_type = tetengo2::gui::menu::command<menu_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using menu_separator_type = tetengo2::gui::menu::separator<menu_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using picture_box_type = tetengo2::gui::widget::picture_box<fast_drawing_details_type<DetailTypeList>>;

        using point_dimension_unit_type = tetengo2::gui::unit::upoint;

        template <typename DetailTypeList>
        using popup_menu_type = tetengo2::gui::menu::popup<menu_details_type<DetailTypeList>>;

        using shell_type = tetengo2::gui::shell;

        template <typename DetailTypeList>
        using timer_details_type = typename DetailTypeList::timer_type;

        template <typename DetailTypeList>
        using side_bar_type = tetengo2::gui::widget::side_bar<timer_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using system_color_set_type = tetengo2::gui::drawing::system_color_set;

        using tab_frame_type = tetengo2::gui::widget::tab_frame;

        using text_box_type = tetengo2::gui::widget::text_box;

        template <typename DetailTypeList>
        using timer_type = tetengo2::gui::timer<tetengo2::gui::widget::widget, timer_details_type<DetailTypeList>>;
    }
#endif

    /*!
        \brief The locale type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    struct ui
    {
        //! The abstract window type.
        using abstract_window_type = detail::ui::abstract_window_type;

        //! The alert type.
        using alert_type = detail::ui::alert_type;

        //! The button type.
        using button_type = detail::ui::button_type;

        //! The canvas type.
        using canvas_type = detail::ui::canvas_type<DetailTypeList>;

        //! The color type.
        using color_type = detail::ui::color_type;

        //! The dialog type.
        using dialog_type = detail::ui::dialog_type;

        //! The dimension type.
        using dimension_type = detail::ui::dimension_type;

        //! The dropdown box type.
        using dropdown_box_type = detail::ui::dropdown_box_type;

        //! The fast canvas type.
        using fast_canvas_type = detail::ui::fast_canvas_type<DetailTypeList>;

        //! The font type.
        using font_type = detail::ui::font_type<DetailTypeList>;

        //! The fast font type.
        using fast_font_type = detail::ui::fast_font_type<DetailTypeList>;

        //! The fast solid background type.
        using fast_solid_background_type = detail::ui::fast_solid_background_type<DetailTypeList>;

        //! The image type.
        using image_type = detail::ui::image_type;

        //! The label type.
        using label_type = detail::ui::label_type;

        //! The link label type.
        using link_label_type = detail::ui::link_label_type;

        //! The list box type.
        using list_box_type = detail::ui::list_box_type;

        //! The map box type.
        using map_box_type = detail::ui::map_box_type;

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

        //! The point dimension unit type.
        using point_dimension_unit_type = detail::ui::point_dimension_unit_type;

        //! The popup menu type.
        using popup_menu_type = detail::ui::popup_menu_type<DetailTypeList>;

        //! The position type.
        using position_type = detail::ui::position_type;

        //! The shell type.
        using shell_type = detail::ui::shell_type;

        //! The timer type.
        using timer_type = detail::ui::timer_type<DetailTypeList>;

        //! The side bar type.
        using side_bar_type = detail::ui::side_bar_type<DetailTypeList>;

        //! The system color set type.
        using system_color_set_type = detail::ui::system_color_set_type<DetailTypeList>;

        //! The tab frame type.
        using tab_frame_type = detail::ui::tab_frame_type;

        //! The text box type.
        using text_box_type = detail::ui::text_box_type;

        //! The transparent background type.
        using transparent_background_type = detail::ui::transparent_background_type<DetailTypeList>;

        //! The widget type.
        using widget_type = detail::ui::widget_type;

        //! The window type.
        using window_type = detail::ui::window_type;
    };


    /**** Common Dialog ******************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail::common_dialog {
        using string_type = type_list::detail::common::string_type;

        template <typename DetailTypeList>
        using common_dialog_details_type = typename DetailTypeList::common_dialog_type;

        template <typename DetailTypeList>
        using menu_details_type = typename DetailTypeList::menu_type;

        template <typename DetailTypeList>
        using color_type = tetengo2::gui::common_dialog::color<
            common_dialog_details_type<DetailTypeList>,
            type_list::detail::ui::widget_details_type<DetailTypeList>,
            type_list::detail::ui::drawing_details_type<DetailTypeList>,
            type_list::detail::ui::scroll_details_type<DetailTypeList>,
            type_list::detail::ui::message_handler_details_type<DetailTypeList>,
            menu_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using file_open_type = tetengo2::gui::common_dialog::file_open<
            common_dialog_details_type<DetailTypeList>,
            type_list::detail::ui::widget_details_type<DetailTypeList>,
            type_list::detail::ui::drawing_details_type<DetailTypeList>,
            type_list::detail::ui::scroll_details_type<DetailTypeList>,
            type_list::detail::ui::message_handler_details_type<DetailTypeList>,
            menu_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using file_save_type = tetengo2::gui::common_dialog::file_save<
            common_dialog_details_type<DetailTypeList>,
            type_list::detail::ui::widget_details_type<DetailTypeList>,
            type_list::detail::ui::drawing_details_type<DetailTypeList>,
            type_list::detail::ui::scroll_details_type<DetailTypeList>,
            type_list::detail::ui::message_handler_details_type<DetailTypeList>,
            menu_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using font_type = tetengo2::gui::common_dialog::font<
            type_list::detail::ui::fast_font_type<DetailTypeList>,
            common_dialog_details_type<DetailTypeList>,
            type_list::detail::ui::widget_details_type<DetailTypeList>,
            type_list::detail::ui::drawing_details_type<DetailTypeList>,
            type_list::detail::ui::scroll_details_type<DetailTypeList>,
            type_list::detail::ui::message_handler_details_type<DetailTypeList>,
            menu_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using message_box_type = tetengo2::gui::common_dialog::message_box<
            common_dialog_details_type<DetailTypeList>,
            type_list::detail::ui::widget_details_type<DetailTypeList>,
            type_list::detail::ui::drawing_details_type<DetailTypeList>,
            type_list::detail::ui::scroll_details_type<DetailTypeList>,
            type_list::detail::ui::message_handler_details_type<DetailTypeList>,
            menu_details_type<DetailTypeList>>;
    }
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


    /**** Traits *************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail::traits {
        using size_type = type_list::detail::common::size_type;

        using difference_type = type_list::detail::common::difference_type;

        using string_type = type_list::detail::common::string_type;

        using position_type = type_list::detail::ui::position_type;

        using dimension_type = type_list::detail::ui::dimension_type;

        using operating_distance_type = type_list::detail::common::operating_distance_type;

        using speed_type = type_list::detail::common::speed_type;

        using scale_type = type_list::detail::common::scale_type;

        template <typename DetailTypeList>
        using fast_canvas_type = type_list::detail::ui::fast_canvas_type<DetailTypeList>;

        template <typename DetailTypeList>
        using fast_font_type = type_list::detail::ui::fast_font_type<DetailTypeList>;

        using dialog_type = type_list::detail::ui::dialog_type;

        using abstract_window_type = type_list::detail::ui::abstract_window_type;

        template <typename DetailTypeList>
        using picture_box_type = type_list::detail::ui::picture_box_type<DetailTypeList>;

        template <typename DetailTypeList>
        using mouse_capture_type = type_list::detail::ui::mouse_capture_type<DetailTypeList>;

        using message_catalog_type = type_list::detail::locale::message_catalog_type;

        template <typename DetailTypeList>
        using dialog_traits_type = dialog_traits<
            string_type,
            position_type,
            dimension_type,
            dialog_type,
            abstract_window_type,
            type_list::detail::ui::label_type,
            type_list::detail::ui::link_label_type,
            type_list::detail::ui::image_type,
            type_list::detail::ui::button_type,
            type_list::detail::ui::text_box_type,
            type_list::detail::ui::list_box_type,
            type_list::detail::ui::dropdown_box_type,
            picture_box_type<DetailTypeList>,
            type_list::detail::ui::transparent_background_type<DetailTypeList>,
            message_catalog_type>;

        template <typename DetailTypeList>
        using load_save_traits_type = bobura::load_save::traits<
            size_type,
            difference_type,
            string_type,
            type_list::detail::common::input_stream_iterator_type,
            type_list::detail::common::output_stream_type,
            operating_distance_type,
            speed_type,
            fast_font_type<DetailTypeList>,
            abstract_window_type,
            type_list::detail::common_dialog::message_box_type<DetailTypeList>,
            type_list::detail::common_dialog::file_open_type<DetailTypeList>,
            type_list::detail::common_dialog::file_save_type<DetailTypeList>,
            dialog_type,
            type_list::detail::ui::timer_type<DetailTypeList>,
            type_list::detail::ui::system_color_set_type<DetailTypeList>,
            model::serializer::oudia_diagram_dialog<dialog_traits_type<DetailTypeList>, size_type>,
            message_catalog_type,
            type_list::detail::locale::timetable_file_encoder_type,
            type_list::detail::locale::windia_file_encoder_type>;

        template <typename DetailTypeList>
        using diagram_view_traits_type = bobura::view::diagram::traits<
            size_type,
            difference_type,
            string_type,
            operating_distance_type,
            speed_type,
            scale_type,
            fast_canvas_type<DetailTypeList>,
            type_list::detail::ui::fast_solid_background_type<DetailTypeList>,
            message_catalog_type>;

        template <typename DetailTypeList>
        using timetable_view_traits_type = bobura::view::timetable::traits<
            size_type,
            difference_type,
            string_type,
            operating_distance_type,
            speed_type,
            fast_canvas_type<DetailTypeList>,
            type_list::detail::ui::fast_solid_background_type<DetailTypeList>,
            message_catalog_type>;

        template <typename DetailTypeList>
        using tab_frame_type = type_list::detail::ui::tab_frame_type<DetailTypeList>;

        template <typename DetailTypeList>
        using map_box_type = type_list::detail::ui::map_box_type<DetailTypeList>;

        template <typename DetailTypeList>
        using side_bar_type = type_list::detail::ui::side_bar_type<DetailTypeList>;

        template <typename DetailTypeList>
        using popup_menu_type = type_list::detail::ui::popup_menu_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_command_type = type_list::detail::ui::menu_command_type<DetailTypeList>;

        template <typename DetailTypeList>
        using menu_separator_type = type_list::detail::ui::menu_separator_type<DetailTypeList>;

        template <typename DetailTypeList>
        using message_loop_details_type = typename DetailTypeList::message_loop_type;

        template <typename DetailTypeList>
        using main_window_traits_type = main_window_traits<
            string_type,
            position_type,
            dimension_type,
            type_list::detail::ui::window_type<DetailTypeList>,
            picture_box_type<DetailTypeList>,
            tab_frame_type<DetailTypeList>,
            map_box_type<DetailTypeList>,
            side_bar_type<DetailTypeList>,
            tetengo2::gui::message::message_loop_break<message_loop_details_type<DetailTypeList>>,
            fast_font_type<DetailTypeList>,
            mouse_capture_type<DetailTypeList>,
            message_catalog_type,
            diagram_view_traits_type<DetailTypeList>,
            load_save_traits_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using command_traits_type = command::traits<
            size_type,
            difference_type,
            string_type,
            operating_distance_type,
            speed_type,
            fast_font_type<DetailTypeList>,
            abstract_window_type<DetailTypeList>,
            mouse_capture_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using command_set_traits_type = command::set_traits<
            size_type,
            string_type,
            position_type,
            dimension_type,
            dialog_type<DetailTypeList>,
            type_list::detail::ui::color_type,
            type_list::detail::ui::point_dimension_unit_type,
            fast_canvas_type<DetailTypeList>,
            scale_type,
            type_list::detail::ui::shell_type,
            type_list::detail::common_dialog::font_type<DetailTypeList>,
            type_list::detail::common_dialog::color_type<DetailTypeList>,
            message_catalog_type,
            command_traits_type<DetailTypeList>,
            main_window_traits_type<DetailTypeList>,
            diagram_view_traits_type<DetailTypeList>,
            load_save_traits_type<DetailTypeList>,
            dialog_traits_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using menu_bar_type = type_list::detail::ui::menu_bar_type<DetailTypeList>;

        template <typename DetailTypeList>
        using main_window_menu_builder_traits_type = bobura::main_window_menu_builder_traits<
            size_type,
            difference_type,
            string_type,
            operating_distance_type,
            speed_type,
            scale_type,
            fast_font_type<DetailTypeList>,
            menu_bar_type<DetailTypeList>,
            popup_menu_type<DetailTypeList>,
            menu_command_type<DetailTypeList>,
            menu_separator_type<DetailTypeList>,
            message_catalog_type,
            command_set_traits_type<DetailTypeList>,
            main_window_traits_type<DetailTypeList>,
            diagram_view_traits_type<DetailTypeList>>;

        using gui_fixture_type = tetengo2::gui::fixture;

        template <typename DetailTypeList>
        using message_loop_type = tetengo2::gui::message::
            message_loop<abstract_window_type<DetailTypeList>, message_loop_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using timer_type = type_list::detail::ui::timer_type<DetailTypeList>;

        template <typename DetailTypeList>
        using application_traits_type = application_traits<
            size_type,
            difference_type,
            string_type,
            position_type,
            dimension_type,
            operating_distance_type,
            speed_type,
            scale_type,
            gui_fixture_type,
            fast_font_type<DetailTypeList>,
            abstract_window_type<DetailTypeList>,
            picture_box_type<DetailTypeList>,
            tab_frame_type<DetailTypeList>,
            map_box_type<DetailTypeList>,
            side_bar_type<DetailTypeList>,
            menu_bar_type<DetailTypeList>,
            popup_menu_type<DetailTypeList>,
            menu_command_type<DetailTypeList>,
            menu_separator_type<DetailTypeList>,
            message_loop_type<DetailTypeList>,
            mouse_capture_type<DetailTypeList>,
            timer_type<DetailTypeList>,
            message_catalog_type,
            main_window_traits_type<DetailTypeList>,
            diagram_view_traits_type<DetailTypeList>,
            timetable_view_traits_type<DetailTypeList>,
            load_save_traits_type<DetailTypeList>,
            command_set_traits_type<DetailTypeList>,
            main_window_menu_builder_traits_type<DetailTypeList>>;
    }
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

        //! The diagram view traits.
        using diagram_view_type = detail::traits::diagram_view_traits_type<DetailTypeList>;

        //! The timetable view traits.
        using timetable_view_type = detail::traits::timetable_view_traits_type<DetailTypeList>;

        //! The main window traits.
        using main_window_type = detail::traits::main_window_traits_type<DetailTypeList>;

        //! The command traits.
        using command_type = detail::traits::command_traits_type<DetailTypeList>;

        //! The command set traits.
        using command_set_type = detail::traits::command_set_traits_type<DetailTypeList>;

        //! The main window menu builder traits type.
        using main_window_menu_builder_type = detail::traits::main_window_menu_builder_traits_type<DetailTypeList>;

        //! The application traits.
        using application_type = detail::traits::application_traits_type<DetailTypeList>;
    };
}


#endif
