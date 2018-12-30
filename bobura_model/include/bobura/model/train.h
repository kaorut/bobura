/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

#include <vector>

#include <boost/operators.hpp>

#include <bobura/model/train_info/stop.h>
#include <bobura/type_list.h>


namespace bobura::model {
    /*!
        \brief The class for a train.
    */
    class train : private boost::equality_comparable<train>
    {
    public:
        // types

        //! The size type.
        using size_type = type_list::common::size_type;

        //! The difference type.
        using difference_type = type_list::common::difference_type;

        //! The string type.
        using string_type = type_list::common::string_type;

        //! The stop type.
        using stop_type = train_info::stop;

        //! The stops type.
        using stops_type = std::vector<stop_type>;

        //! The direction type.
        enum class direction_type
        {
            down, //!< Down.
            up, //!< Up.
        };


        // constructors and destructor

        /*!
            \brief Creates a train.

            \param direction   A direction.
            \param number      A number.
            \param kind_index  A kind index.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
        */
        train(
            direction_type direction,
            string_type    number,
            size_type      kind_index,
            string_type    name,
            string_type    name_number,
            string_type    note);

        /*!
            \brief Creates a train.

            kind_index must be less than the train kind count in the timetable.

            \param direction   A direction.
            \param number      A number.
            \param kind_index  A kind index.
            \param name        A name.
            \param name_number A name number.
            \param note        A note.
            \param stops       Stops.
        */
        train(
            direction_type direction,
            string_type    number,
            size_type      kind_index,
            string_type    name,
            string_type    name_number,
            string_type    note,
            stops_type     stops);


        // functions

        /*!
            \brief Checks whether one train is equal to another.

            \param one     One train.
            \param another Another train.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train& one, const train& another);

        /*!
            \brief Returns the direction.

            \return The direction.
        */
        direction_type direction() const;

        /*!
            \brief Returns the number.

            \return The number.
        */
        const string_type& number() const;

        /*!
            \brief Returns the kind index.

            \return The kind index.
        */
        size_type kind_index() const;

        /*!
            \brief Sets a kind index.

            \param kind_index A kind index.
        */
        void set_kind_index(size_type kind_index);

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name() const;

        /*!
            \brief Returns the name number.

            \return The name number.
        */
        const string_type& name_number() const;

        /*!
            \brief Returns the note.

            \return The note.
        */
        const string_type& note() const;

        /*!
            \brief Returns the stops.

            \return The stops.
        */
        const stops_type& stops() const;

        /*!
            \brief Inserts a stop.

            \param position A position where a stop is inserted.
            \param stop     A stop.
        */
        void insert_stop(typename stops_type::const_iterator position, stop_type stop);

        /*!
            \brief Erases the stops.

            \param first A first iterator among the erased stops.
            \param last  A last iterator among the erased stops.
        */
        void erase_stops(typename stops_type::const_iterator first, typename stops_type::const_iterator last);

        /*!
            \brief Returns the stop previous to the specified stop.

            It returns stops().end() when the specified stop is the origin or earlier.

            \param i_stop An iterator to a stop.

            \return The iterator to the stop previous to the specified stop.
        */
        typename stops_type::const_iterator previous_stop(typename stops_type::const_iterator i_stop) const;

        /*!
            \brief Returns the stop next to the specified stop.

            It returns stops().end() when the specified stop is the destination or later.

            \param i_stop An iterator to a stop.

            \return The iterator to the stop next to the specified stop.
        */
        typename stops_type::const_iterator next_stop(typename stops_type::const_iterator i_stop) const;

        /*!
            \brief Returns the origin stop.

            When this train has no stop with arrival or departure, it returns stops().end().

            \return The iterator to the origin stop.
        */
        typename stops_type::const_iterator origin_stop() const;

        /*!
            \brief Returns the destination stop.

            When this train has no stop with arrival or departure, it returns stops().end().

            \return The iterator to the destination stop.
        */
        typename stops_type::const_iterator destination_stop() const;


    private:
        // variables

        direction_type m_direction;

        string_type m_number;

        size_type m_kind_index;

        string_type m_name;

        string_type m_name_number;

        string_type m_note;

        stops_type m_stops;
    };
}


#endif
