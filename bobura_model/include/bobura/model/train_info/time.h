/*! \file
    \brief The definition of bobura::model::train_info::time.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIME_H)
#define BOBURA_MODEL_TRAININFO_TIME_H

#include <boost/operators.hpp>

#include <bobura/model/train_info/time_span.h>
#include <bobura/type_list.h>


namespace bobura::model::train_info {
    /*!
        \brief The class for a time.
    */
    class time : private boost::totally_ordered<time>,
                 private boost::additive<time, time_span<type_list ::common::difference_type>>
    {
    public:
        // types

        //! The size type.
        using size_type = type_list::common::size_type;

        //! The time span type.
        using time_span_type = time_span<type_list ::common::difference_type>;

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
            hours_minutes_seconds_type(size_type hours, size_type minutes, size_type seconds);

            /*!
                \brief Checks whether one hours-minutes-seconds is equal to another.

                \param one     One hours-minutes-seconds.
                \param another Another hours-minutes-seconds.

                \retval true  When the one is equal to the other.
                \retval false Otherwise.
            */
            friend bool operator==(const hours_minutes_seconds_type& one, const hours_minutes_seconds_type& another);

            /*!
                \brief Returns hours.

                \return Hours.
            */
            size_type hours() const;

            /*!
                \brief Returns minutes.

                \return Minutes.
            */
            size_type minutes() const;

            /*!
                \brief Returns seconds.

                \return Seconds.
            */
            size_type seconds() const;


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
        static const time& uninitialized();


        // constructors and destructor

        /*!
            \brief Creates a time.

            When seconds_from_midnight is greater than time_span_type::seconds_of_whole_day(), it is assumed that the
            result of seconds_from_midnight % time_span_type::seconds_of_whole_day() is passed.

            \param seconds_from_midnight Seconds from the midnight.
        */
        explicit time(size_type seconds_from_midnight);

        /*!
            \brief Creates a time.

            \param hours   Hours. It must be that 0 <= hours <= 23.
            \param minutes Minutes. It must be that 0 <= minutes <= 59.
            \param seconds Seconds. It must be that 0 <= seconds <= 59.

            \throw std::out_of_range When hours, minutes and/or seconds are invalid.
        */
        time(size_type hours, size_type minutes, size_type seconds);


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
        time& operator+=(const time_span_type& time_span);

        /*!
            \brief Subtracts a time span.

            After this operation, seconds_from_midnight() must be that seconds_from_midnight() <
            seconds_of_whole_day(). When time_span is too large or too small, the result is seconds_from_midnight() %
            seconds_from_midnight().

            When this is uninitialized, the result is also uninitialized.

            \param time_span A time span.

            \return This object.
        */
        time& operator-=(const time_span_type& time_span);

        /*!
            \brief Subtracts times.

            The result is always 0 or positive. A smaller minus a larger is calculated over the midnight.

            \param one     One time.
            \param another Another time.

            \return The time span.

            \throw std::logic_error When one and/or another are uninitialized.
        */
        friend time_span_type operator-(const time& one, const time& another);

        /*!
            \brief Checks whether one time is equal to another.

            \param one     One time.
            \param another Another time.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const time& one, const time& another);

        /*!
            \brief Checks whether one time is less than another.

            \param one     One time.
            \param another Another time.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const time& one, const time& another);

        /*!
            \brief Returns the seconds from the midnight.

            \return The seconds from the midnight.

            \throw std::logic_error When this is uninitialized.
        */
        size_type seconds_from_midnight() const;

        /*!
            \brief Returns the hours, minutes and seconds.

            \return The hours, minutes and seconds.

            \throw std::logic_error When this is uninitialized.
        */
        hours_minutes_seconds_type hours_minutes_seconds() const;

        /*!
            \brief Checks whether this time is initialized.

            \retval true  When this time is initialized.
            \retval false Otherwise.
        */
        bool initialized() const;


    private:
        // constructors and destructor

        time();


        // variables

        size_type m_seconds_from_midnight;
    };
}


#endif
