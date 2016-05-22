/*! \file
    \brief The definition of bobura::model::timetable_info::font_color_set.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_FONTCOLORSET_H)
#define BOBURA_MODEL_TIMETABLEINFO_FONTCOLORSET_H

#include <utility>

#include <boost/operators.hpp>
#include <boost/optional.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class template for a font and color.

        \tparam Font A font type.
    */
    template <typename Font>
    class font_color : private boost::equality_comparable<font_color<Font>>
    {
    public:
        // types

        //! The font type.
        using font_type = Font;

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
            boost::optional<font_type>  diagram_font,
            boost::optional<color_type> diagram_color,
            boost::optional<font_type>  timetable_font,
            boost::optional<color_type> timetable_color
        )
        :
        m_diagram_font(std::move(diagram_font)),
        m_diagram_color(std::move(diagram_color)),
        m_timetable_font(std::move(timetable_font)),
        m_timetable_color(std::move(timetable_color))
        {}


        // functions

        /*!
            \brief Checks whether one font and color is equal to another.

            \param one     One font and color.
            \param another Another font and color.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font_color& one, const font_color& another)
        {
            return
                one.m_diagram_font == another.m_diagram_font &&
                one.m_diagram_color == another.m_diagram_color &&
                one.m_timetable_font == another.m_timetable_font &&
                one.m_timetable_color == another.m_timetable_color;
        }

        /*!
            \brief Returns the font for the diagram.

            \return The font for the diagram.
        */
        const boost::optional<font_type>& diagram_font()
        const
        {
            return m_diagram_font;
        }

        /*!
            \brief Returns the color for the diagram.

            \return The color for the diagram.
        */
        const boost::optional<color_type>& diagram_color()
        const
        {
            return m_diagram_color;
        }

        /*!
            \brief Returns the font for the timetable.

            \return The font for the timetable.
        */
        const boost::optional<font_type>& timetable_font()
        const
        {
            return m_timetable_font;
        }

        /*!
            \brief Returns the color for the timetable.

            \return The color for the timetable.
        */
        const boost::optional<color_type>& timetable_color()
        const
        {
            return m_timetable_color;
        }


    private:
        // variables

        boost::optional<font_type> m_diagram_font;

        boost::optional<color_type> m_diagram_color;

        boost::optional<font_type> m_timetable_font;

        boost::optional<color_type> m_timetable_color;


    };


    /*!
        \brief The class template for a font and color set.

        \tparam Font A font type.
    */
    template <typename Font>
    class font_color_set : private boost::equality_comparable<font_color_set<Font>>
    {
    public:
        // types

        //! The font type.
        using font_type = Font;

        //! The font and color type.
        using font_color_type = font_color<font_type>;

        //! The color type.
        using color_type = typename font_color_type::color_type;


        // static functions

        /*!
            \brief Returns the default font and color set.

            \return The default font and color set.
        */
        static const font_color_set& default_()
        {
            static auto singleton = make_default();
            return singleton;
        }


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
            font_color_type principal_terminal_station
        )
        :
        m_background(std::move(background)),
        m_general(std::move(general)),
        m_company_name(std::move(company_name)),
        m_line_name(std::move(line_name)),
        m_note(std::move(note)),
        m_local_station(std::move(local_station)),
        m_principal_station(std::move(principal_station)),
        m_local_terminal_station(std::move(local_terminal_station)),
        m_principal_terminal_station(std::move(principal_terminal_station))
        {}


        // functions

        /*!
            \brief Checks whether one font and color set is equal to another.

            \param one     One font and color set.
            \param another Another font and color set.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font_color_set& one, const font_color_set& another)
        {
            return
                one.m_background == another.m_background &&
                one.m_general == another.m_general &&
                one.m_company_name == another.m_company_name &&
                one.m_line_name == another.m_line_name &&
                one.m_note == another.m_note &&
                one.m_local_station == another.m_local_station &&
                one.m_principal_station == another.m_principal_station &&
                one.m_local_terminal_station == another.m_local_terminal_station &&
                one.m_principal_terminal_station == another.m_principal_terminal_station;
        }

        /*!
            \brief Returns the font and color for the background.

            \return The font and color for the background.
        */
        const font_color_type& background()
        const
        {
            return m_background;
        }

        /*!
            \brief Returns the font and color for the general item.

            \return The font and color for the general item.
        */
        const font_color_type& general()
        const
        {
            return m_general;
        }

        /*!
            \brief Returns the font and color for the company names.

            \return The font and color for the company names.
        */
        const font_color_type& company_name()
        const
        {
            return m_company_name;
        }

        /*!
            \brief Returns the font and color for the line name.

            \return The font and color for the line name.
        */
        const font_color_type& line_name()
        const
        {
            return m_line_name;
        }

        /*!
            \brief Returns the font and color for the note.

            \return The font and color for the note.
        */
        const font_color_type& note()
        const
        {
            return m_note;
        }

        /*!
            \brief Returns the font and color for the local station.

            \return The font and color for the local station.
        */
        const font_color_type& local_station()
        const
        {
            return m_local_station;
        }

        /*!
            \brief Returns the font and color for the principal station.

            \return The font and color for the principal station.
        */
        const font_color_type& principal_station()
        const
        {
            return m_principal_station;
        }

        /*!
            \brief Returns the font and color for the local terminal station.

            \return The font and color for the local terminal station.
        */
        const font_color_type& local_terminal_station()
        const
        {
            return m_local_terminal_station;
        }

        /*!
            \brief Returns the font and color for the principal terminal station.

            \return The font and color for the principal terminal station.
        */
        const font_color_type& principal_terminal_station()
        const
        {
            return m_principal_terminal_station;
        }


    private:
        // static functions

        static font_color_set make_default()
        {
            auto default_font = font_type::dialog_font();
            font_type default_company_line_name_font{
                default_font.family(),
                default_font.size() * 2,
                default_font.bold(),
                default_font.italic(),
                default_font.underline(),
                default_font.strikeout()
            };

            font_color_type default_background_font_color{
                boost::none,
                boost::make_optional(color_type{ 0xF8, 0xFF, 0xF0 }),
                boost::none,
                boost::make_optional(color_type{ 0xF8, 0xFF, 0xF0 })

            };
            font_color_type default_general_font_color{
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x80, 0x80, 0x80 }),
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x40, 0x40, 0x40 })
            };
            font_color_type default_company_name_font_color{
                boost::make_optional(std::move(default_company_line_name_font)),
                boost::make_optional(color_type{ 0x40, 0x40, 0x40 }),
                boost::make_optional(std::move(default_company_line_name_font)),
                boost::make_optional(color_type{ 0x40, 0x40, 0x40 })
            };
            font_color_type default_line_name_font_color{
                boost::make_optional(std::move(default_company_line_name_font)),
                boost::make_optional(color_type{ 0x40, 0x40, 0x40 }),
                boost::make_optional(std::move(default_company_line_name_font)),
                boost::make_optional(color_type{ 0x40, 0x40, 0x40 })
            };
            font_color_type default_note_font_color{
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x40, 0x40, 0x40 }),
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x40, 0x40, 0x40 })
            };
            font_color_type default_local_station_font_color{
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0xA0, 0xA0, 0xA0 }),
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0xA0, 0xA0, 0xA0 })
            };
            font_color_type default_principal_station_font_color{
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x40, 0x40, 0xA0 }),
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x40, 0x40, 0xA0 })
            };
            font_color_type default_local_terminal_station_font_color{
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0xA0, 0x40, 0x40 }),
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0xA0, 0x40, 0x40 })
            };
            font_color_type default_principal_terminal_station_font_color(
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x00, 0x00, 0x00 }),
                boost::make_optional(default_font),
                boost::make_optional(color_type{ 0x00, 0x00, 0x00 })
            );

            return
                font_color_set{
                    std::move(default_background_font_color),
                    std::move(default_general_font_color),
                    std::move(default_company_name_font_color),
                    std::move(default_line_name_font_color),
                    std::move(default_note_font_color),
                    std::move(default_local_station_font_color),
                    std::move(default_principal_station_font_color),
                    std::move(default_local_terminal_station_font_color),
                    std::move(default_principal_terminal_station_font_color)
                };
        }


        // variables

        font_color_type m_background;

        font_color_type m_general;

        font_color_type m_company_name;

        font_color_type m_line_name;

        font_color_type m_note;

        font_color_type m_local_station;

        font_color_type m_principal_station;

        font_color_type m_local_terminal_station;

        font_color_type m_principal_terminal_station;


    };


}}}


#endif
