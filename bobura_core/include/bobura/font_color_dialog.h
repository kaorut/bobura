/*! \file
    \brief The definition of bobura::font_color_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_FONTCOLORDIALOG_H)
#define BOBURA_FONTCOLORDIALOG_H

#include <memory>

#include <boost/optional.hpp>


namespace bobura
{
    /*!
        \brief The class template for the font and color dialog.

        \tparam Traits             A traits type.
        \tparam Size               An integer size type.
        \tparam Font               A font type.
        \tparam PointDimensionUnit A point dimension unit type.
        \tparam Color              A color type.
        \tparam Canvas             A canvas type.
        \tparam FontDialog         A font dialog type.
        \tparam ColorDialog        A color dialog type.
    */
    template <
        typename Traits,
        typename Size,
        typename Font,
        typename PointDimensionUnit,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog
    >
    class font_color_dialog : public Traits::dialog_type
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = typename traits_type::dialog_type;

        //! The abstract window type.
        using abstract_window_type = typename traits_type::abstract_window_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The size type.
        using size_type = Size;

        //! The font type.
        using font_type = Font;

        //! The point dimension unit type.
        using point_dimension_unit_type = PointDimensionUnit;

        //! The color type.
        using color_type = Color;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The font dialog type.
        using font_dialog_type = FontDialog;

        //! The color dialog type.
        using color_dialog_type = ColorDialog;

        //! The font and color type.
        class font_color_type
        {
        public:
            // constructors and destructors

            /*!
                \brief Creates a font and color.
            */
            font_color_type()
            :
            m_diagram_font(),
            m_diagram_color(),
            m_timetable_font(),
            m_timetable_color()
            {}

            /*!
                \brief Creates a font and color.

                \param diagram_font    A font for the diagram.
                \param diagram_color   A color for the diagram.
                \param timetable_font  A font for the timetable.
                \param timetable_color A color for the timetable.
            */
            font_color_type(
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
            friend bool operator==(const font_color_type& one, const font_color_type& another)
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
                \brief Sets a font for the diagram.

                \param diagram_font A font for the diagram.
            */
            void set_diagram_font(boost::optional<font_type> diagram_font)
            {
                m_diagram_font = std::move(diagram_font);
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
                \brief Sets a color for the diagram.

                \param diagram_color A color for the diagram.
            */
            void set_diagram_color(boost::optional<color_type> diagram_color)
            {
                m_diagram_color = std::move(diagram_color);
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
                \brief Sets a font for the timetable.

                \param timetable_font A font for the timetable.
            */
            void set_timetable_font(boost::optional<font_type> timetable_font)
            {
                m_timetable_font = std::move(timetable_font);
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

            /*!
                \brief Sets a color for the timetable.

                \param timetable_color A color for the timetable.
            */
            void set_timetable_color(boost::optional<color_type> timetable_color)
            {
                m_timetable_color = std::move(timetable_color);
            }


        private:
            // variables

            boost::optional<font_type>  m_diagram_font;

            boost::optional<color_type> m_diagram_color;

            boost::optional<font_type>  m_timetable_font;

            boost::optional<color_type> m_timetable_color;


        };


        // constructors and destructor

        /*!
            \brief Creates a font and color dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        font_color_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the font and color dialog.
        */
        virtual ~font_color_dialog()
        noexcept;


        // functions

        /*!
            \brief Returns the color of the background.

            \return The font and color of the background.
        */
        const font_color_type& background()
        const;

        /*!
            \brief Sets a color of the background.

            \param font_color A font and color.
        */
        void set_background(font_color_type font_color);

        /*!
            \brief Returns the font and color of the general item.

            \return The font and color of the general item.
        */
        const font_color_type& general()
        const;

        /*!
            \brief Sets a font and color of the general items in the general.

            \param font_color A font and color.
        */
        void set_general(font_color_type font_color);

        /*!
            \brief Returns the font and color of the company name.

            \return The font and color of the company name.
        */
        const font_color_type& company_name()
        const;

        /*!
            \brief Sets a font and color of the company names.

            \param font_color A font and color.
        */
        void set_company_name(font_color_type font_color);

        /*!
            \brief Returns the font and color of the line name.

            \return The font and color of the line name.
        */
        const font_color_type& line_name()
        const;

        /*!
            \brief Sets a font and color of the line name.

            \param font_color A font and color.
        */
        void set_line_name(font_color_type font_color);

        /*!
            \brief Returns the font and color of the note.

            \return The font and color of the note.
        */
        const font_color_type& note()
        const;

        /*!
            \brief Sets a font and color of the note.

            \param font_color A font and color.
        */
        void set_note(font_color_type font_color);

        /*!
            \brief Returns the font and color of the local stations.

            \return The font and color of the local stations.
        */
        const font_color_type& local_station()
        const;

        /*!
            \brief Sets a font and color of the local stations.

            \param font_color A font and color.
        */
        void set_local_station(font_color_type font_color);

        /*!
            \brief Returns the font and color of the principal stations.

            \return The font and color of the principal stations.
        */
        const font_color_type& principal_station()
        const;

        /*!
            \brief Sets a font and color of the principal stations.

            \param font_color A font and color.
        */
        void set_principal_station(font_color_type font_color);

        /*!
            \brief Returns the font and color of the local terminal stations.

            \return The font and color of the local terminal stations.
        */
        const font_color_type& local_terminal_station()
        const;

        /*!
            \brief Sets a font and color of the local terminal stations.

            \param font_color A font and color.
        */
        void set_local_terminal_station(font_color_type font_color);

        /*!
            \brief Returns the font and color of the principal terminal stations.

            \return The font and color of the principal terminal stations.
        */
        const font_color_type& principal_terminal_station()
        const;

        /*!
            \brief Sets a font and color of the principal terminal stations.

            \param font_color A font and color.
        */
        void set_principal_terminal_station(font_color_type font_color);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void do_modal_impl()
        override;


    };


}


#endif
