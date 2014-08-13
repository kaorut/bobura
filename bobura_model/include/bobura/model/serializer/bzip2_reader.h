/*! \file
    \brief The definition of bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2READER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2READER_H

#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/utility/string_ref.hpp>

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
        explicit bzip2_reader(std::unique_ptr<base_type> p_reader)
        :
        base_type(),
        m_p_reader(std::move(p_reader))
        {}

        /*!
            \brief Destroys the bzip2_reader.
        */
        virtual ~bzip2_reader()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // types

        using input_string_type = std::basic_string<typename iterator::value_type>;

        using input_string_ref_type =
            boost::basic_string_ref<typename iterator::value_type, std::char_traits<typename iterator::value_type>>;


        // variables

        const std::unique_ptr<base_type> m_p_reader;


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            const input_string_type input_string{ first, last };
            if (input_string.length() < 2)
                return false;
            if (input_string_ref_type{ input_string }.substr(0, 2) != input_string_ref_type(TETENGO2_TEXT("BZ")))
                return false;

            std::istringstream input_stream{ input_string };
            boost::iostreams::filtering_istream filtering_input_stream{};
            filtering_input_stream.push(boost::iostreams::bzip2_decompressor());
            filtering_input_stream.push(input_stream);

            try
            {
                return
                    m_p_reader->selects(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>(filtering_input_stream)
                        ),
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>()
                        )
                    );
            }
            catch (const boost::iostreams::bzip2_error&)
            {
                return false;
            }
            catch (...)
            {
                throw;
            }
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            std::istringstream input_stream{ input_string_type{ first, last } };
            boost::iostreams::filtering_istream filtering_input_stream{};
            filtering_input_stream.push(boost::iostreams::bzip2_decompressor());
            filtering_input_stream.push(input_stream);

            try
            {
                return
                    m_p_reader->read(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>(filtering_input_stream)
                        ),
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>()
                        ),
                        error
                    );
            }
            catch (const boost::iostreams::bzip2_error&)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>{};
            }
            catch (...)
            {
                throw;
            }
        }


    };


}}}


#endif
