/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <vector>

#include <boost/operators.hpp>

#include <tetengo2/gui/drawing/font.h>

#include <bobura/model/message/timetable_observer_set.h>
#include <bobura/model/timetable_info/font_color_set.h>
#include <bobura/model/timetable_info/station_interval_calculator.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>
#include <bobura/model/train_kind.h>
#include <bobura/type_list.h>


namespace bobura::model {
    /*!
        \brief The class for a timetable.
    */
    class timetable : private boost::equality_comparable<timetable>
    {
    public:
        // types

        //! The size type.
        using size_type = type_list::common::size_type;

        //! The difference type.
        using difference_type = type_list::common::difference_type;

        //! The string type.
        using string_type = type_list::common::string_type;

        //! The operating distance type.
        using operating_distance_type = type_list::common::operating_distance_type;

        //! The speed type.
        using speed_type = type_list::common::speed_type;

        //! The font type.
        using font_type = tetengo2::gui::drawing::font;

        //! The station location type.
        using station_location_type = timetable_info::station_location;

        //! The station locations type.
        using station_locations_type = std::vector<station_location_type>;

        //! The station interval calculator type.
        using station_interval_calculator_type = timetable_info::station_interval_calculator;

        //! The station intervals type.
        using station_intervals_type = typename station_interval_calculator_type::station_intervals_type;

        //! The train kind type.
        using train_kind_type = train_kind<string_type, font_type>;

        //! The train kinds type.
        using train_kinds_type = std::vector<train_kind_type>;

        //! The train type.
        using train_type = train;

        //! The trains type.
        using trains_type = std::vector<train_type>;

        //! The font color set type.
        using font_color_set_type = timetable_info::font_color_set;

        //! The observer set type.
        using observer_set_type = message::timetable_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable();


        // functions

        /*!
            \brief Checks whether this is equal to another timetable.

            \param one     One timetable.
            \param another Another timetable.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const timetable& one, const timetable& another);

        /*!
            \brief Returns the company name.

            \return The company name.
        */
        const string_type& company_name() const;

        /*!
            \brief Sets a company name.

            \param company_name A company name.
        */
        void set_company_name(string_type company_name);

        /*!
            \brief Returns the line name.

            \return The line name.
        */
        const string_type& line_name() const;

        /*!
            \brief Sets a line name.

            \param line_name A line name.
        */
        void set_line_name(string_type line_name);

        /*!
            \brief Returns the note.

            \return The note.
        */
        const string_type& note() const;

        /*!
            \brief Sets a note.

            \param note A note.
        */
        void set_note(string_type note);

        /*!
            \brief Returns the station locations.

            \return The station locations.
        */
        const station_locations_type& station_locations() const;

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
            typename station_locations_type::const_iterator position,
            station_location_type                           station_location);

        /*!
            \brief Erases the station locations.

            It also erases stops from the every train, so that the count of the station locations coincides with the
            one of the every train stop.

            \param first A first iterator among the erased station locations.
            \param last  A last iterator among the erased station locations.
        */
        void erase_station_locations(
            typename station_locations_type::const_iterator first,
            typename station_locations_type::const_iterator last);

        /*!
            \brief Returns the station intervals.

            \return The station intervals.
        */
        station_intervals_type station_intervals() const;

        /*!
            \brief Returns the train kinds.

            \return The train kinds.
        */
        const train_kinds_type& train_kinds() const;

        /*!
            \brief Checks whether the train kind is referred by trains.

            \param position A train kind position.

            \retval true  The train kind is referred.
            \retval false Otherwise.
        */
        bool train_kind_referred(typename train_kinds_type::const_iterator position) const;

        /*!
            \brief Checks whether the train kind is referred by trains.

            \param train_kind_index A train kind index.

            \retval true  The train kind is referred.
            \retval false Otherwise.
        */
        bool train_kind_referred(const size_type& train_kind_index) const;

        /*!
            \brief Inserts a train kind.

            \param position   A position where a train kind is inserted.
            \param train_kind A train kind.
        */
        void insert_train_kind(typename train_kinds_type::const_iterator position, train_kind_type train_kind);

        /*!
            \brief Sets a train kind.

            \param position   A position where a train kind is inserted.
            \param train_kind A train kind.
        */
        void set_train_kind(typename train_kinds_type::const_iterator position, train_kind_type train_kind);

        /*!
            \brief Erases a train kind.

            train_kind to erase must not be referred by any trains.

            \param position The position of a train kind to erase.

            \throw std::invalid_argument When train_kind is referred by trains.
        */
        void erase_train_kind(typename train_kinds_type::const_iterator position);

        /*!
            \brief Assign train kinds.

            train_kind_index_map is a vector such that train_kind_index_map[old_index] returns the new index.
            The train kind index stored in the trains are updated.

            \param train_kinds          Train kinds.
            \param train_kind_index_map A train kind index map.

            \throw std::out_of_range When the size and/or the elements of train_kind_index_map is out of range.
        */
        void assign_train_kinds(train_kinds_type train_kinds, const std::vector<size_type>& train_kind_index_map);

        /*!
            \brief Returns the down trains.

            \return The down trains
        */
        const trains_type& down_trains() const;

        /*!
            \brief Returns the up trains.

            \return The up trains
        */
        const trains_type& up_trains() const;

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
        void insert_down_train(typename trains_type::const_iterator position, train_type train);

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
        void insert_up_train(typename trains_type::const_iterator position, train_type train);

        /*!
            \brief Erases the down trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_down_trains(typename trains_type::const_iterator first, typename trains_type::const_iterator last);

        /*!
            \brief Erases the up trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_up_trains(typename trains_type::const_iterator first, typename trains_type::const_iterator last);

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
            const typename train_type::stops_type::const_iterator& i_arrival) const;

        /*!
            \brief Returns the font and color set.

            \return The font and color set.
        */
        const font_color_set_type& font_color_set() const;

        /*!
            \brief Sets a font and color set.

            \param font_color_set A font color set.
        */
        void set_font_color_set(font_color_set_type font_color_set);

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set() const;

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set();


    private:
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
    };
}


#endif
