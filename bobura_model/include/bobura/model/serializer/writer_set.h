/*! \file
    \brief The definition of bobura::model::serializer::writer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERSET_H)
#define BOBURA_MODEL_SERIALIZER_WRITERSET_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <bobura/model/serializer/writer.h>


namespace bobura { namespace model { namespace serializer {
    /*!
        \brief The class template for a writer set.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OutputStream      An output stream type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
        \tparam Encoder           An encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Encoder>
    class writer_set : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The output stream type.
        using output_stream_type = OutputStream;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The writer type.
        using writer_type = writer<
            size_type,
            difference_type,
            string_type,
            output_stream_type,
            operating_distance_type,
            speed_type,
            font_type>;


        // static functions

        /*!
            \brief Creates writers.

            \return Unique pointers to writers.
        */
        static std::vector<std::unique_ptr<writer_type>> create_writers();


    private:
        // types

        class impl;


        // forbidden operations

        writer_set() = delete;
    };


}}}


#endif
