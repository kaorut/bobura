/*! \file
    \brief The definition of bobura::model::serializer::json_reader.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONREADER_H)
#define BOBURA_MODEL_SERIALIZER_JSONREADER_H

#include <memory>
#include <stdexcept>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reader.

        \tparam Size                A size type.
        \tparam Difference          A difference type.
        \tparam String              A string type.
        \tparam ForwardIterator     A forward iterator type.
        \tparam Integer             An integer type.
        \tparam Float               A floating point number type.
        \tparam OperatingDistance   An operating distance type.
        \tparam Speed               A speed type.
        \tparam ExecJsonReadingTask A JSON reading task execution type.
        \tparam Font                A font type.
        \tparam Encoder             An encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename Integer,
        typename Float,
        typename OperatingDistance,
        typename Speed,
        typename ExecJsonReadingTask,
        typename Font,
        typename Encoder
    >
    class json_reader : public reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>
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

        //! The integer type.
        using integer_type = Integer;

        //! The float type.
        using float_type = Float;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The JSON reading task execution type.
        using exec_json_reading_task_type = ExecJsonReadingTask;

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
            \brief Creates a JSON reader.

            \param p_exec_json_reading_task A unique pointer to a JSON reading task execution.

            \throw std::invalid_argument When p_exec_json_reading_task is nullptr.
        */
        explicit json_reader(std::unique_ptr<exec_json_reading_task_type> p_exec_json_reading_task);

        /*!
            \brief Destroys the JSON reader.
        */
        virtual ~json_reader()
        noexcept;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool selects_impl(iterator first, iterator last)
        override;

        virtual std::unique_ptr<timetable_type> read_impl(iterator first, iterator last, error_type& error)
        override;


    };


}}}


#endif
