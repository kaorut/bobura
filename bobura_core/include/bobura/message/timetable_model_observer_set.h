/*! \file
    \brief The definition of bobura::message::timetable_model_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_TIMETABLEMODELOBSERVERSET_H)
#define TETENGO2_MESSAGE_TIMETABLEMODELOBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace bobura { namespace message
{
    /*!
        \brief The class for a timetable model observer set.
    */
    class timetable_model_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of reset.
        */
        using reset_type = void ();

        //! The signal type of reset.
        using reset_signal_type = boost::signals2::signal<reset_type>;

        /*!
            \brief The observer type of changed.
        */
        using changed_type = void ();

        //! The signal type of changed.
        using changed_signal_type = boost::signals2::signal<changed_type>;


        // functions

        /*!
            \brief Returns the observer called when a timetable model is reset.

            \return The observer called when a timetable model is reset.
        */
        const reset_signal_type& reset()
        const
        {
            return m_reset;
        }

        /*!
            \brief Returns the observer called when a timetable model is reset.

            \return The observer called when a timetable model is reset.
        */
        reset_signal_type& reset()
        {
            return m_reset;
        }

        /*!
            \brief Returns the observer called when a timetable model is
                   changed.

            \return The observer called when a timetable model is changed.
        */
        const changed_signal_type& changed()
        const
        {
            return m_changed;
        }

        /*!
            \brief Returns the observer called when a timetable model is changed.

            \return The observer called when a timetable model is changed.
        */
        changed_signal_type& changed()
        {
            return m_changed;
        }


    private:
        // variables

        reset_signal_type m_reset;

        changed_signal_type m_changed;


    };


}}


#endif
