/*! \file
    \brief The definition of bobura::view::timetable::train_number_header.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/type_list.h>
#include <bobura/view/timetable/train_number_header.h>
#include <bobura/view/timetable/utility.h>


namespace bobura { namespace view { namespace timetable
{
    template <typename Traits>
    class train_number_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using dimension_type = typename canvas_type::dimension_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename train_number_header::model_type;


        // constructors and destructor

        impl(
            const direction_type        /*direction*/,
            const model_type&           model,
            const message_catalog_type& /*message_catalog*/,
            canvas_type&                canvas,
            const dimension_type&       canvas_dimension,
            const dimension_type&       margin,
            const top_type&             top,
            const width_type&           max_station_name_width
        )
        :
        m_p_ruled_line_color(&*model.timetable().font_color_set().ruled_line().timetable_color()),
        m_position(left_type{ 0 }, top_type{ 0 }),
        m_dimension(width_type{ 0 }, height_type{ 0 })
        {
            calculate_positions_and_dimensions(
                canvas, canvas_dimension, margin, top, max_station_name_width, m_position, m_dimension
            );
        }

        impl(impl&& another)
        :
        m_p_ruled_line_color(another.m_p_ruled_line_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

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
        }


    private:
        // types

        using string_type = typename traits_type::string_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        using unit_size_type = typename canvas_type::unit_size_type;


        // static functions

        static void calculate_positions_and_dimensions(
            canvas_type&          /*canvas*/,
            const dimension_type& canvas_dimension,
            const dimension_type& margin,
            const top_type&       top,
            const width_type      max_station_name_width,
            position_type&        position,
            dimension_type&       dimension
        )
        {
            const auto& canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);

            const auto left_margin = left_type::from(tetengo2::gui::dimension<dimension_type>::width(margin));
            //const auto left_padding = left_type{ 1 } / 2;
            //const auto top_padding = top_type{ 1 } / 2;

            auto header_width = max_station_name_width;
            if (canvas_width < header_width + width_type::from(left_margin) * 2)
            {
                header_width =
                    canvas_width > width_type::from(left_margin) * 2 ?
                    canvas_width - width_type::from(left_margin) * 2 : width_type{ 0 };
            }
            height_type header_height{ 5 };

            position = position_type{ left_margin, top };
            dimension = dimension_type{ std::move(header_width), std::move(header_height) };
        }


        // variables

        const color_type* m_p_ruled_line_color;

        position_type m_position;

        dimension_type m_dimension;


    };


    template <typename Traits>
    train_number_header<Traits>::train_number_header(
        const direction_type        direction,
        const model_type&           model,
        const message_catalog_type& message_catalog,
        canvas_type&                canvas,
        const dimension_type&       canvas_dimension,
        const dimension_type&       margin,
        const top_type&             top,
        const width_type&           max_station_name_width
    )
    :
    base_type(),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            direction, model, message_catalog, canvas, canvas_dimension, margin, top, max_station_name_width
        )
    )
    {}

    template <typename Traits>
    train_number_header<Traits>::train_number_header(train_number_header&& another)
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    train_number_header<Traits>::~train_number_header()
    noexcept
    {}

    template <typename Traits>
    train_number_header<Traits>& train_number_header<Traits>::operator=(train_number_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    const typename train_number_header<Traits>::dimension_type& train_number_header<Traits>::dimension()
    const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void train_number_header<Traits>::draw_on_impl(canvas_type& canvas)
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
    template class train_number_header<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class train_number_header<typename test::traits_type_list_type::timetable_view_type>;


}}}
