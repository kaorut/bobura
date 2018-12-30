/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>


namespace {
    // functions

    bobura::model::train::stops_type::const_iterator find_real_stop(
        const bobura::model::train&                      train,
        bobura::model::train::stops_type::const_iterator i_stop,
        const bool                                       skip_start)
    {
        if (skip_start && i_stop != train.stops().end())
            std::advance(i_stop, 1);

        for (auto i = i_stop; i != train.stops().end(); ++i)
        {
            if (!i->passing())
                return i;
        }

        return train.stops().end();
    }

    bobura::model::train::stops_type::const_iterator rfind_real_stop(
        const bobura::model::train&                      train,
        bobura::model::train::stops_type::const_iterator i_stop,
        const bool                                       skip_start)
    {
        if (skip_start && i_stop != train.stops().begin())
            std::advance(i_stop, -1);

        for (auto i = i_stop;; --i)
        {
            if (i == train.stops().end())
            {
                if (i == train.stops().begin())
                    break;
                else
                    continue;
            }
            if (!i->passing())
                return i;
            if (i == train.stops().begin())
                break;
        }

        return train.stops().end();
    }
}


namespace bobura::model {
    train::train(
        const direction_type direction,
        string_type          number,
        const size_type      kind_index,
        string_type          name,
        string_type          name_number,
        string_type          note)
    : m_direction{ direction }, m_number{ std::move(number) }, m_kind_index{ kind_index }, m_name{ std::move(name) },
      m_name_number{ std::move(name_number) }, m_note{ std::move(note) }, m_stops{}
    {}

    train::train(
        const direction_type direction,
        string_type          number,
        const size_type      kind_index,
        string_type          name,
        string_type          name_number,
        string_type          note,
        stops_type           stops)
    : m_direction{ direction }, m_number{ std::move(number) }, m_kind_index{ kind_index }, m_name{ std::move(name) },
      m_name_number{ std::move(name_number) }, m_note{ std::move(note) }, m_stops{ std::move(stops) }
    {}

    bool operator==(const train& one, const train& another)
    {
        return one.m_direction == another.m_direction && one.m_number == another.m_number &&
               one.m_kind_index == another.m_kind_index && one.m_name == another.m_name &&
               one.m_name_number == another.m_name_number && one.m_note == another.m_note &&
               one.m_stops == another.m_stops;
    }

    train::direction_type train::direction() const
    {
        return m_direction;
    }

    const train::string_type& train::number() const
    {
        return m_number;
    }

    train::size_type train::kind_index() const
    {
        return m_kind_index;
    }

    void train::set_kind_index(const size_type kind_index)
    {
        m_kind_index = kind_index;
    }

    const train::string_type& train::name() const
    {
        return m_name;
    }

    const train::string_type& train::name_number() const
    {
        return m_name_number;
    }

    const train::string_type& train::note() const
    {
        return m_note;
    }

    const train::stops_type& train::stops() const
    {
        return m_stops;
    }

    void train::insert_stop(const typename stops_type::const_iterator position, stop_type stop)
    {
        m_stops.insert(position, std::move(stop));
    }

    void
    train::erase_stops(const typename stops_type::const_iterator first, const typename stops_type::const_iterator last)
    {
        m_stops.erase(first, last);
    }

    train::stops_type::const_iterator train::previous_stop(const typename stops_type::const_iterator i_stop) const
    {
        return m_direction == direction_type::down ? rfind_real_stop(*this, i_stop, true) :
                                                     find_real_stop(*this, i_stop, true);
    }

    train::stops_type::const_iterator train::next_stop(const typename stops_type::const_iterator i_stop) const
    {
        return m_direction == direction_type::down ? find_real_stop(*this, i_stop, true) :
                                                     rfind_real_stop(*this, i_stop, true);
    }

    train::stops_type::const_iterator train::origin_stop() const
    {
        return m_direction == direction_type::down ? find_real_stop(*this, m_stops.begin(), false) :
                                                     rfind_real_stop(*this, m_stops.end(), false);
    }

    train::stops_type::const_iterator train::destination_stop() const
    {
        return m_direction == direction_type::down ? rfind_real_stop(*this, m_stops.end(), false) :
                                                     find_real_stop(*this, m_stops.begin(), false);
    }
}
