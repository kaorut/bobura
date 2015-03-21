/*! \file
    \brief The definition of bobura::model::serializer::reader_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSET_H)
#define BOBURA_MODEL_SERIALIZER_READERSET_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader set.

        \tparam Size                A size type.
        \tparam Difference          A difference type.
        \tparam String              A string type.
        \tparam ForwardIterator     A forward iterator type.
        \tparam OperatingDistance   An operating distance type.
        \tparam Speed               A speed type.
        \tparam ExecJsonReadingTask A JSON reading task execution type.
        \tparam SelectOuDiaDiagram  An OuDia diagram selecting type.
        \tparam Font                A font type.
        \tparam Utf8Encoder         A UTF-8 encoder type.
        \tparam Cp932Encoder        A CP932 encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename ExecJsonReadingTask,
        typename SelectOuDiaDiagram,
        typename Font,
        typename Utf8Encoder,
        typename Cp932Encoder
    >
    class reader_set : private boost::noncopyable
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

        //! The JSON reading task execution type.
        using exec_json_reading_task_type = ExecJsonReadingTask;

        //! The OuDia diagram selecting type.
        using select_oudia_diagram_type = SelectOuDiaDiagram;

        //! The abstract window type.
        using abstract_window_type = typename select_oudia_diagram_type::abstract_window_type;

        //! The message catalog type.
        using message_catalog_type = typename select_oudia_diagram_type::message_catalog_type;

        //! The font type.
        using font_type = Font;

        //! The UTF-8 encoder type.
        using utf8_encoder_type = Utf8Encoder;

        //! The CP932 encoder type.
        using cp932_encoder_type = Cp932Encoder;

        //! The reader type.
        using reader_type =
            reader<size_type, difference_type, string_type, iterator, operating_distance_type, speed_type, font_type>;


        // static functions

        /*!
            \brief Creates readers.

            \param parent          A parent window.
            \param file_name       A file name.
            \param message_catalog A message catalog.

            \return Unique pointers to readers.
        */
        static std::vector<std::unique_ptr<reader_type>> create_readers(
            abstract_window_type&       parent,
            string_type                 file_name,
            const message_catalog_type& message_catalog
        );


    private:
        // types

        class impl;


        // forbidden operations

        reader_set()
        = delete;


    };


}}}


#endif
