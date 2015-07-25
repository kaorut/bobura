/*! \file
    \brief The definition of bobura::model::message::timetable_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_MODEL_MESSAGE_TIMETABLEOBSERVERSET_H)
#define TETENGO2_MODEL_MESSAGE_TIMETABLEOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>

#include <tetengo2.h>


namespace bobura { namespace model { namespace message
{
    /*!
        \brief The class for a timetable observer set.
    */
    class timetable_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of changed.
        */
        using changed_type = void ();

        //! The signal type of changed.
        using changed_signal_type = boost::signals2::signal<changed_type>;


        // constructors and destructor

        /*!
            \brief Creates a timetable observer set.
        */
        timetable_observer_set();

        /*!
           \brief Destroys the timetable observer set.
        */
        ~timetable_observer_set()
        noexcept;


        // functions

        /*!
            \brief Returns the observer called when a timetable is changed.

            \return The observer called when a timetable is changed.
        */
        const changed_signal_type& changed()
        const;

        /*!
            \brief Returns the observer called when a timetable is changed.

            \return The observer called when a timetable is changed.
        */
        changed_signal_type& changed();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
