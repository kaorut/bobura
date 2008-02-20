/*! \file
    \brief The definition of bobura::model::timetable_info::StationAndMetersConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLENINFO_STATIONANDMETERSCONCEPT_H)
#define BOBURA_MODEL_TIMETABLENINFO_STATIONANDMETERSCONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The concept check class template for a station_and_meters.

        \tparam StationAndMeters A station_and_meters type.
    */
    template <typename StationAndMeters>
    class StationAndMetersConcept
    {
    public:
        // constructors and destructor

        StationAndMetersConcept();


        // functions

        /*!
            \brief Checks the constraints on a station_and_meters.
        */
        void constraints()
        {
            typedef typename StationAndMeters::station_type station_type;
            typedef typename StationAndMeters::meters_type meters_type;

            m_station_and_meters.swap(m_station_and_meters);
            std::swap(m_station_and_meters, m_station_and_meters);

            StationAndMeters& station_and_meters =
                m_station_and_meters = m_station_and_meters;
            boost::ignore_unused_variable_warning(station_and_meters);

            const_constraints(m_station_and_meters);
        }

        /*!
            \brief Checks the const constraints on a station_and_meters.
        */
        void const_constraints(const StationAndMeters& station_and_meters)
        {
            const typename StationAndMeters::station_type& station =
                station_and_meters.station();
            boost::ignore_unused_variable_warning(station);

            const typename StationAndMeters::meters_type& meters =
                station_and_meters.meters();
            boost::ignore_unused_variable_warning(meters);

            const bool before = station_and_meters.before(station_and_meters);
            boost::ignore_unused_variable_warning(before);
        }


    private:
        // variables

        StationAndMeters m_station_and_meters;


    };


}}}

#endif
