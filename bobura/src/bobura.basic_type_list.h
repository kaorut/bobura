/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_BASICTYPELIST_H)
#define BOBURA_BASICTYPELIST_H

#include <cstddef>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/rational.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2/gui/alert.h>
#include <tetengo2/gui/common_dialog/color.h>
#include <tetengo2/gui/common_dialog/file_open.h>
#include <tetengo2/gui/common_dialog/file_save.h>
#include <tetengo2/gui/common_dialog/font.h>
#include <tetengo2/gui/common_dialog/message_box.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas_traits.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/picture_reader.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/drawing/transparent_background.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/fixture.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/command.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/popup.h>
#include <tetengo2/gui/menu/separator.h>
#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/menu/shortcut_key_table.h>
#include <tetengo2/gui/menu/traits.h>
#include <tetengo2/gui/message/dialog_message_loop.h>
#include <tetengo2/gui/message/file_drop_observer_set.h>
#include <tetengo2/gui/message/focus_observer_set.h>
#include <tetengo2/gui/message/keyboard_observer_set.h>
#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/message/menu_observer_set.h>
#include <tetengo2/gui/message/message_loop.h>
#include <tetengo2/gui/message/message_loop_break.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/message/scroll_bar_observer_set.h>
#include <tetengo2/gui/message/size_observer_set.h>
#include <tetengo2/gui/message/text_box_observer_set.h>
#include <tetengo2/gui/message/window_observer_set.h>
#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/scroll_bar.h>
#include <tetengo2/gui/shell.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/gui/widget/dropdown_box.h>
#include <tetengo2/gui/widget/image.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/link_label.h>
#include <tetengo2/gui/widget/list_box.h>
#include <tetengo2/gui/widget/map_box.h>
#include <tetengo2/gui/widget/picture_box.h>
#include <tetengo2/gui/widget/side_bar.h>
#include <tetengo2/gui/widget/text_box.h>
#include <tetengo2/gui/widget/traits/abstract_window_traits.h>
#include <tetengo2/gui/widget/traits/button_traits.h>
#include <tetengo2/gui/widget/traits/control_traits.h>
#include <tetengo2/gui/widget/traits/custom_control_traits.h>
#include <tetengo2/gui/widget/traits/dialog_traits.h>
#include <tetengo2/gui/widget/traits/dropdown_box_traits.h>
#include <tetengo2/gui/widget/traits/image_traits.h>
#include <tetengo2/gui/widget/traits/label_traits.h>
#include <tetengo2/gui/widget/traits/link_label_traits.h>
#include <tetengo2/gui/widget/traits/list_box_traits.h>
#include <tetengo2/gui/widget/traits/map_box_traits.h>
#include <tetengo2/gui/widget/traits/picture_box_traits.h>
#include <tetengo2/gui/widget/traits/side_bar_traits.h>
#include <tetengo2/gui/widget/traits/text_box_traits.h>
#include <tetengo2/gui/widget/traits/widget_traits.h>
#include <tetengo2/gui/widget/traits/window_traits.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/message/messages.h>
#include <tetengo2/message/message_catalog.h>
#include <tetengo2/message/message_catalog_parser.h>
#include <tetengo2/meta/assoc_list.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/cp932.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/text/encoding/utf8.h>
#include <tetengo2/text/grammar/json.h>
#include <tetengo2/text/pull_parser.h>
#include <tetengo2/text/push_parser.h>

#include "bobura.about_dialog.h"
#include "bobura.config_traits.h"
#include "bobura.detail_type_list.h"
#include "bobura.diagram_view.h"
#include "bobura.file_property_dialog.h"
#include "bobura.font_color_dialog.h"
#include "bobura.load_save.confirm_file_save.h"
#include "bobura.load_save.load_from_file.h"
#include "bobura.load_save.new_file.h"
#include "bobura.load_save.save_to_file.h"
#include "bobura.message.diagram_selection_observer_set.h"
#include "bobura.message.timetable_model_observer_set.h"
#include "bobura.message.type_list_impl.h"
#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.serializer.reader_selector.h"
#include "bobura.model.serializer.reader_set.h"
#include "bobura.model.serializer.select_oudia_diagram.h"
#include "bobura.model.serializer.writer_selector.h"
#include "bobura.model.serializer.writer_set.h"
#include "bobura.model.station.h"
#include "bobura.model.train.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.font_color_set.h"
#include "bobura.model.timetable_info.station_interval_calculator.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"
#include "bobura.model.train_kind.h"
#include "bobura.oudia_diagram_dialog.h"
#include "bobura.settings.h"
#include "bobura.timetable_model.h"
#include "bobura.train_kind_dialog.h"
#include "bobura.view.diagram.header.h"
#include "bobura.view.diagram.selection.h"
#include "bobura.view.diagram.station_line.h"
#include "bobura.view.diagram.time_line.h"
#include "bobura.view.diagram.train_line.h"
#include "bobura.view.scale_list.h"


namespace bobura
{
    /**** Common ************************************************************/

    namespace type
    {
        struct difference;     //!< The difference type.
        struct size;           //!< The size type.
        struct string;         //!< The string type.
        struct path;           //!< The path type.
        struct input_stream_iterator; //!< The input stream iterator type.
        struct pull_parser;    //!< The pull parser_type.
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
        using json_grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;
        using push_parser_type =
            tetengo2::text::push_parser<input_stream_iterator_type, json_grammar_type, int, double>;
        using pull_parser_type = tetengo2::text::pull_parser<push_parser_type, size_type>;
        using path_type = boost::filesystem::path;
    }
#endif

    //! The common type list.
    using common_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::path, detail::path_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::input_stream_iterator, detail::input_stream_iterator_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::pull_parser, detail::pull_parser_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::output_stream, std::basic_ostream<detail::io_string_type::value_type>>,
        tetengo2::meta::assoc_list_end
        >>>>>>>;


    /**** Locale ************************************************************/

    namespace type { namespace locale
    {
        struct exception_encoder; //!< The encoder type for exceptions.
        struct ui_encoder;     //!< The encoder type for the user interface.
        struct config_encoder; //!< The encoder type for the user interface.
        struct messages_facet; //!< The messages facet type.
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
        using locale_name_encoding_type =
            tetengo2::text::encoding::locale<
                std::string, boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >;
        using message_catalog_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>;
        using message_catalog_parser_type =
            tetengo2::message::message_catalog_parser<
                boost::mpl::at<common_type_list, type::pull_parser>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                message_catalog_encoder_type
            >;
        using locale_name_encoder_type = tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type>;
        using messages_type =
            tetengo2::message::messages<
                boost::mpl::at<common_type_list, type::path>::type,
                message_catalog_parser_type,
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
        tetengo2::meta::assoc_list<boost::mpl::pair<type::locale::messages_facet, detail::locale::messages_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::message_catalog, tetengo2::message::message_catalog<detail::locale::messages_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::timetable_file_encoder, detail::locale::timetable_file_encoder_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::windia_file_encoder, detail::locale::windia_file_encoder_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>;


    /**** User Interface ****************************************************/

    namespace type { namespace ui
    {
        struct abstract_window; //!< The abstract window type.
        struct alert;          //!< The alert type.
        struct button;         //!< The button type.
        struct canvas;         //!< The canvas type.
        struct color;          //!< The color type.
        struct control;        //!< The control type.
        struct dialog;         //!< The dialog type.
        struct dimension;      //!< The dimension type.
        struct dropdown_box;   //!< The dropdown box type.
        struct fast_canvas;    //!< The fast canvas type.
        struct fast_font;      //!< The fast font type.
        struct fast_picture_reader; //!< The fast picture reader type.
        struct fast_solid_background; //!< The fast solid background type.
        struct font;           //!< The font type.
        struct gui_fixture;    //!< The GUI fixture type.
        struct image;          //!< The image type.
        struct label;          //!< The label type.
        struct link_label;     //!< The link label type.
        struct list_box;       //!< The list box type.
        struct map_box;        //!< The map box type.
        struct menu_bar;       //!< The menu bar type.
        struct menu_command;   //!< The menu command type.
        struct menu_separator; //!< The menu separator type;
        struct message_loop;   //!< The message loop type.
        struct message_loop_break; //!< The message loop break type.
        struct mouse_capture;  //!< The mouse capture type.
        struct picture_box;    //!< The picture box type.
        struct picture_reader; //!< The picture reader type.
        struct point_unit_size; //!< The point unit size type.
        struct popup_menu;     //!< The popup menu type.
        struct position;       //!< The position type.
        struct shell;          //!< The shell type.
        struct side_bar;       //!< The side bar type.
        struct solid_background; //!< The solid background type.
        struct text_box;       //!< The text box type.
        struct timer;          //!< The timer type.
        struct transparent_background; //!< The transparent background type.
        struct window;         //!< The window type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        using gui_fixture_type =
            tetengo2::gui::fixture<boost::mpl::at<detail_type_list, type::detail::gui_fixture>::type>;
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
        using color_type = tetengo2::gui::drawing::color<unsigned char>;
        using background_type =
            tetengo2::gui::drawing::background<boost::mpl::at<detail_type_list, type::detail::drawing>::type>;
        using fast_background_type =
            tetengo2::gui::drawing::background<boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type>;
        using solid_background_type =
            tetengo2::gui::drawing::solid_background<
                color_type, boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using fast_solid_background_type =
            tetengo2::gui::drawing::solid_background<
                color_type, boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using transparent_background_type =
            tetengo2::gui::drawing::transparent_background<
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using font_type =
            tetengo2::gui::drawing::font<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using fast_font_type =
            tetengo2::gui::drawing::font<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using picture_type =
            tetengo2::gui::drawing::picture<
                dimension_type, boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using fast_picture_type =
            tetengo2::gui::drawing::picture<
                dimension_type, boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using picture_reader_type =
            tetengo2::gui::drawing::picture_reader<
                picture_type,
                boost::mpl::at<common_type_list, type::path>::type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using fast_picture_reader_type =
            tetengo2::gui::drawing::picture_reader<
                fast_picture_type,
                boost::mpl::at<common_type_list, type::path>::type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using icon_type =
            tetengo2::gui::icon<
                boost::mpl::at<common_type_list, type::path>::type,
                dimension_type,
                boost::mpl::at<detail_type_list, type::detail::icon>::type
            >;
        using canvas_traits_type =
            tetengo2::gui::drawing::canvas_traits<
                unit_size_type,
                boost::mpl::at<common_type_list, type::string>::type,
                position_type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                color_type,
                background_type,
                solid_background_type,
                font_type,
                picture_type,
                icon_type
            >;
        using widget_canvas_type =
            tetengo2::gui::drawing::widget_canvas<
                canvas_traits_type, boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using canvas_type = widget_canvas_type::base_type;
        using fast_canvas_traits_type =
            tetengo2::gui::drawing::canvas_traits<
                unit_size_type,
                boost::mpl::at<common_type_list, type::string>::type,
                position_type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                color_type,
                fast_background_type,
                fast_solid_background_type,
                fast_font_type,
                fast_picture_type,
                icon_type
            >;
        using fast_widget_canvas_type =
            tetengo2::gui::drawing::widget_canvas<
                fast_canvas_traits_type, boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >;
        using fast_canvas_type = fast_widget_canvas_type::base_type;
        using alert_type =
            tetengo2::gui::alert<
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                boost::mpl::at<locale_type_list, type::locale::exception_encoder>::type,
                boost::mpl::at<detail_type_list, type::detail::alert>::type
            >;
        using system_cursor_type =
            tetengo2::gui::cursor::system<boost::mpl::at<detail_type_list, type::detail::cursor>::type>;
        using scroll_bar_type =
            tetengo2::gui::scroll_bar<
                boost::mpl::at<common_type_list, type::size>::type,
                tetengo2::gui::message::scroll_bar_observer_set<boost::mpl::at<common_type_list, type::size>::type>,
                boost::mpl::at<detail_type_list, type::detail::scroll>::type
            >;
        using virtual_key_type =
            tetengo2::gui::virtual_key<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
            >;
        using mouse_observer_set_type =
            tetengo2::gui::message::mouse_observer_set<
                position_type, boost::mpl::at<common_type_list, type::difference>::type
            >;
        using widget_traits_type =
            tetengo2::gui::widget::traits::widget_traits<
                widget_canvas_type,
                alert_type,
                position_type,
                dimension_type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                background_type,
                font_type,
                system_cursor_type,
                scroll_bar_type,
                tetengo2::gui::message::size_observer_set,
                tetengo2::gui::message::focus_observer_set,
                tetengo2::gui::message::paint_observer_set<canvas_type>,
                tetengo2::gui::message::keyboard_observer_set<
                    virtual_key_type, boost::mpl::at<common_type_list, type::string>::type::value_type
                >,
                mouse_observer_set_type
            >;
        using widget_type =
            tetengo2::gui::widget::widget<
                widget_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using shortcut_key_type = tetengo2::gui::menu::shortcut_key<virtual_key_type>;
        using menu_traits_type =
            tetengo2::gui::menu::traits<
                boost::mpl::at<common_type_list, type::string>::type,
                shortcut_key_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                tetengo2::gui::message::menu_observer_set
            >;
        using menu_base_type =
            tetengo2::gui::menu::menu_base<
                menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
            >;
        using shortcut_key_table_type =
            tetengo2::gui::menu::shortcut_key_table<
                shortcut_key_type, menu_base_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
            >;
        using menu_bar_type =
            tetengo2::gui::menu::menu_bar<
                menu_traits_type, shortcut_key_table_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
            >;
        using abstract_window_traits_type =
            tetengo2::gui::widget::traits::abstract_window_traits<
                widget_traits_type,
                icon_type,
                menu_bar_type,
                tetengo2::gui::message::window_observer_set,
                tetengo2::gui::message::file_drop_observer_set<boost::mpl::at<common_type_list, type::path>::type>
            >;
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<
                abstract_window_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using window_traits_type = tetengo2::gui::widget::traits::window_traits<abstract_window_traits_type>;
        using window_type =
            tetengo2::gui::widget::window<
                window_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using message_loop_type =
            tetengo2::gui::message::message_loop<
                abstract_window_type, boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >;
        using message_loop_break_type =
            tetengo2::gui::message::message_loop_break<
                boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >;
        using dialog_message_loop_type =
            tetengo2::gui::message::dialog_message_loop<
                abstract_window_type, boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >;
        using dialog_traits_type =
            tetengo2::gui::widget::traits::dialog_traits<
                abstract_window_traits_type, dialog_message_loop_type, message_loop_break_type
            >;
        using dialog_type =
            tetengo2::gui::widget::dialog<
                dialog_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using control_traits_type = tetengo2::gui::widget::traits::control_traits<widget_traits_type, color_type>;
        using control_type =
            tetengo2::gui::widget::control<
                control_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using button_traits_type = tetengo2::gui::widget::traits::button_traits<control_traits_type>;
        using button_type =
            tetengo2::gui::widget::button<
                button_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using image_traits_type =
            tetengo2::gui::widget::traits::image_traits<control_traits_type, picture_type, icon_type>;
        using image_type =
            tetengo2::gui::widget::image<
                image_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using dropdown_box_traits_type =
            tetengo2::gui::widget::traits::dropdown_box_traits<
                control_traits_type,
                boost::mpl::at<common_type_list, type::size>::type,
                tetengo2::gui::message::list_selection_observer_set
            >;
        using dropdown_box_type =
            tetengo2::gui::widget::dropdown_box<
                dropdown_box_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using label_traits_type = tetengo2::gui::widget::traits::label_traits<control_traits_type>;
        using label_type =
            tetengo2::gui::widget::label<
                label_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using system_color_set_type =
            tetengo2::gui::drawing::system_color_set<
                color_type, boost::mpl::at<detail_type_list, type::detail::system_color>::type
            >;
        using shell_type =
            tetengo2::gui::shell<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                boost::mpl::at<detail_type_list, type::detail::shell>::type
            >;
        using link_label_traits_type =
            tetengo2::gui::widget::traits::link_label_traits<
                label_traits_type, solid_background_type, system_color_set_type, shell_type
            >;
        using link_label_type =
            tetengo2::gui::widget::link_label<
                link_label_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using list_box_traits_type =
            tetengo2::gui::widget::traits::list_box_traits<
                control_traits_type,
                boost::mpl::at<common_type_list, type::size>::type,
                tetengo2::gui::message::list_selection_observer_set
            >;
        using list_box_type =
            tetengo2::gui::widget::list_box<
                list_box_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using mouse_capture_type =
            tetengo2::gui::mouse_capture<
                widget_type,
                mouse_observer_set_type::mouse_button_type,
                boost::mpl::at<detail_type_list, type::detail::mouse_capture>::type
            >;
        using custom_control_traits_type =
            tetengo2::gui::widget::traits::custom_control_traits<control_traits_type, mouse_capture_type>;
        using map_box_traits_type =
            tetengo2::gui::widget::traits::map_box_traits<
                custom_control_traits_type,
                boost::mpl::at<common_type_list, type::size>::type,
                solid_background_type,
                system_color_set_type,
                tetengo2::gui::message::list_selection_observer_set
            >;
        using map_box_type =
            tetengo2::gui::widget::map_box<
                map_box_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using picture_box_traits_type =
            tetengo2::gui::widget::traits::picture_box_traits<
                control_traits_type,
                fast_widget_canvas_type,
                tetengo2::gui::message::paint_observer_set<fast_canvas_type>
            >;
        using picture_box_type =
            tetengo2::gui::widget::picture_box<
                picture_box_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using timer_type =
            tetengo2::gui::timer<widget_type, boost::mpl::at<detail_type_list, type::detail::timer>::type>;
        using side_bar_traits_type =
            tetengo2::gui::widget::traits::side_bar_traits<
                custom_control_traits_type,
                solid_background_type,
                system_color_set_type,
                timer_type
            >;
        using side_bar_type =
            tetengo2::gui::widget::side_bar<
                side_bar_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
        using text_box_traits_type =
            tetengo2::gui::widget::traits::text_box_traits<
                control_traits_type, tetengo2::gui::message::text_box_observer_set
            >;
        using text_box_type =
            tetengo2::gui::widget::text_box<
                text_box_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >;
    }}
#endif

    //! The type list for the user interface.
    using ui_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::abstract_window, detail::ui::abstract_window_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::alert, detail::ui::alert_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::button, detail::ui::button_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::canvas, detail::ui::canvas_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::control, detail::ui::control_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::color, detail::ui::color_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dialog, detail::ui::dialog_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dimension, detail::ui::dimension_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dropdown_box, detail::ui::dropdown_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::fast_canvas, detail::ui::fast_canvas_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::fast_font, detail::ui::fast_font_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::fast_picture_reader, detail::ui::fast_picture_reader_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::fast_solid_background, detail::ui::fast_solid_background_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::font, detail::ui::font_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::gui_fixture, detail::ui::gui_fixture_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::image, detail::ui::image_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::label, detail::ui::label_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::link_label, detail::ui::link_label_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::list_box, detail::ui::list_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::map_box, detail::ui::map_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::menu_bar, detail::ui::menu_bar_type >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::menu_command,
                tetengo2::gui::menu::command<
                    detail::ui::menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::menu_separator,
                tetengo2::gui::menu::separator<
                    detail::ui::menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::message_loop, detail::ui::message_loop_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::message_loop_break, detail::ui::message_loop_break_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::mouse_capture, detail::ui::mouse_capture_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::picture_box, detail::ui::picture_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::picture_reader, detail::ui::picture_reader_type>,
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
                    detail::ui::menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::position, detail::ui::position_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::shell, detail::ui::shell_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::side_bar, detail::ui::side_bar_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::solid_background, detail::ui::solid_background_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::text_box, detail::ui::text_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::timer, detail::ui::timer_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::transparent_background, detail::ui::transparent_background_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::window, detail::ui::window_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>;


    /**** Setting ***********************************************************/

    namespace type { namespace setting
    {
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
                boost::mpl::at<common_type_list, type::path>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                config_traits_type
            >;
    }}
#endif

    //! The type list for the settings.
    using setting_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::setting::settings, detail::setting::settings_type>,
        tetengo2::meta::assoc_list_end
        >;


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
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<ui_type_list, type::ui::color>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_open_dialog,
                tetengo2::gui::common_dialog::file_open<
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_save_dialog,
                tetengo2::gui::common_dialog::file_save<
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::font,
                tetengo2::gui::common_dialog::font<
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::message_box,
                tetengo2::gui::common_dialog::message_box<
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>;


    /**** Dialog ************************************************************/

    namespace type { namespace dialog
    {
        struct about_dialog;   //!< The about dialog type.
        struct file_property_dialog; //!< The file property dialog type.
        struct font_color_dialog; //!< The font and color dialog type.
        struct oudia_diagram_dialog; //!< The OuDia diagram dialog type.
        struct train_kind_dialog; //!< The train kind dialog type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace dialog
    {
        using train_kind_type =
            bobura::model::train_kind<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::color>::type
            >;
    }}
#endif

    //! The type list for the dialogs.
    using dialog_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog::about_dialog,
                about_dialog<
                    boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    boost::mpl::at<setting_type_list, type::setting::settings>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog::file_property_dialog,
                file_property_dialog<
                    boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog::font_color_dialog,
                font_color_dialog<
                    boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    boost::mpl::at<common_type_list, type::size>::type,
                    boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                    boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
                    boost::mpl::at<ui_type_list, type::ui::color>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog::oudia_diagram_dialog,
                oudia_diagram_dialog<
                    boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    boost::mpl::at<common_type_list, type::size>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog::train_kind_dialog,
                train_kind_dialog<
                    boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    boost::mpl::at<common_type_list, type::size>::type,
                    detail::dialog::train_kind_type,
                    boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                    boost::mpl::at<ui_type_list, type::ui::color>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>;


    /**** Model *************************************************************/

    namespace type { namespace model
    {
        struct model;          //!< The model type.
        struct station_grade_type_set; //!< The station grade type set type.
        struct reader_selector; //!< The reader selector type.
        struct reader_set;     //!< The reader set type.
        struct writer_selector; //!< The writer selector type.
        struct writer_set;     //!< The writer set type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace model
    {
        using font_color_type =
            bobura::model::timetable_info::font_color<
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::color>::type
            >;
        using font_color_set_type = bobura::model::timetable_info::font_color_set<font_color_type>;
        using station_grade_type_set_type =
            bobura::model::station_info::grade_type_set<boost::mpl::at<common_type_list, type::string>::type>;
        using select_oudia_diagram_type =
            bobura::model::serializer::select_oudia_diagram<
                boost::mpl::at<dialog_type_list, type::dialog::oudia_diagram_dialog>::type
            >;
        using grade_type = station_grade_type_set_type::grade_type;
        using station_type = bobura::model::station<boost::mpl::at<common_type_list, type::string>::type, grade_type>;
        using distance_type = boost::rational<boost::mpl::at<common_type_list, type::size>::type>;
        using station_location_type = bobura::model::timetable_info::station_location<station_type, distance_type>;
        using train_kind_type =
            bobura::model::train_kind<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::color>::type
            >;
        using time_type =
            bobura::model::train_info::time<
                boost::mpl::at<common_type_list, type::size>::type,
                bobura::model::train_info::time_span<boost::mpl::at<common_type_list, type::difference>::type>
            >;
        using stop_type =
            bobura::model::train_info::stop<time_type, boost::mpl::at<common_type_list, type::string>::type>;
        using train_type =
            bobura::model::train<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                stop_type
            >;
        using station_interval_calculator_type =
            bobura::model::timetable_info::station_interval_calculator<station_location_type, train_type>;
        using speed_type = boost::rational<boost::mpl::at<common_type_list, type::size>::type>;
        using timetable_type =
            bobura::model::timetable<
                boost::mpl::at<common_type_list, type::string>::type,
                station_location_type,
                station_interval_calculator_type,
                train_kind_type,
                train_type,
                speed_type,
                font_color_set_type,
                bobura::model::message::timetable_observer_set
            >;
    }}
#endif

    //! The model type list.
    using model_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::model,
                timetable_model<
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    message::timetable_model_observer_set
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::station_grade_type_set, detail::model::station_grade_type_set_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::reader_selector,
                model::serializer::reader_selector<
                    boost::mpl::at<common_type_list, type::input_stream_iterator>::type, detail::model::timetable_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::reader_set,
                model::serializer::reader_set<
                    boost::mpl::at<common_type_list, type::input_stream_iterator>::type,
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::pull_parser>::type,
                    detail::model::station_grade_type_set_type,
                    detail::model::select_oudia_diagram_type,
                    boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type,
                    boost::mpl::at<locale_type_list, type::locale::windia_file_encoder>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::writer_selector,
                model::serializer::writer_selector<
                    boost::mpl::at<common_type_list, type::output_stream>::type,
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::path>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::writer_set,
                model::serializer::writer_set<
                    boost::mpl::at<common_type_list, type::output_stream>::type,
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>;


    /**** View **************************************************************/

    namespace type { namespace view
    {
        struct view;           //!< The view type.
        struct diagram_header; //!< The diagram header type.
        struct diagram_time_line_list; //!< The diagram time line list type.
        struct diagram_station_line_list; //!< The diagram station line list type.
        struct diagram_train_line_list; //!< The diagram train line list type.
        struct scale_list;     //!< The scale list type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace view
    {
        using model_type = boost::mpl::at<model_type_list, type::model::model>::type;
        using station_location_type = model_type::timetable_type::station_location_type;
        using train_type = model_type::timetable_type::train_type;
        using diagram_selection_observer_set_type =
            bobura::message::diagram_selection_observer_set<station_location_type, train_type>;
        using selection_type =
            bobura::view::diagram::selection<station_location_type, train_type, diagram_selection_observer_set_type>;
        using diagram_header_type =
            bobura::view::diagram::header<
                model_type, selection_type, boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type
            >;
        using diagram_time_line_list_type =
            bobura::view::diagram::time_line_list<
                model_type, selection_type, boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type
            >;
        using diagram_station_line_list_type =
            bobura::view::diagram::station_line_list<
                model_type,
                selection_type,
                boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                boost::mpl::at<model_type_list, type::model::station_grade_type_set>::type
            >;
        using diagram_train_line_list_type =
            bobura::view::diagram::train_line_list<
                model_type,
                selection_type,
                boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;
    }}
#endif

    //! The view type list.
    using view_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::view::view,
                bobura::diagram_view<
                    detail::view::diagram_header_type,
                    detail::view::diagram_time_line_list_type,
                    detail::view::diagram_station_line_list_type,
                    detail::view::diagram_train_line_list_type,
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    detail::view::selection_type,
                    boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                    boost::mpl::at<ui_type_list, type::ui::fast_solid_background>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
                >
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::view::diagram_header, detail::view::diagram_header_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::view::diagram_time_line_list, detail::view::diagram_time_line_list_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::view::diagram_station_line_list, detail::view::diagram_station_line_list_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::view::diagram_train_line_list, detail::view::diagram_train_line_list_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::view::scale_list,
                bobura::view::scale_list<
                    boost::rational<boost::mpl::at<common_type_list, type::size>::type>,
                    boost::mpl::at<common_type_list, type::size>::type,
                    boost::mpl::at<common_type_list, type::string>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>;


    /**** Loading and Saving ************************************************/

    namespace type { namespace load_save
    {
        struct new_file;       //!< The file initialization.
        struct load_from_file; //!< The file loading.
        struct save_to_file;   //!< The file saving.
        struct confirm_file_save; //!< The file save confirmation.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace load_save
    {
        using save_to_file_type =
            bobura::load_save::save_to_file<
                boost::mpl::at<model_type_list, type::model::model>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
                boost::mpl::at<model_type_list, type::model::writer_selector>::type,
                boost::mpl::at<model_type_list, type::model::writer_set>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;
        using confirm_file_save_type =
            bobura::load_save::confirm_file_save<
                boost::mpl::at<model_type_list, type::model::model>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                save_to_file_type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;

    }}
#endif

    //! The type list for the miscellaneous processings.
    using load_save_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::load_save::new_file,
                load_save::new_file<
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    detail::load_save::confirm_file_save_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::load_save::load_from_file,
                load_save::load_from_file<
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                    boost::mpl::at<common_dialog_type_list, type::common_dialog::file_open_dialog>::type,
                    detail::load_save::confirm_file_save_type,
                    boost::mpl::at<model_type_list, type::model::reader_selector>::type,
                    boost::mpl::at<model_type_list, type::model::reader_set>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::load_save::save_to_file, detail::load_save::save_to_file_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::load_save::confirm_file_save, detail::load_save::confirm_file_save_type>,
        tetengo2::meta::assoc_list_end
        >>>>;


}


#endif
