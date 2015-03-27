/*! \file
    \brief The definition of bobura::model::serializer::json_writer.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <type_traits>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/predef.h>
#include <boost/rational.hpp>
#include <boost/utility.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/json_writer.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer
{
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    class json_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder>::impl :
        private boost::noncopyable
    {
    public:
        // types

        using size_type = Size;

        using difference_type = Difference;

        using string_type = String;

        using output_stream_type = OutputStream;

        using operating_distance_type = OperatingDistance;

        using speed_type = Speed;

        using font_type = Font;

        using encoder_type = Encoder;

        using base_type =
            writer<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                font_type
            >;

        using timetable_type = typename base_type::timetable_type;


        // virtual functions

        boost::filesystem::path extension_impl()
        const
        {
            return boost::filesystem::path{ TETENGO2_TEXT(".btt") };
        }

        void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        {
            output_stream << array_begin();

            new_line(1, output_stream);
            write_header(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_font_color_set(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_station_locations(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_train_kinds(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_down_trains(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_up_trains(timetable, 1, output_stream);

            new_line(0, output_stream);
            output_stream << array_end();

            new_line(0, output_stream);
        }


    private:
        // types

        using station_location_type = typename timetable_type::station_location_type;

        using train_kind_type = typename timetable_type::train_kind_type;

        using train_type = typename timetable_type::train_type;

        using stops_type = typename train_type::stops_type;

        using stop_type = typename train_type::stop_type;

        using time_type = typename stop_type::time_type;

        using font_color_set_type = typename timetable_type::font_color_set_type;

        using font_color_type = typename font_color_set_type::font_color_type;

        using color_type = typename font_color_type::color_type;

        using char_type = typename string_type::value_type;

        using output_char_type = typename output_stream_type::char_type;

        using output_string_type = std::basic_string<output_char_type>;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }

        static const output_string_type& comma()
        {
            static const output_string_type singleton{ TETENGO2_TEXT(",") };
            return singleton;
        }

        static const output_string_type& space()
        {
            static const output_string_type singleton{ TETENGO2_TEXT(" ") };
            return singleton;
        }

        static const output_string_type& array_begin()
        {
            static const output_string_type singleton{ TETENGO2_TEXT("[") };
            return singleton;
        }

        static const output_string_type& array_end()
        {
            static const output_string_type singleton{ TETENGO2_TEXT("]") };
            return singleton;
        }

        static const output_string_type& object_begin()
        {
            static const output_string_type singleton{ TETENGO2_TEXT("{") };
            return singleton;
        }

        static const output_string_type& object_end()
        {
            static const output_string_type singleton{ TETENGO2_TEXT("}") };
            return singleton;
        }

        static const string_type quote(const string_type& string)
        {
            static const string_type quotation_symbol{ TETENGO2_TEXT("\"") };
            return quotation_symbol + string + quotation_symbol;
        }

        static void new_line(const size_type level, output_stream_type& output_stream)
        {
            output_stream << std::endl;
            output_stream << output_string_type(level * 4, output_char_type(TETENGO2_TEXT(' ')));
        }

        static void write_object_key(const string_type& key, output_stream_type& output_stream)
        {
            output_stream << encoder().encode(quote(key)) << output_string_type{ TETENGO2_TEXT(": ") };
        }

        static void write_object_entry(
            const string_type&  key,
            const string_type&  value,
            output_stream_type& output_stream
        )
        {
            write_object_key(key, output_stream);
            output_stream << encoder().encode(quote(value));
        }

        template <typename Integer>
        static void write_object_entry(
            const string_type&  key,
            const Integer       value,
            output_stream_type& output_stream,
            const typename std::enable_if<std::is_integral<Integer>::value>::type* const = nullptr
        )
        {
            write_object_key(key, output_stream);
            output_stream << value;
        }

        template <typename Integer>
        static void write_object_entry(
            const string_type&              key,
            const boost::rational<Integer>& value,
            output_stream_type&             output_stream
        )
        {
            write_object_key(key, output_stream);
            output_stream << boost::rational_cast<Integer>(value);
        }

        static void write_object_entry(
            const string_type&  key,
            const bool          value,
            output_stream_type& output_stream
        )
        {
            write_object_key(key, output_stream);
            write_bool(value, output_stream);
        }

        static void write_bool(const bool value, output_stream_type& output_stream)
        {
            output_stream <<
                (value ? output_string_type{ TETENGO2_TEXT("true") } : output_string_type{ TETENGO2_TEXT("false") });
        }

        static void write_header(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << object_begin();

            new_line(level + 1, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("company_name") }, timetable.company_name(), output_stream);
            output_stream << comma();

            new_line(level + 1, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("line_name") }, timetable.line_name(), output_stream);
            output_stream << comma();

            new_line(level + 1, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("note") }, timetable.note(), output_stream);

            new_line(level, output_stream);
            output_stream << object_end();
        }

        static void write_font_color_set(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << object_begin();

            const auto& font_color_set = timetable.font_color_set();
            auto output = false;
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("background") },
                    font_color_set.background(),
                    font_color_set_type::default_().background(),
                    level + 1,
                    output_stream,
                    !output
                );
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("company_line_name") },
                    font_color_set.company_line_name(),
                    font_color_set_type::default_().company_line_name(),
                    level + 1,
                    output_stream,
                    !output
                );
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("note") },
                    font_color_set.note(),
                    font_color_set_type::default_().note(),
                    level + 1,
                    output_stream,
                    !output
                );
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("local_station") },
                    font_color_set.local_station(),
                    font_color_set_type::default_().local_station(),
                    level + 1,
                    output_stream,
                    !output
                );
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("principal_station") },
                    font_color_set.principal_station(),
                    font_color_set_type::default_().principal_station(),
                    level + 1,
                    output_stream,
                    !output
                );
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("local_terminal_station") },
                    font_color_set.local_terminal_station(),
                    font_color_set_type::default_().local_terminal_station(),
                    level + 1,
                    output_stream,
                    !output
                );
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("principal_terminal_station") },
                    font_color_set.principal_terminal_station(),
                    font_color_set_type::default_().principal_terminal_station(),
                    level + 1,
                    output_stream,
                    !output
                );
            output |=
                write_font_color_set_element(
                    string_type{ TETENGO2_TEXT("train_name") },
                    font_color_set.train_name(),
                    font_color_set_type::default_().train_name(),
                    level + 1,
                    output_stream,
                    !output
                );

            if (output)
                new_line(level, output_stream);
            output_stream << object_end();
        }

        static bool write_font_color_set_element(
            const string_type&  key,
            const color_type&   color,
            const color_type&   default_color,
            const size_type     level,
            output_stream_type& output_stream,
            const bool          first_element
        )
        {
            if (color == default_color)
                return false;

            if (!first_element)
                output_stream << comma();

            new_line(level, output_stream);
            write_object_entry(key, to_string(color), output_stream);

            return true;
        }

        static bool write_font_color_set_element(
            const string_type&  key,
            const font_type&    font,
            const font_type&    default_font,
            const size_type     level,
            output_stream_type& output_stream,
            const bool          first_element
        )
        {
            if (font == default_font)
                return false;

            if (!first_element)
                output_stream << comma();

            new_line(level, output_stream);
            write_object_key(key, output_stream);
            write_font(font, output_stream);

            return true;
        }

        static bool write_font_color_set_element(
            const string_type&     key,
            const font_color_type& font_color,
            const font_color_type& default_font_color,
            const size_type        level,
            output_stream_type&    output_stream,
            const bool             first_element
        )
        {
            if (font_color == default_font_color)
                return false;

            if (!first_element)
                output_stream << comma();

            new_line(level, output_stream);
            write_object_key(key, output_stream);

            output_stream << array_begin();

            write_font(font_color.font(), output_stream);
            output_stream << comma() << space();

            output_stream << encoder().encode(quote(to_string(font_color.color())));

            output_stream << array_end();

            return true;
        }

        static void write_font(const font_type& font, output_stream_type& output_stream)
        {
            output_stream << array_begin();

            output_stream << encoder().encode(quote(font.family()));
            output_stream << comma() << space();

            output_stream << font.size();
            output_stream << comma() << space();

            write_bool(font.bold(), output_stream);
            output_stream << comma() << space();

            write_bool(font.italic(), output_stream);
            output_stream << comma() << space();

            write_bool(font.underline(), output_stream);
            output_stream << comma() << space();

            write_bool(font.strikeout(), output_stream);

            output_stream << array_end();
        }

        static void write_station_locations(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.station_locations().empty())
            {
                std::for_each(
                    timetable.station_locations().begin(),
                    boost::prior(timetable.station_locations().end()),
                    [level, &output_stream](const station_location_type& station_location)
                    {
                        write_station_location(station_location, level, output_stream, false);
                    }
                );
                write_station_location(*boost::prior(timetable.station_locations().end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_station_location(
            const station_location_type& station_location,
            const size_type              level,
            output_stream_type&          output_stream,
            const bool                   last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << object_begin();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("name") }, station_location.get_station().name(), output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("grade") }, station_location.get_station().grade().name(), output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("show_down_arrival_times") },
                station_location.get_station().shows_down_arrival_times(),
                output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("show_up_arrival_times") },
                station_location.get_station().shows_up_arrival_times(),
                output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("note") }, station_location.get_station().note(), output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("operating_distance") },
                station_location.operating_distance() * 10,
                output_stream
            );

            new_line(level + 1, output_stream);
            output_stream << object_end();
            if (!last)
                output_stream << comma();
        }

        static void write_train_kinds(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.train_kinds().empty())
            {
                std::for_each(
                    timetable.train_kinds().begin(),
                    boost::prior(timetable.train_kinds().end()),
                    [level, &output_stream](const train_kind_type& train_kind)
                    {
                        write_train_kind(train_kind, level, output_stream, false);
                    }
                );
                write_train_kind(*boost::prior(timetable.train_kinds().end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_train_kind(
            const train_kind_type& train_kind,
            const size_type        level,
            output_stream_type&    output_stream,
            const bool             last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << object_begin();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("name") }, train_kind.name(), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("abbreviation") }, train_kind.abbreviation(), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("color") }, to_string(train_kind.color()), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("weight") }, static_cast<int>(train_kind.weight()), output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type{ TETENGO2_TEXT("line_style") }, static_cast<int>(train_kind.line_style()), output_stream
            );

            new_line(level + 1, output_stream);
            output_stream << object_end();
            if (!last)
                output_stream << comma();
        }

        static string_type to_string(const color_type& color)
        {
            std::basic_ostringstream<char_type> stream{};

            stream <<
                boost::basic_format<char_type>(string_type{ TETENGO2_TEXT("%02X%02X%02X") }, std::locale::classic()) %
                static_cast<int>(color.red()) %
                static_cast<int>(color.green()) %
                static_cast<int>(color.blue());

            return stream.str();
        }

        static void write_down_trains(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.down_trains().empty())
            {
                std::for_each(
                    timetable.down_trains().begin(),
                    boost::prior(timetable.down_trains().end()),
                    [level, &output_stream](const train_type& train)
                    {
                        write_train(train, level, output_stream, false);
                    }
                );
                write_train(*boost::prior(timetable.down_trains().end()), level, output_stream, true);

                new_line(level, output_stream);
            }


            output_stream << array_end();
        }

        static void write_up_trains(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.up_trains().empty())
            {
                std::for_each(
                    timetable.up_trains().begin(),
                    boost::prior(timetable.up_trains().end()),
                    [level, &output_stream](const train_type& train)
                    {
                        write_train(train, level, output_stream, false);
                    }
                );
                write_train(*boost::prior(timetable.up_trains().end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_train(
            const train_type&   train,
            const size_type     level,
            output_stream_type& output_stream,
            const bool          last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << object_begin();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("number") }, train.number(), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("kind_index") }, train.kind_index(), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("name") }, train.name(), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("name_number") }, train.name_number(), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type{ TETENGO2_TEXT("note") }, train.note(), output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_key(string_type{ TETENGO2_TEXT("stops") }, output_stream);
            write_stops(train.stops(), level + 2, output_stream);

            new_line(level + 1, output_stream);
            output_stream << object_end();
            if (!last)
                output_stream << comma();
        }

        static void write_stops(
            const stops_type&   stops,
            const size_type     level,
            output_stream_type& output_stream
        )
        {
            output_stream << array_begin();

            if (!stops.empty())
            {
                std::for_each(
                    stops.begin(),
                    boost::prior(stops.end()),
                    [level, &output_stream](const stop_type& stop) { write_stop(stop, level, output_stream, false); }
                );
                write_stop(*boost::prior(stops.end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_stop(
            const stop_type&    stop,
            const size_type     level,
            output_stream_type& output_stream,
            const bool          last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << array_begin();

            output_stream << time_representation(stop.arrival());
            output_stream << comma() << space();

            output_stream << time_representation(stop.departure());
            output_stream << comma() << space();

            output_stream << boolean_representation(stop.operational());
            output_stream << comma() << space();

            output_stream << encoder().encode(quote(stop.platform()));

            output_stream << array_end();
            if (!last)
                output_stream << comma();
        }

        static output_string_type time_representation(const time_type& time)
        {
            if (!time.initialized())
                return output_string_type{ TETENGO2_TEXT("    -1") };

            using size_type = typename time_type::size_type;
            const auto hours_minutes_seconds = time.hours_minutes_seconds();
            const size_type representation =
                hours_minutes_seconds.hours() * 10000 +
                hours_minutes_seconds.minutes() * 100 +
                hours_minutes_seconds.seconds();
            std::basic_ostringstream<output_char_type> stream{};
            stream <<
                boost::basic_format<output_char_type>(TETENGO2_TEXT("%6d"), std::locale::classic()) % representation;
            return stream.str();
        }

        static output_string_type boolean_representation(const bool value)
        {
            return value ? output_string_type{ TETENGO2_TEXT(" true") } : output_string_type{ TETENGO2_TEXT("false") };
        }


    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    json_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder>::json_writer()
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    json_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder>::~json_writer()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    boost::filesystem::path
    json_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder>::extension_impl()
    const
    {
        return m_p_impl->extension_impl();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    void json_writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font, Encoder>::write_impl(
        const timetable_type& timetable,
        output_stream_type&   output_stream
    )
    {
        m_p_impl->write_impl(timetable, output_stream);
    }


    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class json_writer<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::output_stream_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::locale_type_list_type::timetable_file_encoder_type
    >;
#endif

    template class json_writer<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::output_stream_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type,
        typename test::locale_type_list_type::timetable_file_encoder_type
    >;


}}}
