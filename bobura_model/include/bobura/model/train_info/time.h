/*! \file
    \brief The definition of bobura::model::train_info::time.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIME_H)
#define BOBURA_MODEL_TRAININFO_TIME_H

#include <cassert>
#include <limits>
#include <stdexcept>

#include <boost/operators.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>

#include <bobura/model/train_info/time_span.h>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class template for a time.

        \tparam Size       A size type.
        \tparam Difference A difference type.
    */
    template <typename Size, typename Difference>
    class time :
        private boost::totally_ordered<time<Size, Difference>>,
        private boost::additive<time<Size, Difference>, time_span<Difference>>
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The time span type.
        using time_span_type = time_span<difference_type>;

        //! The hours-minutes-seconds type.
        class hours_minutes_seconds_type : private boost::equality_comparable<hours_minutes_seconds_type>
        {
        public:
            /*!
                \brief Creates hours-minutes-seconds.

                \param hours   Hours.
                \param minutes Minutes.
                \param seconds Seconds.
            */
            hours_minutes_seconds_type(const size_type hours, const size_type minutes, const size_type seconds)
            :
            m_hours(hours),
            m_minutes(minutes),
            m_seconds(seconds)
            {}

            /*!
                \brief Checks whether one hours-minutes-seconds is equal to another.

                \param one     One hours-minutes-seconds.
                \param another Another hours-minutes-seconds.

                \retval true  When the one is equal to the other.
                \retval false Otherwise.
            */
            friend bool operator==(const hours_minutes_seconds_type& one, const hours_minutes_seconds_type& another)
            {
                return
                    one.m_hours == another.m_hours &&
                    one.m_minutes == another.m_minutes &&
                    one.m_seconds == another.m_seconds;
            }

            /*!
                \brief Returns hours.

                \return Hours.
            */
            size_type hours()
            const
            {
                return m_hours;
            }

            /*!
                \brief Returns minutes.

                \return Minutes.
            */
            size_type minutes()
            const
            {
                return m_minutes;
            }

            /*!
                \brief Returns seconds.

                \return Seconds.
            */
            size_type seconds()
            const
            {
                return m_seconds;
            }


        private:
            size_type m_hours;

            size_type m_minutes;

            size_type m_seconds;

        };


        // static functions

        /*!
            \brief Returns the uninitialized time.

            The uninitialized time is not equal to any other time, and it is larger than any other time.
            Addition and subtraction to the uninitialized time always returns the uninitialized time itself.
            The seconds (and also hours, minutes) cannot be obtained.

            \return The uninitialized time.
        */
        static const time& uninitialized()
        {
            static const time singleton{};

            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Creates a time.

            When seconds_from_midnight is greater than time_span_type::seconds_of_whole_day(), it is assumed that the
            result of seconds_from_midnight % time_span_type::seconds_of_whole_day() is passed.

            \param seconds_from_midnight Seconds from the midnight.
        */
        explicit time(const size_type seconds_from_midnight)
        :
        m_seconds_from_midnight(seconds_from_midnight % time_span_type::seconds_of_whole_day())
        {}

        /*!
            \brief Creates a time.

            \param hours   Hours. It must be that 0 <= hours <= 23.
            \param minutes Minutes. It must be that 0 <= minutes <= 59.
            \param seconds Seconds. It must be that 0 <= seconds <= 59.

            \throw std::out_of_range When hours, minutes and/or seconds are invalid.
        */
        time(const size_type hours, const size_type minutes, const size_type seconds)
        :
        m_seconds_from_midnight(calculate_seconds_from_midnight(hours, minutes, seconds))
        {}


        // functions

        /*!
            \brief Adds a time span.

            After this operation, seconds_from_midnight() must be that seconds_from_midnight() <
            seconds_of_whole_day().
            When time_span is too large or too small, the result is seconds_from_midnight() % seconds_from_midnight().

            When this is uninitialized, the result is also uninitialized.

            \param time_span A time span.

            \return This object.
        */
        time& operator+=(const time_span_type& time_span)
        {
            if (*this == uninitialized()) return *this;

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

        /*!
            \brief Subtracts a time span.

            After this operation, seconds_from_midnight() must be that seconds_from_midnight() <
            seconds_of_whole_day(). When time_span is too large or too small, the result is seconds_from_midnight() %
            seconds_from_midnight().

            When this is uninitialized, the result is also uninitialized.

            \param time_span A time span.

            \return This object.
        */
        time& operator-=(const time_span_type& time_span)
        {
            if (*this == uninitialized()) return *this;

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

        /*!
            \brief Subtracts times.

            The result is always 0 or positive. A smaller minus a larger is calculated over the midnight.

            \param one     One time.
            \param another Another time.

            \return The time span.

            \throw std::logic_error When one and/or another are uninitialized.
        */
        friend time_span_type operator-(const time& one, const time& another)
        {
            if (one == uninitialized() || another == uninitialized())
                BOOST_THROW_EXCEPTION(std::logic_error("The time object is uninitialized."));

            typename time_span_type::difference_type seconds = one.m_seconds_from_midnight;
            seconds -= another.m_seconds_from_midnight;
            while (seconds < 0)
                seconds += time_span_type::seconds_of_whole_day();

            return time_span_type{ seconds };
        }

        /*!
            \brief Checks whether one time is equal to another.

            \param one     One time.
            \param another Another time.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const time& one, const time& another)
        {
            return one.m_seconds_from_midnight == another.m_seconds_from_midnight;
        }

        /*!
            \brief Checks whether one time is less than another.

            \param one     One time.
            \param another Another time.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const time& one, const time& another)
        {
            return one.m_seconds_from_midnight < another.m_seconds_from_midnight;
        }

        /*!
            \brief Returns the seconds from the midnight.

            \return The seconds from the midnight.

            \throw std::logic_error When this is uninitialized.
        */
        size_type seconds_from_midnight()
        const
        {
            if (*this == uninitialized())
                BOOST_THROW_EXCEPTION(std::logic_error("The time object is uninitialized."));

            return m_seconds_from_midnight;
        }

        /*!
            \brief Returns the hours, minutes and seconds.

            \return The hours, minutes and seconds.

            \throw std::logic_error When this is uninitialized.
        */
        const hours_minutes_seconds_type hours_minutes_seconds()
        const
        {
            if (*this == uninitialized())
                BOOST_THROW_EXCEPTION(std::logic_error("The time object is uninitialized."));

            const size_type hours = m_seconds_from_midnight / (60 * 60);
            const size_type minutes = m_seconds_from_midnight / 60 - hours * 60;
            const size_type seconds = m_seconds_from_midnight - hours * 60 * 60 - minutes * 60;

            return hours_minutes_seconds_type{ hours, minutes, seconds };
        }

        /*!
            \brief Checks whether this time is initialized.

            \retval true  When this time is initialized.
            \retval false Otherwise.
        */
        bool initialized()
        const
        {
            return *this != uninitialized();
        }


    private:
        // static functions

        static size_type calculate_seconds_from_midnight(
            const size_type hours,
            const size_type minutes,
            const size_type seconds
        )
        {
            if (hours > 23)
                BOOST_THROW_EXCEPTION(std::out_of_range("24 or greater is specified for the hours."));
            else if (minutes > 59)
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or greater is specified for the minutes."));
            else if (seconds > 59)
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or greater is specified for the seconds."));

            const size_type seconds_from_midnight = hours * 60 * 60 + minutes * 60 + seconds;
            assert(seconds_from_midnight < static_cast<size_type>(time_span_type::seconds_of_whole_day()));

            return seconds_from_midnight;
        }


        // constructors and destructor

        time()
        :
        m_seconds_from_midnight(std::numeric_limits<size_type>::max())
        {}


        // variables

        size_type m_seconds_from_midnight;


    };


}}}


#endif
