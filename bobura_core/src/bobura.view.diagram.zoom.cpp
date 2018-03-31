/*! \file
    \brief The definition of bobura::view::diagram::zoom.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/zoom.h>
#include <bobura/view_picture_box.h>


namespace bobura::view::diagram {
    template <typename Traits, typename PictureBox, typename MouseCapture>
    class zoom<Traits, PictureBox, MouseCapture>::impl : private boost::noncopyable
    {
    public:
        // types

        using picture_box_type = typename zoom::picture_box_type;

        using mouse_capture_type = typename zoom::mouse_capture_type;

        using diagram_view_type = typename zoom::diagram_view_type;

        using scale_list_type = typename zoom::scale_list_type;

        using scale_type = typename zoom::scale_type;

        using view_picture_box_type = view_picture_box<picture_box_type, mouse_capture_type>;


        // constructors and destructor

        impl(picture_box_type& picture_box, diagram_view_type& diagram_view)
        : m_p_diagram_view_picture_box{ dynamic_cast<view_picture_box_type*>(&picture_box) }, m_diagram_view{
              diagram_view
          }
        {
            assert(m_p_diagram_view_picture_box);
        }


        // functions

        void set_horizontal_scale(scale_type scale)
        {
            m_diagram_view.set_horizontal_scale(std::move(scale));
            m_p_diagram_view_picture_box->update_scroll_bars(
                m_diagram_view.dimension(), m_diagram_view.page_size(m_p_diagram_view_picture_box->client_dimension()));
            m_p_diagram_view_picture_box->repaint();
        }

        void horizontally_zoom_in(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list{};
            set_horizontal_scale(larger(m_diagram_view.horizontal_scale(), scale_list, snap_to_scale_list));
        }

        void horizontally_zoom_out(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list{};
            set_horizontal_scale(smaller(m_diagram_view.horizontal_scale(), scale_list, snap_to_scale_list));
        }

        void set_vertical_scale(scale_type scale)
        {
            m_diagram_view.set_vertical_scale(std::move(scale));
            m_p_diagram_view_picture_box->update_scroll_bars(
                m_diagram_view.dimension(), m_diagram_view.page_size(m_p_diagram_view_picture_box->client_dimension()));
            m_p_diagram_view_picture_box->repaint();
        }

        void vertically_zoom_in(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list{};
            set_vertical_scale(larger(m_diagram_view.vertical_scale(), scale_list, snap_to_scale_list));
        }

        void vertically_zoom_out(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list{};
            set_vertical_scale(smaller(m_diagram_view.vertical_scale(), scale_list, snap_to_scale_list));
        }


    private:
        // types

        using canvas_type = typename picture_box_type::fast_canvas_type;

        using position_type = typename picture_box_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using scroll_bar_size_type = typename picture_box_type::scroll_bar_type::size_type;


        // static functions

        static scale_type
        larger(const scale_type& scale, const scale_list_type& scale_list, const bool snap_to_scale_list)
        {
            if (snap_to_scale_list)
                return scale_list.larger(scale);

            const auto larger_scale = scale + scale_type{ 1, 10 };
            if (larger_scale > scale_list.at(scale_list.size() - 1))
                return scale;

            return larger_scale;
        }

        static scale_type
        smaller(const scale_type& scale, const scale_list_type& scale_list, const bool snap_to_scale_list)
        {
            if (snap_to_scale_list)
                return scale_list.smaller(scale);

            const auto smaller_scale = scale - scale_type{ 1, 10 };
            if (smaller_scale < scale_list.at(0))
                return scale;

            return smaller_scale;
        }

        static position_type to_position(const scroll_bar_size_type left, const scroll_bar_size_type top)
        {
            return position_type{ position_unit_type{ static_cast<typename position_unit_type::value_type>(left) },
                                  position_unit_type{ static_cast<typename position_unit_type::value_type>(top) } };
        }


        // variables

        view_picture_box_type* const m_p_diagram_view_picture_box;

        diagram_view_type& m_diagram_view;
    };


    template <typename Traits, typename PictureBox, typename MouseCapture>
    zoom<Traits, PictureBox, MouseCapture>::zoom(picture_box_type& picture_box, diagram_view_type& diagram_view)
    : m_p_impl{ tetengo2::stdalt::make_unique<impl>(picture_box, diagram_view) }
    {}

    template <typename Traits, typename PictureBox, typename MouseCapture>
    zoom<Traits, PictureBox, MouseCapture>::~zoom() noexcept
    {}

    template <typename Traits, typename PictureBox, typename MouseCapture>
    void zoom<Traits, PictureBox, MouseCapture>::set_horizontal_scale(scale_type scale)
    {
        m_p_impl->set_horizontal_scale(std::move(scale));
    }

    template <typename Traits, typename PictureBox, typename MouseCapture>
    void zoom<Traits, PictureBox, MouseCapture>::horizontally_zoom_in(const bool snap_to_scale_list)
    {
        m_p_impl->horizontally_zoom_in(snap_to_scale_list);
    }

    template <typename Traits, typename PictureBox, typename MouseCapture>
    void zoom<Traits, PictureBox, MouseCapture>::horizontally_zoom_out(const bool snap_to_scale_list)
    {
        m_p_impl->horizontally_zoom_out(snap_to_scale_list);
    }

    template <typename Traits, typename PictureBox, typename MouseCapture>
    void zoom<Traits, PictureBox, MouseCapture>::set_vertical_scale(scale_type scale)
    {
        m_p_impl->set_vertical_scale(std::move(scale));
    }

    template <typename Traits, typename PictureBox, typename MouseCapture>
    void zoom<Traits, PictureBox, MouseCapture>::vertically_zoom_in(const bool snap_to_scale_list)
    {
        m_p_impl->vertically_zoom_in(snap_to_scale_list);
    }

    template <typename Traits, typename PictureBox, typename MouseCapture>
    void zoom<Traits, PictureBox, MouseCapture>::vertically_zoom_out(const bool snap_to_scale_list)
    {
        m_p_impl->vertically_zoom_out(snap_to_scale_list);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class zoom<
        typename application::traits_type_list_type::diagram_view_type,
        typename application::ui_type_list_type::picture_box_type,
        typename application::ui_type_list_type::mouse_capture_type>;
#endif

    template class zoom<
        typename test::traits_type_list_type::diagram_view_type,
        typename test::ui_type_list_type::picture_box_type,
        typename test::ui_type_list_type::mouse_capture_type>;
}
