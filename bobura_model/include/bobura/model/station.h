/*! \file
    \brief The definition of bobura::model::station.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATION_H)
#define BOBURA_MODEL_STATION_H

#include <boost/operators.hpp>

#include <bobura/model/station_info/grade.h>
#include <bobura/type_list.h>


namespace bobura::model {
    /*!
        \brief The class for a station.
    */
    class station : private boost::equality_comparable<station>
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::common::string_type;

        //! The grade type.
        using grade_type = station_info::grade;


        // constructors and destructor

        /*!
            \brief Creates a station.

            \param name                     A name.
            \param grade                    A grade.
            \param shows_down_arrival_times True when the arrival times of down trains are shown.
            \param shows_up_arrival_times   True when the arrival times of up trains are shown.
            \param note                     A note.
        */
        station(
            string_type       name,
            const grade_type& grade,
            bool              shows_down_arrival_times,
            bool              shows_up_arrival_times,
            string_type       note);


        // functions

        /*!
            \brief Checks whether one station is equal to another.

            \param one     One station.
            \param another Another station.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const station& one, const station& another);

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name() const;

        /*!
            \brief Returns the grade.

            \return The grade.
        */
        const grade_type& grade() const;

        /*!
            \brief Returns whether the arrival times of down trains are shown.

            \retval true  When the arrival times of down trains are shown.
            \retval false Otherwise.
        */
        bool shows_down_arrival_times() const;

        /*!
            \brief Returns whether the arrival times of up trains are shown.

            \retval true  When the arrival times of up trains are shown.
            \retval false Otherwise.
        */
        bool shows_up_arrival_times() const;

        /*!
            \brief Returns the note.

            \return The note.
        */
        const string_type& note() const;


    private:
        // variables

        string_type m_name;

        const grade_type* m_p_grade;

        bool m_shows_down_arrival_times;

        bool m_shows_up_arrival_times;

        string_type m_note;
    };
}


#endif
