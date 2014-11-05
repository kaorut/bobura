/*! \file
    \brief The definition of bobura::timetable_model.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_TIMETABLEMODEL_H)
#define BOBURA_TIMETABLEMODEL_H

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

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
        timetable_model()
        :
        m_p_timetable(tetengo2::stdalt::make_unique<timetable_type>()),
        m_path(),
        m_changed(false),
        m_observer_set()
        {
            set_timetable_observer_set();
        }


        // functions

        /*!
            \brief Returns the timetable.

            \return The timetable.
        */
        const timetable_type& timetable()
        const
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        /*!
            \brief Returns the timetable.

            \return The timetable.
        */
        timetable_type& timetable()
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        /*!
            \brief Resets an empty timetable.
        */
        void reset_timetable()
        {
            reset_timetable_impl(tetengo2::stdalt::make_unique<timetable_type>(), boost::none);
        }

        /*!
            \brief Resets a timetable.

            \param p_timetable A unique pointer to a timetable.

            \throw std::invalid_argument When p_timetable is nullptr.
        */
        void reset_timetable(std::unique_ptr<timetable_type> p_timetable)
        {
            reset_timetable_impl(std::move(p_timetable), boost::none);
        }

        /*!
            \brief Resets a timetable.

            \param p_timetable A unique pointer to a timetable.
            \param path        A path.

            \throw std::invalid_argument When p_timetable is nullptr.
        */
        void reset_timetable(std::unique_ptr<timetable_type> p_timetable, boost::filesystem::path path)
        {
            reset_timetable_impl(std::move(p_timetable), boost::make_optional(std::move(path)));
        }

        /*!
            \brief Checks whether the model has a path.

            \retval true  When the model has a path.
            \retval false Otherwise.
        */
        bool has_path()
        const
        {
            return static_cast<bool>(m_path);
        }

        /*!
            \brief Returns the path.

            \return The path.

            \throw std::logic_error When the model does not have a path.
        */
        const boost::filesystem::path& path()
        const
        {
            if (!has_path())
                BOOST_THROW_EXCEPTION(std::logic_error("This model does not have a path."));

            return *m_path;
        }

        /*!
            \brief Sets a path.

            \param path A path.
        */
        void set_path(boost::filesystem::path path)
        {
            m_path = boost::make_optional(std::move(path));
            m_changed = false;

            m_observer_set.reset()();
        }

        /*!
            \brief Checks whether the model is changed.

            \retval true  When the model is changed.
            \retval false Otherwise.
        */
        bool changed()
        const
        {
            return m_changed;
        }

        /*!
            \brief Sets a changed status.

            \param changed A changed status.
        */
        void set_changed(const bool changed)
        {
            m_changed = changed;

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set()
        const
        {
            return m_observer_set;
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set()
        {
            return m_observer_set;
        }


    private:
        // variables

        std::unique_ptr<timetable_type> m_p_timetable;

        boost::optional<boost::filesystem::path> m_path;

        bool m_changed;

        observer_set_type m_observer_set;


        // functions

        void reset_timetable_impl(
            std::unique_ptr<timetable_type>            p_timetable,
            boost::optional<boost::filesystem::path>&& path
        )
        {
            if (!p_timetable)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Timetable is nullptr."));

            m_p_timetable = std::move(p_timetable);
            m_path = std::forward<boost::optional<boost::filesystem::path>>(path);
            m_changed = false;

            set_timetable_observer_set();

            m_observer_set.reset()();
        }

        void set_timetable_observer_set()
        {
            m_p_timetable->observer_set().changed().connect([this]() { this->set_changed(true); });
        }


    };


}

#endif