/*! \file
    \brief The definition of bobura::timetable_view.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/station_info/grade.h>
#include <bobura/timetable_view.h>
#include <bobura/type_list.h>
#include <bobura/view/timetable/header.h>
#include <bobura/view/timetable/train_number_header.h>
#include <bobura/view/timetable/utility.h>
#include <bobura/view/utility.h>


namespace bobura {
    template <typename Traits>
    class timetable_view<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename timetable_view::position_type;

        using dimension_type = typename timetable_view::dimension_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename timetable_view::model_type;


        // constructors and destructor

        impl(
            const view::timetable::direction_type direction,
            const model_type&                     model,
            const message_catalog_type&           message_catalog)
        : m_direction{ direction }, m_model{ model }, m_message_catalog{ message_catalog }, m_dimension{}, m_p_header{},
          m_p_train_number_header{}
        {}


        // functions

        void
        draw_on(canvas_type& canvas, const dimension_type& canvas_dimension, const position_type& scroll_bar_position)
        {
            clear_background(canvas, canvas_dimension);

            ensure_items_created(canvas, canvas_dimension, scroll_bar_position);
            m_p_header->draw_on(canvas);
            m_p_train_number_header->draw_on(canvas);
        }

        const dimension_type& dimension() const
        {
            return m_dimension;
        }

        void update_dimension()
        {
            m_dimension = dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } };

            m_p_header.reset();
            m_p_train_number_header.reset();
        }

        dimension_type page_size(const dimension_type& canvas_dimension) const
        {
            const auto& page_width = canvas_dimension.width();
            const auto& page_height = canvas_dimension.height();
            return { page_width, page_height };
        }

        void unselect_all_items() {}


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using solid_background_type = typename traits_type::solid_background_type;

        using header_type = view::timetable::header<traits_type>;

        using train_number_header_type = view::timetable::train_number_header<traits_type>;

        using station_locations_type = typename model_type::timetable_type::station_locations_type;

        using font_color_set_type = typename model_type::timetable_type::font_color_set_type;

        using station_grade_type_set_type = model::station_info::grade_type_set;

        using station_grade_type = typename station_grade_type_set_type::grade_type;


        // static functions

        static dimension_unit_type max_station_name_width(
            canvas_type&                  canvas,
            const station_locations_type& station_locations,
            const font_color_set_type&    font_color_set)
        {
            dimension_unit_type max_width{};
            {
                const auto& font = view::select_station_font_color<font_color_set_type, station_grade_type_set_type>(
                                       font_color_set, station_grade_type_set_type::local_type::instance())
                                       .timetable_font();
                assert(font);
                canvas.set_font(*font);

                const auto dimension = canvas.calc_text_dimension(string_type{ TETENGO2_TEXT("M") });
                max_width = dimension.width() * 4 + dimension_unit_type{ 3 };
            }
            for (const auto& station_location : station_locations)
            {
                const auto& station = station_location.get_station();

                const auto& font = view::select_station_font_color<font_color_set_type, station_grade_type_set_type>(
                                       font_color_set, station.grade())
                                       .timetable_font();
                assert(font);
                canvas.set_font(*font);

                const auto dimension = canvas.calc_text_dimension(station.name());
                const auto width = dimension.width() + dimension_unit_type{ 3 };
                if (width > max_width)
                    max_width = width;
            }
            return max_width;
        }

        static dimension_unit_type train_number_height(canvas_type& canvas, const font_color_set_type& font_color_set)
        {
            assert(font_color_set.general().timetable_font());
            canvas.set_font(*font_color_set.general().timetable_font());

            const auto dimension = canvas.calc_text_dimension(string_type{ TETENGO2_TEXT("42") });
            return dimension.height();
        }


        // variables

        const view::timetable::direction_type m_direction;

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;

        dimension_type m_dimension;

        std::unique_ptr<header_type> m_p_header;

        std::unique_ptr<train_number_header_type> m_p_train_number_header;


        // functions

        void clear_background(canvas_type& canvas, const dimension_type& canvas_dimension) const
        {
            canvas.set_background(std::make_unique<const solid_background_type>(
                canvas.drawing_details(), *m_model.timetable().font_color_set().background().diagram_color()));
            canvas.fill_rectangle(position_type{}, canvas_dimension);
        }

        void ensure_items_created(
            canvas_type&                       canvas,
            const dimension_type&              canvas_dimension,
            TETENGO2_STDALT_MAYBE_UNUSED const position_type& scroll_bar_position)
        {
            if (m_p_header)
            {
                assert(m_p_train_number_header);
                return;
            }

            const dimension_type margin{ dimension_unit_type{ 1 } / 2, dimension_unit_type{ 1 } / 2 };
            const auto           operating_distance_width_ = dimension_unit_type{ 5 } / 2;
            const auto           max_station_name_width_ = max_station_name_width(
                canvas, m_model.timetable().station_locations(), m_model.timetable().font_color_set());
            const auto train_number_height_ = train_number_height(canvas, m_model.timetable().font_color_set());
            const auto train_name_height_ = dimension_unit_type{ 5 };

            m_p_header = std::make_unique<header_type>(
                m_direction, m_model, m_message_catalog, canvas, canvas_dimension, margin);

            const auto header_bottom =
                m_p_header->position().top() + position_unit_type::from(m_p_header->dimension().height());

            m_p_train_number_header = std::make_unique<train_number_header_type>(
                m_direction,
                m_model,
                m_message_catalog,
                canvas,
                canvas_dimension,
                margin,
                header_bottom,
                operating_distance_width_,
                max_station_name_width_,
                train_number_height_,
                train_name_height_);
        }
    };


    template <typename Traits>
    timetable_view<Traits>::timetable_view(
        const view::timetable::direction_type direction,
        const model_type&                     model,
        const message_catalog_type&           message_catalog)
    : m_p_impl{ std::make_unique<impl>(direction, model, message_catalog) }
    {}

    template <typename Traits>
    timetable_view<Traits>::~timetable_view() noexcept
    {}

    template <typename Traits>
    void timetable_view<Traits>::draw_on(
        canvas_type&          canvas,
        const dimension_type& canvas_dimension,
        const position_type&  scroll_bar_position)
    {
        m_p_impl->draw_on(canvas, canvas_dimension, scroll_bar_position);
    }

    template <typename Traits>
    const typename timetable_view<Traits>::dimension_type& timetable_view<Traits>::dimension() const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void timetable_view<Traits>::update_dimension()
    {
        m_p_impl->update_dimension();
    }

    template <typename Traits>
    typename timetable_view<Traits>::dimension_type
    timetable_view<Traits>::page_size(const dimension_type& canvas_dimension) const
    {
        return m_p_impl->page_size(canvas_dimension);
    }

    template <typename Traits>
    void timetable_view<Traits>::unselect_all_items()
    {
        m_p_impl->unselect_all_items();
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
    template class timetable_view<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class timetable_view<typename test::traits_type_list_type::timetable_view_type>;
}
