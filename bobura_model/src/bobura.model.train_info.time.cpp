/*! \file
    \brief The definition of bobura::model::train_info::time.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <limits>
#include <stdexcept>

#include <boost/core/swap.hpp>
#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include <bobura/model/train_info/time.h>


namespace bobura::model::train_info {
    namespace {
        time::size_type calculate_seconds_from_midnight(
            const time::size_type hours,
            const time::size_type minutes,
            const time::size_type seconds)
        {
            if (hours > 23)
                BOOST_THROW_EXCEPTION(std::out_of_range("24 or greater is specified for the hours."));
            else if (minutes > 59)
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or greater is specified for the minutes."));
            else if (seconds > 59)
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or greater is specified for the seconds."));

            const time::size_type seconds_from_midnight = hours * 60 * 60 + minutes * 60 + seconds;
            assert(seconds_from_midnight < static_cast<time::size_type>(time::time_span_type::seconds_of_whole_day()));

            return seconds_from_midnight;
        }
    }

    time::hours_minutes_seconds_type::hours_minutes_seconds_type(
        const size_type hours,
        const size_type minutes,
        const size_type seconds)
    : m_hours{ hours }, m_minutes{ minutes }, m_seconds{ seconds }
    {}

    bool operator==(const time::hours_minutes_seconds_type& one, const time::hours_minutes_seconds_type& another)
    {
        return one.m_hours == another.m_hours && one.m_minutes == another.m_minutes &&
               one.m_seconds == another.m_seconds;
    }

    time::size_type time::hours_minutes_seconds_type::hours() const
    {
        return m_hours;
    }

    time::size_type time::hours_minutes_seconds_type::minutes() const
    {
        return m_minutes;
    }

    time::size_type time::hours_minutes_seconds_type::seconds() const
    {
        return m_seconds;
    }

    const time& time::uninitialized()
    {
        static const time singleton{};

        return singleton;
    }

    time::time(const size_type seconds_from_midnight)
    : m_seconds_from_midnight{ seconds_from_midnight % time_span_type::seconds_of_whole_day() }
    {}

    time::time(const size_type hours, const size_type minutes, const size_type seconds)
    : m_seconds_from_midnight{ calculate_seconds_from_midnight(hours, minutes, seconds) }
    {}

    time& time::operator+=(const time_span_type& time_span)
    {
        if (*this == uninitialized())
            return *this;

        typename time_span_type::difference_type seconds = m_seconds_from_midnight;
        while (seconds < -time_span.seconds())
            seconds += time_span_type::seconds_of_whole_day();
        seconds += time_span.seconds();
        seconds %= time_span_type::seconds_of_whole_day();
        assert(0 <= seconds && seconds < time_span_type::seconds_of_whole_day());

        time temp{ static_cast<size_type>(seconds) };
        boost::swap(temp, *this);
        return *this;
    }

    time& time::operator-=(const time_span_type& time_span)
    {
        if (*this == uninitialized())
            return *this;

        typename time_span_type::difference_type seconds = m_seconds_from_midnight;
        while (seconds < time_span.seconds())
            seconds += time_span_type::seconds_of_whole_day();
        seconds -= time_span.seconds();
        seconds %= time_span_type::seconds_of_whole_day();
        assert(0 <= seconds && seconds < time_span_type::seconds_of_whole_day());

        time temp{ static_cast<size_type>(seconds) };
        boost::swap(temp, *this);
        return *this;
    }

    time::time_span_type operator-(const time& one, const time& another)
    {
        if (one == time::uninitialized() || another == time::uninitialized())
            BOOST_THROW_EXCEPTION(std::logic_error("The time object is uninitialized."));

        typename time::time_span_type::difference_type seconds = one.m_seconds_from_midnight;
        seconds -= another.m_seconds_from_midnight;
        while (seconds < 0)
            seconds += time::time_span_type::seconds_of_whole_day();

        return time::time_span_type{ seconds };
    }

    bool operator==(const time& one, const time& another)
    {
        return one.m_seconds_from_midnight == another.m_seconds_from_midnight;
    }

    bool operator<(const time& one, const time& another)
    {
        return one.m_seconds_from_midnight < another.m_seconds_from_midnight;
    }

    time::size_type time::seconds_from_midnight() const
    {
        if (*this == uninitialized())
            BOOST_THROW_EXCEPTION(std::logic_error("The time object is uninitialized."));

        return m_seconds_from_midnight;
    }

    time::hours_minutes_seconds_type time::hours_minutes_seconds() const
    {
        if (*this == uninitialized())
            BOOST_THROW_EXCEPTION(std::logic_error("The time object is uninitialized."));

        const size_type hours = m_seconds_from_midnight / (60 * 60);
        const size_type minutes = m_seconds_from_midnight / 60 - hours * 60;
        const size_type seconds = m_seconds_from_midnight - hours * 60 * 60 - minutes * 60;

        return hours_minutes_seconds_type{ hours, minutes, seconds };
    }

    bool time::initialized() const
    {
        return *this != uninitialized();
    }

    time::time() : m_seconds_from_midnight{ std::numeric_limits<size_type>::max() } {}
}
