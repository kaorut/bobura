/*! \file
    \brief The definition of bobura::view::timetable::header.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/format.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/type_list.h>
#include <bobura/view/timetable/header.h>
#include <bobura/view/timetable/utility.h>


namespace bobura { namespace view { namespace timetable
{
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


        // constructors and destructor

        impl(
            string_type       company_name,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        )
        :
        m_company_name(std::move(company_name)),
        m_p_font(&font),
        m_p_color(&color),
        m_position(std::move(position)),
        m_dimension(std::move(dimension))
        {}

        impl(impl&& another)
        :
        m_company_name(std::move(another.m_company_name)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
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

        void draw_on_impl(canvas_type& canvas)
        const
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
        string_type       company_name,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension
    )
    :
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            std::move(company_name), font, color, std::move(position), std::move(dimension)
        )
    )
    {}

    template <typename Traits>
    company_name_header<Traits>::company_name_header(company_name_header&& another)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    company_name_header<Traits>::~company_name_header()
    noexcept
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
    void company_name_header<Traits>::draw_on_impl(canvas_type& canvas)
    const
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


        // constructors and destructor

        impl(
            string_type       line_name,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        )
        :
        m_line_name(std::move(line_name)),
        m_p_font(&font),
        m_p_color(&color),
        m_position(std::move(position)),
        m_dimension(std::move(dimension))
        {}

        impl(impl&& another)
        :
        m_line_name(std::move(another.m_line_name)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
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

        void draw_on_impl(canvas_type& canvas)
        const
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
        string_type       line_name,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension
    )
    :
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            std::move(line_name), font, color, std::move(position), std::move(dimension)
        )
    )
    {}

    template <typename Traits>
    line_name_header<Traits>::line_name_header(line_name_header&& another)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    line_name_header<Traits>::~line_name_header()
    noexcept
    {}

    template <typename Traits>
    line_name_header<Traits>& line_name_header<Traits>::operator=(line_name_header<Traits>&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void line_name_header<Traits>::draw_on_impl(canvas_type& canvas)
    const
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


        // constructors and destructor

        impl(
            string_type       note,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        )
        :
        m_note(std::move(note)),
        m_p_font(&font),
        m_p_color(&color),
        m_position(std::move(position)),
        m_dimension(std::move(dimension))
        {}

        impl(impl&& another)
        :
        m_note(std::move(another.m_note)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
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

        void draw_on_impl(canvas_type& canvas)
        const
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
        string_type       note,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension
    )
    :
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(std::move(note), font, color, std::move(position), std::move(dimension))
    )
    {}

    template <typename Traits>
    note_header<Traits>::note_header(note_header&& another)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    note_header<Traits>::~note_header()
    noexcept
    {}

    template <typename Traits>
    note_header<Traits>& note_header<Traits>::operator=(note_header<Traits>&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void note_header<Traits>::draw_on_impl(canvas_type& canvas)
    const
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

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename header::model_type;


        // constructors and destructor

        impl(
            const direction_type        direction,
            const model_type&           model,
            const message_catalog_type& message_catalog,
            canvas_type&                canvas,
            const dimension_type&       canvas_dimension
        )
        :
        m_p_company_name_header(),
        m_p_line_name_header(),
        m_p_note_header(),
        m_p_ruled_line_color(&*model.timetable().font_color_set().ruled_line().timetable_color()),
        m_position(left_type{ 0 }, top_type{ 0 }),
        m_dimension(width_type{ 0 }, height_type{ 0 })
        {
            const auto& company_name = model.timetable().company_name();
            const auto& company_name_font = *model.timetable().font_color_set().company_name().diagram_font();
            auto line_name = make_line_name(direction, model, message_catalog);
            const auto& line_name_font = *model.timetable().font_color_set().line_name().diagram_font();
            const auto& note = model.timetable().note();
            const auto& note_font = *model.timetable().font_color_set().note().diagram_font();
            position_type company_name_position{ left_type{ 0 }, top_type{ 0 } };
            dimension_type company_name_dimension{ width_type{ 0 }, height_type{ 0 } };
            position_type line_name_position{ left_type{ 0 }, top_type{ 0 } };
            dimension_type line_name_dimension{ width_type{ 0 }, height_type{ 0 } };
            position_type note_position{ left_type{ 0 }, top_type{ 0 } };
            dimension_type note_dimension{ width_type{ 0 }, height_type{ 0 } };
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
                m_dimension
            );

            const auto& company_name_color = *model.timetable().font_color_set().company_name().diagram_color();
            m_p_company_name_header =
                tetengo2::stdalt::make_unique<company_name_header_type>(
                    std::move(company_name),
                    company_name_font,
                    company_name_color,
                    std::move(company_name_position),
                    std::move(company_name_dimension)
                );                    
            const auto& line_name_color = *model.timetable().font_color_set().line_name().diagram_color();
            m_p_line_name_header =
                tetengo2::stdalt::make_unique<line_name_header_type>(
                    std::move(line_name),
                    line_name_font,
                    line_name_color,
                    std::move(line_name_position),
                    std::move(line_name_dimension)
                );                    
            const auto& note_color = *model.timetable().font_color_set().note().diagram_color();
            m_p_note_header =
                tetengo2::stdalt::make_unique<note_header_type>(
                    std::move(note),
                    note_font,
                    note_color,
                    std::move(note_position),
                    std::move(note_dimension)
                );                    
        }

        impl(impl&& another)
        :
        m_p_company_name_header(std::move(another.m_p_company_name_header)),
        m_p_line_name_header(std::move(another.m_p_line_name_header)),
        m_p_note_header(std::move(another.m_p_note_header)),
        m_p_ruled_line_color(another.m_p_ruled_line_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_company_name_header = std::move(another.m_p_company_name_header);
            m_p_line_name_header = std::move(another.m_p_line_name_header);
            m_p_note_header = std::move(another.m_p_note_header);
            m_p_ruled_line_color = another.m_p_ruled_line_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_line_width(normal_line_width<unit_size_type>());
            canvas.set_line_style(canvas_type::line_style_type::solid);
            canvas.set_color(*m_p_ruled_line_color);

            const auto& left = tetengo2::gui::position<position_type>::left(m_position);
            const auto& top = tetengo2::gui::position<position_type>::top(m_position);
            const auto right = left + left_type::from(tetengo2::gui::dimension<dimension_type>::width(m_dimension));
            const auto bottom = top + top_type::from(tetengo2::gui::dimension<dimension_type>::height(m_dimension));

            canvas.draw_line(position_type{ left, top }, position_type{ right, top });
            canvas.draw_line(position_type{ left, top }, position_type{ left, bottom });
            canvas.draw_line(position_type{ right, top }, position_type{ right, bottom });

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

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        using unit_size_type = typename canvas_type::unit_size_type;


        // static functions

        static string_type make_line_name(
            const direction_type        direction,
            const model_type&           model,
            const message_catalog_type& message_catalog
        )
        {
            switch (direction)
            {
            case direction_type::down:
                return
                    (
                        boost::basic_format<typename string_type::value_type>(
                            message_catalog.get(TETENGO2_TEXT("Timetable:(%1% - Down)"))
                        ) % model.timetable().line_name()
                    ).str();
            default:
                assert(direction == direction_type::up);
                return
                    (
                        boost::basic_format<typename string_type::value_type>(
                            message_catalog.get(TETENGO2_TEXT("Timetable:(%1% - Up)"))
                        ) % model.timetable().line_name()
                    ).str();
            }
        }

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
            dimension_type&       dimension
        )
        {
            const auto& canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);

            canvas.set_font(company_name_font);
            auto company_name_dimension_ = canvas.calc_text_dimension(company_name);
            const auto& company_name_width = tetengo2::gui::dimension<dimension_type>::width(company_name_dimension_);
            const auto& company_name_height =
                company_name.empty() ?
                height_type{ 0 } : tetengo2::gui::dimension<dimension_type>::height(company_name_dimension_);

            canvas.set_font(line_name_font);
            auto line_name_dimension_ = canvas.calc_text_dimension(line_name);
            const auto& line_name_width = tetengo2::gui::dimension<dimension_type>::width(line_name_dimension_);
            const auto& line_name_height =
                line_name.empty() ?
                height_type{ 0 } : tetengo2::gui::dimension<dimension_type>::height(line_name_dimension_);

            canvas.set_font(note_font);
            const auto note_dimension_ = canvas.calc_text_dimension(note);
            const auto& note_height =
                note.empty() ? height_type{ 0 } : tetengo2::gui::dimension<dimension_type>::height(note_dimension_);

            const auto left_margin = left_type{ 1 } / 2;
            const auto top_margin = top_type{ 1 } / 2;
            const auto left_padding = left_type{ 1 } / 2;
            const auto top_padding = top_type{ 1 } / 2;
            const left_type company_line_names_spacing{ 1 };

            position_type company_name_position_{ left_type{ 0 }, top_type{ 0 } };
            position_type line_name_position_{ left_type{ 0 }, top_type{ 0 } };
            const position_type note_position_{ left_margin + left_padding, top_margin + top_padding };
            const auto line_name_top =
                tetengo2::gui::position<position_type>::top(note_position_) + top_type::from(note_height);
            const auto header_width =
                canvas_width > width_type::from(left_margin) * 2 ?
                canvas_width - width_type::from(left_margin) * 2 : width_type{ 0 };
            height_type header_height{ 0 };
            if (company_name_width + line_name_width + company_line_names_spacing + left_padding * 2 <= header_width)
            {
                const auto company_name_left =
                    left_margin +
                    left_type::from(
                        (header_width - (company_name_width + line_name_width + company_line_names_spacing)) / 2
                    );

                const auto max_element_height = std::max({ company_name_height, line_name_height });
                company_name_position_ =
                    position_type{
                        company_name_left,
                        line_name_top + top_type::from(max_element_height - company_name_height) / 2
                    };
                line_name_position_ =
                    position_type{
                        company_name_left + left_type::from(company_name_width + company_line_names_spacing),
                        line_name_top + top_type::from(max_element_height - line_name_height) / 2
                    };
                header_height = note_height + max_element_height + top_padding * 2;
            }
            else
            {
                company_name_position_ = position_type{ left_margin + left_padding, line_name_top };
                line_name_position_ =
                    position_type{ left_margin + left_padding, line_name_top + top_type::from(company_name_height) };
                header_height = note_height + company_name_height + line_name_height + top_padding * 2;
            }

            company_name_position = std::move(company_name_position_);
            company_name_dimension = std::move(company_name_dimension_);
            line_name_position = std::move(line_name_position_);
            line_name_dimension = std::move(line_name_dimension_);
            note_position = std::move(note_position_);
            note_dimension = std::move(note_dimension_);
            position = position_type{ left_margin, top_margin };
            dimension = dimension_type{ std::move(header_width), std::move(header_height) };
        }


        // variables

        std::unique_ptr<company_name_header_type> m_p_company_name_header;

        std::unique_ptr<line_name_header_type> m_p_line_name_header;

        std::unique_ptr<note_header_type> m_p_note_header;

        const color_type* m_p_ruled_line_color;

        position_type m_position;

        dimension_type m_dimension;


    };


    template <typename Traits>
    header<Traits>::header(
        const direction_type        direction,
        const model_type&           model,
        const message_catalog_type& message_catalog,
        canvas_type&                canvas,
        const dimension_type&       canvas_dimension
    )
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(direction, model, message_catalog, canvas, canvas_dimension))
    {}

    template <typename Traits>
    header<Traits>::header(header&& another)
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    header<Traits>::~header()
    noexcept
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
    const typename header<Traits>::dimension_type& header<Traits>::dimension()
    const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void header<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }

        
    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class company_name_header<typename application::traits_type_list_type::timetable_view_type>;

    template class line_name_header<typename application::traits_type_list_type::timetable_view_type>;

    template class note_header<typename application::traits_type_list_type::timetable_view_type>;

    template class header<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class company_name_header<typename test::traits_type_list_type::timetable_view_type>;

    template class line_name_header<typename test::traits_type_list_type::timetable_view_type>;

    template class note_header<typename test::traits_type_list_type::timetable_view_type>;

    template class header<typename test::traits_type_list_type::timetable_view_type>;


}}}
