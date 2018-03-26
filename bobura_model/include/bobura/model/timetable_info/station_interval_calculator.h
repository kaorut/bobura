/*! \file
    \brief The definition of bobura::model::timetable_info::station_interval_calculator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H

#include <algorithm>
#include <cassert>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/none.hpp>
#include <boost/optional.hpp>

#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>


namespace bobura::model::timetable_info {
    /*!
        \brief The class template for a station interval calculator.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
    */
    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    class station_interval_calculator : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The station location type.
        using station_location_type = station_location<string_type, operating_distance_type>;

        //! The station locations type.
        using station_locations_type = std::vector<station_location_type>;

        //! The train type.
        using train_type = train<size_type, difference_type, string_type>;

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
        static const time_span_type& default_interval()
        {
            static const time_span_type singleton{ 3 * 60 };
            return singleton;
        }


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
            const trains_type&            up_trains)
        : m_station_locations{ station_locations }, m_down_trains{ down_trains }, m_up_trains{ up_trains }
        {}


        // functions

        /*!
            \brief Calculates station intervals.

            \return Station intervals.
        */
        station_intervals_type calculate() const
        {
            if (m_station_locations.empty())
                return station_intervals_type(m_station_locations.size(), default_interval());

            station_intervals_type intervals{ m_station_locations.size(), default_interval() + whole_day2() };

            for (const auto& train : m_down_trains)
            {
                const auto intervals_by_train = calculate_by_train(train, true);
                assert(intervals.size() == intervals_by_train.size());
                std::transform(
                    intervals.begin(), intervals.end(), intervals_by_train.begin(), intervals.begin(), select);
            }
            for (const auto& train : m_up_trains)
            {
                const auto intervals_by_train = calculate_by_train(train, false);
                assert(intervals.size() == intervals_by_train.size());
                std::transform(
                    intervals.begin(), intervals.end(), intervals_by_train.begin(), intervals.begin(), select);
            }

            std::for_each(intervals.begin(), intervals.end(), normalize);
            return intervals;
        }


    private:
        // types

        using stop_index_type = typename train_type::stops_type::size_type;


        // static functions

        static const time_span_type& whole_day()
        {
            static const time_span_type singleton{ time_span_type::seconds_of_whole_day() };
            return singleton;
        }

        static const time_span_type& whole_day2()
        {
            static const time_span_type singleton{ whole_day().seconds() * 2 };
            return singleton;
        }

        static void normalize(time_span_type& interval)
        {
            if (interval >= whole_day2())
                interval -= whole_day2();
            else if (interval >= whole_day())
                interval -= whole_day();

            if (interval <= time_span_type{ 0 })
                interval = default_interval();
        }

        static const time_span_type& select(const time_span_type& interval1, const time_span_type& interval2)
        {
            return std::min<time_span_type>(interval1, interval2);
        }


        // variables

        const station_locations_type& m_station_locations;

        const trains_type& m_down_trains;

        const trains_type& m_up_trains;


        // functions

        station_intervals_type calculate_by_train(const train_type& train, const bool down) const
        {
            station_intervals_type intervals{ train.stops().size(), default_interval() + whole_day2() };

            for (stop_index_type from = 0; from < train.stops().size() - 1;)
            {
                if (!calculate_travel_time(train, from, from))
                {
                    ++from;
                    continue;
                }

                stop_index_type to = from + 1;
                for (; to < train.stops().size(); ++to)
                {
                    const auto departure = down ? from : to;
                    const auto arrival = down ? to : from;
                    const auto travel_time = calculate_travel_time(train, departure, arrival);
                    if (travel_time)
                    {
                        time_span_type interval{ static_cast<typename time_span_type::difference_type>(
                            travel_time->seconds() / (to - from)) };
                        if (to - from > 1)
                            interval += whole_day();
                        for (stop_index_type i = from; i < to; ++i)
                            intervals[i] = std::move(interval);
                        break;
                    }
                }

                from = to;
            }

            return intervals;
        }

        boost::optional<time_span_type>
        calculate_travel_time(const train_type& train, const stop_index_type from, const stop_index_type to) const
        {
            const auto& from_stop = train.stops()[from];
            const auto  from_time = from_stop.departure().initialized() ? from_stop.departure() : from_stop.arrival();
            if (!from_time.initialized())
                return boost::none;

            const auto& to_stop = train.stops()[to];
            const auto  to_time = to_stop.arrival().initialized() ? to_stop.arrival() : to_stop.departure();
            if (!to_time.initialized())
                return boost::none;

            return boost::make_optional(to_time - from_time);
        }
    };
}


#endif
