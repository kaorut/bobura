/*! \file
    \brief The definition of bobura::model::serializer::reader_selector.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSELECTOR_H)
#define BOBURA_MODEL_SERIALIZER_READERSELECTOR_H

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader selector.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam ForwardIterator   A forward iterator type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    class reader_selector : public reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The base type.
        using base_type =
            reader<size_type, difference_type, string_type, iterator, operating_distance_type, speed_type, font_type>;

        //! The timetable type.
        using timetable_type = typename base_type::timetable_type;

        //! The error type.
        using error_type = typename base_type::error_type;


        // constructors and destructor

        /*!
            \brief Creates a reader selector.

            \param p_readers Unique pointers to readers.

            \throw std::invalid_argument When the count of the readers is empty.
        */
        explicit reader_selector(std::vector<std::unique_ptr<base_type>> p_readers)
        :
        m_p_readers(std::move(p_readers))
        {
            if (m_p_readers.empty())
                BOOST_THROW_EXCEPTION(std::invalid_argument("No reader is specified."));
        }

        /*!
            \brief Destroys the reader_selector.
        */
        virtual ~reader_selector()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // variables

        const std::vector<std::unique_ptr<base_type>> m_p_readers;


        // virtual functions

#if BOOST_COMP_GNUC
#   pragma GCC diagnostic ignored "-Wreturn-type"
#endif
        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            boost::ignore_unused(first, last);

            BOOST_THROW_EXCEPTION(std::logic_error("This function cannot be called."));
        }
#if BOOST_COMP_GNUC
#   pragma GCC diagnostic warning "-Wreturn-type"
#endif

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            const auto found =
                std::find_if(
                    m_p_readers.begin(),
                    m_p_readers.end(),
                    [first, last](const std::unique_ptr<base_type>& p_reader)
                    {
                        return p_reader->selects(first, last);
                    }
                );
            if (found == m_p_readers.end())
            {
                error = error_type::unsupported;
                return std::unique_ptr<timetable_type>{};
            }

            return (*found)->read(first, last, error);
        }


    };


}}}


#endif
