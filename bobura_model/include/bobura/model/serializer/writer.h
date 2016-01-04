/*! \file
    \brief The definition of bobura::model::serializer::writer.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITER_H)
#define BOBURA_MODEL_SERIALIZER_WRITER_H

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>

#include <tetengo2.h>

#include <bobura/model/timetable.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer.

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
        typename Font
    >
    class writer : private boost::noncopyable
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

        //! The timetable type.
        using timetable_type =
            timetable<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;


        // constructors and destructor

        /*!
            \brief Destroys the writer.
        */
        virtual ~writer()
        noexcept;


        // functions

        /*!
            \brief Returns the extension.

            The extension includes the first dot; not "txt" but ".txt".

            \return The extension.
        */
        boost::filesystem::path extension()
        const;

        /*!
            \brief Checks whether this writer selects a file type.

            \param path A path.

            \retval true  When this writer selects the file type.
            \retval false Otherwise.
        */
        bool selects(const boost::filesystem::path& path)
        const;

        /*!
            \brief Writes a timetable.

            \param timetable     A timetable.
            \param output_stream An output stream.
        */
        void write(const timetable_type& timetable, output_stream_type& output_stream);


    protected:
        // constructors

        /*!
            \brief Creates a writer.
        */
        writer();


    private:
        // virtual functions

        virtual bool selects_impl(const boost::filesystem::path& path)
        const;

        virtual boost::filesystem::path extension_impl()
        const = 0;

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        = 0;


    };


}}}


#endif
