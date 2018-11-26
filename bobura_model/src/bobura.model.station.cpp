/*! \file
    \brief The definition of bobura::model::station.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <string>

#include <bobura/model/station.h>


namespace bobura::model {
    station::station(
        string_type       name,
        const grade_type& grade,
        const bool        shows_down_arrival_times,
        const bool        shows_up_arrival_times,
        string_type       note)
    : m_name{ std::move(name) }, m_p_grade{ &grade }, m_shows_down_arrival_times{ shows_down_arrival_times },
      m_shows_up_arrival_times{ shows_up_arrival_times }, m_note{ std::move(note) }
    {}

    bool operator==(const station& one, const station& another)
    {
        return one.m_name == another.m_name && one.m_p_grade == another.m_p_grade &&
               one.m_shows_down_arrival_times == another.m_shows_down_arrival_times &&
               one.m_shows_up_arrival_times == another.m_shows_up_arrival_times && one.m_note == another.m_note;
    }

    const station::string_type& station::name() const
    {
        return m_name;
    }

    const station::grade_type& station::grade() const
    {
        return *m_p_grade;
    }

    bool station::shows_down_arrival_times() const
    {
        return m_shows_down_arrival_times;
    }

    bool station::shows_up_arrival_times() const
    {
        return m_shows_up_arrival_times;
    }

    const station::string_type& station::note() const
    {
        return m_note;
    }
}
