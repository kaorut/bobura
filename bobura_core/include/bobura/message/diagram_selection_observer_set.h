/*! \file
    \brief The definition of bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H)
#define BOBURA_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>

#include <tetengo2/stdalt.h>

#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>


namespace bobura::message {
    /*!
        \brief The class template for a diagram selection observer set.

        \tparam Size       A size type.
        \tparam Difference A difference type.
        \tparam String     A string type.
    */
    template <typename Size, typename Difference, typename String>
    class diagram_selection_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The station location type.
        using station_location_type = model::timetable_info::station_location;

        //! The train type.
        using train_type = model::train;

        /*!
            \brief The observer type of station selection.

            \param station_location A station location.
        */
        using station_selected_type = void(const station_location_type& station_location);

        //! The signal type of station selection.
        using station_selected_signal_type = boost::signals2::signal<station_selected_type>;

        /*!
            \brief The observer type of train selection.

            \param train                A train.
            \param departure_stop_index A departure stop index. Or TETENGO2_STDALT_NULLOPT when a whole train is
           selected.
        */
        using train_selected_type =
            void(const train_type& train, const tetengo2::stdalt::optional<size_type>& departure_stop_index);

        //! The signal type of train selection.
        using train_selected_signal_type = boost::signals2::signal<train_selected_type>;

        /*!
            \brief The observer type of unselection.
        */
        using all_unselected_type = void();

        //! The signal type of unselection.
        using all_unselected_signal_type = boost::signals2::signal<all_unselected_type>;


        // constructors and destructor

        /*!
            \brief Creates a diagram selection observer set.
        */
        diagram_selection_observer_set();

        /*!
            \brief Destroys the diagram selection observer set.
        */
        ~diagram_selection_observer_set() noexcept;


        // functions

        /*!
            \brief Returns the observer called when a station is selected.

            \return The observer called when a station is selected.
        */
        const station_selected_signal_type& station_selected() const;

        /*!
            \brief Returns the observer called when station is selected.

            \return The observer called when a station is selected.
        */
        station_selected_signal_type& station_selected();

        /*!
            \brief Returns the observer called when a train is selected.

            \return The observer called when a train is selected.
        */
        const train_selected_signal_type& train_selected() const;

        /*!
            \brief Returns the observer called when a train is selected.

            \return The observer called when a train is selected.
        */
        train_selected_signal_type& train_selected();

        /*!
            \brief Returns the observer called when all the items are unselected.

            \return The observer called when all the items are unselected.
        */
        const all_unselected_signal_type& all_unselected() const;

        /*!
            \brief Returns the observer called when all the items are unselected.

            \return The observer called when all the items are unselected.
        */
        all_unselected_signal_type& all_unselected();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
