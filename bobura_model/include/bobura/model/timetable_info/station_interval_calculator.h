/*! \file
    \brief The definition of bobura::model::timetable_info::station_interval_calculator.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/type_list.h>


namespace bobura::model::timetable_info {
    /*!
        \brief The class for a station interval calculator.
    */
    class station_interval_calculator : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = type_list::common::size_type;

        //! The difference type.
        using difference_type = type_list::common::difference_type;

        //! The string type.
        using string_type = type_list::common::string_type;

        //! The station location type.
        using station_location_type = station_location;

        //! The station locations type.
        using station_locations_type = std::vector<station_location_type>;

        //! The train type.
        using train_type = train;

        //! The trains type.
        using trains_type = std::vector<train_type>;

        //! The stop type.
        using stop_type = typename train_type::stop_type;

        //! The time type.
        using time_type = typename stop_type::time_type;

        //! The time span type.
        using time_span_type = typename time_type::time_span_type;

        //! The station intervals type.
        using station_intervals_type = std::vector<time_span_type>;


        // static functions

        /*!
            \brief Returns the default interval.

            \return The default interval.
        */
        static const time_span_type& default_interval();


        // constructors and destructor

        /*!
            \brief Creates a station interval calculator.

            \param station_locations Station locations.
            \param down_trains       Down trains.
            \param up_trains         Up trains.
        */
        station_interval_calculator(
            const station_locations_type& station_locations,
            const trains_type&            down_trains,
            const trains_type&            up_trains);

        /*!
            \brief Destroys the station interval calculator.
        */
        ~station_interval_calculator();


        // functions

        /*!
            \brief Calculates station intervals.

            \return Station intervals.
        */
        station_intervals_type calculate() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
