/*! \file
    \brief The definition of bobura::model::train_kind.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAINKIND_H)
#define BOBURA_MODEL_TRAINKIND_H

#include <utility>

#include <boost/operators.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a train kind.

        \tparam String A string type.
    */
    template <typename String>
    class train_kind : private boost::equality_comparable<train_kind<String>>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The color type.
        using color_type = tetengo2::gui::drawing::color;

        //! The weight type.
        enum class weight_type
        {
            normal, //!< Normal.
            bold,   //!< Bold.
        };

        //! The line style type.
        enum class line_style_type
        {
            solid,      //!< Solid.
            dashed,     //!< Dashed.
            dotted,     //!< Dotted.
            dot_dashed, //!< Dot-Dashed.
        };


        // constructors and destructor

        /*!
            \brief Creates a train kind.

            \param name                 A name.
            \param abbreviation         An abbreviated name.
            \param diagram_line_color   A diagram line color.
            \param diagram_line_weight  A diagram line weight.
            \param diagram_line_style   A diagram line style.
        */
        train_kind(
            string_type           name,
            string_type           abbreviation,
            color_type            diagram_line_color,
            const weight_type     diagram_line_weight,
            const line_style_type diagram_line_style
        )
        :
        m_name(std::move(name)),
        m_abbreviation(std::move(abbreviation)),
        m_diagram_line_color(std::move(diagram_line_color)),
        m_diagram_line_weight(diagram_line_weight),
        m_diagram_line_style(diagram_line_style)
        {}


        // functions

        /*!
            \brief Checks whether one train kind is equal to another.

            \param one     One train kind.
            \param another Another train kind.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train_kind& one, const train_kind& another)
        {
            return
                one.m_name == another.m_name &&
                one.m_abbreviation == another.m_abbreviation &&
                one.m_diagram_line_color == another.m_diagram_line_color &&
                one.m_diagram_line_weight == another.m_diagram_line_weight &&
                one.m_diagram_line_style == another.m_diagram_line_style;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name()
        const
        {
            return m_name;
        }

        /*!
            \brief Returns the abbreviated name.

            \return The abbreviated name.
        */
        const string_type& abbreviation()
        const
        {
            return m_abbreviation;
        }

        /*!
            \brief Returns the diagram line color.

            \return The diagram line color.
        */
        const color_type& diagram_line_color()
        const
        {
            return m_diagram_line_color;
        }

        /*!
            \brief Returns the diagram line weight.

            \return The diagram line weight.
        */
        weight_type diagram_line_weight()
        const
        {
            return m_diagram_line_weight;
        }

        /*!
            \brief Returns the diagram line style.

            \return The diagram line style.
        */
        line_style_type diagram_line_style()
        const
        {
            return m_diagram_line_style;
        }


    private:
        // variables

        string_type m_name;

        string_type m_abbreviation;

        color_type m_diagram_line_color;

        weight_type m_diagram_line_weight;

        line_style_type m_diagram_line_style;


    };


}}


#endif
