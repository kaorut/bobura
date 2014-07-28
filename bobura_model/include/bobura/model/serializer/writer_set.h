/*! \file
    \brief The definition of bobura::model::serializer::writer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERSET_H)
#define BOBURA_MODEL_SERIALIZER_WRITERSET_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/bzip2_writer.h>
#include <bobura/model/serializer/json_writer.h>
#include <bobura/model/serializer/writer.h>
#include <bobura/model/serializer/writer_selector.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer set.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OutputStream      An output stream type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Encoder           An encoder type.
        \tparam DrawingDetails    A detail implementation type of a drawing.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Encoder,
        typename DrawingDetails
    >
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

        //! The encoder type.
        using encoder_type = Encoder;

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;

        //! The writer type.
        using writer_type =
            writer<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                drawing_details_type
            >;

        //! The bzip2 writer type.
        using bzip2_writer_type =
            bzip2_writer<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                drawing_details_type
            >;

        //! The JSON writer type.
        using json_writer_type =
            json_writer<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                encoder_type,
                drawing_details_type
            >;


        // static functions

        /*!
            \brief Creates writers.

            \return Unique pointers to writers.
        */
        static std::vector<std::unique_ptr<writer_type>> create_writers()
        {
            std::vector<std::unique_ptr<writer_type>> writers{};

            writers.push_back(tetengo2::stdalt::make_unique<json_writer_type>());
            writers.push_back(
                tetengo2::stdalt::make_unique<bzip2_writer_type>(tetengo2::stdalt::make_unique<json_writer_type>())
            );

            return std::move(writers);
        }


    private:
        // forbidden operations

        writer_set()
        = delete;


    };


}}}


#endif
