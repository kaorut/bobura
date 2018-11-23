/*! \file
    \brief The definition of bobura::model::train_info::time_span.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define BOBURA_MODEL_TRAININFO_TIMESPAN_H

#include <boost/operators.hpp>

#include <bobura/type_list.h>


namespace bobura::model::train_info {
    /*!
        \brief The class for a time span.
    */
    class time_span : private boost::totally_ordered<time_span>, private boost::additive<time_span>
    {
    public:
        // types

        //! The difference type.
        using difference_type = type_list::common::difference_type;

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
            hours_minutes_seconds_type(difference_type hours, difference_type minutes, difference_type seconds);

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
            difference_type hours() const;

            /*!
                \brief Returns minutes.

                \return Minutes.
            */
            difference_type minutes() const;

            /*!
                \brief Returns seconds.

                \return Seconds.
            */
            difference_type seconds() const;


        private:
            difference_type m_hours;

            difference_type m_minutes;

            difference_type m_seconds;
        };


        // static functions

        /*!
            \brief Returns the seconds of a whole day.

            The value is 24 * 60 * 60 (= 86400).

            \return The seconds of a whole way.
        */
        static difference_type seconds_of_whole_day();


        // constructors and destructor

        /*!
            \brief Creates a time span.

            \param seconds A second span.
        */
        explicit time_span(difference_type seconds);

        /*!
            \brief Creates a time span.

            The hours, the minutes and the seconds must be 0 or must have the
            same signs.

            \param hours   An hour span.
            \param minutes A minute span. It must be that -59 <= minutes <= 59.
            \param seconds A second span. It must be that -59 <= seconds <= 59.

            \throw std::out_of_range     When the minutes and/or seconds are invalid.
            \throw std::invalid_argument When the signs of the hours and the minutes and the seconds are different.
        */
        time_span(difference_type hours, difference_type minutes, difference_type seconds);


        // functions

        /*!
            \brief Adds another time span.

            \param another Another time span.

            \return This object.
        */
        time_span& operator+=(const time_span& another);

        /*!
            \brief Subtracts another time span.

            \param another Another time span.

            \return This object.
        */
        time_span& operator-=(const time_span& another);

        /*!
            \brief Checks whether one time span is equal to another.

            \param one     One time span.
            \param another Another time span.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const time_span& one, const time_span& another);

        /*!
            \brief Checks whether one time span is less than another.

            \param one     One time span.
            \param another Another time span.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const time_span& one, const time_span& another);

        /*!
            \brief Returns the seconds.

            \return The seconds.
        */
        difference_type seconds() const;

        /*!
            \brief Returns the hours, minutes and seconds.

            \return The hours, minutes and seconds.
        */
        hours_minutes_seconds_type hours_minutes_seconds() const;


    private:
        // variables

        difference_type m_seconds;
    };
}


#endif
