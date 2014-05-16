/*! \file
    \brief The definition of bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H)
#define TETENGO2_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/signals2.hpp>


namespace bobura { namespace message
{
    /*!
        \brief The class template for a diagram selection observer set.

        \tparam StationLocation A station location type.
        \tparam Train           A train type.
    */
    template <typename StationLocation, typename Train>
    class diagram_selection_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The station location type.
        using station_location_type = StationLocation;

        //! The train type.
        using train_type = Train;

        //! The stop index type.
        using stop_index_type = typename train_type::stops_type::size_type;

        /*!
            \brief The observer type of station selection.

            \param station_location A station location.
        */
        using station_selected_type = void (const station_location_type& station_location);

        //! The signal type of station selection.
        using station_selected_signal_type = boost::signals2::signal<station_selected_type>;

        /*!
            \brief The observer type of train selection.

            \param train                A train.
            \param departure_stop_index A departure stop index. Or boost::none when a whole train is selected.
        */
        using train_selected_type =
            void (
                const train_type&                       train,
                const boost::optional<stop_index_type>& departure_stop_index
            );

        //! The signal type of train selection.
        using train_selected_signal_type = boost::signals2::signal<train_selected_type>;

        /*!
            \brief The observer type of unselection.
        */
        using all_unselected_type = void ();

        //! The signal type of unselection.
        using all_unselected_signal_type = boost::signals2::signal<all_unselected_type>;


        // functions

        /*!
            \brief Returns the observer called when a station is selected.

            \return The observer called when a station is selected.
        */
        const station_selected_signal_type& station_selected()
        const
        {
            return m_station_selected;
        }

        /*!
            \brief Returns the observer called when station is selected.

            \return The observer called when a station is selected.
        */
        station_selected_signal_type& station_selected()
        {
            return m_station_selected;
        }

        /*!
            \brief Returns the observer called when a train is selected.

            \return The observer called when a train is selected.
        */
        const train_selected_signal_type& train_selected()
        const
        {
            return m_train_selected;
        }

        /*!
            \brief Returns the observer called when a train is selected.

            \return The observer called when a train is selected.
        */
        train_selected_signal_type& train_selected()
        {
            return m_train_selected;
        }

        /*!
            \brief Returns the observer called when all the items are unselected.

            \return The observer called when all the items are unselected.
        */
        const all_unselected_signal_type& all_unselected()
        const
        {
            return m_all_unselected;
        }

        /*!
            \brief Returns the observer called when all the items are unselected.

            \return The observer called when all the items are unselected.
        */
        all_unselected_signal_type& all_unselected()
        {
            return m_all_unselected;
        }


    private:
        // variables

        station_selected_signal_type m_station_selected;

        train_selected_signal_type m_train_selected;

        all_unselected_signal_type m_all_unselected;


    };


}}


#endif
