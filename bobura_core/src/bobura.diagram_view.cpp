/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/diagram_view.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/header.h>
#include <bobura/view/diagram/station_line.h>
#include <bobura/view/diagram/time_line.h>
#include <bobura/view/diagram/train_line.h>


namespace bobura
{
    template <typename Traits>
    class diagram_view<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using scale_type = typename traits_type::scale_type;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename diagram_view::position_type;

        using dimension_type = typename diagram_view::dimension_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename diagram_view::model_type;

        using item_type = typename diagram_view::item_type;

        using selection_observer_set_type = typename diagram_view::selection_observer_set_type;


        // constructors and destructor

        impl(const model_type& model, const message_catalog_type& message_catalog)
        :
        m_model(model),
        m_message_catalog(message_catalog),
        m_selection(),
        m_horizontal_scale(1),
        m_vertical_scale(1),
        m_dimension(width_type{ 0 }, height_type{ 0 }),
        m_header_height(0),
        m_time_header_height(3),
        m_station_header_width(8),
        m_time_offset(time_span_type{ 3, 0, 0 }),
        m_station_intervals(),
        m_station_positions(),
        m_p_header(),
        m_p_time_line_list(),
        m_p_station_line_list(),
        m_p_train_line_list()
        {}


        // functions

        void draw_on(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            clear_background(canvas, canvas_dimension);

            ensure_items_created(canvas, canvas_dimension, scroll_bar_position);
            m_p_header->draw_on(canvas);
            m_p_time_line_list->draw_on(canvas);
            m_p_station_line_list->draw_on(canvas);
            m_p_train_line_list->draw_on(canvas);
        }

        const scale_type& horizontal_scale()
        const
        {
            return m_horizontal_scale;
        }

        void set_horizontal_scale(scale_type scale)
        {
            m_horizontal_scale = std::move(scale);
            update_dimension();
        }

        const scale_type& vertical_scale()
        const
        {
            return m_vertical_scale;
        }

        void set_vertical_scale(scale_type scale)
        {
            m_vertical_scale = std::move(scale);
            update_dimension();
        }

        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        void update_dimension()
        {
            const width_type width{ 20 * 24 * m_horizontal_scale };

            m_station_intervals = m_model.timetable().station_intervals();
            if (m_station_intervals.empty())
            {
                m_station_positions.clear();
                m_dimension = dimension_type{ width, height_type{ 0 } };

                m_p_header.reset();
                m_p_time_line_list.reset();
                m_p_station_line_list.reset();
                m_p_train_line_list.reset();

                return;
            }
            
            std::vector<top_type> positions{};
            positions.reserve(m_station_intervals.size());
            std::transform(
                m_station_intervals.begin(),
                m_station_intervals.end(),
                std::back_inserter(positions),
                to_station_position(m_vertical_scale)
            );

            m_station_positions = std::move(positions);
            m_dimension = dimension_type{ width, height_type::from(m_station_positions.back()) };

            m_p_header.reset();
            m_p_time_line_list.reset();
            m_p_station_line_list.reset();
            m_p_train_line_list.reset();
        }

        dimension_type page_size(const dimension_type& canvas_dimension)
        const
        {
            const auto& canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);
            const auto& header_width = m_station_header_width;
            auto page_width = canvas_width > header_width ? canvas_width - header_width : width_type{ 0 };

            const auto& canvas_height = tetengo2::gui::dimension<dimension_type>::height(canvas_dimension);
            const auto header_height = m_header_height + m_time_header_height;
            auto page_height = canvas_height > header_height ? canvas_height - header_height : height_type{ 0 };

            return { std::move(page_width), std::move(page_height) };
        }

        const item_type* p_item_by_position(const diagram_view& self, const position_type& position)
        const
        {
            return const_cast<diagram_view*>(&self)->p_item_by_position(position);
        }

        item_type* p_item_by_position(const position_type& position)
        {
            if (m_p_header)
            {
                if (auto* const p_item = m_p_header->p_item_by_position(position))
                    return p_item;
            }
            if (m_p_time_line_list)
            {
                if (auto* const p_item = m_p_time_line_list->p_item_by_position(position))
                    return p_item;
            }
            if (m_p_station_line_list)
            {
                if (auto* const p_item = m_p_station_line_list->p_item_by_position(position))
                    return p_item;
            }
            if (m_p_train_line_list)
            {
                if (auto* const p_item = m_p_train_line_list->p_item_by_position(position))
                return p_item;
            }

            return nullptr;
        }

        void unselect_all_items()
        {
            m_selection.unselect_all();
        }

        const selection_observer_set_type& selection_observer_set()
        const
        {
            return m_selection.selection_observer_set();
        }

        selection_observer_set_type& selection_observer_set()
        {
            return m_selection.selection_observer_set();
        }


    private:
        // types

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        using solid_background_type = typename traits_type::solid_background_type;

        using header_type = view::diagram::header<traits_type>;

        using time_line_list_type = view::diagram::time_line_list<traits_type>;

        using station_line_list_type = view::diagram::station_line_list<traits_type>;

        using train_line_list_type = view::diagram::train_line_list<traits_type>;

        using selection_type = typename diagram_view::selection_type;

        using timetable_type = typename model_type::timetable_type;

        using station_intervals_type = typename timetable_type::station_intervals_type;

        using train_type = typename timetable_type::train_type;

        using stop_type = typename train_type::stop_type;

        using time_type = typename stop_type::time_type;

        using time_span_type = typename time_type::time_span_type;

        class to_station_position
        {
        public:
            explicit to_station_position(const scale_type& vertical_scale)
            :
            m_vertical_scale(vertical_scale),
            m_sum(0)
            {}

            top_type operator()(const time_span_type& interval)
            {
                const auto position = m_sum;
                m_sum += interval;
                return
                    top_type{ typename top_type::value_type{ position.seconds(), 60 } } *
                    top_type::from(height_type{ m_vertical_scale }).value();
            }

        private:
            const scale_type& m_vertical_scale;

            time_span_type m_sum;

        };


        // variables

        const model_type& m_model;

        const message_catalog_type& m_message_catalog;

        selection_type m_selection;

        scale_type m_horizontal_scale;

        scale_type m_vertical_scale;

        dimension_type m_dimension;

        height_type m_header_height;

        height_type m_time_header_height;

        width_type m_station_header_width;

        time_span_type m_time_offset;

        station_intervals_type m_station_intervals;

        std::vector<top_type> m_station_positions;

        std::unique_ptr<header_type> m_p_header;

        std::unique_ptr<time_line_list_type> m_p_time_line_list;

        std::unique_ptr<station_line_list_type> m_p_station_line_list;

        std::unique_ptr<train_line_list_type> m_p_train_line_list;


        // functions

        void clear_background(canvas_type& canvas, const dimension_type& canvas_dimension)
        const
        {
            canvas.set_background(
                tetengo2::stdalt::make_unique<const solid_background_type>(
                    m_model.timetable().font_color_set().background()
                )
            );
            canvas.fill_rectangle(position_type{ left_type{ 0 }, top_type{ 0 } }, canvas_dimension);
        }

        void ensure_items_created(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const position_type&  scroll_bar_position
        )
        {
            if (m_p_header)
            {
                assert(m_p_time_line_list && m_p_station_line_list && m_p_train_line_list);
                return;
            }

            m_p_header = tetengo2::stdalt::make_unique<header_type>(m_model, m_selection, canvas, canvas_dimension);
            m_header_height = tetengo2::gui::dimension<dimension_type>::height(m_p_header->dimension());
            m_p_time_line_list =
                tetengo2::stdalt::make_unique<time_line_list_type>(
                    m_model,
                    m_time_offset,
                    m_selection,
                    canvas_dimension,
                    m_dimension,
                    scroll_bar_position,
                    left_type::from(m_station_header_width),
                    top_type::from(m_header_height),
                    m_time_header_height,
                    m_horizontal_scale
                );
            m_p_station_line_list =
                tetengo2::stdalt::make_unique<station_line_list_type>(
                    m_model,
                    m_time_offset,
                    m_selection,
                    canvas_dimension,
                    scroll_bar_position,
                    left_type::from(m_station_header_width),
                    top_type::from(m_header_height),
                    m_time_header_height,
                    m_horizontal_scale,
                    m_station_positions
                );
            m_p_train_line_list =
                tetengo2::stdalt::make_unique<train_line_list_type>(
                    m_model,
                    m_time_offset,
                    m_selection,
                    canvas_dimension,
                    scroll_bar_position,
                    left_type::from(m_station_header_width),
                    top_type::from(m_header_height),
                    m_time_header_height,
                    m_horizontal_scale,
                    m_station_intervals,
                    m_station_positions,
                    m_message_catalog
                );
        }


    };


    template <typename Traits>
    diagram_view<Traits>::diagram_view(const model_type& model, const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(model, message_catalog))
    {}

    template <typename Traits>
    diagram_view<Traits>::~diagram_view()
    noexcept
    {}

    template <typename Traits>
    void diagram_view<Traits>::draw_on(
        canvas_type&          canvas,
        const dimension_type& canvas_dimension,
        const position_type&  scroll_bar_position
    )
    {
        m_p_impl->draw_on(canvas, canvas_dimension, scroll_bar_position);
    }

    template <typename Traits>
    const typename diagram_view<Traits>::scale_type& diagram_view<Traits>::horizontal_scale()
    const
    {
        return m_p_impl->horizontal_scale();
    }

    template <typename Traits>
    void diagram_view<Traits>::set_horizontal_scale(scale_type scale)
    {
        m_p_impl->set_horizontal_scale(std::move(scale));
    }

    template <typename Traits>
    const typename diagram_view<Traits>::scale_type& diagram_view<Traits>::vertical_scale()
    const
    {
        return m_p_impl->vertical_scale();
    }

    template <typename Traits>
    void diagram_view<Traits>::set_vertical_scale(scale_type scale)
    {
        m_p_impl->set_vertical_scale(std::move(scale));
    }

    template <typename Traits>
    const typename diagram_view<Traits>::dimension_type& diagram_view<Traits>::dimension()
    const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void diagram_view<Traits>::update_dimension()
    {
        m_p_impl->update_dimension();
    }

    template <typename Traits>
    typename diagram_view<Traits>::dimension_type diagram_view<Traits>::page_size(
        const dimension_type& canvas_dimension
    )
    const
    {
        return m_p_impl->page_size(canvas_dimension);
    }

    template <typename Traits>
    const typename diagram_view<Traits>::item_type* diagram_view<Traits>::p_item_by_position(
        const position_type& position
    )
    const
    {
        return m_p_impl->p_item_by_position(*this, position);
    }

    template <typename Traits>
    typename diagram_view<Traits>::item_type* diagram_view<Traits>::p_item_by_position(const position_type& position)
    {
        return m_p_impl->p_item_by_position(position);
    }

    template <typename Traits>
    void diagram_view<Traits>::unselect_all_items()
    {
        m_p_impl->unselect_all_items();
    }

    template <typename Traits>
    const typename diagram_view<Traits>::selection_observer_set_type& diagram_view<Traits>::selection_observer_set()
    const
    {
        return m_p_impl->selection_observer_set();
    }

    template <typename Traits>
    typename diagram_view<Traits>::selection_observer_set_type& diagram_view<Traits>::selection_observer_set()
    {
        return m_p_impl->selection_observer_set();
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
    template class diagram_view<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class diagram_view<typename test::traits_type_list_type::diagram_view_type>;


}
