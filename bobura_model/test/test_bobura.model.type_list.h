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
#include <boost/predef.h>

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

        template <typename DetailTypeList>
        using encoding_details_type = typename boost::mpl::at<DetailTypeList, type::detail::encoding>::type;

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

    }
#endif

    /*!
        \brief The common type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    using common_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, detail::difference_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::io_string, detail::io_string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::encoder, detail::encoder_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::io_encoder, detail::io_encoder_type<DetailTypeList>>,
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
        using size_type = model::detail::size_type;

        using difference_type = model::detail::difference_type;

        using string_type = model::detail::string_type;

        using position_type = std::pair<difference_type, difference_type>;

        using dimension_type = std::pair<size_t, size_t>;

        template <typename DetailTypeList>
        using widget_details_type = typename boost::mpl::at<DetailTypeList, type::detail::widget>::type;

        template <typename DetailTypeList>
        using encoding_details_type = typename boost::mpl::at<DetailTypeList, type::detail::encoding>::type;

        template <typename DetailTypeList>
        using internal_encoding_type =
            tetengo2::text::encoding::locale<string_type, encoding_details_type<DetailTypeList>>;

#if BOOST_COMP_MSVC
        template <typename DetailTypeList>
        using ui_string_type = typename boost::mpl::at<DetailTypeList, type::detail::widget>::type::string_type; // Ignore type list type duplication check.
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
        using drawing_details_type = typename boost::mpl::at<DetailTypeList, type::detail::drawing>::type;

        template <typename DetailTypeList>
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                widget_details_type<DetailTypeList>,
                drawing_details_type<DetailTypeList>,
                typename boost::mpl::at<DetailTypeList, type::detail::icon>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::alert>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::cursor>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::scroll>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::message_handler>::type,
                typename boost::mpl::at<DetailTypeList, type::detail::virtual_key>::type
            >;

        template <typename DetailTypeList>
        using menu_details_type = typename boost::mpl::at<DetailTypeList, type::detail::menu>::type;

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
        \brief The UI type list.

        \tparam DetailTypeList A detail type list.
    */
    template <typename DetailTypeList>
    using ui_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::abstract_window, detail::ui::abstract_window_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::window, detail::ui::window_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::font, detail::ui::font_type<DetailTypeList>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::color, detail::ui::color_type>,
        tetengo2::meta::assoc_list_end
        >>>>;


}}


#endif
