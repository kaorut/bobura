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
#include <ostream>
#include <string>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/message/timetable_observer_set.h>
#include <bobura/model/serializer/reader.h>
#include <bobura/model/serializer/reader_selector.h>
#include <bobura/model/serializer/reader_set.h>
#include <bobura/model/serializer/writer.h>
#include <bobura/model/serializer/writer_selector.h>
#include <bobura/model/serializer/writer_set.h>
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
        struct encoder;        //!< The encoder type.
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
        using exception_string_type = std::string;
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using encoder_type  = tetengo2::text::encoder<internal_encoding_type, encoding_type>;
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
        tetengo2::meta::assoc_list<boost::mpl::pair<type::encoder, detail::encoder_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget_traits, detail::widget_traits_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget_details_traits, detail::widget_details_traits_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>;


    /**** Model *************************************************************/

    namespace type { namespace model
    {
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
        using color_type = tetengo2::gui::drawing::color;
        using font_color_type = bobura::model::timetable_info::font_color<font_type, color_type>;
        using font_color_set_type = bobura::model::timetable_info::font_color_set<font_color_type>;
        using grade_type_set_type =
            bobura::model::station_info::grade_type_set<boost::mpl::at<type_list, type::string>::type>;
        using grade_type = grade_type_set_type::grade_type;
        using station_type = bobura::model::station<boost::mpl::at<type_list, type::string>::type, grade_type>;
        using station_location_type =
            bobura::model::timetable_info::station_location<station_type, boost::mpl::at<type_list, type::size>::type>;
        using train_kind_type = bobura::model::train_kind<boost::mpl::at<type_list, type::string>::type, color_type>;
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
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::difference>::type
            >;
        using station_interval_calculator_type =
            bobura::model::timetable_info::station_interval_calculator<station_location_type, train_type>;
    }}
#endif

    //! The model type list.
    using model_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::font_color_set, detail::model::font_color_set_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::grade_type_set, detail::model::grade_type_set_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::station, detail::model::station_type>,
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
            boost::mpl::pair<
                type::model::timetable,
                bobura::model::timetable<
                    boost::mpl::at<type_list, type::string>::type,
                    detail::model::station_location_type,
                    detail::model::station_interval_calculator_type,
                    detail::model::train_kind_type,
                    detail::model::train_type,
                    boost::mpl::at<type_list, type::size>::type,
                    detail::model::font_color_set_type,
                    bobura::model::message::timetable_observer_set
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>;


    /**** Serialization *****************************************************/

    namespace type { namespace serialization
    {
        struct reader;         //!< The reader type.
        struct reader_selector; //!< The reader selector type.
        struct json_reader;    //!< The JSON reader type.
        struct bzip2_reader;   //!< The bzip2 reader type.
        struct oudia_reader;   //!< The OuDia reader type.
        struct windia_reader;  //!< The WinDIA reader type.
        struct reader_set;     //!< The reader set type.
        struct writer;         //!< The writer type.
        struct writer_selector; //!< The writer selector type.
        struct json_writer;    //!< The JSON writer type.
        struct bzip2_writer;   //!< The bzip2 writer type.
        struct writer_set;     //!< The writer set type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace serialization
    {
        using io_string_type = std::string;
        using input_stream_iterator_type =
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;
        using grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;
        using pull_parser_type =
            tetengo2::text::pull_parser<
                input_stream_iterator_type, grammar_type, int, double, boost::mpl::at<type_list, type::size>::type
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
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type =
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::string>::type, encoding_details_type>;
        using timetable_file_encoding_type = tetengo2::text::encoding::locale<io_string_type, encoding_details_type>;
        using timetable_file_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, timetable_file_encoding_type>;
        using reader_set_type =
            bobura::model::serializer::reader_set<
                test_bobura::model::detail::serialization::input_stream_iterator_type,
                boost::mpl::at<model_type_list, type::model::timetable>::type,
                pull_parser_type,
                boost::mpl::at<model_type_list, type::model::grade_type_set>::type,
                select_oudia_diagram_type,
                timetable_file_encoder_type,
                timetable_file_encoder_type
            >;
        using output_stream_type = std::basic_ostream<io_string_type::value_type>;
        using writer_set_type =
            bobura::model::serializer::writer_set<
                output_stream_type, boost::mpl::at<model_type_list,
                type::model::timetable>::type,
                timetable_file_encoder_type
            >;
    }}
#endif

    //! The serialization type list.
    using serialization_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::reader,
                bobura::model::serializer::reader<
                    detail::serialization::input_stream_iterator_type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::reader_selector,
                bobura::model::serializer::reader_selector<
                    detail::serialization::input_stream_iterator_type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::json_reader, detail::serialization::reader_set_type::json_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::bzip2_reader, detail::serialization::reader_set_type::bzip2_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::oudia_reader, detail::serialization::reader_set_type::oudia_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::windia_reader, detail::serialization::reader_set_type::windia_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::serialization::reader_set, detail::serialization::reader_set_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::writer,
                bobura::model::serializer::writer<
                    detail::serialization::output_stream_type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::writer_selector,
                bobura::model::serializer::writer_selector<
                    detail::serialization::output_stream_type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::json_writer, detail::serialization::writer_set_type::json_writer_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::bzip2_writer, detail::serialization::writer_set_type::bzip2_writer_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::serialization::writer_set, detail::serialization::writer_set_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>;


}}


#endif
