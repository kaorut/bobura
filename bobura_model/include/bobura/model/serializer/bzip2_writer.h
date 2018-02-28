/*! \file
    \brief The definition of bobura::model::serializer::bzip2_writer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2WRITER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2WRITER_H

#include <memory>

#include <boost/filesystem.hpp>

#include <bobura/model/serializer/writer.h>


namespace bobura { namespace model { namespace serializer {
    /*!
        \brief The class template for a bzip2 writer.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OutputStream      An output stream type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font>
    class bzip2_writer : public writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>
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

        //! The base type.
        using base_type = writer<
            size_type,
            difference_type,
            string_type,
            output_stream_type,
            operating_distance_type,
            speed_type,
            font_type>;

        //! The timetable type.
        using timetable_type = typename base_type::timetable_type;


        // constructors and destructor

        /*!
            \brief Creates a bzip2 writer.

            \param p_writer A unique pointer to a writer.
        */
        explicit bzip2_writer(std::unique_ptr<base_type> p_writer);

        /*!
            \brief Destroys the bzip2 writer.
        */
        virtual ~bzip2_writer() noexcept;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual boost::filesystem::path extension_impl() const override;

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream) override;
    };


}}}


#endif
