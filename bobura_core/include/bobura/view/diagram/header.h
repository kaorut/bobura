/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_HEADER_H)
#define BOBURA_VIEW_DIAGRAM_HEADER_H

#include <memory>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/view/diagram/item.h>
#include <bobura/view/diagram/selection.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a header of the company and line name in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class company_line_name_header : public item<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The color type.
        using color_type = typename canvas_type::color_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The selection type.
        using selection_type = selection<traits_type>;


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
        );

        /*!
            \brief Moves a company and line name header.

            \param another Another company and line name header.
        */
        company_line_name_header(company_line_name_header&& another);

        /*!
            \brief Destroys the company and line name header.
        */
        virtual ~company_line_name_header()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Assigns a company and line name header.

            \param another Another company and line name header.

            \return This company and line name header.
        */
        company_line_name_header& operator=(company_line_name_header&& another);


    private:
        // types

        using base_type = item<traits_type>;

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override;


    };


     /*!
        \brief The class template for a header of the note in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class note_header : public item<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The color type.
        using color_type = typename canvas_type::color_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The selection type.
        using selection_type = selection<traits_type>;


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
        );

        /*!
            \brief Moves a note header.

            \param another Another note header.
        */
        note_header(note_header&& another);

        /*!
            \brief Destroys the note header.
        */
        virtual ~note_header()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Assigns a note header.

            \param another Another note header.

            \return This note header.
        */
        note_header& operator=(note_header&& another);


    private:
        // types

        using base_type = item<traits_type>;

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override;


    };


     /*!
        \brief The class template for a header in the diagram view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class header : public item<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The selection type.
        using selection_type = selection<traits_type>;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;


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
        );

        /*!
            \brief Moves a header.

            \param another Another header
        */
        header(header&& another);

        /*!
            \brief Destroys the header.
        */
        virtual ~header()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Assigns a header.

            \param another Another header.

            \return This header.
        */
        header& operator=(header&& another);

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const;


    private:
        // types

        using base_type = item<traits_type>;

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const override;


    };


}}}


#endif
