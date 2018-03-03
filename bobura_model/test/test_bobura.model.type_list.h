/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

#include <cstddef>
#include <string>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>


namespace test_bobura { namespace model {
    namespace type_list {
    /**** Common *****************************************************************************************************/

#if !defined(DOCUMENTATION)
        namespace detail { namespace common {
            using size_type = std::size_t;

            using difference_type = std::ptrdiff_t;

            using string_type = std::string;

            using operating_distance_type = size_type;

            using speed_type = size_type;

        }}
#endif

        /*!
            \brief The common type list.
        */
        struct common
        {
            //! The size type.
            using size_type = detail::common::size_type;

            //! The difference type.
            using difference_type = detail::common::difference_type;

            //! The string type.
            using string_type = detail::common::string_type;

            //! The operating distance type.
            using operating_distance_type = detail::common::operating_distance_type;

            //! The speed type.
            using speed_type = detail::common::speed_type;
        };


        /**** User Interface *****************************************************************************************/

#if !defined(DOCUMENTATION)
        namespace detail { namespace ui {
            using size_type = type_list::detail::common::size_type;

            using string_type = type_list::detail::common::string_type;

            template <typename DetailTypeList>
            using drawing_details_type = typename DetailTypeList::drawing_type;

            template <typename DetailTypeList>
            using font_type =
                tetengo2::gui::drawing::font<string_type, size_type, drawing_details_type<DetailTypeList>>;

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
            //! The font type.
            using font_type = detail::ui::font_type<DetailTypeList>;

            //! The color type.
            using color_type = detail::ui::color_type;
        };
    }
}}


#endif
