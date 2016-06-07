/*! \file
    \brief The definition of bobura::view::timetable::train_number_header.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_TIMETABLE_TRAINNUMBERHEADER_H)
#define BOBURA_VIEW_TIMETABLE_TRAINNUMBERHEADER_H

#include <memory>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/view/timetable/item.h>
#include <bobura/view/timetable/utility.h>


namespace bobura { namespace view { namespace timetable
{
    /*!
        \brief The class template for a header of the operating distance in the timetable view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class operating_distance_header : public item<Traits>
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


        // constructors and destructor

        /*!
            \brief Creates an operating distance header.

            \param description A description.
            \param font        A font.
            \param color       A color.
            \param position    A position.
            \param dimension   A dimension.
        */
        operating_distance_header(
            string_type       description,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        );

        /*!
            \brief Moves an operating distance header.

            \param another Another operating distance header.
        */
        operating_distance_header(operating_distance_header&& another);

        /*!
            \brief Destroys the train number description header.
        */
        virtual ~operating_distance_header()
        noexcept;


        // functions

        /*!
            \brief Assigns an operating distance header.

            \param another Another operating distance header.

            \return This operating distance header.
        */
        operating_distance_header& operator=(operating_distance_header&& another);


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
        \brief The class template for a header of the operating distance in the timetable view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_number_description_header : public item<Traits>
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


        // constructors and destructor

        /*!
            \brief Creates a train number description header.

            \param description A description.
            \param font        A font.
            \param color       A color.
            \param position    A position.
            \param dimension   A dimension.
        */
        train_number_description_header(
            string_type       description,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        );

        /*!
            \brief Moves a train number description header.

            \param another Another train number description header.
        */
        train_number_description_header(train_number_description_header&& another);

        /*!
            \brief Destroys the train number description header.
        */
        virtual ~train_number_description_header()
        noexcept;


        // functions

        /*!
            \brief Assigns a train number description header.

            \param another Another train number description header.

            \return This train number description header.
        */
        train_number_description_header& operator=(train_number_description_header&& another);


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
        \brief The class template for a header of the train name description in the timetable view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_name_description_header : public item<Traits>
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


        // constructors and destructor

        /*!
            \brief Creates a train name description header.

            \param description A description.
            \param font        A font.
            \param color       A color.
            \param position    A position.
            \param dimension   A dimension.
        */
        train_name_description_header(
            string_type       description,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        );

        /*!
            \brief Moves a train name description header.

            \param another Another train name description header.
        */
        train_name_description_header(train_name_description_header&& another);

        /*!
            \brief Destroys the train number description header.
        */
        virtual ~train_name_description_header()
        noexcept;


        // functions

        /*!
            \brief Assigns a train name description header.

            \param another Another train name description header.

            \return This train name description header.
        */
        train_name_description_header& operator=(train_name_description_header&& another);


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
        \brief The class template for a train number header in the timetable view.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_number_header : public item<Traits>
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

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The top type.
        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        //! The dimension type.
        using dimension_type = typename canvas_type::dimension_type;

        //! The width type.
        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        //! The height type.
        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        //! The font type.
        using font_type = typename canvas_type::font_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;


        // constructors and destructor

        /*!
            \brief Creates a train number header.

            \param direction                A direction.
            \param model                    A model.
            \param message_catalog          A message catalog.
            \param canvas                   A canvas.
            \param canvas_dimension         A canvas dimension.
            \param margin                   A margin.
            \param top                      A top.
            \param operating_distance_width A operating distance width.
            \param station_name_width       A max station name width.
            \param train_number_height      A train number height.
            \param train_name_height        A train name height.
        */
        train_number_header(
            direction_type              direction,
            const model_type&           model,
            const message_catalog_type& message_catalog,
            canvas_type&                canvas,
            const dimension_type&       canvas_dimension,
            const dimension_type&       margin,
            const top_type&             top,
            const width_type&           operating_distance_width,
            const width_type&           station_name_width,
            const height_type&          train_number_height,
            const height_type&          train_name_height
        );

        /*!
            \brief Moves a train number header.

            \param another Another train number header
        */
        train_number_header(train_number_header&& another);

        /*!
            \brief Destroys the train number header.
        */
        virtual ~train_number_header()
        noexcept;


        // functions

        /*!
            \brief Assigns a train number header.

            \param another Another train number header.

            \return This train number header.
        */
        train_number_header& operator=(train_number_header&& another);


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
