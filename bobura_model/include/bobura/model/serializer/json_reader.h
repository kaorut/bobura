/*! \file
    \brief The definition of bobura::model::serializer::json_reader.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONREADER_H)
#define BOBURA_MODEL_SERIALIZER_JSONREADER_H

#include <cstddef>
#include <ios>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>
#include <bobura/model/station_info/grade.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reader.

        \tparam Size                A size type.
        \tparam Difference          A difference type.
        \tparam String              A string type.
        \tparam ForwardIterator     A forward iterator type.
        \tparam Integer             An integer type.
        \tparam Float               A floating point number type.
        \tparam OperatingDistance   An operating distance type.
        \tparam Speed               A speed type.
        \tparam ExecJsonReadingTask A JSON reading task execution type.
        \tparam Font                A font type.
        \tparam Encoder             An encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename Integer,
        typename Float,
        typename OperatingDistance,
        typename Speed,
        typename ExecJsonReadingTask,
        typename Font,
        typename Encoder
    >
    class json_reader : public reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The integer type.
        using integer_type = Integer;

        //! The float type.
        using float_type = Float;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The JSON reading task execution type.
        using exec_json_reading_task_type = ExecJsonReadingTask;

        //! The font type.
        using font_type = Font;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The grammar type.
        using grammar_type = tetengo2::text::grammar::json<iterator>;

        //! The pull parser type.
        using pull_parser_type =
            tetengo2::text::pull_parser<iterator, grammar_type, integer_type, float_type, size_type>;

        //! The push parser type.
        using push_parser_type = typename pull_parser_type::push_parser_type;

        //! The station grade type set type.
        using station_grade_type_set_type = station_info::grade_type_set<string_type>;

        //! The base type.
        using base_type =
            reader<size_type, difference_type, string_type, iterator, operating_distance_type, speed_type, font_type>;

        //! The timetable type.
        using timetable_type = typename base_type::timetable_type;

        //! The error type.
        using error_type = typename base_type::error_type;


        // constructors and destructor

        /*!
            \brief Creates a JSON reader.

            \param p_exec_json_reading_task A unique pointer to a JSON reading task execution.

            \throw std::invalid_argument When p_exec_json_reading_task is nullptr.
        */
        explicit json_reader(std::unique_ptr<exec_json_reading_task_type> p_exec_json_reading_task)
        :
        base_type(),
        m_p_exec_json_reading_task(std::move(p_exec_json_reading_task))
        {
            if (!m_p_exec_json_reading_task)
                BOOST_THROW_EXCEPTION(std::invalid_argument("JSON reading task execution is nullptr."));
        }

        /*!
            \brief Destroys the JSON reader.
        */
        virtual ~json_reader()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // types

        using font_color_set_type = typename timetable_type::font_color_set_type;

        using font_color_type = typename font_color_set_type::font_color_type;

        using color_type = typename font_color_type::color_type;

        using font_color_set_element_type = boost::variant<font_color_type, font_type, color_type>;

        using train_kind_index_type = typename timetable_type::size_type;

        using input_string_type = typename push_parser_type::string_type;

        using header_type = std::unordered_map<string_type, string_type>;

        using station_location_type = typename timetable_type::station_location_type;

        using station_type = typename station_location_type::station_type;

        using station_grade_type = typename station_type::grade_type;

        using train_kind_type = typename timetable_type::train_kind_type;

        using weight_type = typename train_kind_type::weight_type;

        using line_style_type = typename train_kind_type::line_style_type;

        using train_type = typename timetable_type::train_type;

        using direction_type = typename train_type::direction_type;

        using stop_type = typename train_type::stop_type;

        using time_type = typename stop_type::time_type;

        using element_type = typename pull_parser_type::element_type;

        using structure_begin_type = typename pull_parser_type::structure_begin_type;

        using structure_end_type = typename pull_parser_type::structure_end_type;

        using attribute_map_type = typename pull_parser_type::attribute_map_type;

        using value_type = typename pull_parser_type::value_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }

        static std::unique_ptr<timetable_type> read_timetable(pull_parser_type& pull_parser, error_type& error)
        {
            auto p_timetable = tetengo2::stdalt::make_unique<timetable_type>();

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            pull_parser.next();

            auto header = read_header(pull_parser);
            if (!header)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            {
                const auto found = header->find(string_type{ TETENGO2_TEXT("company_name") });
                if (found != header->end())
                    p_timetable->set_company_name(std::move(found->second));
            }
            {
                const auto found = header->find(string_type{ TETENGO2_TEXT("line_name") });
                if (found != header->end())
                    p_timetable->set_line_name(std::move(found->second));
            }
            {
                const auto found = header->find(string_type{ TETENGO2_TEXT("note") });
                if (found != header->end())
                    p_timetable->set_note(std::move(found->second));
            }

            auto font_color_set = read_font_color_set(pull_parser);
            if (!font_color_set)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            p_timetable->set_font_color_set(std::move(*font_color_set));

            auto stations = read_stations(pull_parser);
            if (!stations)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            for (auto& station: *stations)
                p_timetable->insert_station_location(p_timetable->station_locations().end(), std::move(station));

            auto train_kinds = read_train_kinds(pull_parser);
            if (!train_kinds)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            for (auto& train_kind: *train_kinds)
                p_timetable->insert_train_kind(p_timetable->train_kinds().end(), std::move(train_kind));

            auto down_trains = read_trains(pull_parser, direction_type::down, stations->size(), train_kinds->size());
            if (!down_trains)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            for (auto& train: *down_trains)
                p_timetable->insert_down_train(p_timetable->down_trains().end(), std::move(train));

            auto up_trains = read_trains(pull_parser, direction_type::up, stations->size(), train_kinds->size());
            if (!up_trains)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            for (auto& train: *up_trains)
                p_timetable->insert_up_train(p_timetable->up_trains().end(), std::move(train));

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            pull_parser.next();

            return std::move(p_timetable);
        }

        static boost::optional<header_type> read_header(pull_parser_type& pull_parser)
        {
            header_type header{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    break;

                header.insert(std::move(*member));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(header));
        }

        static boost::optional<font_color_set_type> read_font_color_set(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            auto background_color = font_color_set_type::default_().background();
            auto company_line_name_font_color = font_color_set_type::default_().company_line_name();
            auto note_font_color = font_color_set_type::default_().note();
            auto time_line_font_color = font_color_set_type::default_().time_line();
            auto local_station_font_color = font_color_set_type::default_().local_station();
            auto principal_station_font_color = font_color_set_type::default_().principal_station();
            auto local_terminal_station_font_color = font_color_set_type::default_().local_terminal_station();
            auto principal_terminal_station_font_color = font_color_set_type::default_().principal_terminal_station();
            auto train_name_font = font_color_set_type::default_().train_name();
            for (;;)
            {
                auto element = read_font_color_set_element(pull_parser);
                if (!element)
                    break;

                if      (element->first == string_type{ TETENGO2_TEXT("background") })
                {
                    if (element->second.which() != 2)
                        return boost::none;
                    background_color = std::move(boost::get<color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("company_line_name") })
                {
                    if (element->second.which() != 0)
                        return boost::none;
                    company_line_name_font_color = std::move(boost::get<font_color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("note") })
                {
                    if (element->second.which() != 0)
                        return boost::none;
                    note_font_color = std::move(boost::get<font_color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("time_line") })
                {
                    if (element->second.which() != 0)
                        return boost::none;
                    time_line_font_color = std::move(boost::get<font_color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("local_station") })
                {
                    if (element->second.which() != 0)
                        return boost::none;
                    local_station_font_color = std::move(boost::get<font_color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("principal_station") })
                {
                    if (element->second.which() != 0)
                        return boost::none;
                    principal_station_font_color = std::move(boost::get<font_color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("local_terminal_station") })
                {
                    if (element->second.which() != 0)
                        return boost::none;
                    local_terminal_station_font_color = std::move(boost::get<font_color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("principal_terminal_station") })
                {
                    if (element->second.which() != 0)
                        return boost::none;
                    principal_terminal_station_font_color = std::move(boost::get<font_color_type>(element->second));
                }
                else if (element->first == string_type{ TETENGO2_TEXT("train_name") })
                {
                    if (element->second.which() != 1)
                        return boost::none;
                    train_name_font = std::move(boost::get<font_type>(element->second));
                }
                else
                {
                    return boost::none;
                }
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    font_color_set_type{
                        std::move(background_color),
                        std::move(company_line_name_font_color),
                        std::move(note_font_color),
                        std::move(time_line_font_color),
                        std::move(local_station_font_color),
                        std::move(principal_station_font_color),
                        std::move(local_terminal_station_font_color),
                        std::move(principal_terminal_station_font_color),
                        std::move(train_name_font)
                    }
                );
        }

        static boost::optional<std::pair<string_type, font_color_set_element_type>> read_font_color_set_element(
            pull_parser_type& pull_parser
        )
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            const auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            auto value = read_font_color(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), std::move(*value)));
        }

        static boost::optional<font_color_set_element_type> read_font_color(pull_parser_type& pull_parser)
        {
            if (next_is_string(pull_parser))
            {
                auto color = read_color(pull_parser);
                if (!color)
                    return boost::none;
                return boost::make_optional<font_color_set_element_type>(std::move(*color));
            }

            return read_font_or_font_color(pull_parser);
        }

        static boost::optional<font_color_set_element_type> read_font_or_font_color(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            if (next_is_string(pull_parser))
            {
                auto font_name = read_string(pull_parser);
                if (!font_name)
                    return boost::none;
                auto font_size = read_integer<typename font_type::size_type>(pull_parser);
                if (!font_size)
                    return boost::none;
                auto font_bold = read_boolean(pull_parser);
                if (!font_bold)
                    return boost::none;
                auto font_italic = read_boolean(pull_parser);
                if (!font_italic)
                    return boost::none;
                auto font_underline = read_boolean(pull_parser);
                if (!font_underline)
                    return boost::none;
                auto font_strikeout = read_boolean(pull_parser);
                if (!font_strikeout)
                    return boost::none;

                if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                    return boost::none;
                pull_parser.next();

                return
                    boost::make_optional<font_color_set_element_type>(
                        font_type{
                            encoder().decode(std::move(*font_name)),
                            std::move(*font_size),
                            std::move(*font_bold),
                            std::move(*font_italic),
                            std::move(*font_underline),
                            std::move(*font_strikeout)
                        }
                    );
            }

            auto font = read_font_or_font_color(pull_parser);
            if (!font || font->which() != 1)
                return boost::none;

            auto color = read_color(pull_parser);
            if (!color)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional<font_color_set_element_type>(
                    font_color_type(boost::get<font_type>(std::move(*font)), std::move(*color))
                );

        }

        static boost::optional<color_type> read_color(pull_parser_type& pull_parser)
        {
            auto color_string = read_string(pull_parser);
            if (!color_string)
                return boost::none;
            return to_color(encoder().decode(std::move(*color_string)));
        }

        static boost::optional<std::vector<station_location_type>> read_stations(pull_parser_type& pull_parser)
        {
            std::vector<station_location_type> stations{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                auto station = read_station(pull_parser);
                if (!station)
                    break;

                stations.push_back(std::move(*station));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(stations));
        }

        static boost::optional<station_location_type> read_station(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            string_type name{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("name") })
                    return boost::none;

                name = std::move(member->second);
            }

            const station_grade_type* p_grade = nullptr;
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("grade") })
                    return boost::none;

                p_grade = to_station_grade(std::move(member->second));
                if (!p_grade)
                    return boost::none;
            }

            auto show_down_arrival_times = false;
            {
                auto member = read_boolean_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("show_down_arrival_times") })
                    return boost::none;

                show_down_arrival_times = std::move(member->second);
            }

            auto show_up_arrival_times = false;
            {
                auto member = read_boolean_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("show_up_arrival_times") })
                    return boost::none;

                show_up_arrival_times = std::move(member->second);
            }

            string_type note{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("note") })
                    return boost::none;

                note = std::move(member->second);
            }

            operating_distance_type operating_distance{};
            {
                auto member = read_integer_member<operating_distance_type>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("operating_distance") })
                    return boost::none;

                operating_distance = operating_distance_type{ member->second } / 10;
            }
            
            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    station_location_type{
                        station_type{
                            std::move(name),
                            *p_grade,
                            show_down_arrival_times,
                            show_up_arrival_times,
                            std::move(note)
                        },
                        std::move(operating_distance)
                    }
                );
        }

        static const station_grade_type* to_station_grade(const string_type& name)
        {
            if      (name == station_grade_type_set_type::local_type::instance().name())
                return &station_grade_type_set_type::local_type::instance();
            else if (name == station_grade_type_set_type::principal_type::instance().name())
                return &station_grade_type_set_type::principal_type::instance();
            else if (name == station_grade_type_set_type::local_terminal_type::instance().name())
                return &station_grade_type_set_type::local_terminal_type::instance();
            else if (name == station_grade_type_set_type::principal_terminal_type::instance().name())
                return &station_grade_type_set_type::principal_terminal_type::instance();
            else
                return nullptr;
        }

        static boost::optional<std::vector<train_kind_type>> read_train_kinds(pull_parser_type& pull_parser)
        {
            std::vector<train_kind_type> train_kinds{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                auto train_kind = read_train_kind(pull_parser);
                if (!train_kind)
                    break;

                train_kinds.push_back(std::move(*train_kind));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(train_kinds));
        }

        static boost::optional<train_kind_type> read_train_kind(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            string_type name{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("name") })
                    return boost::none;

                name = std::move(member->second);
            }

            string_type abbreviation{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("abbreviation") })
                    return boost::none;

                abbreviation = std::move(member->second);
            }

            boost::optional<color_type> color{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("color") })
                    return boost::none;

                color = to_color(std::move(member->second));
                if (!color)
                    return boost::none;
            }

            boost::optional<weight_type> weight{};
            {
                const auto member = read_integer_member<int>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("weight") })
                    return boost::none;

                weight = to_weight(member->second);
                if (!weight)
                    return boost::none;
            }

            boost::optional<line_style_type> line_style{};
            {
                const auto member = read_integer_member<int>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("line_style") })
                    return boost::none;

                line_style = to_line_style(member->second);
                if (!line_style)
                    return boost::none;
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    train_kind_type(std::move(name), std::move(abbreviation), std::move(*color), *weight, *line_style)
                );
        }

        static boost::optional<color_type> to_color(string_type color_string)
        {
            if (color_string.length() != 6)
                return boost::none;

            const auto color_value = to_color_value(std::move(color_string));

            return
                boost::make_optional(
                    color_type{
                        static_cast<unsigned char>((color_value / 0x010000) & 0x0000FF),
                        static_cast<unsigned char>((color_value / 0x000100) & 0x0000FF),
                        static_cast<unsigned char>(color_value & 0x0000FF)
                    }
                );
        }

        static unsigned int to_color_value(string_type color_string)
        {
            std::basic_istringstream<typename string_type::value_type> stream(std::move(color_string));

            unsigned int value = 0;
            stream >> std::hex >> value;

            return value;
        }

        static boost::optional<weight_type> to_weight(const int weight_integer)
        {
            switch (weight_integer)
            {
            case 0:
                return boost::make_optional(train_kind_type::weight_type::normal);
            case 1:
                return boost::make_optional(train_kind_type::weight_type::bold);
            default:
                return boost::none;
            }
        }

        static boost::optional<line_style_type> to_line_style(const int line_style_integer)
        {
            switch (line_style_integer)
            {
            case 0:
                return boost::make_optional(train_kind_type::line_style_type::solid);
            case 1:
                return boost::make_optional(train_kind_type::line_style_type::dashed);
            case 2:
                return boost::make_optional(train_kind_type::line_style_type::dotted);
            case 3:
                return boost::make_optional(train_kind_type::line_style_type::dot_dashed);
            default:
                return boost::none;
            }
        }

        static boost::optional<std::vector<train_type>> read_trains(
            pull_parser_type&    pull_parser,
            const direction_type direction,
            const std::size_t    station_count,
            const std::size_t    kind_count
        )
        {
            std::vector<train_type> trains{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                auto train = read_train(pull_parser, direction, station_count, kind_count);
                if (!train)
                    break;

                trains.push_back(std::move(*train));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(trains));
        }

        static boost::optional<train_type> read_train(
            pull_parser_type&    pull_parser,
            const direction_type direction,
            const std::size_t    station_count,
            const std::size_t    kind_count
        )
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            string_type number{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("number") })
                    return boost::none;

                number = std::move(member->second);
            }

            train_kind_index_type kind_index{};
            {
                auto member = read_integer_member<train_kind_index_type>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("kind_index") })
                    return boost::none;

                kind_index = std::move(member->second);
                if (kind_index >= kind_count)
                    return boost::none;
            }

            string_type name{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("name") })
                    return boost::none;

                name = std::move(member->second);
            }

            string_type name_number{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("name_number") })
                    return boost::none;

                name_number = std::move(member->second);
            }

            string_type note{};
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("note") })
                    return boost::none;

                note = std::move(member->second);
            }

            train_type train{
                direction, std::move(number), kind_index, std::move(name), std::move(name_number), std::move(note)
            };

            auto stops = read_stops(pull_parser);
            if (!stops)
                return boost::none;
            if (stops->size() > station_count)
                return boost::none;
            for (auto& stop: *stops)
                train.insert_stop(train.stops().end(), std::move(stop));
            for (std::size_t i = stops->size(); i < station_count; ++i)
                train.insert_stop(train.stops().end(), empty_stop());

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(train));
        }

        static stop_type empty_stop()
        {
            return stop_type{ time_type::uninitialized(), time_type::uninitialized(), false, string_type{} };
        }

        static boost::optional<std::vector<stop_type>> read_stops(pull_parser_type& pull_parser)
        {
            std::vector<stop_type> stops{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            const auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            if (key != "stops")
                return boost::none;
            pull_parser.next();

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                auto stop = read_stop(pull_parser);
                if (!stop)
                    break;

                stops.push_back(std::move(*stop));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(stops));
        }

        static boost::optional<stop_type> read_stop(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            auto arrival_input = read_integer<std::ptrdiff_t>(pull_parser);
            if (!arrival_input)
                return boost::none;
            const auto arrival_time = to_time(*arrival_input);
            if (!arrival_time)
                return boost::none;

            const auto departure_input = read_integer<std::ptrdiff_t>(pull_parser);
            if (!departure_input)
                return boost::none;
            const auto departure_time = to_time(*departure_input);
            if (!departure_time)
                return boost::none;

            const auto operational = read_boolean(pull_parser);
            if (!operational)
                return boost::none;

            auto platform = read_string(pull_parser);
            if (!platform)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    stop_type{
                        std::move(*arrival_time),
                        std::move(*departure_time),
                        *operational,
                        encoder().decode(std::move(*platform))
                    }
                );
        }

        static boost::optional<time_type> to_time(const std::ptrdiff_t input)
        {
            if (input < 0)
                return boost::make_optional(time_type::uninitialized());

            const std::size_t hours = (input / 10000) % 100;
            if (hours > 23)
                return boost::none;

            const std::size_t minutes = (input / 100) % 100;
            if (minutes > 59)
                return boost::none;

            const std::size_t seconds = input % 100;
            if (seconds > 59)
                return boost::none;

            return boost::make_optional(time_type{ hours, minutes, seconds });
        }

        static boost::optional<std::pair<string_type, string_type>> read_string_member(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            auto value = read_string(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    std::make_pair(encoder().decode(std::move(key)), encoder().decode(std::move(*value)))
                );
        }

        static boost::optional<input_string_type> read_string(pull_parser_type& pull_parser)
        {
            if (!pull_parser.has_next())
                return boost::none;
            const auto& element = pull_parser.peek();
            if (element.which() != 2)
                return boost::none;
            const auto& value = boost::get<value_type>(element);
            if (value.which() != 4)
                return boost::none;
            auto string = boost::get<input_string_type>(value);
            pull_parser.next();
            return boost::make_optional(std::move(string));
        }

        template <typename Int>
        static boost::optional<std::pair<string_type, Int>> read_integer_member(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            const auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            const auto value = read_integer<Int>(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), *value));
        }

        template <typename Int>
        static boost::optional<Int> read_integer(pull_parser_type& pull_parser)
        {
            if (!pull_parser.has_next())
                return boost::none;
            const auto& element = pull_parser.peek();
            if (element.which() != 2)
                return boost::none;
            const auto& value = boost::get<value_type>(element);
            if (value.which() != 2)
                return boost::none;
            const auto integer = boost::get<integer_type>(value);
            pull_parser.next();
            return boost::make_optional<Int>(integer);
        }

        static boost::optional<std::pair<string_type, bool>> read_boolean_member(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            const auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            const auto value = read_boolean(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), *value));
        }

        static boost::optional<bool> read_boolean(pull_parser_type& pull_parser)
        {
            if (!pull_parser.has_next())
                return boost::none;
            const auto& element = pull_parser.peek();
            if (element.which() != 2)
                return boost::none;
            const auto& value = boost::get<value_type>(element);
            if (value.which() != 0)
                return boost::none;
            const auto boolean = boost::get<bool>(value);
            pull_parser.next();
            return boost::make_optional(boolean);
        }

        static bool next_is_structure_begin(const pull_parser_type& pull_parser, const input_string_type& name)
        {
            if (!pull_parser.has_next())
                return false;
            const auto& element = pull_parser.peek();
            if (element.which() != 0)
                return false;
            if (boost::get<structure_begin_type>(element).name() != name)
                return false;

            return true;
        }

        static bool next_is_structure_end(const pull_parser_type& pull_parser, const input_string_type& name)
        {
            if (!pull_parser.has_next())
                return false;
            const auto& element = pull_parser.peek();
            if (element.which() != 1)
                return false;
            if (boost::get<structure_end_type>(element).name() != name)
                return false;

            return true;
        }

        static bool next_is_string(const pull_parser_type& pull_parser)
        {
            return next_is_value(pull_parser, 4);
        }

        static bool next_is_value(const pull_parser_type& pull_parser, const int which)
        {
            if (!pull_parser.has_next())
                return false;
            const auto& element = pull_parser.peek();
            if (element.which() != 2)
                return false;
            const auto& value = boost::get<value_type>(element);
            if (value.which() != which)
                return false;

            return true;
        }

        static input_string_type get_attribute(const structure_begin_type& structure)
        {
            const typename attribute_map_type::const_iterator found =
                structure.attribute_map().find(input_string_type{ TETENGO2_TEXT("name") });
            if (found == structure.attribute_map().end())
                return input_string_type{};
            if (found->second.which() != 4)
                return input_string_type{};
            
            return boost::get<input_string_type>(found->second);
        }


        // variables

        const std::unique_ptr<exec_json_reading_task_type> m_p_exec_json_reading_task;


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    first, last, tetengo2::stdalt::make_unique<grammar_type>()
                );
            pull_parser_type pull_parser{ std::move(p_push_parser), 5 };

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return false;
            pull_parser.next();
            return
                next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }) ||
                next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") });
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    first, last, tetengo2::stdalt::make_unique<grammar_type>()
                );
            pull_parser_type pull_parser{ std::move(p_push_parser), 5 };

            (*m_p_exec_json_reading_task)();
            return read_timetable(pull_parser, error);
        }


    };


}}}


#endif
