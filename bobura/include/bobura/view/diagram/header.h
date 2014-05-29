/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_HEADER_H)
#define BOBURA_VIEW_DIAGRAM_HEADER_H

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/view/diagram/item.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a header of the company and line name in the diagram view.

        \tparam Selection A selection type.
        \tparam Canvas    A canvas type.
    */
    template <typename Selection, typename Canvas>
    class company_line_name_header : public item<Selection, Canvas>
    {
    public:
        // types

        //! The selection type.
        using selection_type = Selection;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The string type.
        using string_type = typename canvas_type::string_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The color type.
        using color_type = typename canvas_type::color_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The base type.
        using base_type = item<selection_type, canvas_type>;


        // constructors and destructor

        /*!
            \brief Creates a company and line name header.

            \param selection         A selection.
            \param company_line_name A company and line name.
            \param font              A font.
            \param color             A color.
            \param position          A position.
            \param dimension         A dimension.
        */
        company_line_name_header(
            selection_type&   selection,
            string_type       company_line_name,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        )
        :
        base_type(selection),
        m_company_line_name(std::move(company_line_name)),
        m_p_font(&font),
        m_p_color(&color),
        m_position(std::move(position)),
        m_dimension(std::move(dimension))
        {}

        /*!
            \brief Moves a company and line name header.

            \param another Another company and line name header.
        */
        company_line_name_header(company_line_name_header&& another)
        :
        base_type(another.selection()),
        m_company_line_name(std::move(another.m_company_line_name)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}

        /*!
            \brief Destroys the company and line name header.
        */
        virtual ~company_line_name_header()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Assigns a company and line name header.

            \param another Another company and line name header.

            \return This company and line name header.
        */
        company_line_name_header& operator=(company_line_name_header&& another)
        {
            if (&another == this)
                return *this;

            m_company_line_name = std::move(another.m_company_line_name);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // variables

        string_type m_company_line_name;

        const font_type* m_p_font;

        const color_type* m_p_color;

        position_type m_position;

        dimension_type m_dimension;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);
            canvas.draw_text(m_company_line_name, m_position);
        }


    };


     /*!
        \brief The class template for a header of the note in the diagram view.

        \tparam Selection A selection type.
        \tparam Canvas    A canvas type.
    */
    template <typename Selection, typename Canvas>
    class note_header : public item<Selection, Canvas>
    {
    public:
        // types

        //! The selection type.
        using selection_type = Selection;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The string type.
        using string_type = typename canvas_type::string_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The color type.
        using color_type = typename canvas_type::color_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The base type.
        using base_type = item<selection_type, canvas_type>;


        // constructors and destructor

        /*!
            \brief Creates a note header.

            \param selection A selection.
            \param note      A company and line name.
            \param font      A font.
            \param color     A color.
            \param position  A position.
            \param dimension A dimension.
        */
        note_header(
            selection_type&   selection,
            string_type       note,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        )
        :
        base_type(selection),
        m_note(std::move(note)),
        m_p_font(&font),
        m_p_color(&color),
        m_position(std::move(position)),
        m_dimension(std::move(dimension))
        {}

        /*!
            \brief Moves a note header.

            \param another Another note header.
        */
        note_header(note_header&& another)
        :
        base_type(another.selection()),
        m_note(std::move(another.m_note)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}

        /*!
            \brief Destroys the note header.
        */
        virtual ~note_header()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Assigns a note header.

            \param another Another note header.

            \return This note header.
        */
        note_header& operator=(note_header&& another)
        {
            if (&another == this)
                return *this;

            m_note = std::move(another.m_note);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // variables

        string_type m_note;

        const font_type* m_p_font;

        const color_type* m_p_color;

        position_type m_position;

        dimension_type m_dimension;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);
            canvas.draw_text(m_note, m_position);
        }


    };


     /*!
        \brief The class template for a header in the diagram view.

        \tparam Model     A model type.
        \tparam Selection A selection type.
        \tparam Canvas    A canvas type.
    */
    template <typename Model, typename Selection, typename Canvas>
    class header : public item<Selection, Canvas>
    {
    public:
        // types

        //! The model type.
        using model_type = Model;

        //! The selection type.
        using selection_type = Selection;

        //! The canvas type.
        using canvas_type = Canvas;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The base type.
        using base_type = item<selection_type, canvas_type>;


        // constructors and destructor

        /*!
            \brief Creates a header.

            \param model            A model.
            \param selection        A selection.
            \param canvas           A canvas.
            \param canvas_dimension A canvas dimension.
        */
        header(
            const model_type&     model,
            selection_type&       selection,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension
        )
        :
        base_type(selection),
        m_p_company_line_name_header(),
        m_p_note_header(),
        m_position(left_type{ 0 }, top_type{ 0 }),
        m_dimension(width_type{ 0 }, height_type{ 0 })
        {
            auto company_line_name = make_company_line_name(model);
            const auto& company_line_name_font = model.timetable().font_color_set().company_line_name().font();
            auto note = make_note(model);
            const auto& note_font = model.timetable().font_color_set().note().font();
            position_type company_line_name_position(left_type{ 0 }, top_type{ 0 });
            dimension_type company_line_name_dimension(width_type{ 0 }, height_type{ 0 });
            position_type note_position(left_type{ 0 }, top_type{ 0 });
            dimension_type note_dimension(width_type{ 0 }, height_type{ 0 });
            calculate_positions_and_dimensions(
                canvas,
                canvas_dimension,
                company_line_name,
                company_line_name_font,
                note,
                note_font,
                company_line_name_position,
                company_line_name_dimension,
                note_position,
                note_dimension,
                m_position,
                m_dimension
            );

            const auto& company_line_name_color = model.timetable().font_color_set().company_line_name().color();
            const auto& note_color = model.timetable().font_color_set().note().color();
            m_p_company_line_name_header =
                tetengo2::stdalt::make_unique<company_line_name_header_type>(
                    selection,
                    std::move(company_line_name),
                    company_line_name_font,
                    company_line_name_color,
                    std::move(company_line_name_position),
                    std::move(company_line_name_dimension)
                );
            m_p_note_header =
                tetengo2::stdalt::make_unique<note_header_type>(
                    selection,
                    std::move(note),
                    note_font,
                    note_color,
                    std::move(note_position),
                    std::move(note_dimension)
                );                    
        }

        /*!
            \brief Moves a header.

            \param another Another header
        */
        explicit header(header&& another)
        :
        base_type(another.selection()),
        m_p_company_line_name_header(std::move(another.m_p_company_line_name_header)),
        m_p_note_header(std::move(another.m_p_note_header)),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}

        /*!
            \brief Destroys the header.
        */
        virtual ~header()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Assigns a header.

            \param another Another header.

            \return This header.
        */
        header& operator=(header&& another)
        {
            if (&another == this)
                return *this;

            m_p_company_line_name_header = std::move(another.m_p_company_line_name_header);
            m_p_note_header = std::move(another.m_p_note_header);
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);
            base_type::operator=(std::move(another));

            return *this;
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }


    private:
        // types

        using company_line_name_header_type = company_line_name_header<selection_type, canvas_type>;

        using note_header_type = note_header<selection_type, canvas_type>;

        using string_type = typename canvas_type::string_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;


        // static functions

        static string_type make_company_line_name(const model_type& model)
        {
            return
                model.timetable().company_name() +
                (model.timetable().company_name().empty() ? string_type{} : string_type{ TETENGO2_TEXT(" ") }) +
                model.timetable().line_name();
        }

        static string_type make_note(const model_type& model)
        {
            return model.timetable().note();
        }

        static void calculate_positions_and_dimensions(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const string_type&    company_line_name,
            const font_type&      company_line_name_font,
            const string_type&    note,
            const font_type&      note_font,
            position_type&        company_line_name_position,
            dimension_type&       company_line_name_dimension,
            position_type&        note_position,
            dimension_type&       note_dimension,
            position_type&        position,
            dimension_type&       dimension
        )
        {
            const auto& canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);

            canvas.set_font(company_line_name_font);
            auto company_line_name_dimension_ = canvas.calc_text_dimension(company_line_name);
            const auto& company_line_name_width =
                tetengo2::gui::dimension<dimension_type>::width(company_line_name_dimension_);
            const auto& company_line_name_height =
                company_line_name.empty() ?
                height_type{ 0 } : tetengo2::gui::dimension<dimension_type>::height(company_line_name_dimension_);

            canvas.set_font(note_font);
            const auto note_dimension_ = canvas.calc_text_dimension(note);
            const auto& note_width = tetengo2::gui::dimension<dimension_type>::width(note_dimension_);
            const auto& note_height =
                note.empty() ? height_type{ 0 } : tetengo2::gui::dimension<dimension_type>::height(note_dimension_);

            position_type company_line_name_position_(left_type{ 0 }, top_type{ 0 });
            position_type note_position_(left_type{ 0 }, top_type{ 0 });
            width_type header_width(0);
            height_type header_height(0);
            if (company_line_name_width + note_width <= canvas_width)
            {
                header_width = canvas_width;

                const auto height_diff = top_type::from(company_line_name_height) - top_type::from(note_height);
                if (height_diff > 0)
                {
                    const top_type note_top(height_diff / top_type{ 2 });
                    company_line_name_position_ = position_type{ left_type{ 0 }, top_type{ 0 } };
                    note_position_ = position_type{ left_type::from(canvas_width - note_width), note_top };
                    header_height = company_line_name_height;
                }
                else
                {
                    const top_type company_line_name_top((top_type{ 0 } - height_diff) / top_type{ 2 });
                    company_line_name_position_ = position_type{ left_type{ 0 }, company_line_name_top };
                    note_position_ = position_type{ left_type::from(canvas_width - note_width), top_type{ 0 } };
                    header_height = note_height;
                }
            }
            else
            {
                company_line_name_position_ = position_type{ left_type{ 0 }, top_type{ 0 } };
                note_position_ = position_type{ left_type{ 0 }, top_type::from(company_line_name_height) };
                header_width = std::max(company_line_name_width, note_width);
                header_height = company_line_name_height + note_height;
            }

            company_line_name_position = std::move(company_line_name_position_);
            company_line_name_dimension = std::move(company_line_name_dimension_);
            note_position = std::move(note_position_);
            note_dimension = std::move(note_dimension_);
            position = position_type{ left_type{ 0 }, top_type{ 0 } };
            dimension = dimension_type{ std::move(header_width), std::move(header_height) };
        }


        // variables

        std::unique_ptr<company_line_name_header_type> m_p_company_line_name_header;

        std::unique_ptr<note_header_type> m_p_note_header;

        position_type m_position;

        dimension_type m_dimension;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override
        {
            assert(m_p_company_line_name_header);
            m_p_company_line_name_header->draw_on(canvas);

            assert(m_p_note_header);
            m_p_note_header->draw_on(canvas);
        }


    };


}}}


#endif
