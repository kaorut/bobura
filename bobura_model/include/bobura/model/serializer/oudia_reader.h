/*! \file
    \brief The definition of bobura::model::serializer::oudia_reader.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_OUDIAREADER_H)
#define BOBURA_MODEL_SERIALIZER_OUDIAREADER_H

#include <memory>

#include <bobura/model/serializer/reader.h>
#include <bobura/model/station_info/grade.h>


namespace bobura { namespace model { namespace serializer {
    /*!
        \brief The class template for an OuDia reader.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam ForwardIterator   A forward iterator type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam SelectDiagram     A diagram selecting type.
        \tparam Font              A font type.
        \tparam Encoder           An encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename SelectDiagram,
        typename Font,
        typename Encoder>
    class oudia_reader : public reader<Size, Difference, String, ForwardIterator, OperatingDistance, Speed, Font>
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

        //! The diagram selecting type.
        using select_diagram_type = SelectDiagram;

        //! The font type.
        using font_type = Font;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The base type.
        using base_type =
            reader<size_type, difference_type, string_type, iterator, operating_distance_type, speed_type, font_type>;

        //! The timetable type.
        using timetable_type = typename base_type::timetable_type;

        //! The error type.
        using error_type = typename base_type::error_type;

        //! The station grade type set type.
        using station_grade_type_set_type = station_info::grade_type_set<string_type>;


        // constructors and destructor

        /*!
            \brief Creates a WinDIA reader.

            \param p_select_diagram A unique pointer to a diagram selecting.

            \throw std::invalid_argument When p_select_diagram is nullptr.
        */
        explicit oudia_reader(std::unique_ptr<select_diagram_type> p_select_diagram);

        /*!
            \brief Destroys the oudia_reader.
        */
        virtual ~oudia_reader() noexcept;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool selects_impl(iterator first, iterator last) override;

        virtual std::unique_ptr<timetable_type> read_impl(iterator first, iterator last, error_type& error) override;
    };


}}}


#endif
