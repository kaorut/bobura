/*! \file
    \brief The definition of bobura::model::train_kind.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAINKIND_H)
#define BOBURA_MODEL_TRAINKIND_H

#include <boost/operators.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>

#include <bobura/type_list.h>


namespace bobura::model {
    /*!
        \brief The class for a train kind.
    */
    class train_kind : private boost::equality_comparable<train_kind>
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::common::string_type;

        //! The font type.
        using font_type = tetengo2::gui::drawing::font;

        //! The color type.
        using color_type = tetengo2::gui::drawing::color;

        //! The weight type.
        enum class weight_type
        {
            normal, //!< Normal.
            bold, //!< Bold.
        };

        //! The line style type.
        enum class line_style_type
        {
            solid, //!< Solid.
            dashed, //!< Dashed.
            dotted, //!< Dotted.
            dot_dashed, //!< Dot-Dashed.
        };


        // static functions

        /*!
            \brief Returns the default train kind.

            \return The default train kind.
        */
        static const train_kind& default_();


        // constructors and destructor

        /*!
            \brief Creates a train kind.

            \param name                 A name.
            \param abbreviation         An abbreviated name.
            \param diagram_font         A font for the diagram.
            \param diagram_color        A color for the diagram.
            \param diagram_line_weight  A line weight for the diagram.
            \param diagram_line_style   A line style for the diagram.
            \param timetable_font       A font for the timetable.
            \param timetable_color      A color for the timetable.
        */
        train_kind(
            string_type           name,
            string_type           abbreviation,
            font_type             diagram_font,
            color_type            diagram_color,
            const weight_type     diagram_line_weight,
            const line_style_type diagram_line_style,
            font_type             timetable_font,
            color_type            timetable_color);


        // functions

        /*!
            \brief Checks whether one train kind is equal to another.

            \param one     One train kind.
            \param another Another train kind.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train_kind& one, const train_kind& another);

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name() const;

        /*!
            \brief Returns the abbreviated name.

            \return The abbreviated name.
        */
        const string_type& abbreviation() const;

        /*!
            \brief Returns the font for the diagram.

            \return The font for the diagram.
        */
        const font_type& diagram_font() const;

        /*!
            \brief Returns the color for the diagram.

            \return The color for the diagram.
        */
        const color_type& diagram_color() const;

        /*!
            \brief Returns the line weight for the diagram.

            \return The line weight for the diagram.
        */
        weight_type diagram_line_weight() const;

        /*!
            \brief Returns the line style for the diagram.

            \return The line style for the diagram.
        */
        line_style_type diagram_line_style() const;

        /*!
            \brief Returns the timetable font for the timetable.

            \return The timetable font for the timetable.
        */
        const font_type& timetable_font() const;

        /*!
            \brief Returns the timetable color for the timetable.

            \return Thetimetable color for the timetable.
        */
        const color_type& timetable_color() const;


    private:
        // variables

        string_type m_name;

        string_type m_abbreviation;

        font_type m_diagram_font;

        color_type m_diagram_color;

        weight_type m_diagram_line_weight;

        line_style_type m_diagram_line_style;

        font_type m_timetable_font;

        color_type m_timetable_color;
    };
}


#endif
