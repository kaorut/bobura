/*! \file
    \brief The definition of bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H

#include <utility>

#include <boost/operators.hpp>

#include <bobura/model/station.h>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class template for a station location.

        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
    */
    template <typename String, typename OperatingDistance>
    class station_location : private boost::equality_comparable<station_location<String, OperatingDistance>>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The station type.
        using station_type = station<string_type>;


        // constructors and destructor

        /*!
            \brief Creates a station location.

            \param station            A station.
            \param operating_distance An operating distance.
        */
        station_location(station_type station, operating_distance_type operating_distance)
        :
        m_station(std::move(station)),
        m_operating_distance(std::move(operating_distance))
        {}


        // functions

        /*!
            \brief Checks whether one station location is equal to another.

            \param one     One station location.
            \param another Another station location.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const station_location& one, const station_location& another)
        {
            return one.m_station == another.m_station && one.m_operating_distance == another.m_operating_distance;
        }

        /*!
            \brief Returns the station.

            \return The station.
        */
        const station_type& station()
        const
        {
            return m_station;
        }

        /*!
            \brief Returns the operating distance.

            \return The operating distance.
        */
        const operating_distance_type& operating_distance()
        const
        {
            return m_operating_distance;
        }

        /*!
            \brief Checks this station is located before another.

            \param another Another sation_location.

            \retval true  When operating_distance() < another.operating_distance().
            \retval false Otherwise.
        */
        bool before(const station_location& another)
        const
        {
            return m_operating_distance < another.m_operating_distance;
        }


    private:
        // variables

        station_type m_station;

        operating_distance_type m_operating_distance;


    };


}}}


#endif
