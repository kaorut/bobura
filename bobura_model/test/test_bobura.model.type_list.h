/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

#include <cstddef>
#include <string>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_bobura.model.detail_type_list.h"


namespace test_bobura { namespace model
{
    /**** Common ************************************************************/

    namespace type
    {
        struct size;           //!< The size type.
        struct difference;     //!< The difference type.
        struct string;         //!< The string type.
        struct io_string;      //!< The I/O string type.
        struct encoder;        //!< The encoder type.
        struct io_encoder;     //!< The I/O encoder type.
        struct operating_distance; //!< The operating distance type.
        struct speed;          //!< The speed type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using string_type = std::string;
        using io_string_type = std::string;
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using encoder_type  = tetengo2::text::encoder<internal_encoding_type, encoding_type>;
        using io_encoding_type = tetengo2::text::encoding::locale<io_string_type, encoding_details_type>;
        using io_encoder_type  = tetengo2::text::encoder<internal_encoding_type, io_encoding_type>;
        using operating_distance_type = size_type;
        using speed_type = size_type;
    }
#endif

    //! The common type list.
    using type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, detail::difference_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::io_string, detail::io_string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::encoder, detail::encoder_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::io_encoder, detail::io_encoder_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::operating_distance, detail::operating_distance_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::speed, detail::speed_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>;


    /**** UI ****************************************************************/

    namespace type { namespace ui
    {
        struct abstract_window; //!< The abstract window type.
        struct window;         //!< The window type.
        struct font;           //!< The font type.
        struct color;          //!< The color type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        using size_type = boost::mpl::at<type_list, type::size>::type;
        using difference_type = boost::mpl::at<type_list, type::difference>::type;
        using string_type = boost::mpl::at<type_list, type::string>::type;
        using position_type = std::pair<difference_type, difference_type>;
        using dimension_type = std::pair<size_t, size_t>;
        using widget_details_type = boost::mpl::at<detail_type_list, type::detail::widget>::type;
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using ui_encoding_type =
            tetengo2::text::encoding::locale<widget_details_type::string_type, encoding_details_type>;
        using ui_encoder_type  = tetengo2::text::encoder<internal_encoding_type, ui_encoding_type>;
        using exception_string_type = std::string;
        using exception_encoding_type = tetengo2::text::encoding::locale<exception_string_type, encoding_details_type>;
        using exception_encoder_type = tetengo2::text::encoder<internal_encoding_type, exception_encoding_type>;
        using widget_traits_type =
            tetengo2::gui::widget::widget_traits<
                size_type,
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                ui_encoder_type,
                exception_encoder_type
            >;
        using drawing_details_type = boost::mpl::at<detail_type_list, type::detail::drawing>::type;
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                widget_details_type,
                drawing_details_type,
                boost::mpl::at<detail_type_list, type::detail::icon>::type,
                boost::mpl::at<detail_type_list, type::detail::alert>::type,
                boost::mpl::at<detail_type_list, type::detail::cursor>::type,
                boost::mpl::at<detail_type_list, type::detail::scroll>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
            >;
        using menu_details_type = boost::mpl::at<detail_type_list, type::detail::menu>::type;
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;
        using window_type =
            tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;
        using font_type = tetengo2::gui::drawing::font<string_type, size_type, drawing_details_type>;
        using color_type = tetengo2::gui::drawing::color;
    }}
#endif

    //! The UI type list.
    using ui_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::abstract_window, detail::ui::abstract_window_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::window, detail::ui::window_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::font, detail::ui::font_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::color, detail::ui::color_type>,
        tetengo2::meta::assoc_list_end
        >>>>;


}}


#endif
