/*! \file
    \brief The definition of bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>

#include <bobura/model/station.h>
#include <bobura/model/timetable_info/station_location.h>


namespace bobura::model::timetable_info {
    class station_location::impl
    {
    public:
        // types

        using station_type = station_location::station_type;

        using operating_distance_type = station_location::operating_distance_type;


        // constructors and destructor

        impl(station_type station, operating_distance_type operating_distance)
        : m_station{ std::move(station) }, m_operating_distance{ std::move(operating_distance) }
        {}


        // functions

        friend bool operator_equal(const impl& one, const impl& another)
        {
            return one.m_station == another.m_station && one.m_operating_distance == another.m_operating_distance;
        }

        station_location& operator_assign(const impl& another, station_location& self)
        {
            m_station = another.m_station;
            m_operating_distance = another.m_operating_distance;

            return self;
        }

        station_location& operator_assign(impl&& another, station_location& self)
        {
            m_station = std::move(another.m_station);
            m_operating_distance = std::move(another.m_operating_distance);

            return self;
        }

        const station_type& get_station() const
        {
            return m_station;
        }

        const operating_distance_type& operating_distance() const
        {
            return m_operating_distance;
        }

        bool before(const station_location& another) const
        {
            return m_operating_distance < another.m_p_impl->m_operating_distance;
        }


    private:
        // variables

        station_type m_station;

        operating_distance_type m_operating_distance;
    };


    station_location::station_location(station_type station, operating_distance_type operating_distance)
    : m_p_impl{ std::make_unique<impl>(std::move(station), std::move(operating_distance)) }
    {}

    station_location::station_location(const station_location& another)
    : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) }
    {}

    station_location::station_location(station_location&& another)
    : m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    station_location::~station_location() = default;

    bool operator==(const station_location& one, const station_location& another)
    {
        return operator_equal(*one.m_p_impl, *another.m_p_impl);
    }

    station_location& station_location::operator=(const station_location& another)
    {
        return m_p_impl->operator_assign(*another.m_p_impl, *this);
    }

    station_location& station_location::operator=(station_location&& another)
    {
        return m_p_impl->operator_assign(std::move(*another.m_p_impl), *this);
    }

    const station_location::station_type& station_location::get_station() const
    {
        return m_p_impl->get_station();
    }

    const station_location::operating_distance_type& station_location::operating_distance() const
    {
        return m_p_impl->operating_distance();
    }

    bool station_location::before(const station_location& another) const
    {
        return m_p_impl->before(another);
    }
}
