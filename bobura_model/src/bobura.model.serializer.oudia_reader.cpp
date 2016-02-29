/*! \file
    \brief The definition of bobura::model::serializer::oudia_reader.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <ios>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>
#include <boost/utility/string_ref.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/oudia_reader.h>
#include <bobura/model/serializer/select_oudia_diagram.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer
{
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename SelectDiagram,
        typename Font,
        typename Encoder
    >
    class oudia_reader<
        Size, Difference, String, ForwardIterator, OperatingDistance, Speed, SelectDiagram, Font, Encoder
    >::impl :
        private boost::noncopyable
    {
    public:
        // types

        using size_type = Size;

        using difference_type = Difference;

        using string_type = String;

        using iterator = ForwardIterator;

        using operating_distance_type = OperatingDistance;

        using speed_type = Speed;

        using select_diagram_type = SelectDiagram;

        using font_type = Font;

        using encoder_type = Encoder;

        using base_type =
            reader<size_type, difference_type, string_type, iterator, operating_distance_type, speed_type, font_type>;

        using timetable_type = typename base_type::timetable_type;

        using error_type = typename base_type::error_type;

        using station_grade_type_set_type = station_info::grade_type_set<string_type>;


        // constructors and destructor

        explicit impl(std::unique_ptr<select_diagram_type> p_select_diagram)
        :
        m_p_select_diagram(std::move(p_select_diagram))
        {
            if (!m_p_select_diagram)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Diagram selector is nullptr."));
        }


        // functions

        bool selects_impl(const iterator first, const iterator last)
        {
            auto mutable_first = first;
            const auto key_value = parse_line(next_line(mutable_first, last));
            const auto file_type_ = parse_file_type(key_value.second);

            return
                key_value.first == string_type{ TETENGO2_TEXT("FileType") } &&
                file_type_.m_name == string_type{ TETENGO2_TEXT("OuDia") } &&
                file_type_.m_major_version == 1 &&
                (1 <= file_type_.m_minor_version && file_type_.m_minor_version <= 2);
        }

        std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        {
            if (!selects_impl(first, last))
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            
            const auto selected_diagram_name = select_diagram(first, last);
            if (!selected_diagram_name)
            {
                error = error_type::canceled;
                return std::unique_ptr<timetable_type>{};
            }

            return read_timetable(first, last, error, *selected_diagram_name);
        }


    private:
        // types

        using input_char_type = typename iterator::value_type;

        using input_string_type = std::basic_string<input_char_type>;

        using string_ref_type =
            boost::basic_string_ref<
                typename string_type::value_type, std::char_traits<typename string_type::value_type>
            >;

        using char_type = typename string_type::value_type;

        using station_location_type = typename timetable_type::station_location_type;

        using station_type = typename station_location_type::station_type;

        using station_grade_type = typename station_type::grade_type;

        using train_kind_type = typename timetable_type::train_kind_type;

        using color_type = typename train_kind_type::color_type;

        using train_type = typename timetable_type::train_type;

        using direction_type = typename train_type::direction_type;

        struct file_type
        {
            string_type m_name;
            int         m_major_version;
            int         m_minor_version;

            file_type(string_type name, int major_version, int minor_version)
            :
            m_name(std::move(name)),
            m_major_version(major_version),
            m_minor_version(minor_version)
            {}

        };

        class state
        {
        public:
            virtual ~state()
            = default;

            bool parse(const string_type& line)
            {
                auto key_value = parse_line(line);
                if (key_value.first.empty())
                    return false;

                return parse_impl(key_value.first, std::move(key_value.second));
            }

            bool entered()
            {
                return entered_impl();
            }

            bool leaving()
            {
                return leaving_impl();
            }

        private:
            virtual bool parse_impl(const string_type& key, string_type value)
            {
                boost::ignore_unused(key, value);

                return true;
            }

            virtual bool entered_impl()
            {
                return true;
            }

            virtual bool leaving_impl()
            {
                return true;
            }

        };

        class unknown_state : public state
        {
        public:
            virtual ~unknown_state()
            = default;

        };

        class initial_state : public state
        {
        public:
            explicit initial_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~initial_state()
            = default;

        private:
            timetable_type& m_timetable;

            virtual bool parse_impl(const string_type& key, string_type value)
            override
            {
                if (key == string_type{ TETENGO2_TEXT("Comment") })
                    m_timetable.set_note(std::move(value));

                return true;
            }

        };

        class rosen_state : public state
        {
        public:
            explicit rosen_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~rosen_state()
            = default;

        private:
            timetable_type& m_timetable;

            virtual bool parse_impl(const string_type& key, string_type value)
            override
            {
                if (key == string_type{ TETENGO2_TEXT("Rosenmei") })
                    m_timetable.set_line_name(std::move(value));

                return true;
            }

        };

        class eki_state : public state
        {
        public:
            explicit eki_state(timetable_type& timetable)
            :
            m_timetable(timetable),
            m_ekimei(),
            m_ekijikokukeisiki(),
            m_ekikibo()
            {}

            virtual ~eki_state()
            = default;

        private:
            static const station_grade_type& to_station_grade(
                const string_type& ekijikokukeisiki,
                const string_type& ekikibo
            )
            {
                const auto both_arrival_and_departure =
                    ekijikokukeisiki == string_type{ TETENGO2_TEXT("Jikokukeisiki_Hatsuchaku") };
                const auto principal = ekikibo == string_type{ TETENGO2_TEXT("Ekikibo_Syuyou") };

                if (both_arrival_and_departure)
                {
                    if (principal)
                        return station_grade_type_set_type::principal_terminal_type::instance();
                    else
                        return station_grade_type_set_type::local_terminal_type::instance();
                }
                else
                {
                    if (principal)
                        return station_grade_type_set_type::principal_type::instance();
                    else
                        return station_grade_type_set_type::local_type::instance();
                }
            }

            static bool shows_down_arrival_times(const string_type& ekijikokukeisiki)
            {
                return ekijikokukeisiki == string_type{ TETENGO2_TEXT("Jikokukeisiki_KudariChaku") };
            }

            static bool shows_up_arrival_times(const string_type& ekijikokukeisiki)
            {
                return ekijikokukeisiki == string_type{ TETENGO2_TEXT("Jikokukeisiki_NoboriChaku") };
            }

            timetable_type& m_timetable;

            string_type m_ekimei;

            string_type m_ekijikokukeisiki;

            string_type m_ekikibo;

            virtual bool parse_impl(const string_type& key, string_type value)
            override
            {
                if (key == string_type{ TETENGO2_TEXT("Ekimei") })
                    m_ekimei = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Ekijikokukeisiki") })
                    m_ekijikokukeisiki = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Ekikibo") })
                    m_ekikibo = std::move(value);

                return true;
            }

            virtual bool leaving_impl()
            override
            {
                m_timetable.insert_station_location(
                    m_timetable.station_locations().end(),
                    station_location_type{
                        station_type{
                            std::move(m_ekimei),
                            to_station_grade(m_ekijikokukeisiki, m_ekikibo),
                            shows_down_arrival_times(m_ekijikokukeisiki),
                            shows_up_arrival_times(m_ekijikokukeisiki),
                            string_type{}
                        },
                        m_timetable.station_locations().empty() ?
                        0 : m_timetable.station_locations().back().operating_distance() + 1
                    }
                );

                return true;
            }

        };

        class ressyasyubetsu_state : public state
        {
        public:
            explicit ressyasyubetsu_state(timetable_type& timetable)
            :
            m_timetable(timetable),
            m_syubetsumei(),
            m_ryakusyou(),
            m_diagram_sen_color(),
            m_diagram_sen_style(),
            m_diagram_sen_is_bold()
            {}

            virtual ~ressyasyubetsu_state()
            = default;

        private:
            using weight_type = typename train_kind_type::weight_type;

            using line_style_type = typename train_kind_type::line_style_type;

            static weight_type to_weight(const string_type& weight_string)
            {
                if (weight_string == string_type{ TETENGO2_TEXT("1") })
                    return weight_type::bold;
                else
                    return weight_type::normal;
            }

            static line_style_type to_line_style(const string_type& line_style_string)
            {
                if      (line_style_string == string_type{ TETENGO2_TEXT("SenStyle_Hasen") })
                    return line_style_type::dashed;
                else if (line_style_string == string_type{ TETENGO2_TEXT("SenStyle_Tensen") })
                    return line_style_type::dotted;
                else if (line_style_string == string_type{ TETENGO2_TEXT("SenStyle_Ittensasen") })
                    return line_style_type::dot_dashed;
                else
                    return line_style_type::solid;
            }

            timetable_type& m_timetable;

            string_type m_syubetsumei;

            string_type m_ryakusyou;

            string_type m_diagram_sen_color;

            string_type m_diagram_sen_style;

            string_type m_diagram_sen_is_bold;

            virtual bool parse_impl(const string_type& key, string_type value)
            override
            {
                if (key == string_type{ TETENGO2_TEXT("Syubetsumei") })
                    m_syubetsumei = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Ryakusyou") })
                    m_ryakusyou = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("DiagramSenColor") })
                    m_diagram_sen_color = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("DiagramSenStyle") })
                    m_diagram_sen_style = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("DiagramSenIsBold") })
                    m_diagram_sen_is_bold = std::move(value);

                return true;
            }

            virtual bool leaving_impl()
            override
            {
                auto abbreviation = m_ryakusyou.empty() ? m_syubetsumei : std::move(m_ryakusyou);
                auto color = to_color(m_diagram_sen_color);
                if (!color)
                    return false;
                m_timetable.insert_train_kind(
                    m_timetable.train_kinds().end(),
                    train_kind_type{
                        std::move(m_syubetsumei),
                        std::move(abbreviation),
                        train_kind_type::default_().diagram_font(),
                        std::move(*color),
                        to_weight(m_diagram_sen_is_bold),
                        to_line_style(m_diagram_sen_style),
                        train_kind_type::default_().timetable_font(),
                        train_kind_type::default_().timetable_color()
                    }
                );

                return true;
            }

        };

        class dia_state : public state
        {
        public:
            explicit dia_state(string_type& current_diagram_name)
            :
            m_current_diagram_name(current_diagram_name)
            {}

            virtual ~dia_state()
            = default;

        private:
            string_type& m_current_diagram_name;

            virtual bool parse_impl(const string_type& key, string_type value)
            override
            {
                if (key == string_type{ TETENGO2_TEXT("DiaName") })
                    m_current_diagram_name = std::move(value);

                return true;
            }

        };

        class kudari_state : public state
        {
        public:
            explicit kudari_state(direction_type& direction)
            :
            m_direction(direction)
            {}

            virtual ~kudari_state()
            = default;

        private:
            direction_type& m_direction;

            virtual bool entered_impl()
            override
            {
                m_direction = direction_type::down;
                return true;
            }

        };

        class nobori_state : public state
        {
        public:
            explicit nobori_state(direction_type& direction)
            :
            m_direction(direction)
            {}

            virtual ~nobori_state()
            = default;

        private:
            direction_type& m_direction;

            virtual bool entered_impl()
            override
            {
                m_direction = direction_type::up;
                return true;
            }

        };

        class ressya_state : public state
        {
        public:
            explicit ressya_state(timetable_type& timetable, const direction_type direction)
            :
            m_timetable(timetable),
            m_direction(direction),
            m_syubetsu(),
            m_ressyabangou(),
            m_ressyamei(),
            m_gousuu(),
            m_eki_jikoku()
            {}

            virtual ~ressya_state()
            = default;

        private:
            using stop_type = typename train_type::stop_type;

            using time_type = typename stop_type::time_type;

            struct insert_stop
            {
                train_type& m_train;

                explicit insert_stop(train_type& train)
                :
                m_train(train)
                {}

                void operator()(stop_type& stop)
                {
                    m_train.insert_stop(m_train.stops().end(), std::move(stop));
                }

            };

            static boost::optional<std::vector<stop_type>> parse_stops(
                const string_type&                               stops_string,
                const typename std::vector<stop_type>::size_type station_location_count,
                const bool                                       direction_down
            )
            {
                const auto stop_strings = split(stops_string, char_type(TETENGO2_TEXT(',')));

                std::vector<stop_type> stops{};
                stops.reserve(stop_strings.size());
                for (const auto& stop_string: stop_strings)
                {
                    auto stop = parse_stop(stop_string);
                    if (!stop)
                        return boost::none;
                    stops.push_back(std::move(*stop));
                }
                if (stops.size() > station_location_count)
                    return boost::none;

                std::fill_n(
                    std::back_inserter(stops),
                    station_location_count - stops.size(),
                    stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{})
                );
                
                if (!direction_down)
                    std::reverse(stops.begin(), stops.end());

                return stops;
            }

            static boost::optional<stop_type> parse_stop(const string_type& stop_string)
            {
                const auto kind_time = split(stop_string, char_type(TETENGO2_TEXT(';')));
                if (kind_time.empty())
                    return boost::none;

                const auto stopping = kind_time[0] == string_type{ TETENGO2_TEXT("1") } && kind_time.size() >= 2;
                const auto operational = !stopping && kind_time.size() >= 2;
                if (!stopping && !operational)
                    return stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{});

                const auto arrival_departure = split(kind_time[1], char_type(TETENGO2_TEXT('/')));
                if (arrival_departure.empty())
                    return boost::none;

                auto arrival = boost::make_optional(time_type::uninitialized());
                auto departure = boost::make_optional(time_type::uninitialized());
                if (arrival_departure.size() < 2)
                {
                    departure = parse_time(arrival_departure[0]);
                    if (!departure)
                        return boost::none;
                }
                else
                {
                    arrival = parse_time(arrival_departure[0]);
                    if (!arrival)
                        return boost::none;
                    departure = parse_time(arrival_departure[1]);
                    if (!departure)
                        return boost::none;
                }

                return
                    boost::make_optional(
                        stop_type(std::move(*arrival), std::move(*departure), operational, string_type{})
                    );
            }

            static boost::optional<time_type> parse_time(const string_type& time_string)
            {
                if (time_string.empty())
                    return boost::make_optional(time_type::uninitialized());
                if (time_string.size() > 4)
                    return boost::none;

                const auto hours =
                    time_string.length() > 2 ?
                    to_number<unsigned int>(time_string.substr(0, time_string.length() - 2)) :
                    boost::make_optional<unsigned int>(0);
                if (!hours || *hours >= 24)
                    return boost::none;
                const auto minutes =
                    time_string.length() > 2 ?
                    to_number<unsigned int>(time_string.substr(time_string.length() - 2)) :
                    to_number<unsigned int>(time_string);
                if (!minutes || *minutes >= 60)
                    return boost::none;

                return boost::make_optional(time_type{ *hours, *minutes, 0 });
            }

            timetable_type& m_timetable;

            const direction_type m_direction;

            string_type m_houkou;

            string_type m_syubetsu;

            string_type m_ressyabangou;

            string_type m_ressyamei;

            string_type m_gousuu;

            string_type m_eki_jikoku;

            string_type m_bikou;

            virtual bool parse_impl(const string_type& key, string_type value)
            override
            {
                if      (key == string_type{ TETENGO2_TEXT("Houkou") })
                    m_houkou = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Syubetsu") })
                    m_syubetsu = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Ressyabangou") })
                    m_ressyabangou = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Ressyamei") })
                    m_ressyamei = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Gousuu") })
                    m_gousuu = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("EkiJikoku") })
                    m_eki_jikoku = std::move(value);
                else if (key == string_type{ TETENGO2_TEXT("Bikou") })
                    m_bikou = std::move(value);

                return true;
            }

            virtual bool leaving_impl()
            override
            {
                if (m_houkou.empty() || m_syubetsu.empty())
                    return true;

                const auto train_kind_index = to_number<typename timetable_type::size_type>(m_syubetsu);
                if (!train_kind_index || *train_kind_index >= m_timetable.train_kinds().size())
                    return false;

                train_type train{ m_direction, m_ressyabangou, *train_kind_index, m_ressyamei, m_gousuu, m_bikou };

                auto stops =
                    parse_stops(
                        m_eki_jikoku,
                        m_timetable.station_locations().size(),
                        m_houkou == string_type{ TETENGO2_TEXT("Kudari") }
                    );
                if (!stops || stops->size() != m_timetable.station_locations().size())
                    return false;
                std::for_each(stops->begin(), stops->end(), insert_stop(train));

                if (m_direction == direction_type::down)
                    m_timetable.insert_down_train(m_timetable.down_trains().end(), std::move(train));
                else
                    m_timetable.insert_up_train(m_timetable.up_trains().end(), std::move(train));

                return true;
            }

        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }

        static std::vector<string_type> collect_diagram_names(const iterator first, const iterator last)
        {
            std::vector<string_type> names{};

            auto next_line_first = first;
            for (;;)
            {
                const auto input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                auto key_value = parse_line(input_line);
                if (key_value.first.empty() || key_value.second.empty())
                    continue;
                if (key_value.first != string_type{ TETENGO2_TEXT("DiaName") })
                    continue;

                names.push_back(std::move(key_value.second));
            }

            return names;
        }

        static string_type next_line(iterator& first, const iterator last)
        {
            skip_line_breaks(first, last);
            const auto next_line_break = std::find_if(first, last, line_break);
            auto line = encoder().decode(input_string_type{ first, next_line_break });
            first = next_line_break;
            return line;
        }

        static void skip_line_breaks(iterator& first, const iterator last)
        {
            while (first != last && line_break(*first))
                ++first;
        }

        static bool line_break(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\r')) ||
                character == input_char_type(TETENGO2_TEXT('\n'));
        }

        template <typename T>
        static boost::optional<T> to_number(const string_type& number_string)
        {
            try
            {
                return boost::make_optional(boost::lexical_cast<T>(number_string));
            }
            catch (const boost::bad_lexical_cast&)
            {
                return boost::none;
            }
        }

        static boost::optional<color_type> to_color(const string_type& color_string)
        {
            if (color_string.length() != 8)
                return boost::none;

            const auto red = from_hex_string<unsigned int>(color_string.substr(2, 2));
            if (!red)
                return boost::none;
            const auto green = from_hex_string<unsigned int>(color_string.substr(4, 2));
            if (!green)
                return boost::none;
            const auto blue = from_hex_string<unsigned int>(color_string.substr(6, 2));
            if (!blue)
                return boost::none;
            return
                boost::make_optional(
                    color_type{
                        static_cast<unsigned char>(*red),
                        static_cast<unsigned char>(*green),
                        static_cast<unsigned char>(*blue)
                    }
                );
        }

        template <typename T>
        static boost::optional<T> from_hex_string(const string_type& hex_string)
        {
            std::basic_istringstream<char_type> stream{ hex_string };
            T result = 0;
            stream >> std::hex >> result;
            return boost::make_optional(stream.eof() || stream.good(), std::move(result));
        }

        static std::unique_ptr<state> dispatch(
            const string_type& line,
            timetable_type&    timetable,
            const string_type& selected_diagram_name,
            string_type&       current_diagram_name,
            direction_type&    direction
        )
        {
            if (line.empty() || line[line.length() - 1] != char_type(TETENGO2_TEXT('.')))
                return std::unique_ptr<state>{};

            const auto name = string_ref_type{ line }.substr(0, line.length() - 1);
            if (name.empty())
            {
                return tetengo2::stdalt::make_unique<initial_state>(timetable);
            }
            else if (name == string_ref_type(TETENGO2_TEXT("Rosen")))
            {
                return tetengo2::stdalt::make_unique<rosen_state>(timetable);
            }
            else if (name == string_ref_type(TETENGO2_TEXT("Eki")))
            {
                return tetengo2::stdalt::make_unique<eki_state>(timetable);
            }
            else if (name == string_ref_type(TETENGO2_TEXT("Ressyasyubetsu")))
            {
                return tetengo2::stdalt::make_unique<ressyasyubetsu_state>(timetable);
            }
            else if (name == string_ref_type(TETENGO2_TEXT("Dia")))
            {
                return tetengo2::stdalt::make_unique<dia_state>(current_diagram_name);
            }
            else if (!current_diagram_name.empty() && current_diagram_name == selected_diagram_name)
            {
                if      (name == string_ref_type(TETENGO2_TEXT("Kudari")))
                    return tetengo2::stdalt::make_unique<kudari_state>(direction);
                else if (name == string_ref_type(TETENGO2_TEXT("Nobori")))
                    return tetengo2::stdalt::make_unique<nobori_state>(direction);
                else if (name == string_ref_type(TETENGO2_TEXT("Ressya")))
                    return tetengo2::stdalt::make_unique<ressya_state>(timetable, direction);
                else
                    return tetengo2::stdalt::make_unique<unknown_state>();
            }
            else
            {
                return tetengo2::stdalt::make_unique<unknown_state>();
            }
        }

        static std::pair<string_type, string_type> parse_line(const string_type& line)
        {
            auto splitted = split(line, char_type(TETENGO2_TEXT('=')));
            if (splitted.size() < 2)
                return std::make_pair(line, string_type{});

            return std::make_pair(std::move(splitted[0]), remove_escape_sequences(std::move(splitted[1])));
        }

        static std::vector<string_type> split(const string_type& string, const char_type splitter)
        {
            std::vector<string_type> result{};
            boost::split(result, string, [splitter](const char_type character) { return character == splitter; });
            return result;
        }

        static string_type remove_escape_sequences(string_type string)
        {
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\r\\n") }, string_type{ TETENGO2_TEXT(" ") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\r") }, string_type{ TETENGO2_TEXT(" ") });
            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\n") }, string_type{ TETENGO2_TEXT(" ") });

            boost::replace_all(string, string_type{ TETENGO2_TEXT("\\") }, string_type{});

            return string;
        }

        static file_type parse_file_type(const string_type& file_type_string)
        {
            auto splitted = split(file_type_string, char_type(TETENGO2_TEXT('.')));
            auto name = splitted.size() >= 1 ? std::move(splitted[0]) : string_type{};
            const auto major_version = splitted.size() >= 2 ? to_number<int>(splitted[1]) : boost::none;
            const auto minor_version = splitted.size() >= 3 ? to_number<int>(splitted[2]) : boost::none;
            return file_type(std::move(name), major_version ? *major_version : 0, minor_version ? *minor_version : 0);
        }


        // variables

        const std::unique_ptr<select_diagram_type> m_p_select_diagram;


        // functions

        boost::optional<string_type> select_diagram(const iterator first, const iterator last)
        {
            auto diagram_names = collect_diagram_names(first, last);
            if (diagram_names.empty())
                return string_type{};

            const auto found = (*m_p_select_diagram)(diagram_names.begin(), diagram_names.end());
            if (found == diagram_names.end())
                return boost::none;

            return std::move(*found);
        }

        std::unique_ptr<timetable_type> read_timetable(
            const iterator     first,
            const iterator     last,
            error_type&        error,
            const string_type& selected_diagram_name
        )
        {
            auto p_timetable = tetengo2::stdalt::make_unique<timetable_type>();
            string_type current_diagram_name{};
            auto direction = direction_type::down;

            std::unique_ptr<state> p_state = tetengo2::stdalt::make_unique<initial_state>(*p_timetable);
            auto next_line_first = first;
            for (;;)
            {
                const auto input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                auto p_new_state =
                    dispatch(input_line, *p_timetable, selected_diagram_name, current_diagram_name, direction);
                if (p_new_state)
                {
                    if (!p_state->leaving())
                    {
                        error = error_type::corrupted;
                        return std::unique_ptr<timetable_type>{};
                    }
                    p_state = std::move(p_new_state);
                    if (!p_state->entered())
                    {
                        error = error_type::corrupted;
                        return std::unique_ptr<timetable_type>{};
                    }
                }
                else
                {
                    if (!p_state->parse(input_line))
                    {
                        error = error_type::corrupted;
                        return std::unique_ptr<timetable_type>{};
                    }
                }
            }

            if (!dynamic_cast<initial_state*>(p_state.get()))
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }

            return std::move(p_timetable);
        }


    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename SelectDiagram,
        typename Font,
        typename Encoder
    >
    oudia_reader<
        Size, Difference, String, ForwardIterator, OperatingDistance, Speed, SelectDiagram, Font, Encoder
    >::oudia_reader(std::unique_ptr<select_diagram_type> p_select_diagram)
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(p_select_diagram)))
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename SelectDiagram,
        typename Font,
        typename Encoder
    >
    oudia_reader<
        Size, Difference, String, ForwardIterator, OperatingDistance, Speed, SelectDiagram, Font, Encoder
    >::~oudia_reader()
    noexcept
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename SelectDiagram,
        typename Font,
        typename Encoder
    >
    bool
    oudia_reader<
        Size, Difference, String, ForwardIterator, OperatingDistance, Speed, SelectDiagram, Font, Encoder
    >::selects_impl(const iterator first, const iterator last)
    {
        return m_p_impl->selects_impl(first, last);
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename SelectDiagram,
        typename Font,
        typename Encoder
    >
    std::unique_ptr<typename oudia_reader<
        Size, Difference, String, ForwardIterator, OperatingDistance, Speed, SelectDiagram, Font, Encoder
    >::timetable_type>
    oudia_reader<
        Size, Difference, String, ForwardIterator, OperatingDistance, Speed, SelectDiagram, Font, Encoder
    >::read_impl(const iterator first, const iterator last, error_type& error)
    {
        return m_p_impl->read_impl(first, last, error);
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

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

            using select_oudia_diagram_type =
                select_oudia_diagram<
                    oudia_diagram_dialog<
                        typename type_list::traits<detail_type_list_type>::dialog_type,
                        typename type_list::common::size_type
                    >
                >;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

            using select_oudia_diagram_type =
                select_oudia_diagram<
                    oudia_diagram_dialog<
                        typename type_list::traits<detail_type_list_type>::dialog_type,
                        typename type_list::common::size_type
                    >
                >;

            using select_oudia_diagram_for_test_type =
                select_oudia_diagram_for_test<typename type_list::common::string_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class oudia_reader<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::input_stream_iterator_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        application::select_oudia_diagram_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::locale_type_list_type::windia_file_encoder_type
    >;
#endif

    template class oudia_reader<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        test::select_oudia_diagram_type,
        typename test::ui_type_list_type::font_type,
        typename test::locale_type_list_type::windia_file_encoder_type
    >;

    template class oudia_reader<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        test::select_oudia_diagram_for_test_type,
        typename test::ui_type_list_type::font_type,
        typename test::locale_type_list_type::windia_file_encoder_type
    >;


}}}
