/*! \file
    \brief The definition of bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>
#include <boost/utility/string_ref.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/windia_reader.h>
#include <bobura/model/station_info/grade.h>
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
        typename Font,
        typename Encoder
    >
    class windia_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font, Encoder>::impl :
        private boost::noncopyable
    {
    public:
        // types

        using string_type = String;

        using iterator = ForwardIterator;

        using encoder_type = Encoder;

        using base_type = typename windia_reader::base_type;

        using timetable_type = typename windia_reader::timetable_type;

        using error_type = typename windia_reader::error_type;


        // constructors and destructor

        impl()
        {}


        // functions

        bool selects_impl(const iterator first, const iterator last)
        {
            auto mutable_first = first;
            return next_line(mutable_first, last) == windia_section_label();
        }

        std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        {
            auto p_timetable = tetengo2::stdalt::make_unique<timetable_type>();

            insert_preset_train_kinds(*p_timetable);

            std::unique_ptr<state> p_state = tetengo2::stdalt::make_unique<initial_state>();
            auto next_line_first = first;
            for (;;)
            {
                const auto input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                if      (input_line == windia_section_label())
                    p_state = tetengo2::stdalt::make_unique<windia_state>(*p_timetable);
                else if (input_line == station_section_label())
                    p_state = tetengo2::stdalt::make_unique<station_state>(*p_timetable);
                else if (input_line == line_kind_section_label())
                    p_state = tetengo2::stdalt::make_unique<line_kind_state>(*p_timetable);
                else if (input_line == down_train_section_label())
                    p_state = tetengo2::stdalt::make_unique<down_train_state>(*p_timetable);
                else if (input_line == up_train_section_label())
                    p_state = tetengo2::stdalt::make_unique<up_train_state>(*p_timetable);
                else
                {
                    if (!p_state->parse(input_line))
                    {
                        error = error_type::corrupted;
                        return std::unique_ptr<timetable_type>{};
                    }
                }
            }

            erase_unreferred_train_kinds(*p_timetable);

            if (dynamic_cast<up_train_state*>(p_state.get()) == 0)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }

            return std::move(p_timetable);
        }


    private:
        // types

        using input_char_type = typename iterator::value_type;

        using input_string_type = std::basic_string<input_char_type>;

        using char_type = typename string_type::value_type;

        using string_ref_type = boost::basic_string_ref<char_type, std::char_traits<char_type>>;

        using train_kind_type = typename timetable_type::train_kind_type;

        using color_type = typename train_kind_type::color_type;

        using weight_type = typename train_kind_type::weight_type;

        using line_style_type = typename train_kind_type::line_style_type;

        using train_type = typename timetable_type::train_type;

        using direction_type = typename train_type::direction_type;

        class state : private boost::noncopyable
        {
        public:
            virtual ~state()
            = default;

            virtual bool parse(const string_type& line)
            = 0;

        };

        class initial_state : public state
        {
        public:
            virtual ~initial_state()
            = default;

            virtual bool parse(const string_type& line)
            override
            {
                boost::ignore_unused(line);

                return false;
            }

        };

        class windia_state : public state
        {
        public:
            explicit windia_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~windia_state()
            = default;

            virtual bool parse(const string_type& line)
            override
            {
                m_timetable.set_line_name(line);
                return true;
            }

        private:
            timetable_type& m_timetable;

        };

        class station_state : public state
        {
        public:
            explicit station_state(timetable_type& timetable)
            :
            m_timetable(timetable),
            m_operating_distance()
            {}

            virtual ~station_state()
            = default;

            virtual bool parse(const string_type& line)
            override
            {
                const auto comma_position = line.find(TETENGO2_TEXT(','));
                if (comma_position == string_type::npos)
                    return false;

                const auto props = string_ref_type{ line }.substr(0, comma_position);
                auto name = line.substr(comma_position + 1);

                station_location_type station_location{
                    station_type{
                        std::move(name),
                        to_grade(
                        props.find(TETENGO2_TEXT('p')) != string_ref_type::npos,
                        props.find(TETENGO2_TEXT('b')) != string_ref_type::npos
                        ),
                        props.find(TETENGO2_TEXT('d')) != string_ref_type::npos,
                        props.find(TETENGO2_TEXT('u')) != string_ref_type::npos,
                        string_type{}
                    },
                    m_operating_distance
                };
                m_timetable.insert_station_location(
                    m_timetable.station_locations().end(), std::move(station_location)
                );

                m_operating_distance += operating_distance_type{ 1 };

                return true;
            }

        private:
            using station_location_type = typename timetable_type::station_location_type;

            using station_type = typename station_location_type::station_type;

            using grade_type = typename station_type::grade_type;

            using operating_distance_type = typename station_location_type::operating_distance_type;

            using station_grade_type_set_type = station_info::grade_type_set<string_type>;

            static const grade_type& to_grade(const bool principal, const bool show_arrival_and_departure_time)
            {
                if      (principal && show_arrival_and_departure_time)
                    return station_grade_type_set_type::principal_terminal_type::instance();
                else if (show_arrival_and_departure_time)
                    return station_grade_type_set_type::local_terminal_type::instance();
                else if (principal)
                    return station_grade_type_set_type::principal_type::instance();
                else
                    return station_grade_type_set_type::local_type::instance();
            }

            timetable_type& m_timetable;

            operating_distance_type m_operating_distance;

        };

        class line_kind_state : public state
        {
        public:
            explicit line_kind_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~line_kind_state()
            = default;

            virtual bool parse(const string_type& line)
            override
            {
                const auto split = split_line(line);
                if (!split)
                    return false;

                if (split->key == string_ref_type(TETENGO2_TEXT("LINES")))
                    return set_line_props(split->values);
                else if (split->key == string_ref_type(TETENGO2_TEXT("Train")))
                    return set_name(split->index, split->values);
                else
                    return false;
            }

        private:
            struct split_type
            {
                string_ref_type key{};
                std::size_t index;
                std::vector<string_ref_type> values{};

                split_type(string_ref_type key, const std::size_t index, std::vector<string_ref_type> values)
                :
                key(std::move(key)),
                index(index),
                values(std::move(values))
                {}

            };

            static boost::optional<split_type> split_line(const string_type& line)
            {
                const auto equal_position = line.find(TETENGO2_TEXT('='));
                if (equal_position == string_type::npos)
                    return boost::none;

                const auto key_and_index = string_ref_type{ line }.substr(0, equal_position);
                const auto index_position = key_and_index.find_first_of(string_ref_type(TETENGO2_TEXT("0123456789")));
                auto key = string_ref_type{ key_and_index }.substr(0, index_position);
                std::size_t index = 0;
                if (index_position != string_type::npos)
                {
                    try
                    {
                        index = boost::lexical_cast<std::size_t>(key_and_index.substr(index_position));
                    }
                    catch (const boost::bad_lexical_cast&)
                    {
                        return boost::none;
                    }
                }

                auto values = split_by_comma(string_ref_type{ line }.substr(equal_position + 1));

                return boost::make_optional(split_type(std::move(key), index, std::move(values)));
            }

            timetable_type& m_timetable;

            bool set_line_props(const std::vector<string_ref_type>& props)
            {
                const auto train_kind_count = m_timetable.train_kinds().size();
                if (props.size() < train_kind_count)
                    return false;

                for (std::size_t i = 0; i < train_kind_count; ++i)
                {
                    unsigned int prop = 0;
                    try
                    {
                        if (!props[i].empty())
                            prop = boost::lexical_cast<unsigned int>(props[i]);
                    }
                    catch (const boost::bad_lexical_cast&)
                    {
                        return false;
                    }

                    auto new_train_kind =
                        make_train_kind(
                            boost::make_optional<const train_kind_type&>(m_timetable.train_kinds()[i]), prop
                        );
                    if (!new_train_kind)
                        return false;
                    m_timetable.set_train_kind(
                        std::next(m_timetable.train_kinds().begin(), i), std::move(*new_train_kind)
                    );
                }
                for (std::size_t i = train_kind_count; i < props.size(); ++i)
                {
                    unsigned int prop = 0;
                    try
                    {
                        if (!props[i].empty())
                            prop = boost::lexical_cast<unsigned int>(props[i]);
                    }
                    catch (const boost::bad_lexical_cast&)
                    {
                        return false;
                    }

                    auto new_train_kind = make_train_kind(boost::none, prop);
                    if (!new_train_kind)
                        return false;
                    m_timetable.insert_train_kind(m_timetable.train_kinds().end(), std::move(*new_train_kind));
                }

                return true;
            }

            bool set_name(const std::size_t index, const std::vector<string_ref_type>& name_and_abbreviation)
            {
                if (index >= m_timetable.train_kinds().size())
                    return false;
                if (name_and_abbreviation.size() < 2)
                    return false;

                train_kind_type new_kind{
                    string_type(name_and_abbreviation[0].begin(), name_and_abbreviation[0].end()),
                    string_type(name_and_abbreviation[1].begin(), name_and_abbreviation[1].end()),
                    m_timetable.train_kinds()[index].diagram_font(),
                    m_timetable.train_kinds()[index].diagram_color(),
                    m_timetable.train_kinds()[index].diagram_line_weight(),
                    m_timetable.train_kinds()[index].diagram_line_style(),
                    m_timetable.train_kinds()[index].timetable_font(),
                    m_timetable.train_kinds()[index].timetable_color()
                };

                m_timetable.set_train_kind(
                    std::next(m_timetable.train_kinds().begin(), index), std::move(new_kind)
                );

                return true;
            }

        };

        class train_state : public state
        {
        public:
            explicit train_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~train_state()
            = default;

            virtual bool parse(const string_type& line)
            override
            {
                auto others_and_note = split_line(line);
                auto split = split_by_comma(others_and_note.first);
                if (split.size() < 4 + m_timetable.station_locations().size())
                    return false;

                const auto train_kind_index = to_train_kind_index(split[0]);
                if (!train_kind_index)
                    return false;
                if (*train_kind_index >= m_timetable.train_kinds().size())
                    return false;

                train_type train{
                    direction(),
                    string_type(split[1].begin(), split[1].end()),
                    *train_kind_index,
                    string_type(split[2].begin(), split[2].end()),
                    string_type(split[3].begin(), split[3].end()),
                    string_type(others_and_note.second.begin(), others_and_note.second.end())
                };
                for (std::size_t i = 0; i < m_timetable.station_locations().size(); ++i)
                {
                    auto stop = to_stop(std::move(split[4 + i]));
                    if (!stop)
                        return false;
                    train.insert_stop(train.stops().end(), std::move(*stop));
                }

                insert_train(std::move(train));

                return true;
            }

        protected:
            timetable_type& m_timetable;

        private:
            using size_type = typename train_type::size_type;

            using stop_type = typename train_type::stop_type;

            using time_type = typename stop_type::time_type;

            static std::pair<string_ref_type, string_ref_type> split_line(const string_ref_type& line)
            {
                const auto percent_position = line.find(TETENGO2_TEXT('%'));
                if (percent_position == string_ref_type::npos)
                    return std::make_pair(line, string_ref_type{});

                return std::make_pair(line.substr(0, percent_position), line.substr(percent_position + 1));
            }

            direction_type direction()
            const
            {
                return direction_impl();
            }

            virtual direction_type direction_impl()
            const = 0;

            void insert_train(train_type train)
            {
                if (train.stops().size() != m_timetable.station_locations().size())
                    return;

                insert_train_impl(std::move(train));
            }

            virtual void insert_train_impl(train_type train)
            = 0;

            boost::optional<size_type> to_train_kind_index(const string_ref_type& train_kind_string)
            {
                const auto opening_paren_position = train_kind_string.find(TETENGO2_TEXT('('));
                if (opening_paren_position == string_type::npos)
                {
                    try
                    {
                        return
                            train_kind_string.empty() ?
                            boost::make_optional(static_cast<size_type>(0)) :
                            boost::make_optional(boost::lexical_cast<size_type>(train_kind_string));
                    }
                    catch (const boost::bad_lexical_cast&)
                    {
                        return boost::none;
                    }
                }

                const auto closing_paren_position = train_kind_string.find(TETENGO2_TEXT(')'));
                if (closing_paren_position == string_type::npos || closing_paren_position <= opening_paren_position)
                    return boost::none;

                size_type base_index = 0;
                try
                {
                    const auto index_string = train_kind_string.substr(0, opening_paren_position);
                    base_index = index_string.empty() ? 0 : boost::lexical_cast<size_type>(index_string);
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }
                if (base_index >= m_timetable.train_kinds().size())
                    return boost::none;

                unsigned int prop = 0;
                try
                {
                    prop =
                        boost::lexical_cast<unsigned int>(
                            train_kind_string.substr(
                                opening_paren_position + 1, closing_paren_position - opening_paren_position - 1
                            )
                        );
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }

                auto new_train_kind =
                    make_train_kind(
                        boost::make_optional<const train_kind_type&>(m_timetable.train_kinds()[base_index]), prop
                    );
                if (!new_train_kind)
                    return boost::none;
                m_timetable.insert_train_kind(m_timetable.train_kinds().end(), std::move(*new_train_kind));

                return boost::make_optional<size_type>(m_timetable.train_kinds().size() - 1);
            }

            boost::optional<stop_type> to_stop(string_ref_type time_string)
            {
                const auto arrival_and_departure_string = split_time_string(std::move(time_string));

                auto arrival = to_time(arrival_and_departure_string.first);
                if (!arrival)
                    return boost::none;
                auto departure = to_time(arrival_and_departure_string.second);
                if (!departure)
                    return boost::none;

                const auto operational =
                    is_operational(arrival_and_departure_string.first) ||
                    is_operational(arrival_and_departure_string.second);

                return stop_type(std::move(*arrival), std::move(*departure), operational, string_type{});
            }

            std::pair<string_ref_type, string_ref_type> split_time_string(string_ref_type time_string)
            {
                const auto slash_position = time_string.find(TETENGO2_TEXT('/'));
                if (slash_position == string_ref_type::npos)
                    return std::make_pair(string_ref_type{}, std::move(time_string));

                return std::make_pair(time_string.substr(0, slash_position), time_string.substr(slash_position + 1));
            }

            boost::optional<time_type> to_time(const string_ref_type& time_string)
            {
                if (time_string.empty() || time_string == string_ref_type(TETENGO2_TEXT("-")))
                    return boost::make_optional(time_type::uninitialized());

                const auto time_string_length =
                    time_string[time_string.length() - 1] == char_type(TETENGO2_TEXT('?')) ?
                    time_string.length() - 1 : time_string.length();
                if (time_string_length < 3 && 4 < time_string_length)
                    return boost::none;
                const std::size_t minute_position = time_string_length == 3 ? 1 : 2;

                size_type hours = 0;
                try
                {
                    hours = boost::lexical_cast<size_type>(time_string.substr(0, minute_position));
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }
                hours %= 24;

                size_type minutes = 0;
                try
                {
                    minutes = boost::lexical_cast<size_type>(time_string.substr(minute_position, 2));
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }
                if (minutes > 59)
                    return boost::none;

                return boost::make_optional(time_type{ hours, minutes, 0 });
            }

            bool is_operational(const string_ref_type& time_string)
            {
                return !time_string.empty() && time_string[time_string.length() - 1] == char_type(TETENGO2_TEXT('?'));
            }

        };

        class down_train_state : public train_state
        {
        public:
            explicit down_train_state(timetable_type& timetable)
            :
            train_state(timetable)
            {}

            virtual ~down_train_state()
            = default;

        private:
            virtual direction_type direction_impl()
            const override
            {
                return direction_type::down;
            }

            virtual void insert_train_impl(train_type train)
            override
            {
                train_state::m_timetable.insert_down_train(
                    train_state::m_timetable.down_trains().end(), std::move(train)
                );
            }

        };

        class up_train_state : public train_state
        {
        public:
            explicit up_train_state(timetable_type& timetable)
            :
            train_state(timetable)
            {}

            virtual ~up_train_state()
            = default;

        private:
            virtual direction_type direction_impl()
            const override
            {
                return direction_type::up;
            }

            virtual void insert_train_impl(train_type train)
            override
            {
                train_state::m_timetable.insert_up_train(
                    train_state::m_timetable.up_trains().end(), std::move(train)
                );
            }

        };

        struct preset_train_kind_type
        {
            input_string_type name{};
            input_string_type abbreviation{};
            weight_type weight{};
            line_style_type line_style{};

            preset_train_kind_type(
                input_string_type     name,
                input_string_type     abbreviation,
                const weight_type     weight,
                const line_style_type line_style
            )
            :
            name(std::move(name)),
            abbreviation(std::move(abbreviation)),
            weight(weight),
            line_style(line_style)
            {}

        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }

        static const string_type& windia_section_label()
        {
            static const string_type singleton{
                encoder().decode(input_string_type{ TETENGO2_TEXT("[WinDIA]") })
            };
            return singleton;
        }

        static const string_type& station_section_label()
        {
            static const string_type singleton{
                encoder().decode(input_string_type{ TETENGO2_TEXT("[\x89\x77]") })
            }; // "eki"
            return singleton;
        }

        static const string_type& line_kind_section_label()
        {
            static const string_type singleton{
                encoder().decode(input_string_type{ TETENGO2_TEXT("[\x90\xFC\x8E\xED]") })
            }; // "senshu"
            return singleton;
        }

        static const string_type& down_train_section_label()
        {
            static const string_type singleton{
                encoder().decode(input_string_type{ TETENGO2_TEXT("[\x89\xBA\x82\xE8]") })
            }; // "kudari"
            return singleton;
        }

        static const string_type& up_train_section_label()
        {
            static const string_type singleton{
                encoder().decode(input_string_type{ TETENGO2_TEXT("[\x8F\xE3\x82\xE8]") })
            }; // "nobori"
            return singleton;
        }

        static void insert_preset_train_kinds(timetable_type& timetable)
        {
            const std::vector<preset_train_kind_type> kinds{
                {
                    input_string_type{ TETENGO2_TEXT("\x95\x81\x92\xCA") }, // "futsuu"
                    input_string_type{ TETENGO2_TEXT("\x95\x81\x92\xCA") }, // "futsuu"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x89\xF5\x91\xAC") }, // "kaosoku"
                    input_string_type{ TETENGO2_TEXT("\x89\xF5\x91\xAC") }, // "kaosoku"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x93\xC1\x95\xCA\x89\xF5\x91\xAC") }, // "tokubetsukaisoku"
                    input_string_type{ TETENGO2_TEXT("\x93\xC1\x89\xF5") }, // "tokkai"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x90\x56\x89\xF5\x91\xAC") }, // "shinkaisoku"
                    input_string_type{ TETENGO2_TEXT("\x90\x56\x89\xF5") }, // "shinkai"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x92\xCA\x8B\xCE\x89\xF5\x91\xAC") }, // "tsuukinkaisoku"
                    input_string_type{ TETENGO2_TEXT("\x92\xCA\x89\xF5") }, // "tsuukai"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x8F\x80\x8B\x7D") }, // "junkyuu"
                    input_string_type{ TETENGO2_TEXT("\x8F\x80\x8B\x7D") }, // "junkyuu"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x8B\x7D\x8D\x73") }, // "kyuukou"
                    input_string_type{ TETENGO2_TEXT("\x8B\x7D\x8D\x73") }, // "kyuukou"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x89\xF5\x91\xAC\x8B\x7D\x8D\x73") }, // "kaisokukyuukou"
                    input_string_type{ TETENGO2_TEXT("\x89\xF5\x8B\x7D") }, // "kaikyuu"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x93\xC1\x8B\x7D") }, // "tokkyuu"
                    input_string_type{ TETENGO2_TEXT("\x93\xC1\x8B\x7D") }, // "tokkyuu"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x89\xF5\x91\xAC\x93\xC1\x8B\x7D") }, // "kaisokutokkyuu"
                    input_string_type{ TETENGO2_TEXT("\x89\xF5\x93\xC1") }, // "kaitoku"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x92\xCA\x8B\xCE\x8F\x80\x8B\x7D") }, // "tsuukinjunkyuu"
                    input_string_type{ TETENGO2_TEXT("\x92\xCA\x8F\x80") }, // "tsuujun"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x92\xCA\x8B\xCE\x8B\x7D\x8D\x73") }, // "tsuukinkyuukou"
                    input_string_type{ TETENGO2_TEXT("\x92\xCA\x8B\x7D") }, // "tsuukyuu"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x8B\xE6\x8A\xD4\x89\xF5\x91\xAC") }, // "kukankaisoku"
                    input_string_type{ TETENGO2_TEXT("\x8B\xE6\x89\xF5") }, // "kukai"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x8B\xE6\x8A\xD4\x8B\x7D\x8D\x73") }, // "kukankyuukou"
                    input_string_type{ TETENGO2_TEXT("\x8B\xE6\x8B\x7D") }, // "kukyuu"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::solid
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x89\xF1\x91\x97") }, // "kaisou"
                    input_string_type{ TETENGO2_TEXT("\x89\xF1\x91\x97") }, // "kaisou"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::dot_dashed
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x89\xDD\x95\xA8") }, // "kamotsu"
                    input_string_type{ TETENGO2_TEXT("\x89\xDD\x95\xA8") }, // "kamotsu"
                    train_kind_type::weight_type::normal,
                    train_kind_type::line_style_type::dashed
                },
                {
                    input_string_type{ TETENGO2_TEXT("\x8B\x7D\x8D\x73\x89\xDD\x95\xA8") }, // "kyuukoukamotsu"
                    input_string_type{ TETENGO2_TEXT("\x8B\x7D\x89\xDD") }, // "kyuuka"
                    train_kind_type::weight_type::bold,
                    train_kind_type::line_style_type::dashed
                },
            };

            for (const auto& kind: kinds)
            {
                timetable.insert_train_kind(
                    timetable.train_kinds().end(),
                    train_kind_type{
                        encoder().decode(kind.name),
                        encoder().decode(kind.abbreviation),
                        train_kind_type::default_().diagram_font(),
                        train_kind_type::default_().diagram_color(),
                        kind.weight,
                        kind.line_style,
                        train_kind_type::default_().timetable_font(),
                        train_kind_type::default_().timetable_color()
                    }
                );
            }
        }

        static const std::vector<color_type>& preset_palette()
        {
            static const auto singleton = make_preset_palette();
            return singleton;
        }

        static std::vector<color_type> make_preset_palette()
        {
            return
                {
                    { 0, 0, 255 },
                    { 0, 255, 0 },
                    { 0, 0, 128 },
                    { 0, 128, 0 },
                    { 0, 255, 255 },
                    { 255, 0, 0 },
                    { 0, 128, 128 },
                    { 128, 0, 0 },
                    { 255, 0, 255 },
                    { 255, 255, 0 },
                    { 128, 0, 128 },
                    { 128, 128, 0 },
                    { 0, 0, 0 },
                    { 128, 128, 128 },
                    { 192, 192, 192 },
                    { 255, 255, 255 },
                };
        }

        static string_type next_line(iterator& first, const iterator last)
        {
            string_type line{};
            for (;;)
            {
                skip_line_breaks(first, last);
                const auto next_line_break = std::find_if(first, last, line_break);
                line += encoder().decode(input_string_type{ first, next_line_break });

                first = next_line_break;
                if (!line.empty() && line_contination(line[line.length() - 1]))
                    line.resize(line.length() - 1);
                else
                    break;
            }

            return line;
        }

        static void skip_line_breaks(iterator& first, const iterator last)
        {
            while (first != last && (line_break(*first) || tab(*first)))
                ++first;
        }

        static bool line_break(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\r')) ||
                character == input_char_type(TETENGO2_TEXT('\n'));
        }

        static bool tab(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\t'));
        }

        static bool line_contination(const char_type character)
        {
            return character == char_type(TETENGO2_TEXT('\\'));
        }

        static std::vector<string_ref_type> split_by_comma(const string_ref_type& string_ref)
        {
            std::vector<string_ref_type> values{};

            std::size_t offset = 0;
            for (;;)
            {
                const auto value_length = string_ref.substr(offset).find(TETENGO2_TEXT(','));
                values.push_back(string_ref.substr(offset, value_length));
                if (value_length == string_ref_type::npos)
                    break;
                offset += value_length + 1;
            }

            return values;
        }

        static boost::optional<train_kind_type> make_train_kind(
            const boost::optional<const train_kind_type&>& base,
            const unsigned int                             prop
        )
        {
            const auto diagram_line_style = to_line_style(prop & 0x03);
            const auto custom_color = (prop & 0x40) != 0;
            const auto& diagram_font = base ? base->diagram_font() : train_kind_type::default_().diagram_font();
            const auto diagram_color = 
                custom_color ?
                to_color((prop & 0x3C) / 0x04) :
                (
                    base ?
                    boost::make_optional(base->diagram_color()) :
                    boost::make_optional(train_kind_type::default_().diagram_color())
                );
            if (!diagram_color)
                return boost::none;
            const auto diagram_line_weight = to_weight((prop & 0x80) != 0);
            const auto& timetable_font = base ? base->timetable_font() : train_kind_type::default_().timetable_font();
            const auto& timetable_color =
                base ? base->timetable_color() : train_kind_type::default_().timetable_color();

            return
                base ?
                boost::make_optional(
                    train_kind_type(
                        base->name(),
                        base->abbreviation(),
                        diagram_font,
                        std::move(*diagram_color),
                        diagram_line_weight,
                        diagram_line_style,
                        timetable_font,
                        timetable_color
                    )
                ) :
                boost::make_optional(
                    train_kind_type(
                        string_type{},
                        string_type{},
                        diagram_font,
                        std::move(*diagram_color),
                        diagram_line_weight,
                        diagram_line_style,
                        timetable_font,
                        timetable_color
                    )
                );
        }

        static boost::optional<color_type> to_color(const std::size_t index)
        {
            if (index >= preset_palette().size())
                return boost::none;
            return boost::make_optional(preset_palette()[index]);
        }

        static weight_type to_weight(const bool bold)
        {
            return bold ? train_kind_type::weight_type::bold : train_kind_type::weight_type::normal;
        }

        static line_style_type to_line_style(const std::size_t index)
        {
            switch (index)
            {
            case 0:
                return train_kind_type::line_style_type::solid;
            case 1:
                return train_kind_type::line_style_type::dashed;
            case 2:
                return train_kind_type::line_style_type::dotted;
            case 3:
                return train_kind_type::line_style_type::dot_dashed;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("We must not come here."));
            }
        }

        static void erase_unreferred_train_kinds(timetable_type& timetable)
        {
            for (;;)
            {
                auto found = timetable.train_kinds().end();
                for (auto i = timetable.train_kinds().begin(); i != timetable.train_kinds().end(); ++i)
                {
                    if (!timetable.train_kind_referred(i))
                    {
                        found = i;
                        break;
                    }
                }

                if (found == timetable.train_kinds().end())
                    break;

                timetable.erase_train_kind(found);
            }
        }


    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    windia_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font, Encoder>::windia_reader()
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    windia_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font, Encoder>::~windia_reader()
    noexcept
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder
    >
    bool windia_reader<
        Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font, Encoder
    >::selects_impl(
        const iterator first,
        const iterator last
    )
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
        typename Font,
        typename Encoder
    >
    std::unique_ptr<
        typename windia_reader<
            Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font, Encoder
        >::timetable_type
    >
    windia_reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font, Encoder>::read_impl(
        const iterator first,
        const iterator last,
        error_type&    error
    )
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
    template class windia_reader<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::input_stream_iterator_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::locale_type_list_type::windia_file_encoder_type
    >;
#endif

    template class windia_reader<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type,
        typename test::locale_type_list_type::windia_file_encoder_type
    >;


}}}
