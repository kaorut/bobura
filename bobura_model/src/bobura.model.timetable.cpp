/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>

#include <bobura/model/message/timetable_observer_set.h>
#include <bobura/model/timetable.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>
#include <bobura/model/train_info/time_span.h>
#include <bobura/model/train_kind.h>


namespace {
    // types

    using direction_type = bobura::model::timetable::train_type::direction_type;

    using stop_type = bobura::model::timetable::train_type::stop_type;

    using time_type = stop_type::time_type;

    using time_span_type = typename time_type::time_span_type;

    struct replace_train_kind_index
    {
        const bobura::model::timetable::train_kinds_type& m_train_kinds;

        const std::vector<bobura::model::timetable::size_type>& m_train_kind_index_map;

        replace_train_kind_index(
            const bobura::model::timetable::train_kinds_type&       train_kinds,
            const std::vector<bobura::model::timetable::size_type>& train_kind_index_map)
        : m_train_kinds{ train_kinds }, m_train_kind_index_map{ train_kind_index_map }
        {}

        void operator()(bobura::model::timetable::train_type& train) const
        {
            if (train.kind_index() >= m_train_kind_index_map.size())
                BOOST_THROW_EXCEPTION(std::out_of_range("Invalid old index in the train kind index map."));
            const auto new_index = m_train_kind_index_map[train.kind_index()];
            if (new_index >= m_train_kinds.size())
                BOOST_THROW_EXCEPTION(std::out_of_range("Invalid new index in the train_kind index map."));

            train.set_kind_index(new_index);
        }
    };


    // functions

    void insert_train_stop(
        bobura::model::timetable::train_type&           train,
        const bobura::model::timetable::difference_type offset)
    {
        train.insert_stop(
            train.stops().begin() + offset,
            stop_type(
                time_type::uninitialized(),
                time_type::uninitialized(),
                false,
                bobura::model::timetable::string_type{}));
    }

    void erase_train_stops(
        bobura::model::timetable::train_type&           train,
        const bobura::model::timetable::difference_type first_offset,
        const bobura::model::timetable::difference_type last_offset)
    {
        train.erase_stops(train.stops().begin() + first_offset, train.stops().begin() + last_offset);
    }

    void update_train_kind_index(
        bobura::model::timetable::train_type&     train,
        const bobura::model::timetable::size_type index,
        const std::ptrdiff_t                      index_delta)
    {
        if (train.kind_index() < index)
            return;

        bobura::model::timetable::train_type new_train{
            train.direction(), train.number(),      train.kind_index() + index_delta,
            train.name(),      train.name_number(), train.note()
        };
        for (const auto& stop : train.stops())
            new_train.insert_stop(new_train.stops().end(), stop);

        train = new_train;
    }

    bobura::model::timetable::operating_distance_type distance_between(
        const bobura::model::timetable::station_locations_type&                 station_locations,
        const bobura::model::timetable::train_type&                             train,
        const bobura::model::timetable::train_type::stops_type::const_iterator& i_departure,
        const bobura::model::timetable::train_type::stops_type::const_iterator& i_arrival)
    {
        const auto departure_index = std::distance(train.stops().begin(), i_departure);
        assert(static_cast<bobura::model::timetable::size_type>(departure_index) < station_locations.size());
        const auto& departure_distance = station_locations[departure_index].operating_distance();

        const auto arrival_index = std::distance(train.stops().begin(), i_arrival);
        assert(static_cast<bobura::model::timetable::size_type>(arrival_index) < station_locations.size());
        const auto& arrival_distance = station_locations[arrival_index].operating_distance();

        return train.direction() == direction_type::down ? arrival_distance - departure_distance :
                                                           departure_distance - arrival_distance;
    }

    time_span_type time_span_between(
        const bobura::model::timetable::train_type::stops_type::const_iterator& i_departure,
        const bobura::model::timetable::train_type::stops_type::const_iterator& i_arrival)
    {
        if (i_departure->passing())
            BOOST_THROW_EXCEPTION(std::invalid_argument("The departure is passing."));
        if (i_arrival->passing())
            BOOST_THROW_EXCEPTION(std::invalid_argument("The departure is passing."));

        const auto departure_time =
            i_departure->departure().initialized() ? i_departure->departure() : i_departure->arrival();
        const auto arrival_time = i_arrival->arrival().initialized() ? i_arrival->arrival() : i_arrival->departure();
        assert(departure_time.initialized() && arrival_time.initialized());

        return arrival_time - departure_time;
    }

    bool can_insert_to(
        const bobura::model::timetable&                                        timetable,
        const bobura::model::timetable::station_locations_type::const_iterator position,
        const bobura::model::timetable::station_location_type&                 station_location)
    {
        if (position != timetable.station_locations().begin() && !std::prev(position)->before(station_location))
            return false;

        if (position != timetable.station_locations().end() && !station_location.before(*position))
            return false;

        return true;
    }

    void insert_train_impl(
        const bobura::model::timetable&                             timetable,
        bobura::model::timetable::trains_type&                      trains,
        const bobura::model::timetable::trains_type::const_iterator position,
        bobura::model::timetable::train_type                        train)
    {
        if (train.kind_index() >= timetable.train_kinds().size())
        {
            BOOST_THROW_EXCEPTION(
                std::invalid_argument("The kind index of the train is greater than the train kind count."));
        }
        if (train.stops().size() != timetable.station_locations().size())
        {
            BOOST_THROW_EXCEPTION(std::invalid_argument(
                "The count of the train stops does not coincide with the one of the station locations."));
        }

        trains.insert(position, std::move(train));

        timetable.observer_set().changed()();
    }

    void erase_trains_impl(
        const bobura::model::timetable&                             timetable,
        bobura::model::timetable::trains_type&                      trains,
        const bobura::model::timetable::trains_type::const_iterator first,
        const bobura::model::timetable::trains_type::const_iterator last)
    {
        trains.erase(first, last);

        timetable.observer_set().changed()();
    }
}


namespace bobura::model {
    timetable::timetable()
    : m_company_name{}, m_line_name{}, m_note{}, m_station_locations{}, m_train_kinds{}, m_down_trains{}, m_up_trains{},
      m_font_color_set{ font_color_set_type::default_() }, m_observer_set{}
    {}

    bool operator==(const timetable& one, const timetable& another)
    {
        return one.m_company_name == another.m_company_name && one.m_line_name == another.m_line_name &&
               one.m_note == another.m_note && one.m_station_locations == another.m_station_locations &&
               one.m_train_kinds == another.m_train_kinds && one.m_down_trains == another.m_down_trains &&
               one.m_up_trains == another.m_up_trains;
    }

    const timetable::string_type& timetable::company_name() const
    {
        return m_company_name;
    }

    void timetable::set_company_name(string_type company_name)
    {
        m_company_name = std::move(company_name);

        m_observer_set.changed()();
    }

    const timetable::string_type& timetable::line_name() const
    {
        return m_line_name;
    }

    void timetable::set_line_name(string_type line_name)
    {
        m_line_name = std::move(line_name);

        m_observer_set.changed()();
    }

    const timetable::string_type& timetable::note() const
    {
        return m_note;
    }

    void timetable::set_note(string_type note)
    {
        m_note = std::move(note);

        m_observer_set.changed()();
    }

    const timetable::station_locations_type& timetable::station_locations() const
    {
        return m_station_locations;
    }

    void timetable::insert_station_location(
        const typename station_locations_type::const_iterator position,
        station_location_type                                 station_location)
    {
        if (!can_insert_to(*this, position, station_location))
            BOOST_THROW_EXCEPTION(std::invalid_argument("The insertion position is invalid."));

        const difference_type offset =
            std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), position);

        m_station_locations.insert(position, std::move(station_location));

        std::for_each(m_down_trains.begin(), m_down_trains.end(), [offset](train_type& train) {
            insert_train_stop(train, offset);
        });
        std::for_each(
            m_up_trains.begin(), m_up_trains.end(), [offset](train_type& train) { insert_train_stop(train, offset); });

        m_observer_set.changed()();
    }

    void timetable::erase_station_locations(
        const typename station_locations_type::const_iterator first,
        const typename station_locations_type::const_iterator last)
    {
        const difference_type first_offset =
            std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), first);
        const difference_type last_offset =
            std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), last);

        m_station_locations.erase(first, last);

        std::for_each(m_down_trains.begin(), m_down_trains.end(), [first_offset, last_offset](train_type& train) {
            erase_train_stops(train, first_offset, last_offset);
        });
        std::for_each(m_up_trains.begin(), m_up_trains.end(), [first_offset, last_offset](train_type& train) {
            erase_train_stops(train, first_offset, last_offset);
        });

        m_observer_set.changed()();
    }

    timetable::station_intervals_type timetable::station_intervals() const
    {
        const station_interval_calculator_type calculator{ m_station_locations, m_down_trains, m_up_trains };
        return calculator.calculate();
    }

    const timetable::train_kinds_type& timetable::train_kinds() const
    {
        return m_train_kinds;
    }

    bool timetable::train_kind_referred(const typename train_kinds_type::const_iterator position) const
    {
        return train_kind_referred(std::distance(m_train_kinds.begin(), position));
    }

    bool timetable::train_kind_referred(const size_type& train_kind_index) const
    {
        const auto referred_by_down_trains =
            std::find_if(m_down_trains.begin(), m_down_trains.end(), [train_kind_index](const train_type& train) {
                return train.kind_index() == train_kind_index;
            }) != m_down_trains.end();
        const auto referred_by_up_trains =
            std::find_if(m_up_trains.begin(), m_up_trains.end(), [train_kind_index](const train_type& train) {
                return train.kind_index() == train_kind_index;
            }) != m_up_trains.end();

        return referred_by_down_trains || referred_by_up_trains;
    }

    void
    timetable::insert_train_kind(const typename train_kinds_type::const_iterator position, train_kind_type train_kind)
    {
        const size_type inserted_index =
            std::distance<typename train_kinds_type::const_iterator>(m_train_kinds.begin(), position);

        m_train_kinds.insert(position, std::move(train_kind));

        std::for_each(m_down_trains.begin(), m_down_trains.end(), [inserted_index](train_type& train) {
            update_train_kind_index(train, inserted_index, 1);
        });
        std::for_each(m_up_trains.begin(), m_up_trains.end(), [inserted_index](train_type& train) {
            update_train_kind_index(train, inserted_index, 1);
        });

        m_observer_set.changed();
    }

    void timetable::set_train_kind(const typename train_kinds_type::const_iterator position, train_kind_type train_kind)
    {
        auto mutable_position = m_train_kinds.begin();
        std::advance(
            mutable_position,
            std::distance(static_cast<typename train_kinds_type::const_iterator>(m_train_kinds.begin()), position));

        *mutable_position = std::move(train_kind);

        m_observer_set.changed();
    }

    void timetable::erase_train_kind(const typename train_kinds_type::const_iterator position)
    {
        if (train_kind_referred(position))
            BOOST_THROW_EXCEPTION(std::invalid_argument("The train kind is still referred."));

        const size_type erased_index =
            std::distance<typename train_kinds_type::const_iterator>(m_train_kinds.begin(), position);

        m_train_kinds.erase(position);

        std::for_each(m_down_trains.begin(), m_down_trains.end(), [erased_index](train_type& train) {
            update_train_kind_index(train, erased_index, -1);
        });
        std::for_each(m_up_trains.begin(), m_up_trains.end(), [erased_index](train_type& train) {
            update_train_kind_index(train, erased_index, -1);
        });

        m_observer_set.changed();
    }

    void timetable::assign_train_kinds(train_kinds_type train_kinds, const std::vector<size_type>& train_kind_index_map)
    {
        std::for_each(
            m_down_trains.begin(), m_down_trains.end(), replace_train_kind_index(train_kinds, train_kind_index_map));
        std::for_each(
            m_up_trains.begin(), m_up_trains.end(), replace_train_kind_index(train_kinds, train_kind_index_map));

        m_train_kinds = std::move(train_kinds);

        m_observer_set.changed()();
    }

    const timetable::trains_type& timetable::down_trains() const
    {
        return m_down_trains;
    }

    const timetable::trains_type& timetable::up_trains() const
    {
        return m_up_trains;
    }

    void timetable::insert_down_train(const typename trains_type::const_iterator position, train_type train)
    {
        if (train.direction() != direction_type::down)
            BOOST_THROW_EXCEPTION(std::invalid_argument("The train is not downward."));

        insert_train_impl(*this, m_down_trains, position, std::move(train));
    }

    void timetable::insert_up_train(const typename trains_type::const_iterator position, train_type train)
    {
        if (train.direction() != direction_type::up)
            BOOST_THROW_EXCEPTION(std::invalid_argument("The train is not upward."));

        insert_train_impl(*this, m_up_trains, position, std::move(train));
    }

    void timetable::erase_down_trains(
        const typename trains_type::const_iterator first,
        const typename trains_type::const_iterator last)
    {
        erase_trains_impl(*this, m_down_trains, first, last);
    }

    void timetable::erase_up_trains(
        const typename trains_type::const_iterator first,
        const typename trains_type::const_iterator last)
    {
        erase_trains_impl(*this, m_up_trains, first, last);
    }

    timetable::speed_type timetable::scheduled_speed(
        const train_type&                                      train,
        const typename train_type::stops_type::const_iterator& i_departure,
        const typename train_type::stops_type::const_iterator& i_arrival) const
    {
        if (i_departure == train.stops().end())
            BOOST_THROW_EXCEPTION(std::invalid_argument("i_departure is invalid."));
        if (i_arrival == train.stops().end())
            BOOST_THROW_EXCEPTION(std::invalid_argument("i_departure is invalid."));
        if (std::find_if(
                m_down_trains.begin(), m_down_trains.end(), [&train](const train_type& t) { return &t == &train; }) ==
                m_down_trains.end() &&
            std::find_if(m_up_trains.begin(), m_up_trains.end(), [&train](const train_type& t) {
                return &t == &train;
            }) == m_up_trains.end())
        {
            BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown train."));
        }
        if ((train.direction() == direction_type::down && std::distance(i_departure, i_arrival) <= 0) ||
            (train.direction() == direction_type::up && std::distance(i_departure, i_arrival) >= 0))
        {
            BOOST_THROW_EXCEPTION(std::invalid_argument("The departure is not before the arrival."));
        }

        const auto distance = distance_between(m_station_locations, train, i_departure, i_arrival);
        assert(distance > operating_distance_type{ 0 });

        const auto time_span = time_span_between(i_departure, i_arrival);

        return (distance * 60U * 60U) / static_cast<operating_distance_type>(time_span.seconds());
    }

    const timetable::font_color_set_type& timetable::font_color_set() const
    {
        return m_font_color_set;
    }

    void timetable::set_font_color_set(font_color_set_type font_color_set)
    {
        m_font_color_set = std::move(font_color_set);

        m_observer_set.changed()();
    }

    const timetable::observer_set_type& timetable::observer_set() const
    {
        return m_observer_set;
    }

    timetable::observer_set_type& timetable::observer_set()
    {
        return m_observer_set;
    }
}
