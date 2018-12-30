/*! \file
    \brief The definition of bobura::model::train_kind.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <string>
#include <utility>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>

#include <bobura/model/train_kind.h>


namespace {
    bobura::model::train_kind make_default()
    {
        const auto& default_font = bobura::model::train_kind::font_type::dialog_font();
        return bobura::model::train_kind{ bobura::model::train_kind::string_type{},
                                          bobura::model::train_kind::string_type{},
                                          default_font,
                                          bobura::model::train_kind::color_type{ 0x00, 0x00, 0x00 },
                                          bobura::model::train_kind::weight_type::normal,
                                          bobura::model::train_kind::line_style_type::solid,
                                          default_font,
                                          bobura::model::train_kind::color_type{ 0x00, 0x00, 0x00 } };
    }
}


namespace bobura::model {
    const train_kind& train_kind::default_()
    {
        static auto singleton = make_default();
        return singleton;
    }

    train_kind::train_kind(
        string_type           name,
        string_type           abbreviation,
        font_type             diagram_font,
        color_type            diagram_color,
        const weight_type     diagram_line_weight,
        const line_style_type diagram_line_style,
        font_type             timetable_font,
        color_type            timetable_color)
    : m_name{ std::move(name) }, m_abbreviation{ std::move(abbreviation) }, m_diagram_font{ std::move(diagram_font) },
      m_diagram_color{ std::move(diagram_color) }, m_diagram_line_weight{ diagram_line_weight },
      m_diagram_line_style{ diagram_line_style }, m_timetable_font{ std::move(timetable_font) }, m_timetable_color{
          std::move(timetable_color)
      }
    {}

    bool operator==(const train_kind& one, const train_kind& another)
    {
        return one.m_name == another.m_name && one.m_abbreviation == another.m_abbreviation &&
               one.m_diagram_font == another.m_diagram_font && one.m_diagram_color == another.m_diagram_color &&
               one.m_diagram_line_weight == another.m_diagram_line_weight &&
               one.m_diagram_line_style == another.m_diagram_line_style &&
               one.m_timetable_font == another.m_timetable_font && one.m_timetable_color == another.m_timetable_color;
    }

    const train_kind::string_type& train_kind::name() const
    {
        return m_name;
    }

    const train_kind::string_type& train_kind::abbreviation() const
    {
        return m_abbreviation;
    }

    const train_kind::font_type& train_kind::diagram_font() const
    {
        return m_diagram_font;
    }

    const train_kind::color_type& train_kind::diagram_color() const
    {
        return m_diagram_color;
    }

    train_kind::weight_type train_kind::diagram_line_weight() const
    {
        return m_diagram_line_weight;
    }

    train_kind::line_style_type train_kind::diagram_line_style() const
    {
        return m_diagram_line_style;
    }

    const train_kind::font_type& train_kind::timetable_font() const
    {
        return m_timetable_font;
    }

    const train_kind::color_type& train_kind::timetable_color() const
    {
        return m_timetable_color;
    }
}
