/*! \file
    \brief The definition of bobura::message::timetable_model_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TIMETABLEMODELOBSERVERSET_H)
#define BOBURA_MESSAGE_TIMETABLEMODELOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace bobura::message {
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
        using reset_type = void();

        //! The signal type of reset.
        using reset_signal_type = boost::signals2::signal<reset_type>;

        /*!
            \brief The observer type of changed.
        */
        using changed_type = void();

        //! The signal type of changed.
        using changed_signal_type = boost::signals2::signal<changed_type>;


        // constructors and destructor

        /*!
            \brief Creates a timetable model observer set.
        */
        timetable_model_observer_set();

        /*!
            \brief Destroys the timetable model observer set.
        */
        ~timetable_model_observer_set() noexcept;


        // functions

        /*!
            \brief Returns the observer called when a timetable model is reset.

            \return The observer called when a timetable model is reset.
        */
        const reset_signal_type& reset() const;

        /*!
            \brief Returns the observer called when a timetable model is reset.

            \return The observer called when a timetable model is reset.
        */
        reset_signal_type& reset();

        /*!
            \brief Returns the observer called when a timetable model is
                   changed.

            \return The observer called when a timetable model is changed.
        */
        const changed_signal_type& changed() const;

        /*!
            \brief Returns the observer called when a timetable model is changed.

            \return The observer called when a timetable model is changed.
        */
        changed_signal_type& changed();


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
