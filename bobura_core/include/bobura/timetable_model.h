/*! \file
    \brief The definition of bobura::timetable_model.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_TIMETABLEMODEL_H)
#define BOBURA_TIMETABLEMODEL_H

#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>

#include <bobura/message/timetable_model_observer_set.h>
#include <bobura/model/timetable.h>


namespace bobura
{
   /*!
        \brief The class template for a model.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    class timetable_model : private boost::noncopyable
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

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The timetable type.
        using timetable_type =
            model::timetable<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The observer set type.
        using observer_set_type = message::timetable_model_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a model.
        */
        timetable_model();

        /*!
            \brief Destroys the model.
        */
        ~timetable_model()
        noexcept;


        // functions

        /*!
            \brief Returns the timetable.

            \return The timetable.
        */
        const timetable_type& timetable()
        const;

        /*!
            \brief Returns the timetable.

            \return The timetable.
        */
        timetable_type& timetable();

        /*!
            \brief Resets an empty timetable.
        */
        void reset_timetable();

        /*!
            \brief Resets a timetable.

            \param p_timetable A unique pointer to a timetable.

            \throw std::invalid_argument When p_timetable is nullptr.
        */
        void reset_timetable(std::unique_ptr<timetable_type> p_timetable);

        /*!
            \brief Resets a timetable.

            \param p_timetable A unique pointer to a timetable.
            \param path        A path.

            \throw std::invalid_argument When p_timetable is nullptr.
        */
        void reset_timetable(std::unique_ptr<timetable_type> p_timetable, boost::filesystem::path path);

        /*!
            \brief Checks whether the model has a path.

            \retval true  When the model has a path.
            \retval false Otherwise.
        */
        bool has_path()
        const;

        /*!
            \brief Returns the path.

            \return The path.

            \throw std::logic_error When the model does not have a path.
        */
        const boost::filesystem::path& path()
        const;

        /*!
            \brief Sets a path.

            \param path A path.
        */
        void set_path(boost::filesystem::path path);

        /*!
            \brief Checks whether the model is changed.

            \retval true  When the model is changed.
            \retval false Otherwise.
        */
        bool changed()
        const;

        /*!
            \brief Sets a changed status.

            \param changed A changed status.
        */
        void set_changed(bool changed);

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set()
        const;

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}

#endif
