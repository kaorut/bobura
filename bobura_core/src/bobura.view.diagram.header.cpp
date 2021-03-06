/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/header.h>


namespace bobura::view::diagram {
    template <typename Traits>
    class company_name_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;

        using selection_type = typename company_name_header::selection_type;


        // constructors and destructor

        impl(
            selection_type&,
            string_type       company_name,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension)
        : m_company_name{ std::move(company_name) }, m_p_font{ &font }, m_p_color{ &color },
          m_position{ std::move(position) }, m_dimension{ std::move(dimension) }
        {}

        impl(impl&& another)
        : m_company_name{ std::move(another.m_company_name) }, m_p_font{ another.m_p_font },
          m_p_color{ another.m_p_color }, m_position{ std::move(another.m_position) }, m_dimension{ std::move(
                                                                                           another.m_dimension) }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_company_name = std::move(another.m_company_name);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas) const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);
            canvas.draw_text(m_company_name, m_position);
        }


    private:
        // variables

        string_type m_company_name;

        const font_type* m_p_font;

        const color_type* m_p_color;

        position_type m_position;

        dimension_type m_dimension;
    };


    template <typename Traits>
    company_name_header<Traits>::company_name_header(
        selection_type&   selection,
        string_type       company_name,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension)
    : base_type{ selection }, m_p_impl{ std::make_unique<impl>(
                                  selection,
                                  std::move(company_name),
                                  font,
                                  color,
                                  std::move(position),
                                  std::move(dimension)) }
    {}

    template <typename Traits>
    company_name_header<Traits>::company_name_header(company_name_header&& another)
    : base_type{ another.get_selection() }, m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    company_name_header<Traits>::~company_name_header() noexcept
    {}

    template <typename Traits>
    company_name_header<Traits>& company_name_header<Traits>::operator=(company_name_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void company_name_header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    template <typename Traits>
    class line_name_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;

        using selection_type = typename line_name_header::selection_type;


        // constructors and destructor

        impl(
            selection_type&,
            string_type       line_name,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension)
        : m_line_name{ std::move(line_name) }, m_p_font{ &font }, m_p_color{ &color },
          m_position{ std::move(position) }, m_dimension{ std::move(dimension) }
        {}

        impl(impl&& another)
        : m_line_name{ std::move(another.m_line_name) }, m_p_font{ another.m_p_font }, m_p_color{ another.m_p_color },
          m_position{ std::move(another.m_position) }, m_dimension{ std::move(another.m_dimension) }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_line_name = std::move(another.m_line_name);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas) const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);
            canvas.draw_text(m_line_name, m_position);
        }


    private:
        // variables

        string_type m_line_name;

        const font_type* m_p_font;

        const color_type* m_p_color;

        position_type m_position;

        dimension_type m_dimension;
    };


    template <typename Traits>
    line_name_header<Traits>::line_name_header(
        selection_type&   selection,
        string_type       line_name,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension)
    : base_type{ selection }, m_p_impl{ std::make_unique<impl>(
                                  selection,
                                  std::move(line_name),
                                  font,
                                  color,
                                  std::move(position),
                                  std::move(dimension)) }
    {}

    template <typename Traits>
    line_name_header<Traits>::line_name_header(line_name_header&& another)
    : base_type{ another.get_selection() }, m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    line_name_header<Traits>::~line_name_header() noexcept
    {}

    template <typename Traits>
    line_name_header<Traits>& line_name_header<Traits>::operator=(line_name_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void line_name_header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    template <typename Traits>
    class note_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;

        using selection_type = typename note_header::selection_type;


        // constructors and destructor

        impl(
            selection_type&,
            string_type       note,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension)
        : m_note{ std::move(note) }, m_p_font{ &font }, m_p_color{ &color }, m_position{ std::move(position) },
          m_dimension{ std::move(dimension) }
        {}

        impl(impl&& another)
        : m_note{ std::move(another.m_note) }, m_p_font{ another.m_p_font }, m_p_color{ another.m_p_color },
          m_position{ std::move(another.m_position) }, m_dimension{ std::move(another.m_dimension) }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_note = std::move(another.m_note);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas) const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);
            canvas.draw_text(m_note, m_position);
        }


    private:
        // variables

        string_type m_note;

        const font_type* m_p_font;

        const color_type* m_p_color;

        position_type m_position;

        dimension_type m_dimension;
    };


    template <typename Traits>
    note_header<Traits>::note_header(
        selection_type&   selection,
        string_type       note,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension)
    : base_type{ selection }, m_p_impl{
          std::make_unique<impl>(selection, std::move(note), font, color, std::move(position), std::move(dimension))
      }
    {}

    template <typename Traits>
    note_header<Traits>::note_header(note_header&& another)
    : base_type{ another.get_selection() }, m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    note_header<Traits>::~note_header() noexcept
    {}


    template <typename Traits>
    note_header<Traits>& note_header<Traits>::operator=(note_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void note_header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    template <typename Traits>
    class header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using dimension_type = typename canvas_type::dimension_type;

        using selection_type = typename header::selection_type;

        using model_type = typename header::model_type;


        // constructors and destructor

        impl(
            const model_type&     model,
            selection_type&       selection,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension)
        : m_p_company_name_header{}, m_p_line_name_header{}, m_p_note_header{}, m_position{}, m_dimension{}
        {
            const auto&    company_name = model.timetable().company_name();
            const auto&    company_name_font = *model.timetable().font_color_set().company_name().diagram_font();
            const auto&    line_name = model.timetable().line_name();
            const auto&    line_name_font = *model.timetable().font_color_set().line_name().diagram_font();
            const auto&    note = model.timetable().note();
            const auto&    note_font = *model.timetable().font_color_set().note().diagram_font();
            position_type  company_name_position{};
            dimension_type company_name_dimension{};
            position_type  line_name_position{};
            dimension_type line_name_dimension{};
            position_type  note_position{};
            dimension_type note_dimension{};
            calculate_positions_and_dimensions(
                canvas,
                canvas_dimension,
                company_name,
                company_name_font,
                line_name,
                line_name_font,
                note,
                note_font,
                company_name_position,
                company_name_dimension,
                line_name_position,
                line_name_dimension,
                note_position,
                note_dimension,
                m_position,
                m_dimension);

            const auto& company_name_color = *model.timetable().font_color_set().company_name().diagram_color();
            m_p_company_name_header = std::make_unique<company_name_header_type>(
                selection,
                std::move(company_name),
                company_name_font,
                company_name_color,
                std::move(company_name_position),
                std::move(company_name_dimension));
            const auto& line_name_color = *model.timetable().font_color_set().line_name().diagram_color();
            m_p_line_name_header = std::make_unique<line_name_header_type>(
                selection,
                std::move(line_name),
                line_name_font,
                line_name_color,
                std::move(line_name_position),
                std::move(line_name_dimension));
            const auto& note_color = *model.timetable().font_color_set().note().diagram_color();
            m_p_note_header = std::make_unique<note_header_type>(
                selection, std::move(note), note_font, note_color, std::move(note_position), std::move(note_dimension));
        }

        impl(impl&& another)
        : m_p_company_name_header{ std::move(another.m_p_company_name_header) }, m_p_line_name_header{ std::move(
                                                                                     another.m_p_line_name_header) },
          m_p_note_header{ std::move(another.m_p_note_header) }, m_position{ std::move(another.m_position) },
          m_dimension{ std::move(another.m_dimension) }
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_company_name_header = std::move(another.m_p_company_name_header);
            m_p_line_name_header = std::move(another.m_p_line_name_header);
            m_p_note_header = std::move(another.m_p_note_header);
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        const dimension_type& dimension() const
        {
            return m_dimension;
        }

        void draw_on_impl(canvas_type& canvas) const
        {
            assert(m_p_company_name_header);
            m_p_company_name_header->draw_on(canvas);

            assert(m_p_line_name_header);
            m_p_line_name_header->draw_on(canvas);

            assert(m_p_note_header);
            m_p_note_header->draw_on(canvas);
        }


    private:
        // types

        using company_name_header_type = company_name_header<traits_type>;

        using line_name_header_type = line_name_header<traits_type>;

        using note_header_type = note_header<traits_type>;

        using string_type = typename traits_type::string_type;

        using font_type = typename canvas_type::font_type;

        using position_type = typename canvas_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;


        // static functions

        static void calculate_positions_and_dimensions(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const string_type&    company_name,
            const font_type&      company_name_font,
            const string_type&    line_name,
            const font_type&      line_name_font,
            const string_type&    note,
            const font_type&      note_font,
            position_type&        company_name_position,
            dimension_type&       company_name_dimension,
            position_type&        line_name_position,
            dimension_type&       line_name_dimension,
            position_type&        note_position,
            dimension_type&       note_dimension,
            position_type&        position,
            dimension_type&       dimension)
        {
            const auto& canvas_width = canvas_dimension.width();

            canvas.set_font(company_name_font);
            auto        company_name_dimension_ = canvas.calc_text_dimension(company_name);
            const auto& company_name_width = company_name_dimension_.width();
            const auto& company_name_height =
                company_name.empty() ? dimension_unit_type{} : company_name_dimension_.height();

            canvas.set_font(line_name_font);
            auto        line_name_dimension_ = canvas.calc_text_dimension(line_name);
            const auto& line_name_width = line_name_dimension_.width();
            const auto& line_name_height = line_name.empty() ? dimension_unit_type{} : line_name_dimension_.height();

            canvas.set_font(note_font);
            const auto  note_dimension_ = canvas.calc_text_dimension(note);
            const auto& note_width = note_dimension_.width();
            const auto& note_height = note.empty() ? dimension_unit_type{} : note_dimension_.height();

            const position_unit_type line_names_spacing{ 1 };

            position_type       company_name_position_{};
            position_type       line_name_position_{};
            position_type       note_position_{};
            const auto&         header_width = canvas_width;
            dimension_unit_type header_height{};
            if (company_name_width + line_name_width + note_width + line_names_spacing <= canvas_width)
            {
                const auto max_element_height = std::max({ company_name_height, line_name_height, note_height });
                company_name_position_ =
                    position_type{ position_unit_type{},
                                   position_unit_type::from(max_element_height - company_name_height) / 2 };
                line_name_position_ =
                    position_type{ position_unit_type::from(company_name_width) + line_names_spacing,
                                   position_unit_type::from(max_element_height - line_name_height) / 2 };
                note_position_ = position_type{ position_unit_type::from(canvas_width - note_width),
                                                position_unit_type::from(max_element_height - note_height) / 2 };
                header_height = max_element_height;
            }
            else if (company_name_width + line_name_width + line_names_spacing <= canvas_width)
            {
                const auto max_element_height = std::max({ company_name_height, line_name_height });
                company_name_position_ =
                    position_type{ position_unit_type{},
                                   position_unit_type::from(max_element_height - company_name_height) / 2 };
                line_name_position_ =
                    position_type{ position_unit_type::from(company_name_width) + line_names_spacing,
                                   position_unit_type::from(max_element_height - line_name_height) / 2 };
                note_position_ = position_type{ position_unit_type{}, position_unit_type::from(max_element_height) };
                header_height = max_element_height + note_height;
            }
            else
            {
                company_name_position_ = position_type{};
                line_name_position_ =
                    position_type{ position_unit_type{}, position_unit_type::from(company_name_height) };
                note_position_ = position_type{ position_unit_type{},
                                                position_unit_type::from(company_name_height + line_name_height) };
                header_height = company_name_height + line_name_height + note_height;
            }

            company_name_position = std::move(company_name_position_);
            company_name_dimension = std::move(company_name_dimension_);
            line_name_position = std::move(line_name_position_);
            line_name_dimension = std::move(line_name_dimension_);
            note_position = std::move(note_position_);
            note_dimension = std::move(note_dimension_);
            position = position_type{};
            dimension = dimension_type{ std::move(header_width), std::move(header_height) };
        }


        // variables

        std::unique_ptr<company_name_header_type> m_p_company_name_header;

        std::unique_ptr<line_name_header_type> m_p_line_name_header;

        std::unique_ptr<note_header_type> m_p_note_header;

        position_type m_position;

        dimension_type m_dimension;
    };


    template <typename Traits>
    header<Traits>::header(
        const model_type&     model,
        selection_type&       selection,
        canvas_type&          canvas,
        const dimension_type& canvas_dimension)
    : base_type{ selection }, m_p_impl{ std::make_unique<impl>(model, selection, canvas, canvas_dimension) }
    {}

    template <typename Traits>
    header<Traits>::header(header&& another)
    : base_type{ another.get_selection() }, m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename Traits>
    header<Traits>::~header() noexcept
    {}

    template <typename Traits>
    header<Traits>& header<Traits>::operator=(header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    const typename header<Traits>::dimension_type& header<Traits>::dimension() const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void header<Traits>::draw_on_impl(canvas_type& canvas) const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class company_name_header<typename application::traits_type_list_type::diagram_view_type>;

    template class line_name_header<typename application::traits_type_list_type::diagram_view_type>;

    template class note_header<typename application::traits_type_list_type::diagram_view_type>;

    template class header<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class company_name_header<typename test::traits_type_list_type::diagram_view_type>;

    template class line_name_header<typename test::traits_type_list_type::diagram_view_type>;

    template class note_header<typename test::traits_type_list_type::diagram_view_type>;

    template class header<typename test::traits_type_list_type::diagram_view_type>;
}
