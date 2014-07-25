/*! \file
    \brief The definition of bobura::model::serializer::writer_selector.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERSELECTOR_H)
#define BOBURA_MODEL_SERIALIZER_WRITERSELECTOR_H

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/writer.h>
#include <bobura/model/timetable.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer selector.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OutputStream      An output stream type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam DrawingDetails    A detail implementation type of a drawing.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename DrawingDetails
    >
    class writer_selector : public writer<OutputStream, timetable<Size, Difference, String, OperatingDistance, Speed, DrawingDetails>>
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

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;

        //! The timetable type.
        using timetable_type =
            timetable<
                size_type, difference_type, string_type, operating_distance_type, speed_type, drawing_details_type
            >;

        //! The base type.
        using base_type = writer<output_stream_type, timetable_type>;


        // constructors and destructor

        /*!
            \brief Creates a writer selector.

            When no writer selects the file type, the first writer of
            p_writers is used.

            \param p_writers Unique pointers to writers.
            \param path      A path.

            \throw std::invalid_argument When the count of the writers is
                                         empty.
        */
        writer_selector(std::vector<std::unique_ptr<base_type>> p_writers, boost::filesystem::path path)
        :
        m_p_writers(std::move(p_writers)),
        m_path(std::move(path))
        {
            if (m_p_writers.empty())
                BOOST_THROW_EXCEPTION(std::invalid_argument("No writer is specified."));
        }

        /*!
            \brief Destroys the writer_selector.
        */
        virtual ~writer_selector()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // variables

        const std::vector<std::unique_ptr<base_type>> m_p_writers;

        const boost::filesystem::path m_path;


        // virtual functions

        virtual bool selects_impl(const boost::filesystem::path& path)
        const override
        {
            return
                std::find_if(
                    m_p_writers.begin(),
                    m_p_writers.end(),
                    [&path](const std::unique_ptr<base_type>& p_writer) { return p_writer->selects(path); }
                ) != m_p_writers.end();
        }

        virtual boost::filesystem::path extension_impl()
        const override
        {
            BOOST_THROW_EXCEPTION(std::logic_error("No extension."));
            return boost::filesystem::path(); // for warning suppression
        }

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        override
        {
            const auto found =
                std::find_if(
                    m_p_writers.begin(),
                    m_p_writers.end(),
                    [this](const std::unique_ptr<base_type>& p_writer) { return p_writer->selects(this->m_path); }
                );
            if (found == m_p_writers.end())
                BOOST_THROW_EXCEPTION(std::logic_error("No writer selects this file type."));

            (*found)->write(timetable, output_stream);
        }


    };


}}}


#endif
