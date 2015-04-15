/*! \file
    \brief The definition of bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2READER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2READER_H

#include <memory>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>
#include <bobura/model/timetable.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a bzip2 reader.

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
    class bzip2_reader :
        public reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>
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
            \brief Creates a bzip2 reader.

            \param p_reader A unique pointer to a reader.
        */
        explicit bzip2_reader(std::unique_ptr<base_type> p_reader);

        /*!
            \brief Destroys the bzip2_reader.
        */
        virtual ~bzip2_reader()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool selects_impl(iterator first, iterator last)
        override;

        virtual std::unique_ptr<timetable_type> read_impl(iterator first, iterator last, error_type& error)
        override;


    };


}}}


#endif
