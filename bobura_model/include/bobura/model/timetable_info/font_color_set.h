/*! \file
    \brief The definition of bobura::model::timetable_info::font_color_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_FONTCOLORSET_H)
#define BOBURA_MODEL_TIMETABLEINFO_FONTCOLORSET_H

#include <memory>

#include <boost/operators.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/stdalt.h>


namespace bobura::model::timetable_info {
    /*!
        \brief The class for a font and color.
    */
    class font_color : private boost::equality_comparable<font_color>
    {
    public:
        // types

        //! The font type.
        using font_type = tetengo2::gui::drawing::font;

        //! The color type.
        using color_type = tetengo2::gui::drawing::color;


        // constructors and destructor

        /*!
            \brief Creates a font and color.

            \param diagram_font    A font for the diagram.
            \param diagram_color   A color for the diagram.
            \param timetable_font  A font for the timetable.
            \param timetable_color A color for the timetable.
        */
        font_color(
            tetengo2::stdalt::optional<font_type>  diagram_font,
            tetengo2::stdalt::optional<color_type> diagram_color,
            tetengo2::stdalt::optional<font_type>  timetable_font,
            tetengo2::stdalt::optional<color_type> timetable_color);

        /*!
            \brief Copies a font and color.

            \param another Another font and color.
        */
        font_color(const font_color& another);

        /*!
            \brief Moves a font and color.

            \param another Another font and color.
        */
        font_color(font_color&& another);

        /*!
            \brief Destroys the font and color.
        */
        ~font_color();


        // functions

        /*!
            \brief Checks whether one font and color is equal to another.

            \param one     One font and color.
            \param another Another font and color.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font_color& one, const font_color& another);

        /*!
            \brief Assigns a font and color.

            \param another Another font and color.

            \return This object.
        */
        font_color& operator=(const font_color& another);

        /*!
            \brief Assigns a font and color.

            \param another Another font and color.

            \return This object.
        */
        font_color& operator=(font_color&& another);

        /*!
            \brief Returns the font for the diagram.

            \return The font for the diagram.
        */
        const tetengo2::stdalt::optional<font_type>& diagram_font() const;

        /*!
            \brief Returns the color for the diagram.

            \return The color for the diagram.
        */
        const tetengo2::stdalt::optional<color_type>& diagram_color() const;

        /*!
            \brief Returns the font for the timetable.

            \return The font for the timetable.
        */
        const tetengo2::stdalt::optional<font_type>& timetable_font() const;

        /*!
            \brief Returns the color for the timetable.

            \return The color for the timetable.
        */
        const tetengo2::stdalt::optional<color_type>& timetable_color() const;


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };


    /*!
        \brief The class for a font and color set.
    */
    class font_color_set : private boost::equality_comparable<font_color_set>
    {
    public:
        // types

        //! The font and color type.
        using font_color_type = font_color;

        //! The font type.
        using font_type = font_color_type::font_type;

        //! The color type.
        using color_type = font_color_type::color_type;


        // static functions

        /*!
            \brief Returns the default font and color set.

            \return The default font and color set.
        */
        static const font_color_set& default_();


        // constructors and destructor

        /*!
            \brief Creates a font and color set.

            \param background                 A font and color for the background.
            \param general                    A font and color for the general item.
            \param company_name               A font and color for the company name.
            \param line_name                  A font and color for the line name.
            \param note                       A font and color for the note.
            \param local_station              A font and color for the local station.
            \param principal_station          A font and color for the principal station.
            \param local_terminal_station     A font and color for the local terminal station.
            \param principal_terminal_station A font and color for the principal terminal station.
        */
        font_color_set(
            font_color_type background,
            font_color_type general,
            font_color_type company_name,
            font_color_type line_name,
            font_color_type note,
            font_color_type local_station,
            font_color_type principal_station,
            font_color_type local_terminal_station,
            font_color_type principal_terminal_station);

        /*!
            \brief Copies a font and color set.

            \param another Another font and color set.
        */
        font_color_set(const font_color_set& another);

        /*!
            \brief Moves a font and color set.

            \param another Another font and color set.
        */
        font_color_set(font_color_set&& another);

        /*!
            \brief Destroys the font and color set.
        */
        ~font_color_set();


        // functions

        /*!
            \brief Checks whether one font and color set is equal to another.

            \param one     One font and color set.
            \param another Another font and color set.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font_color_set& one, const font_color_set& another);

        /*!
            \brief Assigns a font and color set.

            \param another Another font and color set.

            \return This object.
        */
        font_color_set& operator=(const font_color_set& another);

        /*!
            \brief Assigns a font and color set.

            \param another Another font and color set.

            \return This object.
        */
        font_color_set& operator=(font_color_set&& another);

        /*!
            \brief Returns the font and color for the background.

            \return The font and color for the background.
        */
        const font_color_type& background() const;

        /*!
            \brief Returns the font and color for the general item.

            \return The font and color for the general item.
        */
        const font_color_type& general() const;

        /*!
            \brief Returns the font and color for the company names.

            \return The font and color for the company names.
        */
        const font_color_type& company_name() const;

        /*!
            \brief Returns the font and color for the line name.

            \return The font and color for the line name.
        */
        const font_color_type& line_name() const;

        /*!
            \brief Returns the font and color for the note.

            \return The font and color for the note.
        */
        const font_color_type& note() const;

        /*!
            \brief Returns the font and color for the local station.

            \return The font and color for the local station.
        */
        const font_color_type& local_station() const;

        /*!
            \brief Returns the font and color for the principal station.

            \return The font and color for the principal station.
        */
        const font_color_type& principal_station() const;

        /*!
            \brief Returns the font and color for the local terminal station.

            \return The font and color for the local terminal station.
        */
        const font_color_type& local_terminal_station() const;

        /*!
            \brief Returns the font and color for the principal terminal station.

            \return The font and color for the principal terminal station.
        */
        const font_color_type& principal_terminal_station() const;


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
