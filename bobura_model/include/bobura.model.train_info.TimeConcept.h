/*! \file
    \brief The definition of bobura::model::timetable_info::TimeConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMECONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMECONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a time.

        \tparam Time A time type.
    */
    template <typename Time>
    class TimeConcept
    {
    public:
        // constructors and destructor

        TimeConcept();


        // functions

        /*!
            \brief Checks the constraints on a time.
        */
        void constraints()
        {
            typedef typename Time::size_type size_type;
            typedef typename Time::time_span_type time_span_type;

            m_time.swap(m_time);
            std::swap(m_time, m_time);

            Time& assigned = m_time = m_time;
            boost::ignore_unused_variable_warning(assigned);

            const_constraints(m_time);
        }

        /*!
            \brief Checks the const constraints on a time.

            \param time A constant object.
        */
        void const_constraints(const Time& time)
        {
            const bool equality = time_span == time_span;
            boost::ignore_unused_variable_warning(equality);

            //const typename Time::station_type& station =
            //    time.station();
            //boost::ignore_unused_variable_warning(station);
        }


    private:
        // variables

        Time m_time;


    };


}}}

#endif
