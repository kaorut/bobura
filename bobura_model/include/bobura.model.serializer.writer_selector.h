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

#include <boost/throw_exception.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.model.serializer.writer.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer selector.

        \tparam OutputStream An output stream type.
        \tparam Timetable    A timetable type.
        \tparam Path         A path type.
    */
    template <typename OutputStream, typename Timetable, typename Path>
    class writer_selector : public writer<OutputStream, Timetable, Path>
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;

        //! The base type.
        typedef writer<output_stream_type, timetable_type, path_type> base_type;


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
        writer_selector(std::vector<std::unique_ptr<base_type>> p_writers, path_type path)
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
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION


    private:
        // variables

        const std::vector<std::unique_ptr<base_type>> m_p_writers;

        const path_type m_path;


        // virtual functions

        virtual bool selects_impl(const path_type& path)
        const override
        {
            return
                std::find_if(
                    m_p_writers.begin(),
                    m_p_writers.end(),
                    [&path](const std::unique_ptr<base_type>& p_writer) { return p_writer->selects(path); }
                ) != m_p_writers.end();
        }

        virtual path_type extension_impl()
        const override
        {
            BOOST_THROW_EXCEPTION(std::logic_error("No extension."));
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
