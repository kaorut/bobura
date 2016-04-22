/*! \file
    \brief The definition of bobura::view::timetable::train_number_header.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <cassert>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/station_info/grade.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/train_number_header.h>
#include <bobura/view/timetable/utility.h>
#include <bobura/view/utility.h>


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
            const dimension_type&       canvas_dimension
        )
        :
        m_p_ruled_line_color(&*model.timetable().font_color_set().ruled_line().timetable_color()),
        m_position(left_type{ 0 }, top_type{ 0 }),
        m_dimension(width_type{ 0 }, height_type{ 0 })
        {
            calculate_positions_and_dimensions(
                canvas, canvas_dimension, model.timetable().station_locations(), model.timetable().font_color_set()
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

        void draw_on_impl(canvas_type& /*canvas*/)
        const
        {

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

        using station_locations_type = typename model_type::timetable_type::station_locations_type;

        using station_grade_type =
            typename model_type::timetable_type::station_location_type::station_type::grade_type;

        using font_color_set_type = typename model_type::timetable_type::font_color_set_type;

        using font_color_type = typename font_color_set_type::font_color_type;

        using station_grade_type_set_type = model::station_info::grade_type_set<string_type>;


        // static functions

        static void calculate_positions_and_dimensions(
            canvas_type&                  canvas,
            const dimension_type&         /*canvas_dimension*/,
            const station_locations_type& station_locations,
            const font_color_set_type&    font_color_set
        )
        {
            const width_type width = max_station_name_width(canvas, station_locations, font_color_set);
        }

        static width_type max_station_name_width(
            canvas_type&                  canvas,
            const station_locations_type& station_locations,
            const font_color_set_type&    font_color_set
        )
        {
            width_type max_width{ 0 };
            for (const auto& station_location: station_locations)
            {
                const auto& station = station_location.get_station();

                const auto& font =
                    select_station_font_color<font_color_set_type, station_grade_type_set_type>(
                        font_color_set, station.grade()
                    ).timetable_font();
                assert(font);
                canvas.set_font(*font);

                const auto dimension = canvas.calc_text_dimension(station.name());
                const auto width = tetengo2::gui::dimension<dimension_type>::width(dimension);
                if (width > max_width)
                    max_width = width;
            }
            return max_width;
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
        const dimension_type&       canvas_dimension
    )
    :
    base_type(),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(direction, model, message_catalog, canvas, canvas_dimension))
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
