/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

#include <cstddef>
#include <string>
#include <utility>

#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_bobura.model.detail_type_list.h"


namespace test_bobura { namespace model { namespace type_list
{
    /**** Common *****************************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace common
    {
        using size_type = std::size_t;

        using difference_type = std::ptrdiff_t;

        using string_type = std::string;

        using io_string_type = std::string;

        template <typename DetailTypeList>
        using encoding_details_type = typename DetailTypeList::encoding_type;

        template <typename DetailTypeList>
        using internal_encoding_type =
            tetengo2::text::encoding::locale<string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using io_encoding_type =
            tetengo2::text::encoding::locale<io_string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using io_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, io_encoding_type<DetailTypeList>>;

        using operating_distance_type = size_type;

        using speed_type = size_type;

    }}
#endif

    /*!
        \brief The common type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    struct common
    {
        //! The size type.
        using size_type = detail::common::size_type;

        //! The difference type.
        using difference_type = detail::common::difference_type;

        //! The string type.
        using string_type = detail::common::string_type;

        //! The I/O string type.
        using io_string_type = detail::common::io_string_type;

        //! The encoder type.
        using encoder_type = detail::common::encoder_type<DetailTypeList>;

        //! The I/O encoder type.
        using io_encoder_type = detail::common::io_encoder_type<DetailTypeList>;

        //! The operating distance type.
        using operating_distance_type = detail::common::operating_distance_type;

        //! The speed type.
        using speed_type = detail::common::speed_type;

    };


    /**** User Interface *********************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        using size_type = type_list::detail::common::size_type;

        using difference_type = type_list::detail::common::difference_type;

        using string_type = type_list::detail::common::string_type;

        using position_type = std::pair<difference_type, difference_type>;

        using dimension_type = std::pair<size_t, size_t>;

        template <typename DetailTypeList>
        using widget_details_type = typename DetailTypeList::widget_type;

        template <typename DetailTypeList>
        using encoding_details_type = typename DetailTypeList::encoding_type;

        template <typename DetailTypeList>
        using internal_encoding_type =
            tetengo2::text::encoding::locale<string_type, encoding_details_type<DetailTypeList>>;

#if BOOST_COMP_MSVC
        template <typename DetailTypeList>
        using ui_string_type = typename DetailTypeList::widget_type::string_type; // Ignore type list type duplication check.
#else
        // The code below somehow causes a compilation error with VC++ 2013.
        template <typename DetailTypeList>
        using ui_string_type = typename widget_details_type<DetailTypeList>::string_type;
#endif

        template <typename DetailTypeList>
        using ui_encoding_type =
            tetengo2::text::encoding::locale<ui_string_type<DetailTypeList>, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using ui_encoder_type  =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, ui_encoding_type<DetailTypeList>>;

        using exception_string_type = std::string;

        template <typename DetailTypeList>
        using exception_encoding_type =
            tetengo2::text::encoding::locale<exception_string_type, encoding_details_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using exception_encoder_type =
            tetengo2::text::encoder<internal_encoding_type<DetailTypeList>, exception_encoding_type<DetailTypeList>>;

        template <typename DetailTypeList>
        using widget_traits_type =
            tetengo2::gui::widget::widget_traits<
                size_type,
                size_type,
                difference_type,
                string_type,
                position_type,
                dimension_type,
                ui_encoder_type<DetailTypeList>,
                exception_encoder_type<DetailTypeList>
            >;

        template <typename DetailTypeList>
        using drawing_details_type = typename DetailTypeList::drawing_type;

        template <typename DetailTypeList>
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                widget_details_type<DetailTypeList>,
                drawing_details_type<DetailTypeList>,
                typename DetailTypeList::icon_type,
                typename DetailTypeList::alert_type,
                typename DetailTypeList::cursor_type,
                typename DetailTypeList::scroll_type,
                typename DetailTypeList::message_handler_type,
                typename DetailTypeList::virtual_key_type
            >;

        template <typename DetailTypeList>
        using menu_details_type = typename DetailTypeList::menu_type;

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
        using font_type = tetengo2::gui::drawing::font<string_type, size_type, drawing_details_type<DetailTypeList>>;

        using color_type = tetengo2::gui::drawing::color;

    }}
#endif

    /*!
        \brief The user interface type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    struct ui
    {
        //! The abstract window type.
        using abstract_window_type = detail::ui::abstract_window_type<DetailTypeList>;

        //! The window type.
        using window_type = detail::ui::window_type<DetailTypeList>;

        //! The font type.
        using font_type = detail::ui::font_type<DetailTypeList>;

        //! The color type.
        using color_type = detail::ui::color_type;

    };
    

}}}


#endif
