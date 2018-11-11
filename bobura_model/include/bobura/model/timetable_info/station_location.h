/*! \file
    \brief The definition of bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H

#include <memory>

#include <boost/operators.hpp>

#include <bobura/model/station.h>
#include <bobura/type_list.h>


namespace bobura::model::timetable_info {
    /*!
        \brief The class for a station location.
    */
    class station_location : private boost::equality_comparable<station_location>
    {
    public:
        // types

        //! The station type.
        using station_type = station<type_list::common::string_type>;

        //! The operating distance type.
        using operating_distance_type = type_list::common::operating_distance_type;


        // constructors and destructor

        /*!
            \brief Creates a station location.

            \param station            A station.
            \param operating_distance An operating distance.
        */
        station_location(station_type station, operating_distance_type operating_distance);

        /*!
            \brief Copies a station location.

            \param another Another station location.
        */
        station_location(const station_location& another);

        /*!
            \brief Moves a station location.

            \param another Another station location.
        */
        station_location(station_location&& another);

        /*!
            \brief Destroys the station location.
        */
        ~station_location();


        // functions

        /*!
            \brief Checks whether one station location is equal to another.

            \param one     One station location.
            \param another Another station location.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const station_location& one, const station_location& another);

        /*!
            \brief Assigns a station location.

            \param another Another station location.

            \return This object.
        */
        station_location& operator=(const station_location& another);

        /*!
            \brief Assigns a station location.

            \param another Another station location.

            \return This object.
        */
        station_location& operator=(station_location&& another);

        /*!
            \brief Returns the station.

            \return The station.
        */
        const station_type& get_station() const;

        /*!
            \brief Returns the operating distance.

            \return The operating distance.
        */
        const operating_distance_type& operating_distance() const;

        /*!
            \brief Checks this station is located before another.

            \param another Another sation_location.

            \retval true  When operating_distance() < another.operating_distance().
            \retval false Otherwise.
        */
        bool before(const station_location& another) const;


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
