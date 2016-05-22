/*! \file
    \brief The definition of bobura::model::serializer::json_reader.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <cstddef>
#include <ios>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/exec_json_reading_task.h>
#include <bobura/model/serializer/json_reader.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer
{
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
    class json_reader<
        Size,
        Difference,
        String,
        ForwardIterator,
        Integer,
        Float,
        OperatingDistance,
        Speed,
        ExecJsonReadingTask,
        Font,
        Encoder
    >::impl :
        private boost::noncopyable
    {
    public:
        // types

        using iterator = ForwardIterator;

        using operating_distance_type = OperatingDistance;

        using exec_json_reading_task_type = ExecJsonReadingTask;

        using base_type = typename json_reader::base_type;

        using timetable_type = typename json_reader::timetable_type;

        using error_type = typename json_reader::error_type;


        // constructors and destructor

        explicit impl(std::unique_ptr<exec_json_reading_task_type> p_exec_json_reading_task)
        :
        m_p_exec_json_reading_task(std::move(p_exec_json_reading_task))
        {
            if (!m_p_exec_json_reading_task)
                BOOST_THROW_EXCEPTION(std::invalid_argument("JSON reading task execution is nullptr."));
        }


        // functions

        bool selects_impl(const iterator first, const iterator last)
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

        std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        {
            return
                (*m_p_exec_json_reading_task)(
                    [this, first, last, &error](promise_type& promise)
                    {
                        return read_impl_impl(first, last, error, promise);
                    }
                );
        }


    private:
        // types

        using size_type = Size;

        using string_type = String;

        using integer_type = Integer;

        using float_type = Float;

        using font_type = Font;

        using encoder_type = Encoder;

        using grammar_type = tetengo2::text::grammar::json<iterator>;

        using pull_parser_type =
            tetengo2::text::pull_parser<iterator, grammar_type, integer_type, float_type, size_type>;

        using push_parser_type = typename pull_parser_type::push_parser_type;

        using station_grade_type_set_type = station_info::grade_type_set<string_type>;

        using promise_type = typename exec_json_reading_task_type::promise_type;

        using font_color_set_type = typename timetable_type::font_color_set_type;

        using font_color_type = typename font_color_set_type::font_color_type;

        using color_type = typename font_color_type::color_type;

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

        static std::unique_ptr<timetable_type> read_timetable(
            pull_parser_type& pull_parser,
            error_type&       error,
            promise_type&     promise
        )
        {
            auto p_timetable = tetengo2::stdalt::make_unique<timetable_type>();

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            pull_parser.next();

            auto header = read_header(pull_parser, error, promise);
            if (!header)
                return std::unique_ptr<timetable_type>{};
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

            auto font_color_set = read_font_color_set(pull_parser, error, promise);
            if (!font_color_set)
                return std::unique_ptr<timetable_type>{};
            p_timetable->set_font_color_set(std::move(*font_color_set));

            auto stations = read_stations(pull_parser, error, promise);
            if (!stations)
                return std::unique_ptr<timetable_type>{};
            for (auto& station: *stations)
                p_timetable->insert_station_location(p_timetable->station_locations().end(), std::move(station));

            auto train_kinds = read_train_kinds(pull_parser, error, promise);
            if (!train_kinds)
                return std::unique_ptr<timetable_type>{};
            for (auto& train_kind: *train_kinds)
                p_timetable->insert_train_kind(p_timetable->train_kinds().end(), std::move(train_kind));

            auto down_trains =
                read_trains(pull_parser, error, promise, direction_type::down, stations->size(), train_kinds->size());
            if (!down_trains)
                return std::unique_ptr<timetable_type>{};
            for (auto& train: *down_trains)
                p_timetable->insert_down_train(p_timetable->down_trains().end(), std::move(train));

            auto up_trains =
                read_trains(pull_parser, error, promise, direction_type::up, stations->size(), train_kinds->size());
            if (!up_trains)
                return std::unique_ptr<timetable_type>{};
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

        static boost::optional<header_type> read_header(
            pull_parser_type& pull_parser,
            error_type&       error,
            promise_type&     promise
        )
        {
            header_type header{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            for (;;)
            {
                if (promise.abort_requested())
                {
                    error = error_type::canceled;
                    return boost::none;
                }

                auto member = read_string_member(pull_parser);
                if (!member)
                    break;

                header.insert(std::move(*member));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            return boost::make_optional(std::move(header));
        }

        static boost::optional<font_color_set_type> read_font_color_set(
            pull_parser_type& pull_parser,
            error_type&       error,
            promise_type&     promise
        )
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            auto general_font_color = font_color_set_type::default_().general();
            auto background_font_color = font_color_set_type::default_().background();
            auto company_name_font_color = font_color_set_type::default_().company_name();
            auto line_name_font_color = font_color_set_type::default_().line_name();
            auto note_font_color = font_color_set_type::default_().note();
            auto local_station_font_color = font_color_set_type::default_().local_station();
            auto principal_station_font_color = font_color_set_type::default_().principal_station();
            auto local_terminal_station_font_color = font_color_set_type::default_().local_terminal_station();
            auto principal_terminal_station_font_color = font_color_set_type::default_().principal_terminal_station();
            for (;;)
            {
                if (promise.abort_requested())
                {
                    error = error_type::canceled;
                    return boost::none;
                }

                auto element = read_font_color_element(pull_parser);
                if (!element)
                    break;

                if (element->first == string_type{ TETENGO2_TEXT("background") })
                {
                    if (
                        !(
                            !element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            !element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    background_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("general") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    general_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("company_name") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    company_name_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("line_name") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    line_name_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("note") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    note_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("local_station") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    local_station_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("principal_station") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    principal_station_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("local_terminal_station") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    local_terminal_station_font_color = std::move(element->second);
                }
                else if (element->first == string_type{ TETENGO2_TEXT("principal_terminal_station") })
                {
                    if (
                        !(
                            element->second.diagram_font() &&
                            element->second.diagram_color() &&
                            element->second.timetable_font() &&
                            element->second.timetable_color()
                        )
                    )
                    {
                        error = error_type::corrupted;
                        return boost::none;
                    }
                    principal_terminal_station_font_color = std::move(element->second);
                }
                else
                {
                    error = error_type::corrupted;
                    return boost::none;
                }
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            return
                boost::make_optional(
                    font_color_set_type{
                        std::move(background_font_color),
                        std::move(general_font_color),
                        std::move(company_name_font_color),
                        std::move(line_name_font_color),
                        std::move(note_font_color),
                        std::move(local_station_font_color),
                        std::move(principal_station_font_color),
                        std::move(local_terminal_station_font_color),
                        std::move(principal_terminal_station_font_color)
                    }
                );
        }

        static boost::optional<std::pair<string_type, font_color_type>> read_font_color_element(
            pull_parser_type& pull_parser
        )
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            const auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            auto value = read_font_color_element_value(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), std::move(*value)));
        }

        static boost::optional<font_color_type> read_font_color_element_value(
            pull_parser_type& pull_parser
        )
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            auto diagram_font = read_font(pull_parser);
            auto diagram_color = read_color(pull_parser);
            auto timetable_font = read_font(pull_parser);
            auto timetable_color = read_color(pull_parser);
            if (!diagram_font && !diagram_color && !timetable_font && !timetable_color)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional<font_color_type>(
                    font_color_type{ diagram_font, diagram_color, timetable_font, timetable_color }
                );

        }

        static boost::optional<std::pair<string_type, font_type>> read_font_element(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            const auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            auto value = read_font(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), std::move(*value)));
        }

        static boost::optional<font_type> read_font(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                if (next_is_null(pull_parser))
                    pull_parser.next();
                return boost::none;
            }
            pull_parser.next();

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
                boost::make_optional<font_type>(
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

        static boost::optional<std::pair<string_type, color_type>> read_color_element(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            const auto key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            auto value = read_color(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("member") }))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), std::move(*value)));
        }

        static boost::optional<color_type> read_color(pull_parser_type& pull_parser)
        {
            if (next_is_null(pull_parser))
            {
                pull_parser.next();
                return boost::none;
            }
            auto color_string = read_string(pull_parser);
            if (!color_string)
                return boost::none;
            return to_color(encoder().decode(std::move(*color_string)));
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

        static boost::optional<std::vector<station_location_type>> read_stations(
            pull_parser_type& pull_parser,
            error_type&       error,
            promise_type&     promise
        )
        {
            std::vector<station_location_type> stations{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            for (;;)
            {
                if (promise.abort_requested())
                {
                    error = error_type::canceled;
                    return boost::none;
                }

                auto station = read_station(pull_parser);
                if (!station)
                    break;

                stations.push_back(std::move(*station));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
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

        static boost::optional<std::vector<train_kind_type>> read_train_kinds(
            pull_parser_type& pull_parser,
            error_type&       error,
            promise_type&     promise
        )
        {
            std::vector<train_kind_type> train_kinds{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            for (;;)
            {
                if (promise.abort_requested())
                {
                    error = error_type::canceled;
                    return boost::none;
                }

                auto train_kind = read_train_kind(pull_parser);
                if (!train_kind)
                    break;

                train_kinds.push_back(std::move(*train_kind));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            return boost::make_optional(std::move(train_kinds));
        }

        static boost::optional<train_kind_type> read_train_kind(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            auto name = train_kind_type::default_().name();
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("name") })
                    return boost::none;

                name = std::move(member->second);
            }

            auto abbreviation = train_kind_type::default_().abbreviation();
            {
                auto member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("abbreviation") })
                    return boost::none;

                abbreviation = std::move(member->second);
            }

            auto diagram_font = train_kind_type::default_().diagram_font();
            {
                auto element = read_font_element(pull_parser);
                if (!element)
                    return boost::none;
                if (element->first != string_type{ TETENGO2_TEXT("diagram_font") })
                    return boost::none;

                diagram_font = std::move(element->second);
            }

            auto diagram_color = train_kind_type::default_().diagram_color();
            {
                auto element = read_color_element(pull_parser);
                if (!element)
                    return boost::none;
                if (element->first != string_type{ TETENGO2_TEXT("diagram_color") })
                    return boost::none;

                diagram_color = std::move(element->second);
            }

            auto diagram_line_weight = train_kind_type::default_().diagram_line_weight();
            {
                const auto member = read_integer_member<int>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("diagram_line_weight") })
                    return boost::none;

                const auto weight_ = to_weight(member->second);
                if (!weight_)
                    return boost::none;
                diagram_line_weight = *weight_;
            }

            auto diagram_line_style = train_kind_type::default_().diagram_line_style();
            {
                const auto member = read_integer_member<int>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type{ TETENGO2_TEXT("diagram_line_style") })
                    return boost::none;

                const auto line_style_ = to_line_style(member->second);
                if (!line_style_)
                    return boost::none;
                diagram_line_style = *line_style_;
            }

            auto timetable_font = train_kind_type::default_().timetable_font();
            {
                auto element = read_font_element(pull_parser);
                if (!element)
                    return boost::none;
                if (element->first != string_type{ TETENGO2_TEXT("timetable_font") })
                    return boost::none;

                diagram_font = std::move(element->second);
            }

            auto timetable_color = train_kind_type::default_().timetable_color();
            {
                auto element = read_color_element(pull_parser);
                if (!element)
                    return boost::none;
                if (element->first != string_type{ TETENGO2_TEXT("timetable_color") })
                    return boost::none;

                diagram_color = std::move(element->second);
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("object") }))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    train_kind_type{
                        std::move(name),
                        std::move(abbreviation),
                        std::move(diagram_font),
                        std::move(diagram_color),
                        diagram_line_weight,
                        diagram_line_style,
                        std::move(timetable_font),
                        std::move(timetable_color)
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
            error_type&          error,
            promise_type&        promise,
            const direction_type direction,
            const std::size_t    station_count,
            const std::size_t    kind_count
        )
        {
            std::vector<train_type> trains{};

            if (!next_is_structure_begin(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            for (;;)
            {
                if (promise.abort_requested())
                {
                    error = error_type::canceled;
                    return boost::none;
                }

                auto train = read_train(pull_parser, error, promise, direction, station_count, kind_count);
                if (!train)
                {
                    if (error == error_type::canceled)
                        return boost::none;
                    else
                        break;
                }

                trains.push_back(std::move(*train));
            }

            if (!next_is_structure_end(pull_parser, input_string_type{ TETENGO2_TEXT("array") }))
            {
                error = error_type::corrupted;
                return boost::none;
            }
            pull_parser.next();

            return boost::make_optional(std::move(trains));
        }

        static boost::optional<train_type> read_train(
            pull_parser_type&    pull_parser,
            error_type&          error,
            promise_type&        promise,
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

            auto stops = read_stops(pull_parser, error, promise);
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

        static boost::optional<std::vector<stop_type>> read_stops(
            pull_parser_type& pull_parser,
            error_type&       error,
            promise_type&     promise
        )
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
                if (promise.abort_requested())
                {
                    error = error_type::canceled;
                    return boost::none;
                }

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

        static bool next_is_null(const pull_parser_type& pull_parser)
        {
            return next_is_value(pull_parser, 1);
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


        // functions

        std::unique_ptr<timetable_type> read_impl_impl(
            const iterator first,
            const iterator last,
            error_type&    error,
            promise_type&  promise
        )
        {
            auto observing_first = first;
            const auto content_size = static_cast<std::size_t>(first.distance_to(last));
            std::size_t skip = 0;
            observing_first.set_increment_observer(
                [&skip, observing_first, content_size, &promise](const iterator current)
                {
                    ++skip;
                    if (skip % 16384 == 0)
                    {
                        const auto progress = static_cast<std::size_t>(observing_first.distance_to(current));
                        promise.set_progress({ progress, content_size });
                    }
                }
            );

            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    observing_first, last, tetengo2::stdalt::make_unique<grammar_type>()
                );
            pull_parser_type pull_parser{ std::move(p_push_parser), 5 };

            return read_timetable(pull_parser, error, promise);
        }


    };


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
    json_reader<
        Size,
        Difference,
        String,
        ForwardIterator,
        Integer,
        Float,
        OperatingDistance,
        Speed,
        ExecJsonReadingTask,
        Font,
        Encoder
    >::json_reader(std::unique_ptr<exec_json_reading_task_type> p_exec_json_reading_task)
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(p_exec_json_reading_task)))
    {}

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
    json_reader<
        Size,
        Difference,
        String,
        ForwardIterator,
        Integer,
        Float,
        OperatingDistance,
        Speed,
        ExecJsonReadingTask,
        Font,
        Encoder
    >::~json_reader()
    noexcept
    {}

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
    bool
    json_reader<
        Size,
        Difference,
        String,
        ForwardIterator,
        Integer,
        Float,
        OperatingDistance,
        Speed,
        ExecJsonReadingTask,
        Font,
        Encoder
    >::selects_impl(const iterator first, const iterator last)
    {
        return m_p_impl->selects_impl(first, last);
    }

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
    std::unique_ptr<
        typename json_reader<
            Size,
            Difference,
            String,
            ForwardIterator,
            Integer,
            Float,
            OperatingDistance,
            Speed,
            ExecJsonReadingTask,
            Font,
            Encoder
        >::timetable_type
    > 
    json_reader<
        Size,
        Difference,
        String,
        ForwardIterator,
        Integer,
        Float,
        OperatingDistance,
        Speed,
        ExecJsonReadingTask,
        Font,
        Encoder
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

            using exec_json_reading_task_type =
                exec_json_reading_task<
                    typename application::common_type_list_type::size_type,
                    typename application::common_type_list_type::difference_type,
                    typename application::common_type_list_type::string_type,
                    typename application::common_type_list_type::operating_distance_type,
                    typename application::common_type_list_type::speed_type,
                    typename application::ui_type_list_type::fast_font_type,
                    typename application::ui_type_list_type::dialog_type,
                    typename application::ui_type_list_type::timer_type,
                    typename application::ui_type_list_type::system_color_set_type,
                    typename application::locale_type_list_type::message_catalog_type
                >;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using exec_json_reading_task_type =
                exec_json_reading_task<
                    typename test::common_type_list_type::size_type,
                    typename test::common_type_list_type::difference_type,
                    typename test::common_type_list_type::string_type,
                    typename test::common_type_list_type::operating_distance_type,
                    typename test::common_type_list_type::speed_type,
                    typename test::ui_type_list_type::font_type,
                    typename test::ui_type_list_type::dialog_type,
                    typename test::ui_type_list_type::timer_type,
                    typename test::ui_type_list_type::system_color_set_type,
                    typename test::locale_type_list_type::message_catalog_type
                >;

        }

    }

#if BOOST_COMP_MSVC
    template class json_reader<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::input_stream_iterator_type,
        int,
        double,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        application::exec_json_reading_task_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::locale_type_list_type::timetable_file_encoder_type
    >;
#endif

#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
    template class json_reader<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        int,
        double,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        test::exec_json_reading_task_type,
        typename test::ui_type_list_type::font_type,
        typename test::locale_type_list_type::timetable_file_encoder_type
    >;
#endif


}}}
