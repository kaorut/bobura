/*! \file
    \brief The definition of bobura::model::train_info::time_span.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/core/swap.hpp>
#include <boost/throw_exception.hpp>

#include <bobura/model/train_info/time_span.h>


namespace bobura::model::train_info {
    namespace {

        time_span::difference_type calculate_seconds(
            const time_span::difference_type hours,
            const time_span::difference_type minutes,
            const time_span::difference_type seconds)
        {
            if (!(hours >= 0 && minutes >= 0 && seconds >= 0) && !(hours <= 0 && minutes <= 0 && seconds <= 0))
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("The signs of the hours, the minutes and the seconds are different."));
            }
            else if (minutes > 59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or larger is specified for the minutes."));
            }
            else if (minutes < -59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("-60 or smaller is specified for the minutes."));
            }
            else if (seconds > 59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or larger is specified for the seconds."));
            }
            else if (seconds < -59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("-60 or smaller is specified for the seconds."));
            }

            return hours * 60 * 60 + minutes * 60 + seconds;
        }
    }

    time_span::hours_minutes_seconds_type::hours_minutes_seconds_type(
        const difference_type hours,
        const difference_type minutes,
        const difference_type seconds)
    : m_hours{ hours }, m_minutes{ minutes }, m_seconds{ seconds }
    {}

    bool
    operator==(const time_span::hours_minutes_seconds_type& one, const time_span::hours_minutes_seconds_type& another)
    {
        return one.m_hours == another.m_hours && one.m_minutes == another.m_minutes &&
               one.m_seconds == another.m_seconds;
    }

    time_span::difference_type time_span::hours_minutes_seconds_type::hours() const
    {
        return m_hours;
    }

    time_span::difference_type time_span::hours_minutes_seconds_type::minutes() const
    {
        return m_minutes;
    }

    time_span::difference_type time_span::hours_minutes_seconds_type::seconds() const
    {
        return m_seconds;
    }

    time_span::difference_type time_span::seconds_of_whole_day()
    {
        return 24 * 60 * 60;
    }

    time_span::time_span(const difference_type seconds) : m_seconds{ seconds } {}

    time_span::time_span(const difference_type hours, const difference_type minutes, const difference_type seconds)
    : m_seconds{ calculate_seconds(hours, minutes, seconds) }
    {}

    time_span& time_span::operator+=(const time_span& another)
    {
        time_span temp{ *this };

        temp.m_seconds += another.m_seconds;

        boost::swap(temp, *this);
        return *this;
    }

    time_span& time_span::operator-=(const time_span& another)
    {
        time_span temp{ *this };

        temp.m_seconds -= another.m_seconds;

        boost::swap(temp, *this);
        return *this;
    }

    bool operator==(const time_span& one, const time_span& another)
    {
        return one.m_seconds == another.m_seconds;
    }

    bool operator<(const time_span& one, const time_span& another)
    {
        return one.m_seconds < another.m_seconds;
    }

    time_span::difference_type time_span::seconds() const
    {
        return m_seconds;
    }

    time_span::hours_minutes_seconds_type time_span::hours_minutes_seconds() const
    {
        const difference_type hours = m_seconds / (60 * 60);
        const difference_type minutes = m_seconds / 60 - hours * 60;
        const difference_type seconds = m_seconds - hours * 60 * 60 - minutes * 60;

        return hours_minutes_seconds_type{ hours, minutes, seconds };
    }
}
