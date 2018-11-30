/*! \file
    \brief The definition of bobura::model::timetable_info::font_color_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/operators.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/stdalt.h>

#include <bobura/model/timetable_info/font_color_set.h>


namespace bobura::model::timetable_info {
    class font_color::impl
    {
    public:
        // types

        using font_type = font_color::font_type;

        using color_type = font_color::color_type;


        // constructors and destructor

        impl(
            tetengo2::stdalt::optional<font_type>  diagram_font,
            tetengo2::stdalt::optional<color_type> diagram_color,
            tetengo2::stdalt::optional<font_type>  timetable_font,
            tetengo2::stdalt::optional<color_type> timetable_color)
        : m_diagram_font{ std::move(diagram_font) }, m_diagram_color{ std::move(diagram_color) },
          m_timetable_font{ std::move(timetable_font) }, m_timetable_color{ std::move(timetable_color) }
        {}


        // functions

        friend bool operator_equal(const impl& one, const impl& another)
        {
            return one.m_diagram_font == another.m_diagram_font && one.m_diagram_color == another.m_diagram_color &&
                   one.m_timetable_font == another.m_timetable_font &&
                   one.m_timetable_color == another.m_timetable_color;
        }

        font_color& operator_assign(const impl& another, font_color& self)
        {
            m_diagram_font = another.m_diagram_font;
            m_diagram_color = another.m_diagram_color;
            m_timetable_font = another.m_timetable_font;
            m_timetable_color = another.m_timetable_color;

            return self;
        }

        font_color& operator_assign(impl&& another, font_color& self)
        {
            m_diagram_font = std::move(another.m_diagram_font);
            m_diagram_color = std::move(another.m_diagram_color);
            m_timetable_font = std::move(another.m_timetable_font);
            m_timetable_color = std::move(another.m_timetable_color);

            return self;
        }

        const tetengo2::stdalt::optional<font_type>& diagram_font() const
        {
            return m_diagram_font;
        }

        const tetengo2::stdalt::optional<color_type>& diagram_color() const
        {
            return m_diagram_color;
        }

        const tetengo2::stdalt::optional<font_type>& timetable_font() const
        {
            return m_timetable_font;
        }

        const tetengo2::stdalt::optional<color_type>& timetable_color() const
        {
            return m_timetable_color;
        }


    private:
        // variables

        tetengo2::stdalt::optional<font_type> m_diagram_font;

        tetengo2::stdalt::optional<color_type> m_diagram_color;

        tetengo2::stdalt::optional<font_type> m_timetable_font;

        tetengo2::stdalt::optional<color_type> m_timetable_color;
    };


    font_color::font_color(
        tetengo2::stdalt::optional<font_type>  diagram_font,
        tetengo2::stdalt::optional<color_type> diagram_color,
        tetengo2::stdalt::optional<font_type>  timetable_font,
        tetengo2::stdalt::optional<color_type> timetable_color)
    : m_p_impl{ std::make_unique<impl>(
          std::move(diagram_font),
          std::move(diagram_color),
          std::move(timetable_font),
          std::move(timetable_color)) }
    {}

    font_color::font_color(const font_color& another) : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) } {}

    font_color::font_color(font_color&& another) : m_p_impl{ std::move(another.m_p_impl) } {}

    font_color::~font_color() = default;

    bool operator==(const font_color& one, const font_color& another)
    {
        return operator_equal(*one.m_p_impl, *another.m_p_impl);
    }

    font_color& font_color::operator=(const font_color& another)
    {
        return m_p_impl->operator_assign(*another.m_p_impl, *this);
    }

    font_color& font_color::operator=(font_color&& another)
    {
        return m_p_impl->operator_assign(std::move(*another.m_p_impl), *this);
    }

    const tetengo2::stdalt::optional<font_color::font_type>& font_color::diagram_font() const
    {
        return m_p_impl->diagram_font();
    }

    const tetengo2::stdalt::optional<font_color::color_type>& font_color::diagram_color() const
    {
        return m_p_impl->diagram_color();
    }

    const tetengo2::stdalt::optional<font_color::font_type>& font_color::timetable_font() const
    {
        return m_p_impl->timetable_font();
    }

    const tetengo2::stdalt::optional<font_color::color_type>& font_color::timetable_color() const
    {
        return m_p_impl->timetable_color();
    }


    class font_color_set::impl
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

        static const font_color_set& default_()
        {
            static auto singleton = make_default();
            return singleton;
        }


        // constructors and destructor

        impl(
            font_color_type background,
            font_color_type general,
            font_color_type company_name,
            font_color_type line_name,
            font_color_type note,
            font_color_type local_station,
            font_color_type principal_station,
            font_color_type local_terminal_station,
            font_color_type principal_terminal_station)
        : m_background{ std::move(background) }, m_general{ std::move(general) },
          m_company_name{ std::move(company_name) }, m_line_name{ std::move(line_name) }, m_note{ std::move(note) },
          m_local_station{ std::move(local_station) }, m_principal_station{ std::move(principal_station) },
          m_local_terminal_station{ std::move(local_terminal_station) }, m_principal_terminal_station{ std::move(
                                                                             principal_terminal_station) }
        {}


        // functions

        friend bool operator_equal(const impl& one, const impl& another)
        {
            return one.m_background == another.m_background && one.m_general == another.m_general &&
                   one.m_company_name == another.m_company_name && one.m_line_name == another.m_line_name &&
                   one.m_note == another.m_note && one.m_local_station == another.m_local_station &&
                   one.m_principal_station == another.m_principal_station &&
                   one.m_local_terminal_station == another.m_local_terminal_station &&
                   one.m_principal_terminal_station == another.m_principal_terminal_station;
        }

        font_color_set& operator_assign(const impl& another, font_color_set& self)
        {
            m_background = another.m_background;
            m_general = another.m_general;
            m_company_name = another.m_company_name;
            m_line_name = another.m_line_name;
            m_note = another.m_note;
            m_local_station = another.m_local_station;
            m_principal_station = another.m_principal_station;
            m_local_terminal_station = another.m_local_terminal_station;
            m_principal_terminal_station = another.m_principal_terminal_station;

            return self;
        }

        font_color_set& operator_assign(impl&& another, font_color_set& self)
        {
            m_background = std::move(another.m_background);
            m_general = std::move(another.m_general);
            m_company_name = std::move(another.m_company_name);
            m_line_name = std::move(another.m_line_name);
            m_note = std::move(another.m_note);
            m_local_station = std::move(another.m_local_station);
            m_principal_station = std::move(another.m_principal_station);
            m_local_terminal_station = std::move(another.m_local_terminal_station);
            m_principal_terminal_station = std::move(another.m_principal_terminal_station);

            return self;
        }

        const font_color_type& background() const
        {
            return m_background;
        }

        const font_color_type& general() const
        {
            return m_general;
        }

        const font_color_type& company_name() const
        {
            return m_company_name;
        }

        const font_color_type& line_name() const
        {
            return m_line_name;
        }

        const font_color_type& note() const
        {
            return m_note;
        }

        const font_color_type& local_station() const
        {
            return m_local_station;
        }

        const font_color_type& principal_station() const
        {
            return m_principal_station;
        }

        const font_color_type& local_terminal_station() const
        {
            return m_local_terminal_station;
        }

        const font_color_type& principal_terminal_station() const
        {
            return m_principal_terminal_station;
        }


    private:
        // static functions

        static font_color_set make_default()
        {
            auto            default_font = font_type::dialog_font();
            const font_type default_company_line_name_font{ default_font.family(),    default_font.size() * 2,
                                                            default_font.bold(),      default_font.italic(),
                                                            default_font.underline(), default_font.strikeout() };

            font_color_type default_background_font_color{
                TETENGO2_STDALT_NULLOPT,
                tetengo2::stdalt::make_optional(color_type{ 0xF8, 0xFF, 0xF0 }),
                TETENGO2_STDALT_NULLOPT,
                tetengo2::stdalt::make_optional(color_type{ 0xF8, 0xFF, 0xF0 })

            };
            font_color_type default_general_font_color{ tetengo2::stdalt::make_optional(font_type{ default_font }),
                                                        tetengo2::stdalt::make_optional(color_type{ 0x80, 0x80, 0x80 }),
                                                        tetengo2::stdalt::make_optional(font_type{ default_font }),
                                                        tetengo2::stdalt::make_optional(
                                                            color_type{ 0x40, 0x40, 0x40 }) };
            font_color_type default_company_name_font_color{
                tetengo2::stdalt::make_optional(font_type{ default_company_line_name_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0x40 }),
                tetengo2::stdalt::make_optional(font_type{ default_company_line_name_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0x40 })
            };
            font_color_type default_line_name_font_color{
                tetengo2::stdalt::make_optional(font_type{ default_company_line_name_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0x40 }),
                tetengo2::stdalt::make_optional(font_type{ default_company_line_name_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0x40 })
            };
            font_color_type default_note_font_color{ tetengo2::stdalt::make_optional(font_type{ default_font }),
                                                     tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0x40 }),
                                                     tetengo2::stdalt::make_optional(font_type{ default_font }),
                                                     tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0x40 }) };
            font_color_type default_local_station_font_color{
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0xA0, 0xA0, 0xA0 }),
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0xA0, 0xA0, 0xA0 })
            };
            font_color_type default_principal_station_font_color{
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0xA0 }),
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x40, 0x40, 0xA0 })
            };
            font_color_type default_local_terminal_station_font_color{
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0xA0, 0x40, 0x40 }),
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0xA0, 0x40, 0x40 })
            };
            font_color_type default_principal_terminal_station_font_color(
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x00, 0x00, 0x00 }),
                tetengo2::stdalt::make_optional(font_type{ default_font }),
                tetengo2::stdalt::make_optional(color_type{ 0x00, 0x00, 0x00 }));

            return font_color_set{ std::move(default_background_font_color),
                                   std::move(default_general_font_color),
                                   std::move(default_company_name_font_color),
                                   std::move(default_line_name_font_color),
                                   std::move(default_note_font_color),
                                   std::move(default_local_station_font_color),
                                   std::move(default_principal_station_font_color),
                                   std::move(default_local_terminal_station_font_color),
                                   std::move(default_principal_terminal_station_font_color) };
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


    const font_color_set& font_color_set::default_()
    {
        return impl::default_();
    }

    font_color_set::font_color_set(
        font_color_type background,
        font_color_type general,
        font_color_type company_name,
        font_color_type line_name,
        font_color_type note,
        font_color_type local_station,
        font_color_type principal_station,
        font_color_type local_terminal_station,
        font_color_type principal_terminal_station)
    : m_p_impl{ std::make_unique<impl>(
          std::move(background),
          std ::move(general),
          std ::move(company_name),
          std ::move(line_name),
          std ::move(note),
          std ::move(local_station),
          std ::move(principal_station),
          std::move(local_terminal_station),
          std::move(principal_terminal_station)) }
    {}

    font_color_set::font_color_set(const font_color_set& another)
    : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) }
    {}

    font_color_set::font_color_set(font_color_set&& another) : m_p_impl{ std::move(another.m_p_impl) } {}

    font_color_set::~font_color_set() = default;

    bool operator==(const font_color_set& one, const font_color_set& another)
    {
        return operator_equal(*one.m_p_impl, *another.m_p_impl);
    }

    font_color_set& font_color_set::operator=(const font_color_set& another)
    {
        return m_p_impl->operator_assign(*another.m_p_impl, *this);
    }

    font_color_set& font_color_set::operator=(font_color_set&& another)
    {
        return m_p_impl->operator_assign(std::move(*another.m_p_impl), *this);
    }

    const font_color_set::font_color_type& font_color_set::background() const
    {
        return m_p_impl->background();
    }

    const font_color_set::font_color_type& font_color_set::general() const
    {
        return m_p_impl->general();
    }

    const font_color_set::font_color_type& font_color_set::company_name() const
    {
        return m_p_impl->company_name();
    }

    const font_color_set::font_color_type& font_color_set::line_name() const
    {
        return m_p_impl->line_name();
    }

    const font_color_set::font_color_type& font_color_set::note() const
    {
        return m_p_impl->note();
    }

    const font_color_set::font_color_type& font_color_set::local_station() const
    {
        return m_p_impl->local_station();
    }

    const font_color_set::font_color_type& font_color_set::principal_station() const
    {
        return m_p_impl->principal_station();
    }

    const font_color_set::font_color_type& font_color_set::local_terminal_station() const
    {
        return m_p_impl->local_terminal_station();
    }

    const font_color_set::font_color_type& font_color_set::principal_terminal_station() const
    {
        return m_p_impl->principal_terminal_station();
    }
}
