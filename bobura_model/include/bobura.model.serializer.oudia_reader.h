/*! \file
    \brief The definition of bobura::model::serializer::oudia_reader.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_OUDIAREADER_H)
#define BOBURA_MODEL_SERIALIZER_OUDIAREADER_H

#include <algorithm>
//#include <memory>
#include <string>
//#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for an OuDia reader.

        \tparam ForwardIterator     A forward iterator type.
        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Encoder             An encoder type.
    */
    template <typename ForwardIterator, typename Timetable, typename StationGradeTypeSet, typename Encoder>
    class oudia_reader : public reader<ForwardIterator, Timetable>
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The base type.
        typedef reader<iterator, timetable_type> base_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a WinDIA reader.
        */
        oudia_reader()
        :
        base_type()
        {}

        /*!
            \brief Destroys the oudia_reader.
        */
        virtual ~oudia_reader()
        {}


    private:
        // types

        typedef typename iterator::value_type input_char_type;

        typedef std::basic_string<input_char_type> input_string_type;

        typedef typename timetable_type::string_type string_type;

        typedef typename string_type::value_type char_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        typedef typename train_kind_type::color_type color_type;

        typedef typename train_kind_type::weight_type weight_type;

        typedef typename train_kind_type::line_style_type line_style_type;

        typedef typename timetable_type::train_type train_type;

        struct is_splitter
        {
            char_type m_splitter;

            explicit is_splitter(const char_type splitter)
            :
            m_splitter(splitter)
            {}

            bool operator()(const char_type character)
            const
            {
                return character == m_splitter;
            }

        };

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
            {}

            bool parse(const string_type& line)
            {
                std::pair<string_type, string_type> key_value = parse_line(line);
                if (key_value.first.empty())
                    return false;

                return parse_impl(key_value.first, std::move(key_value.second));
            }

            void moving_to_another()
            {
                moving_to_another_impl();
            }

        private:
            virtual bool parse_impl(const string_type& key, string_type value)
            = 0;

            virtual void moving_to_another_impl()
            = 0;

        };

        class unknown_state : public state
        {
        public:
            virtual ~unknown_state()
            {}

        private:
            virtual bool parse_impl(const string_type& key, string_type value)
            {
                return true;
            }

            virtual void moving_to_another_impl()
            {}

        };

        class initial_state : public state
        {
        public:
            explicit initial_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~initial_state()
            {}

        private:
            timetable_type& m_timetable;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                if (key == string_type(TETENGO2_TEXT("Comment")))
                    m_timetable.set_note(remove_line_break_escape_sequences(std::move(value)));

                return true;
            }

            virtual void moving_to_another_impl()
            {}

        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static string_type next_line(iterator& first, const iterator last)
        {
            skip_line_breaks(first, last);
            const iterator next_line_break = std::find_if(first, last, line_break);
            string_type line = encoder().decode(input_string_type(first, next_line_break));
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

        static string_type remove_line_break_escape_sequences(string_type string)
        {
            boost::replace_all(string, string_type(TETENGO2_TEXT("\\r\\n")), string_type());
            boost::replace_all(string, string_type(TETENGO2_TEXT("\\r")), string_type());
            boost::replace_all(string, string_type(TETENGO2_TEXT("\\n")), string_type());

            return string;
        }

        static std::unique_ptr<state> move_to_another_state(const string_type& line, timetable_type& timetable)
        {
            if (line.empty() || line[line.length() - 1] != char_type(TETENGO2_TEXT('.')))
                return std::unique_ptr<state>();

            const string_type name = line.substr(0, line.length() - 1);
            if (name.empty())
                return tetengo2::make_unique<initial_state>(timetable);
            else
                return tetengo2::make_unique<unknown_state>();
        }

        static std::pair<string_type, string_type> parse_line(const string_type& line)
        {
            std::vector<string_type> splitted = split(line, char_type(TETENGO2_TEXT('=')));
            if (splitted.size() < 2)
                return std::make_pair(line, string_type());

            return std::make_pair(std::move(splitted[0]), std::move(splitted[1]));
        }

        static std::vector<string_type> split(const string_type& string, const char_type splitter)
        {
            std::vector<string_type> result;
            boost::split(result, string, is_splitter(splitter));
            return result;
        }

        static file_type parse_file_type(const string_type& file_type_string)
        {
            std::vector<string_type> splitted = split(file_type_string, char_type(TETENGO2_TEXT('.')));
            string_type name = splitted.size() >= 1 ? std::move(splitted[0]) : string_type();
            const int major_version = splitted.size() >= 2 ? boost::lexical_cast<int>(splitted[1]) : 0;
            const int minor_version = splitted.size() >= 3 ? boost::lexical_cast<int>(splitted[2]) : 0;
            return file_type(std::move(name), major_version, minor_version);
        }


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            iterator mutable_first = first;
            const std::pair<string_type, string_type> key_value = parse_line(next_line(mutable_first, last));
            const file_type file_type_ = parse_file_type(key_value.second);

            return
                key_value.first == string_type(TETENGO2_TEXT("FileType")) &&
                file_type_.m_name == string_type(TETENGO2_TEXT("OuDia")) &&
                file_type_.m_major_version == 1 &&
                file_type_.m_minor_version == 2;
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last)
        {
            if (!selects(first, last))
                return std::unique_ptr<timetable_type>();

            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();

            std::unique_ptr<state> p_state = tetengo2::make_unique<initial_state>(*p_timetable);
            iterator next_line_first = first;
            for (;;)
            {
                const string_type input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                std::unique_ptr<state> p_new_state = move_to_another_state(input_line, *p_timetable);
                if (p_new_state)
                {
                    p_state->moving_to_another();
                    p_state = std::move(p_new_state);
                }
                else
                {
                    if (!p_state->parse(input_line))
                        return std::unique_ptr<timetable_type>();
                }
            }

            if (!dynamic_cast<initial_state*>(p_state.get()))
                return std::unique_ptr<timetable_type>();

            return std::move(p_timetable);
        }


    };


}}}


#endif
