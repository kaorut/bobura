/*! \file
    \brief The definition of bobura::view::diagram::selection.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_SELECTION_H)
#define BOBURA_VIEW_DIAGRAM_SELECTION_H

#include <cassert>
#include <limits>
#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include <tetengo2.h>

#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view selection.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
    */
    template <typename Size, typename Difference, typename String, typename OperatingDistance>
    class selection : private boost::noncopyable
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
        using station_location_type = model::timetable_info::station_location<string_type, operating_distance_type>;

        //! The train type.
        using train_type = model::train<size_type, difference_type, string_type>;

        //! The selection observer set type.
        using selection_observer_set_type =
            message::diagram_selection_observer_set<size_type, difference_type, string_type, operating_distance_type>;


        // constructors and destructor

        /*!
            \brief Creates a selection.
        */
        selection()
        :
        m_p_selected_station_location(nullptr),
        m_p_selected_train(nullptr),
        m_p_selection_observer_set(tetengo2::stdalt::make_unique<selection_observer_set_type>())
        {}

        /*!
            \brief Moves a selection.

            \param another Another selection.
        */
        selection(selection&& another)
        :
        m_p_selected_station_location(another.m_p_selected_station_location),
        m_p_selected_train(another.m_p_selected_train),
        m_p_selection_observer_set(std::move(another.m_p_selection_observer_set))
        {}


        // functions

        /*!
            \brief Checks whether the station location is selected.

            \param station_location A station location.

            \retval true  When the station location is selected.
            \retval false Otherwise.
        */
        bool selected(const station_location_type& station_location)
        const
        {
            if (!m_p_selected_station_location)
                return false;

            return &station_location == m_p_selected_station_location;
        }

        /*!
            \brief Checks whether the train is selected.

            \param train                A train.
            \param departure_stop_index A departure stop index.
                                        Specity std::numeric_limits<size_type>::max() to test whether any fragment is
                                        selected. Or specify boost::none to test whether a whole train is selected.

            \retval true  When the train is selected.
            \retval false Otherwise.
        */
        bool selected(const train_type& train, const boost::optional<size_type>& departure_stop_index)
        const
        {
            if (!m_p_selected_train)
                return false;
            if (!departure_stop_index != !m_departure_stop_index)
                return false;
            if (!departure_stop_index)
            {
                assert(!m_departure_stop_index);
                return &train == m_p_selected_train;
            }
            return
                &train == m_p_selected_train &&
                (
                    *departure_stop_index == std::numeric_limits<size_type>::max() ||
                    *departure_stop_index == *m_departure_stop_index
                );
        }

        /*!
            \brief Selects a station location.

            \param station_location A station location.
        */
        void select(const station_location_type& station_location)
        {
            unselect_all();

            m_p_selected_station_location = &station_location;

            m_p_selection_observer_set->station_selected()(station_location);
        }

        /*!
            \brief Selects a train.

            \param train                A train.
            \param departure_stop_index A departure stop index. Or specify boost::none when a whole train is selected.
        */
        void select(
            const train_type&                 train,
            const boost::optional<size_type>& departure_stop_index
        )
        {
            unselect_all();

            m_p_selected_train = &train;
            m_departure_stop_index = departure_stop_index;

            m_p_selection_observer_set->train_selected()(train, departure_stop_index);
        }

        /*!
            \brief Unselects all the items.
        */
        void unselect_all()
        {
            m_p_selected_station_location = nullptr;
            m_p_selected_train = nullptr;
            m_departure_stop_index = boost::none;

            m_p_selection_observer_set->all_unselected()();
        }

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        const selection_observer_set_type& selection_observer_set()
        const
        {
            return *m_p_selection_observer_set;
        }

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        selection_observer_set_type& selection_observer_set()
        {
            return *m_p_selection_observer_set;
        }


    private:
        // variables

        const station_location_type* m_p_selected_station_location;

        const train_type* m_p_selected_train;

        boost::optional<size_type> m_departure_stop_index;

        std::unique_ptr<selection_observer_set_type> m_p_selection_observer_set;


    };


}}}


#endif
