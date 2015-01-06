/*! \file
    \brief The definition of bobura::model::serializer::reader_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSET_H)
#define BOBURA_MODEL_SERIALIZER_READERSET_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/bzip2_reader.h>
#include <bobura/model/serializer/json_reader.h>
#include <bobura/model/serializer/oudia_reader.h>
#include <bobura/model/serializer/reader.h>
#include <bobura/model/serializer/reader_selector.h>
#include <bobura/model/serializer/windia_reader.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader set.

        \tparam Size               A size type.
        \tparam Difference         A difference type.
        \tparam String             A string type.
        \tparam ForwardIterator    A forward iterator type.
        \tparam OperatingDistance  An operating distance type.
        \tparam Speed              A speed type.
        \tparam SelectOuDiaDiagram An OuDia diagram selecting type.
        \tparam Font               A font type.
        \tparam Utf8Encoder        A UTF-8 encoder type.
        \tparam Cp932Encoder       A CP932 encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
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

        //! The JSON reader type.
        using json_reader_type =
            json_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                int,
                double,
                operating_distance_type,
                speed_type,
                font_type,
                utf8_encoder_type
            >;

        //! The bzip2 reader type.
        using bzip2_reader_type =
            bzip2_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                font_type
            >;

        //! The OuDia reader type.
        using oudia_reader_type =
            oudia_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                select_oudia_diagram_type,
                font_type,
                cp932_encoder_type
            >;

        //! The WinDIA reader type.
        using windia_reader_type =
            windia_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                font_type,
                cp932_encoder_type
            >;


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
        )
        {
            std::vector<std::unique_ptr<reader_type>> readers{};

            readers.push_back(tetengo2::stdalt::make_unique<json_reader_type>());
            readers.push_back(
                tetengo2::stdalt::make_unique<bzip2_reader_type>(tetengo2::stdalt::make_unique<json_reader_type>())
            );
            readers.push_back(create_oudia_reader(parent, std::move(file_name), message_catalog));
            readers.push_back(tetengo2::stdalt::make_unique<windia_reader_type>());

            return std::move(readers);
        }


    private:
        // static functions

        static std::unique_ptr<reader_type> create_oudia_reader(
            abstract_window_type&       parent,
            string_type                 file_name,
            const message_catalog_type& message_catalog
        )
        {
            auto p_select_oudia_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(
                    parent, std::move(file_name), message_catalog
                );
            return tetengo2::stdalt::make_unique<oudia_reader_type>(std::move(p_select_oudia_diagram));
        }


        // forbidden operations

        reader_set()
        = delete;


    };


}}}


#endif
