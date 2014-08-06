/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <string>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/station_info/grade.h>
#include <bobura/model/station.h>
#include <bobura/model/timetable.h>
#include <bobura/model/timetable_info/font_color_set.h>
#include <bobura/model/timetable_info/station_interval_calculator.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>
#include <bobura/model/train_info/time_span.h>
#include <bobura/model/train_kind.h>

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
        struct widget_traits;  //!< The widget traits type.
        struct widget_details_traits; //!< The widget details traits type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using position_type = std::pair<difference_type, difference_type>;
        using dimension_type = std::pair<size_t, size_t>;
        using string_type = std::string;
        using io_string_type = std::string;
        using exception_string_type = std::string;
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using encoder_type  = tetengo2::text::encoder<internal_encoding_type, encoding_type>;
        using io_encoding_type = tetengo2::text::encoding::locale<io_string_type, encoding_details_type>;
        using io_encoder_type  = tetengo2::text::encoder<internal_encoding_type, io_encoding_type>;
        using ui_encoding_type =
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::widget>::type::string_type, encoding_details_type
            >;
        using ui_encoder_type  = tetengo2::text::encoder<internal_encoding_type, ui_encoding_type>;
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
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget_traits, detail::widget_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget_details_traits, detail::widget_details_traits_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>;


    /**** Model *************************************************************/

    namespace type { namespace model
    {
        struct font;           //!< The font type.
        struct font_color;     //!< The font and color type.
        struct font_color_set; //!< The font and color set type.
        struct grade_type_set; //!< The station grade type set type.
        struct station;        //!< The station type.
        struct station_location; //!< The station location type.
        struct train_kind;     //!< The train kind type.
        struct time_span;      //!< The time span type.
        struct time;           //!< The time type.
        struct stop;           //!< The stop type.
        struct train;          //!< The train type.
        struct station_interval_calculator; //!< The station interval calculator type.
        struct operating_distance; //!< The operating distance type.
        struct speed;          //!< The speed type.
        struct timetable;      //!< The timetable type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace model
    {
        using font_type =
            tetengo2::gui::drawing::font<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >;
        using font_color_set_type = bobura::model::timetable_info::font_color_set<font_type>;
        using grade_type_set_type =
            bobura::model::station_info::grade_type_set<boost::mpl::at<type_list, type::string>::type>;
        using operating_distance_type = boost::mpl::at<type_list, type::size>::type;
        using station_location_type =
            bobura::model::timetable_info::station_location<
                boost::mpl::at<type_list, type::string>::type, operating_distance_type
            >;
        using train_kind_type = bobura::model::train_kind<boost::mpl::at<type_list, type::string>::type>;
        using time_span_type = bobura::model::train_info::time_span<boost::mpl::at<type_list, type::difference>::type>;
        using time_type =
            bobura::model::train_info::time<
                boost::mpl::at<type_list, type::size>::type, boost::mpl::at<type_list, type::difference>::type
            >;
        using stop_type =
            bobura::model::train_info::stop<
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::difference>::type,
                boost::mpl::at<type_list, type::string>::type
            >;
        using train_type =
            bobura::model::train<
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::difference>::type,
                boost::mpl::at<type_list, type::string>::type
            >;
        using station_interval_calculator_type =
            bobura::model::timetable_info::station_interval_calculator<
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::difference>::type,
                boost::mpl::at<type_list, type::string>::type,
                operating_distance_type
            >;
        using speed_type = boost::mpl::at<type_list, type::size>::type;
    }}
#endif

    //! The model type list.
    using model_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::font, detail::model::font_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::font_color_set, detail::model::font_color_set_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::grade_type_set, detail::model::grade_type_set_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::station, bobura::model::station<boost::mpl::at<type_list, type::string>::type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::station_location, detail::model::station_location_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::train_kind, detail::model::train_kind_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::time_span, detail::model::time_span_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::time, detail::model::time_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::stop, detail::model::stop_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::train, detail::model::train_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::station_interval_calculator, detail::model::station_interval_calculator_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::operating_distance, detail::model::operating_distance_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::speed, detail::model::speed_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::timetable,
                bobura::model::timetable<
                    boost::mpl::at<type_list, type::size>::type,
                    boost::mpl::at<type_list, type::difference>::type,
                    boost::mpl::at<type_list, type::string>::type,
                    detail::model::operating_distance_type,
                    detail::model::speed_type,
                    detail::model::font_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>;


    /**** Serialization *****************************************************/

    namespace type { namespace serialization
    {
        struct select_oudia_diagram; //!< The OuDia diagram selector type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace serialization
    {
        using input_stream_iterator_type =
            boost::spirit::multi_pass<
                std::istreambuf_iterator<boost::mpl::at<type_list, type::io_string>::type::value_type>
            >;
        struct select_oudia_diagram_type
        {
            using size_type = boost::mpl::at<type_list, type::size>::type;

            using string_type = boost::mpl::at<type_list, type::string>::type;

            using encoder_type = boost::mpl::at<type_list, type::encoder>::type;

            using abstract_window_type =
                tetengo2::gui::widget::abstract_window<
                    boost::mpl::at<type_list, type::widget_traits>::type,
                    boost::mpl::at<type_list, type::widget_details_traits>::type,
                    boost::mpl::at<detail_type_list, type::detail::menu>::type
                >;

            using message_catalog_type =
                tetengo2::message::message_catalog<
                    input_stream_iterator_type, string_type, size_type, encoder_type, encoder_type
                >;

            string_type m_wanted;

            select_oudia_diagram_type(abstract_window_type&, string_type, const message_catalog_type&)
            :
            m_wanted()
            {}

            explicit select_oudia_diagram_type(string_type wanted)
            :
            m_wanted(std::move(wanted))
            {}

            template <typename Iterator>
            Iterator operator()(const Iterator first, const Iterator last)
            const
            {
                return std::find(first, last, m_wanted);
            }

        };
    }}
#endif

    //! The serialization type list.
    using serialization_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::select_oudia_diagram, detail::serialization::select_oudia_diagram_type
            >,
        tetengo2::meta::assoc_list_end
        >;


}}


#endif
