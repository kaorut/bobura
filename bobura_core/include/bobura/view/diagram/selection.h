/*! \file
    \brief The definition of bobura::view::diagram::selection.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_SELECTION_H)
#define BOBURA_VIEW_DIAGRAM_SELECTION_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <bobura/message/diagram_selection_observer_set.h>
#include <bobura/model/timetable_info/station_location.h>
#include <bobura/model/train.h>

namespace boost
{
    template <class T> class optional;
}


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view selection.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class selection : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

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
        selection();

        /*!
            \brief Moves a selection.

            \param another Another selection.
        */
        selection(selection&& another);

        /*!
            \brief Destroys the selection.
        */
        ~selection()
        noexcept;


        // functions

        /*!
            \brief Checks whether the station location is selected.

            \param station_location A station location.

            \retval true  When the station location is selected.
            \retval false Otherwise.
        */
        bool selected(const station_location_type& station_location)
        const;

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
        const;

        /*!
            \brief Selects a station location.

            \param station_location A station location.
        */
        void select(const station_location_type& station_location);

        /*!
            \brief Selects a train.

            \param train                A train.
            \param departure_stop_index A departure stop index. Or specify boost::none when a whole train is selected.
        */
        void select(
            const train_type&                 train,
            const boost::optional<size_type>& departure_stop_index
        );

        /*!
            \brief Unselects all the items.
        */
        void unselect_all();

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        const selection_observer_set_type& selection_observer_set()
        const;

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        selection_observer_set_type& selection_observer_set();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
