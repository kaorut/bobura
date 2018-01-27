/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include <bobura/model/message/timetable_observer_set.h>
#include <bobura/model/timetable_info/font_color_set.h>
#include <bobura/model/timetable_info/station_interval_calculator.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_kind.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    class timetable :
        private boost::equality_comparable<timetable<Size, Difference, String, OperatingDistance, Speed, Font>>
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

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The station location type.
        using station_location_type = timetable_info::station_location<string_type, operating_distance_type>;

        //! The station locations type.
        using station_locations_type = std::vector<station_location_type>;

        //! The station interval calculator type.
        using station_interval_calculator_type =
            timetable_info::station_interval_calculator<
                size_type, difference_type, string_type, operating_distance_type
            >;

        //! The station intervals type.
        using station_intervals_type = typename station_interval_calculator_type::station_intervals_type;

        //! The train kind type.
        using train_kind_type = train_kind<string_type, font_type>;

        //! The train kinds type.
        using train_kinds_type = std::vector<train_kind_type>;

        //! The train type.
        using train_type = train<size_type, difference_type, string_type>;

        //! The trains type.
        using trains_type = std::vector<train_type>;

        //! The font color set type.
        using font_color_set_type = timetable_info::font_color_set<font_type>;

        //! The observer set type.
        using observer_set_type = message::timetable_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        :
        m_company_name(),
        m_line_name(),
        m_note(),
        m_station_locations(),
        m_train_kinds(),
        m_down_trains(),
        m_up_trains(),
        m_font_color_set(font_color_set_type::default_()),
        m_observer_set()
        {}


        // functions

        /*!
            \brief Checks whether this is equal to another timetable.

            \param one     One timetable.
            \param another Another timetable.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const timetable& one, const timetable& another)
        {
            return
                one.m_company_name == another.m_company_name &&
                one.m_line_name == another.m_line_name &&
                one.m_note == another.m_note &&
                one.m_station_locations == another.m_station_locations &&
                one.m_train_kinds == another.m_train_kinds &&
                one.m_down_trains == another.m_down_trains &&
                one.m_up_trains == another.m_up_trains;
        }

        /*!
            \brief Returns the company name.

            \return The company name.
        */
        const string_type& company_name()
        const
        {
            return m_company_name;
        }

        /*!
            \brief Sets a company name.

            \param company_name A company name.
        */
        void set_company_name(string_type company_name)
        {
            m_company_name = std::move(company_name);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the line name.

            \return The line name.
        */
        const string_type& line_name()
        const
        {
            return m_line_name;
        }

        /*!
            \brief Sets a line name.

            \param line_name A line name.
        */
        void set_line_name(string_type line_name)
        {
            m_line_name = std::move(line_name);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the note.

            \return The note.
        */
        const string_type& note()
        const
        {
            return m_note;
        }

        /*!
            \brief Sets a note.

            \param note A note.
        */
        void set_note(string_type note)
        {
            m_note = std::move(note);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the station locations.

            \return The station locations.
        */
        const station_locations_type& station_locations()
        const
        {
            return m_station_locations;
        }

        /*!
            \brief Inserts a station location.

            After the insertion, the station locations must be sequenced in ascending order.

            It also inserts a stop to the every train with uninitialized arrival and departure time and an empty
            platform, so that the count of the station locations coincides with the one of the every train stop.

            \param position         A position where a station location is inserted.
            \param station_location A station location.

            \throw std::invalid_argument When the station locations are not sequenced in ascending order after the
                                         insertion.
        */
        void insert_station_location(
            const typename station_locations_type::const_iterator position,
            station_location_type                                 station_location
        )
        {
            if (!can_insert_to(position, station_location))
                BOOST_THROW_EXCEPTION(std::invalid_argument("The insertion position is invalid."));

            const difference_type offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), position);

            m_station_locations.insert(position, std::move(station_location));

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                [offset](train_type& train) { insert_train_stop(train, offset); } 
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                [offset](train_type& train) { insert_train_stop(train, offset); }
            );

            m_observer_set.changed()();
        }

        /*!
            \brief Erases the station locations.

            It also erases stops from the every train, so that the count of the station locations coincides with the
            one of the every train stop.

            \param first A first iterator among the erased station locations.
            \param last  A last iterator among the erased station locations.
        */
        void erase_station_locations(
            const typename station_locations_type::const_iterator first,
            const typename station_locations_type::const_iterator last
        )
        {
            const difference_type first_offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), first);
            const difference_type last_offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), last);

            m_station_locations.erase(first, last);

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                [first_offset, last_offset](train_type& train) { erase_train_stops(train, first_offset, last_offset); }
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                [first_offset, last_offset](train_type& train) { erase_train_stops(train, first_offset, last_offset); }
            );

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the station intervals.

            \return The station intervals.
        */
        station_intervals_type station_intervals()
        const
        {
            const station_interval_calculator_type calculator{ m_station_locations, m_down_trains, m_up_trains };
            return calculator.calculate();
        }

        /*!
            \brief Returns the train kinds.

            \return The train kinds.
        */
        const train_kinds_type& train_kinds()
        const
        {
            return m_train_kinds;
        }

        /*!
            \brief Checks whether the train kind is referred by trains.

            \param position A train kind position.

            \retval true  The train kind is referred.
            \retval false Otherwise.
        */
        bool train_kind_referred(const typename train_kinds_type::const_iterator position)
        const
        {
            return train_kind_referred(std::distance(m_train_kinds.begin(), position));
        }

        /*!
            \brief Checks whether the train kind is referred by trains.

            \param train_kind_index A train kind index.

            \retval true  The train kind is referred.
            \retval false Otherwise.
        */
        bool train_kind_referred(const size_type& train_kind_index)
        const
        {
            const auto referred_by_down_trains =
                std::find_if(
                    m_down_trains.begin(),
                    m_down_trains.end(),
                    [train_kind_index](const train_type& train) { return train.kind_index() == train_kind_index; }
                ) != m_down_trains.end();
            const auto referred_by_up_trains =
                std::find_if(
                    m_up_trains.begin(),
                    m_up_trains.end(),
                    [train_kind_index](const train_type& train) { return train.kind_index() == train_kind_index; }
                ) != m_up_trains.end();

            return referred_by_down_trains || referred_by_up_trains;
        }

        /*!
            \brief Inserts a train kind.

            \param position   A position where a train kind is inserted.
            \param train_kind A train kind.
        */
        void insert_train_kind(
            const typename train_kinds_type::const_iterator position,
            train_kind_type                                 train_kind
        )
        {
            const size_type inserted_index =
                std::distance<typename train_kinds_type::const_iterator>(m_train_kinds.begin(), position);

            m_train_kinds.insert(position, std::move(train_kind));

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                [inserted_index](train_type& train) { update_train_kind_index(train, inserted_index, 1); }
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                [inserted_index](train_type& train) { update_train_kind_index(train, inserted_index, 1); }
            );

            m_observer_set.changed();
        }

        /*!
            \brief Sets a train kind.

            \param position   A position where a train kind is inserted.
            \param train_kind A train kind.
        */
        void set_train_kind(
            const typename train_kinds_type::const_iterator position,
            train_kind_type                                 train_kind
        )
        {
            auto mutable_position = m_train_kinds.begin();
            std::advance(
                mutable_position,
                std::distance(static_cast<typename train_kinds_type::const_iterator>(m_train_kinds.begin()), position)
            );

            *mutable_position = std::move(train_kind);

            m_observer_set.changed();
        }

        /*!
            \brief Erases a train kind.

            train_kind to erase must not be referred by any trains.

            \param position The position of a train kind to erase.

            \throw std::invalid_argument When train_kind is referred by trains.
        */
        void erase_train_kind(const typename train_kinds_type::const_iterator position)
        {
            if (train_kind_referred(position))
                BOOST_THROW_EXCEPTION(std::invalid_argument("The train kind is still referred."));

            const size_type erased_index =
                std::distance<typename train_kinds_type::const_iterator>(m_train_kinds.begin(), position);

            m_train_kinds.erase(position);

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                [erased_index](train_type& train) { update_train_kind_index(train, erased_index, -1); }
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                [erased_index](train_type& train) { update_train_kind_index(train, erased_index, -1); }
            );

            m_observer_set.changed();
        }

        /*!
            \brief Assign train kinds.

            train_kind_index_map is a vector such that train_kind_index_map[old_index] returns the new index.
            The train kind index stored in the trains are updated.

            \param train_kinds          Train kinds.
            \param train_kind_index_map A train kind index map.

            \throw std::out_of_range When the size and/or the elements of train_kind_index_map is out of range.
        */
        void assign_train_kinds(train_kinds_type train_kinds, const std::vector<size_type>& train_kind_index_map)
        {
            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                replace_train_kind_index(train_kinds, train_kind_index_map)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                replace_train_kind_index(train_kinds, train_kind_index_map)
            );

            m_train_kinds = std::move(train_kinds);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the down trains.

            \return The down trains
        */
        const trains_type& down_trains()
        const
        {
            return m_down_trains;
        }

        /*!
            \brief Returns the up trains.

            \return The up trains
        */
        const trains_type& up_trains()
        const
        {
            return m_up_trains;
        }

        /*!
            \brief Inserts a down train.

            The count of train stops must coincide with the one of the station locations.

            \param position A position where a down train is inserted.
            \param train    A down train.

            \throw std::invalid_argument When the train is not downward.
            \throw std::invalid_argument When the kind index of a train is greater than the train kind count.
            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        void insert_down_train(const typename trains_type::const_iterator position, train_type train)
        {
            if (train.direction() != direction_type::down)
                BOOST_THROW_EXCEPTION(std::invalid_argument("The train is not downward."));

            insert_train_impl(m_down_trains, position, std::move(train));
        }

        /*!
            \brief Inserts a up train.

            The count of train stops must coincide with the one of the station locations.

            \param position A position where a up train is inserted.
            \param train    A up train.

            \throw std::invalid_argument When the train is not upward.
            \throw std::invalid_argument When the kind index of a train is greater than the train kind count.
            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        void insert_up_train(const typename trains_type::const_iterator position, train_type train)
        {
            if (train.direction() != direction_type::up)
                BOOST_THROW_EXCEPTION(std::invalid_argument("The train is not upward."));

            insert_train_impl(m_up_trains, position, std::move(train));
        }

        /*!
            \brief Erases the down trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_down_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            erase_trains_impl(m_down_trains, first, last);
        }

        /*!
            \brief Erases the up trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_up_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            erase_trains_impl(m_up_trains, first, last);
        }
        
        /*!
            \brief Returns the scheduled speed.

            \param train       A train.
            \param i_departure An iterator to a departure stop.
            \param i_arrival   An iterator to an arrival stop.

            \return The scheduled speed.

            \throw std::invalid_argument When the specified train does not belong to this timetable.
            \throw std::invalid_argument When i_departure or i_arrival equals to train.stops().end().
            \throw std::invalid_argument When the departure is not before the arrival.
            \throw std::invalid_argument When the departure or the arrival is passing.
        */
        speed_type scheduled_speed(
            const train_type&                                      train,
            const typename train_type::stops_type::const_iterator& i_departure,
            const typename train_type::stops_type::const_iterator& i_arrival
        )
        const
        {
            if (i_departure == train.stops().end())
                BOOST_THROW_EXCEPTION(std::invalid_argument("i_departure is invalid."));
            if (i_arrival == train.stops().end())
                BOOST_THROW_EXCEPTION(std::invalid_argument("i_departure is invalid."));
            if (
                std::find_if(
                    m_down_trains.begin(), m_down_trains.end(), [&train](const train_type& t) { return &t == &train; }
                ) == m_down_trains.end() &&
                std::find_if(
                    m_up_trains.begin(), m_up_trains.end(), [&train](const train_type& t) { return &t == &train; }
                ) == m_up_trains.end()
            )
            {
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown train."));
            }
            if (
                (train.direction() == direction_type::down && std::distance(i_departure, i_arrival) <= 0) ||
                (train.direction() == direction_type::up && std::distance(i_departure, i_arrival) >= 0)
            )
            {
                BOOST_THROW_EXCEPTION(std::invalid_argument("The departure is not before the arrival."));
            }

            const auto distance = distance_between(m_station_locations, train, i_departure, i_arrival);
            assert(distance > operating_distance_type{ 0 });

            const auto time_span = time_span_between(i_departure, i_arrival);

            return (distance * 60U * 60U) / static_cast<operating_distance_type>(time_span.seconds());
        }

        /*!
            \brief Returns the font and color set.

            \return The font and color set.
        */
        const font_color_set_type& font_color_set()
        const
        {
            return m_font_color_set;
        }

        /*!
            \brief Sets a font and color set.

            \param font_color_set A font color set.
        */
        void set_font_color_set(font_color_set_type font_color_set)
        {
            m_font_color_set = std::move(font_color_set);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set()
        const
        {
            return m_observer_set;
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set()
        {
            return m_observer_set;
        }


    private:
        // types

        using direction_type = typename train_type::direction_type;

        using stop_type = typename train_type::stop_type;

        using time_type = typename stop_type::time_type;

        using time_span_type = typename time_type::time_span_type;

        struct replace_train_kind_index
        {
            const train_kinds_type& m_train_kinds;

            const std::vector<size_type>& m_train_kind_index_map;

            replace_train_kind_index(
                const train_kinds_type&       train_kinds,
                const std::vector<size_type>& train_kind_index_map
            )
            :
            m_train_kinds(train_kinds),
            m_train_kind_index_map(train_kind_index_map)
            {}

            void operator()(train_type& train)
            const
            {
                if (train.kind_index() >= m_train_kind_index_map.size())
                    BOOST_THROW_EXCEPTION(std::out_of_range("Invalid old index in the train kind index map."));
                const auto new_index = m_train_kind_index_map[train.kind_index()];
                if (new_index >= m_train_kinds.size())
                    BOOST_THROW_EXCEPTION(std::out_of_range("Invalid new index in the train_kind index map."));

                train.set_kind_index(new_index);
            }

        };


        // static functions

        static void insert_train_stop(train_type& train, const difference_type offset)
        {
            train.insert_stop(
                train.stops().begin() + offset,
                stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type{})
            );
        }

        static void erase_train_stops(
            train_type&           train,
            const difference_type first_offset,
            const difference_type last_offset
        )
        {
            train.erase_stops(train.stops().begin() + first_offset, train.stops().begin() + last_offset);
        }

        static void update_train_kind_index(train_type& train, const size_type index, const std::ptrdiff_t index_delta)
        {
            if (train.kind_index() < index)
                return;

            train_type new_train{
                train.direction(),
                train.number(),
                train.kind_index() + index_delta,
                train.name(),
                train.name_number(),
                train.note()
            };
            for (const auto& stop: train.stops())
                new_train.insert_stop(new_train.stops().end(), stop);

            train = new_train;
        }

        static operating_distance_type distance_between(
            const station_locations_type&                          station_locations,
            const train_type&                                      train,
            const typename train_type::stops_type::const_iterator& i_departure,
            const typename train_type::stops_type::const_iterator& i_arrival
        )
        {
            const auto departure_index = std::distance(train.stops().begin(), i_departure);
            assert(static_cast<size_type>(departure_index) < station_locations.size());
            const auto& departure_distance = station_locations[departure_index].operating_distance();

            const auto arrival_index = std::distance(train.stops().begin(), i_arrival);
            assert(static_cast<size_type>(arrival_index) < station_locations.size());
            const auto& arrival_distance = station_locations[arrival_index].operating_distance();

            return
                train.direction() == direction_type::down ?
                arrival_distance - departure_distance : departure_distance - arrival_distance;
        }

        static time_span_type time_span_between(
            const typename train_type::stops_type::const_iterator& i_departure,
            const typename train_type::stops_type::const_iterator& i_arrival
        )
        {
            if (i_departure->passing())
                BOOST_THROW_EXCEPTION(std::invalid_argument("The departure is passing."));
            if (i_arrival->passing())
                BOOST_THROW_EXCEPTION(std::invalid_argument("The departure is passing."));

            const auto departure_time =
                i_departure->departure().initialized() ? i_departure->departure() : i_departure->arrival();
            const auto arrival_time =
                i_arrival->arrival().initialized() ? i_arrival->arrival() : i_arrival->departure();
            assert(departure_time.initialized() && arrival_time.initialized());

            return arrival_time - departure_time;
        }


        // variables

        string_type m_company_name;

        string_type m_line_name;

        string_type m_note;

        station_locations_type m_station_locations;

        train_kinds_type m_train_kinds;

        trains_type m_down_trains;

        trains_type m_up_trains;

        font_color_set_type m_font_color_set;

        observer_set_type m_observer_set;


        // functions

        bool can_insert_to(
            const typename station_locations_type::const_iterator position,
            const station_location_type&                          station_location
        )
        const
        {
            if (position != m_station_locations.begin() && !std::prev(position)->before(station_location))
                return false;

            if (position != m_station_locations.end() && !station_location.before(*position))
                return false;

            return true;
        }

        void insert_train_impl(
            trains_type&                               trains,
            const typename trains_type::const_iterator position,
            train_type                                 train
        )
        {
            if (train.kind_index() >= m_train_kinds.size())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("The kind index of the train is greater than the train kind count.")
                );
            }
            if (train.stops().size() != m_station_locations.size())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The count of the train stops does not coincide with the one of the station locations."
                    )
                );
            }

            trains.insert(position, std::move(train));

            m_observer_set.changed()();
        }

        void erase_trains_impl(
            trains_type&                               trains,
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            trains.erase(first, last);

            m_observer_set.changed()();
        }


    };


}}


#endif
