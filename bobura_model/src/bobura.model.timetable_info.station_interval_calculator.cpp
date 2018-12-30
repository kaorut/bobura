/*! \file
    \brief The definition of bobura::model::timetable_info::station_interval_calculator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/stdalt.h>

#include <bobura/model/timetable_info/station_interval_calculator.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/type_list.h>


namespace bobura::model::timetable_info {
    class station_interval_calculator::impl : private boost::noncopyable
    {
    public:
        // types

        using station_locations_type = station_interval_calculator::station_locations_type;

        using trains_type = station_interval_calculator::trains_type;

        using time_span_type = station_interval_calculator::time_span_type;

        using station_intervals_type = station_interval_calculator::station_intervals_type;


        // static functions

        static const time_span_type& default_interval()
        {
            static const time_span_type singleton{ 3 * 60 };
            return singleton;
        }


        // constructors and destructor

        impl(
            const station_locations_type& station_locations,
            const trains_type&            down_trains,
            const trains_type&            up_trains)
        : m_station_locations{ station_locations }, m_down_trains{ down_trains }, m_up_trains{ up_trains }
        {}


        // functions

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

        using train_type = station_interval_calculator::train_type;

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

        tetengo2::stdalt::optional<time_span_type>
        calculate_travel_time(const train_type& train, const stop_index_type from, const stop_index_type to) const
        {
            const auto& from_stop = train.stops()[from];
            const auto  from_time = from_stop.departure().initialized() ? from_stop.departure() : from_stop.arrival();
            if (!from_time.initialized())
                return TETENGO2_STDALT_NULLOPT;

            const auto& to_stop = train.stops()[to];
            const auto  to_time = to_stop.arrival().initialized() ? to_stop.arrival() : to_stop.departure();
            if (!to_time.initialized())
                return TETENGO2_STDALT_NULLOPT;

            return tetengo2::stdalt::make_optional(to_time - from_time);
        }
    };


    const station_interval_calculator::time_span_type& station_interval_calculator::default_interval()
    {
        return impl::default_interval();
    }

    station_interval_calculator::station_interval_calculator(
        const station_locations_type& station_locations,
        const trains_type&            down_trains,
        const trains_type&            up_trains)
    : m_p_impl{ std::make_unique<impl>(station_locations, down_trains, up_trains) }
    {}

    station_interval_calculator::~station_interval_calculator() = default;

    station_interval_calculator::station_intervals_type station_interval_calculator::calculate() const
    {
        return m_p_impl->calculate();
    }
}
