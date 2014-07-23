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

        \tparam OutputStream        An output stream type.
        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set type.
        \tparam Encoder             An encoder type.
    */
    template <typename OutputStream, typename Timetable, typename Encoder>
    class writer_set : private boost::noncopyable
    {
    public:
        // types

        //! The output stream type.
        using output_stream_type = OutputStream;

        //! The timetable type.
        using timetable_type = Timetable;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The writer type.
        using writer_type = writer<output_stream_type, timetable_type>;

        //! The bzip2 writer type.
        using bzip2_writer_type =
            bzip2_writer<
                typename timetable_type::size_type,
                typename timetable_type::difference_type,
                typename timetable_type::string_type,
                output_stream_type,
                typename timetable_type::operating_distance_type,
                typename timetable_type::speed_type,
                typename timetable_type::drawing_details_type
            >;

        //! The JSON writer type.
        using json_writer_type =
            json_writer<
                typename timetable_type::size_type,
                typename timetable_type::difference_type,
                typename timetable_type::string_type,
                output_stream_type,
                typename timetable_type::operating_distance_type,
                typename timetable_type::speed_type,
                encoder_type,
                typename timetable_type::drawing_details_type
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
