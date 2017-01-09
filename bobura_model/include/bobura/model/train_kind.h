/*! \file
    \brief The definition of bobura::model::train_kind.

    Copyright (C) 2007-2017 kaoru

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
        \tparam Font   A font type.
    */
    template <typename String, typename Font>
    class train_kind : private boost::equality_comparable<train_kind<String, Font>>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The font type.
        using font_type = Font;

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


        // static functions

        /*!
            \brief Returns the default train kind.

            \return The default train kind.
        */
        static const train_kind& default_()
        {
            static auto singleton = make_default();
            return singleton;
        }


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
            color_type            timetable_color
        )
        :
        m_name(std::move(name)),
        m_abbreviation(std::move(abbreviation)),
        m_diagram_font(std::move(diagram_font)),
        m_diagram_color(std::move(diagram_color)),
        m_diagram_line_weight(diagram_line_weight),
        m_diagram_line_style(diagram_line_style),
        m_timetable_font(std::move(timetable_font)),
        m_timetable_color(std::move(timetable_color))
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
                one.m_diagram_font == another.m_diagram_font &&
                one.m_diagram_color == another.m_diagram_color &&
                one.m_diagram_line_weight == another.m_diagram_line_weight &&
                one.m_diagram_line_style == another.m_diagram_line_style &&
                one.m_timetable_font == another.m_timetable_font &&
                one.m_timetable_color == another.m_timetable_color;
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
            \brief Returns the font for the diagram.

            \return The font for the diagram.
        */
        const font_type& diagram_font()
        const
        {
            return m_diagram_font;
        }

        /*!
            \brief Returns the color for the diagram.

            \return The color for the diagram.
        */
        const color_type& diagram_color()
        const
        {
            return m_diagram_color;
        }

        /*!
            \brief Returns the line weight for the diagram.

            \return The line weight for the diagram.
        */
        weight_type diagram_line_weight()
        const
        {
            return m_diagram_line_weight;
        }

        /*!
            \brief Returns the line style for the diagram.

            \return The line style for the diagram.
        */
        line_style_type diagram_line_style()
        const
        {
            return m_diagram_line_style;
        }

        /*!
            \brief Returns the timetable font for the timetable.

            \return The timetable font for the timetable.
        */
        const font_type& timetable_font()
        const
        {
            return m_timetable_font;
        }

        /*!
            \brief Returns the timetable color for the timetable.

            \return Thetimetable color for the timetable.
        */
        const color_type& timetable_color()
        const
        {
            return m_timetable_color;
        }


    private:
        // static functions

        static train_kind make_default()
        {
            auto default_font = font_type::dialog_font();
            return
                train_kind{
                    string_type{},
                    string_type{},
                    default_font,
                    color_type{ 0x00, 0x00, 0x00 },
                    weight_type::normal,
                    line_style_type::solid,
                    default_font,
                    color_type{ 0x00, 0x00, 0x00 }
                };
        }


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


}}


#endif
