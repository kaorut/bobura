/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOP_H)
#define BOBURA_MODEL_TRAININFO_STOP_H

#include <memory>

#include <boost/operators.hpp>

#include <bobura/model/train_info/time.h>
#include <bobura/type_list.h>


namespace bobura::model::train_info {
    /*!
        \brief The class for a train stop.
    */
    class stop : private boost::equality_comparable<stop>
    {
    public:
        // types

        //! The time type.
        using time_type = time;

        //! The string type.
        using string_type = type_list::common::string_type;


        // constructors and destructor

        /*!
            \brief Creates a stop.

            \param arrival     An arrival time.
            \param departure   A departure time.
            \param operational Set true for an operational stop.
            \param platform    A platform.
        */
        stop(time_type arrival, time_type departure, const bool operational, string_type platform);

        /*!
            \brief Copies a stop.

            \param another Another stop.
        */
        stop(const stop& another);

        /*!
            \brief Moves a stop.

            \param another Another stop.
        */
        stop(stop&& another);

        /*!
            \brief Destorys the stop.
        */
        ~stop();


        // functions

        /*!
            \brief Checks whether one stop is equal to another.

            \param one     One stop.
            \param another Another stop.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const stop& one, const stop& another);

        /*!
            \brief Assigns a stop.

            \param another Another stop.

            \return This object.
        */
        stop& operator=(const stop& another);

        /*!
            \brief Assigns a stop.

            \param another Another stop.

            \return This object.
        */
        stop& operator=(stop&& another);

        /*!
            \brief Returns the arrival time.

            \return The arrival time.
        */
        const time_type& arrival() const;

        /*!
            \brief Returns the departure time.

            \return The departure time.
        */
        const time_type& departure() const;

        /*!
            \brief Checks whether the stop is passing.

            \retval true  When the stop is passing.
            \retval false Otherwise.
        */
        bool passing() const;

        /*!
            \brief Checks whether the stop is operational.

            \retval true  When the stop is operational.
            \retval false Otherwise.
        */
        bool operational() const;

        /*!
            \brief Returns the platform.

            \return The platform.
        */
        const string_type& platform() const;


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
