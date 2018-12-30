/*! \file
    \brief The definition of bobura::message::timetable_model_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <bobura/message/timetable_model_observer_set.h>


namespace bobura::message {
    class timetable_model_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using reset_type = timetable_model_observer_set::reset_type;

        using reset_signal_type = timetable_model_observer_set::reset_signal_type;

        using changed_type = timetable_model_observer_set::changed_type;

        using changed_signal_type = timetable_model_observer_set::changed_signal_type;


        // functions

        const reset_signal_type& reset() const
        {
            return m_reset;
        }

        reset_signal_type& reset()
        {
            return m_reset;
        }

        const changed_signal_type& changed() const
        {
            return m_changed;
        }

        changed_signal_type& changed()
        {
            return m_changed;
        }


    private:
        // variables

        reset_signal_type m_reset;

        changed_signal_type m_changed;
    };


    timetable_model_observer_set::timetable_model_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    timetable_model_observer_set::~timetable_model_observer_set() noexcept {}

    const timetable_model_observer_set::reset_signal_type& timetable_model_observer_set::reset() const
    {
        return m_p_impl->reset();
    }

    timetable_model_observer_set::reset_signal_type& timetable_model_observer_set::reset()
    {
        return m_p_impl->reset();
    }

    const timetable_model_observer_set::changed_signal_type& timetable_model_observer_set::changed() const
    {
        return m_p_impl->changed();
    }

    timetable_model_observer_set::changed_signal_type& timetable_model_observer_set::changed()
    {
        return m_p_impl->changed();
    }
}
