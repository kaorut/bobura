/*! \file
    \brief The definition of bobura::message::view_picture_box::timetable.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>

#include <boost/predef.h>

#include <tetengo2/gui/message/scroll_bar_observer_set.h>
#include <tetengo2/gui/scroll_bar.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/gui/widget/widget.h>

#include <bobura/detail_type_list.h>
#include <bobura/message/view_picture_box/timetable.h>
#include <bobura/type_list.h>


namespace bobura::message::view_picture_box::timetable {
    template <typename ViewTraits>
    mouse_pressed<ViewTraits>::mouse_pressed(
        picture_box_type&             picture_box,
        const set_mouse_capture_type& set_mouse_capture,
        view_type&                    view)
    : m_picture_box{ picture_box }, m_set_mouse_capture{ set_mouse_capture }, m_view{ view }
    {}

    template <typename ViewTraits>
    void mouse_pressed<ViewTraits>::operator()(
        const mouse_button_type /*button*/,
        const position_type& /*position*/,
        const bool /*shift*/,
        const bool /*control*/,
        const bool /*meta*/) const
    {
        // m_picture_box.set_focus();

        // m_set_mouse_capture(button);

        // auto* const p_item = m_view.p_item_by_position(position);
        // if (p_item)
        //    p_item->select(button != mouse_button_type::right);
        // else
        //    m_view.unselect_all_items();

        // m_picture_box.repaint();
    }


    template <typename ViewTraits>
    mouse_released<ViewTraits>::mouse_released(const release_mouse_capture_type& release_mouse_capture, view_type& view)
    : m_release_mouse_capture{ release_mouse_capture }, m_view{ view }
    {}

    template <typename ViewTraits>
    void mouse_released<ViewTraits>::operator()(
        const mouse_button_type /*button*/,
        const position_type& /*position*/,
        const bool /*shift*/,
        const bool /*control*/,
        const bool /*meta*/) const
    {
        // m_release_mouse_capture(button);
    }


    template <typename ViewTraits>
    mouse_moved<ViewTraits>::mouse_moved(picture_box_type& picture_box, const view_type& view)
    : m_picture_box{ picture_box }, m_view{ view }
    {}

    template <typename ViewTraits>
    void mouse_moved<ViewTraits>::
         operator()(const position_type& /*position*/, const bool /*shift*/, const bool /*control*/, const bool /*meta*/)
        const
    {
        // const auto* const p_item = m_view.p_item_by_position(position);
        // const auto cursor = m_picture_box.cursor();
        // const auto* const p_system_cursor =
        //    cursor ? dynamic_cast<const system_cursor_type*>(&*cursor) : nullptr;
        // if (p_item)
        //{
        //    if (!p_system_cursor || p_system_cursor->style() != system_cursor_type::style_type::hand)
        //    {
        //        m_picture_box.set_cursor(
        //            std::make_unique<system_cursor_type>(system_cursor_type::style_type::hand)
        //        );
        //    }
        //}
        // else
        //{
        //    if (p_system_cursor)
        //    {
        //        m_picture_box.set_cursor(std::unique_ptr<cursor_type>{});
        //    }
        //}
    }


    template <typename ViewTraits>
    mouse_wheeled<ViewTraits>::mouse_wheeled(picture_box_type& picture_box, view_type& view)
    : m_picture_box{ picture_box }, m_view{ view }
    {}

    template <typename ViewTraits>
    void mouse_wheeled<ViewTraits>::operator()(
        const delta_type& /*delta*/,
        const direction_type /*direction*/,
        const bool /*shift*/,
        const bool /*control*/,
        const bool /*meta*/) const
    {
        // const auto adjusted_delta =
        //    direction == picture_box_type::mouse_observer_set_type::direction_type::horizontal ? delta : -delta;

        // if (!control && !meta)
        //    scroll(adjusted_delta, is_vertical(direction, shift));
        // else if (control && !meta)
        //    zoom(adjusted_delta, is_vertical(direction, shift));
    }

    // template <typename ViewTraits>
    // bool mouse_wheeled<ViewTraits>::is_vertical(const direction_type direction, const bool shift) const
    //{
    //    return (!shift && direction == picture_box_type::mouse_observer_set_type::direction_type::vertical) ||
    //           (shift && direction == picture_box_type::mouse_observer_set_type::direction_type::horizontal);
    //}

    // template <typename ViewTraits>
    // void mouse_wheeled<ViewTraits>::scroll(const delta_type& delta, const bool vertical) const
    //{
    //    if (vertical)
    //    {
    //        assert(m_picture_box.has_vertical_scroll_bar());
    //        if (!m_picture_box.vertical_scroll_bar().enabled())
    //            return;

    //        const auto new_position = calculate_new_position(m_picture_box.vertical_scroll_bar(), delta);
    //        m_picture_box.vertical_scroll_bar().set_position(new_position);
    //        m_picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
    //    }
    //    else
    //    {
    //        assert(m_picture_box.has_horizontal_scroll_bar());
    //        if (!m_picture_box.horizontal_scroll_bar().enabled())
    //            return;

    //        const auto new_position = calculate_new_position(m_picture_box.horizontal_scroll_bar(), delta);
    //        m_picture_box.horizontal_scroll_bar().set_position(new_position);
    //        m_picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
    //    }
    //}

    // template <typename ViewTraits>
    // typename mouse_wheeled<ViewTraits>::scroll_bar_size_type mouse_wheeled<ViewTraits>::calculate_new_position(
    //    const typename picture_box_type::scroll_bar_type& scroll_bar,
    //    const delta_type&                                 delta) const
    //{
    //    using delta_int_type = typename delta_type::int_type;
    //    auto int_delta = boost::rational_cast<delta_int_type>(delta * 3);
    //    if (int_delta == 0)
    //    {
    //        if (delta > 0)
    //            ++int_delta;
    //        else
    //            --int_delta;
    //    }
    //    const delta_int_type new_position = scroll_bar.position() + int_delta;

    //    if (new_position < static_cast<delta_int_type>(scroll_bar.range().first))
    //        return scroll_bar.range().first;
    //    if (new_position > static_cast<delta_int_type>(scroll_bar.range().second - scroll_bar.page_size() + 1))
    //        return scroll_bar.range().second - scroll_bar.page_size() + 1;

    //    return new_position;
    //}

    // template <typename ViewTraits>
    // void mouse_wheeled<ViewTraits>::zoom(const delta_type delta, const bool vertical) const
    //{
    //    view_zoom_type zoom{ m_picture_box, m_view };

    //    if (vertical)
    //    {
    //        if (delta > 0)
    //            zoom.vertically_zoom_in(false);
    //        else
    //            zoom.vertically_zoom_out(false);
    //    }
    //    else
    //    {
    //        if (delta > 0)
    //            zoom.horizontally_zoom_in(false);
    //        else
    //            zoom.horizontally_zoom_out(false);
    //    }
    //}
    // template <typename ViewTraits>
    // bool mouse_wheeled<ViewTraits>::is_vertical(const direction_type direction, const bool shift) const
    //{
    //    return (!shift && direction == picture_box_type::mouse_observer_set_type::direction_type::vertical) ||
    //           (shift && direction == picture_box_type::mouse_observer_set_type::direction_type::horizontal);
    //}

    // template <typename ViewTraits>
    // void mouse_wheeled<ViewTraits>::scroll(const delta_type& delta, const bool vertical) const
    //{
    //    if (vertical)
    //    {
    //        assert(m_picture_box.has_vertical_scroll_bar());
    //        if (!m_picture_box.vertical_scroll_bar().enabled())
    //            return;

    //        const auto new_position = calculate_new_position(m_picture_box.vertical_scroll_bar(), delta);
    //        m_picture_box.vertical_scroll_bar().set_position(new_position);
    //        m_picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
    //    }
    //    else
    //    {
    //        assert(m_picture_box.has_horizontal_scroll_bar());
    //        if (!m_picture_box.horizontal_scroll_bar().enabled())
    //            return;

    //        const auto new_position = calculate_new_position(m_picture_box.horizontal_scroll_bar(), delta);
    //        m_picture_box.horizontal_scroll_bar().set_position(new_position);
    //        m_picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
    //    }
    //}

    // template <typename ViewTraits>
    // typename mouse_wheeled<ViewTraits>::scroll_bar_size_type mouse_wheeled<ViewTraits>::calculate_new_position(
    //    const typename picture_box_type::scroll_bar_type& scroll_bar,
    //    const delta_type&                                 delta) const
    //{
    //    using delta_int_type = typename delta_type::int_type;
    //    auto int_delta = boost::rational_cast<delta_int_type>(delta * 3);
    //    if (int_delta == 0)
    //    {
    //        if (delta > 0)
    //            ++int_delta;
    //        else
    //            --int_delta;
    //    }
    //    const delta_int_type new_position = scroll_bar.position() + int_delta;

    //    if (new_position < static_cast<delta_int_type>(scroll_bar.range().first))
    //        return scroll_bar.range().first;
    //    if (new_position > static_cast<delta_int_type>(scroll_bar.range().second - scroll_bar.page_size() + 1))
    //        return scroll_bar.range().second - scroll_bar.page_size() + 1;

    //    return new_position;
    //}

    // template <typename ViewTraits>
    // void mouse_wheeled<ViewTraits>::zoom(const delta_type delta, const bool vertical) const
    //{
    //    view_zoom_type zoom{ m_picture_box, m_view };

    //    if (vertical)
    //    {
    //        if (delta > 0)
    //            zoom.vertically_zoom_in(false);
    //        else
    //            zoom.vertically_zoom_out(false);
    //    }
    //    else
    //    {
    //        if (delta > 0)
    //            zoom.horizontally_zoom_in(false);
    //        else
    //            zoom.horizontally_zoom_out(false);
    //    }
    //}


    keyboard_key_down::keyboard_key_down(picture_box_type& picture_box) : m_picture_box{ picture_box } {}

    void keyboard_key_down::operator()(
        const virtual_key_type& /*virtual_key*/,
        const bool /*shift*/,
        const bool /*control*/,
        const bool /*meta*/) const
    {
        // if (
        //    virtual_key == virtual_key_type::left() ||
        //    virtual_key == virtual_key_type::right() ||
        //    virtual_key == virtual_key_type::up() ||
        //    virtual_key == virtual_key_type::down() ||
        //    virtual_key == virtual_key_type::page_up() ||
        //    virtual_key == virtual_key_type::page_down() ||
        //    virtual_key == virtual_key_type::home() ||
        //    virtual_key == virtual_key_type::end()
        //)
        //{
        //    if (!control && !meta)
        //        scroll(virtual_key, shift);
        //}
    }

    void keyboard_key_down::scroll(const virtual_key_type& virtual_key, const bool shift) const
    {
        const auto vertical = is_vertical(virtual_key, shift);
        if (vertical)
        {
            assert(m_picture_box.has_vertical_scroll_bar());
            if (!m_picture_box.vertical_scroll_bar().enabled())
                return;

            const auto new_position = calculate_new_position(m_picture_box.vertical_scroll_bar(), virtual_key);
            m_picture_box.vertical_scroll_bar().set_position(new_position);
            m_picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
        }
        else
        {
            assert(m_picture_box.has_horizontal_scroll_bar());
            if (!m_picture_box.horizontal_scroll_bar().enabled())
                return;

            const auto new_position = calculate_new_position(m_picture_box.horizontal_scroll_bar(), virtual_key);
            m_picture_box.horizontal_scroll_bar().set_position(new_position);
            m_picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
        }
    }

    bool keyboard_key_down::is_vertical(const virtual_key_type& virtual_key, const bool shift) const
    {
        if (virtual_key == virtual_key_type::up() || virtual_key == virtual_key_type::down())
        {
            return true;
        }
        else if (!shift && (virtual_key == virtual_key_type::page_up() || virtual_key == virtual_key_type::page_down()))
        {
            return true;
        }
        else if (!shift && (virtual_key == virtual_key_type::home() || virtual_key == virtual_key_type::end()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    keyboard_key_down::scroll_bar_size_type keyboard_key_down::calculate_new_position(
        const typename picture_box_type::scroll_bar_type& scroll_bar,
        const virtual_key_type&                           virtual_key) const
    {
        const auto min_position = scroll_bar.range().first;
        const auto max_position = scroll_bar.range().second - scroll_bar.page_size() + 1;

        if (virtual_key == virtual_key_type::home())
        {
            return min_position;
        }
        else if (virtual_key == virtual_key_type::end())
        {
            return max_position;
        }
        else if (virtual_key == virtual_key_type::page_up())
        {
            return scroll_bar.position() > min_position + scroll_bar.page_size() ?
                       scroll_bar.position() - scroll_bar.page_size() :
                       min_position;
        }
        else if (virtual_key == virtual_key_type::page_down())
        {
            return scroll_bar.position() + scroll_bar.page_size() < max_position ?
                       scroll_bar.position() + scroll_bar.page_size() :
                       max_position;
        }
        else if (virtual_key == virtual_key_type::up() || virtual_key == virtual_key_type::left())
        {
            return scroll_bar.position() > min_position + 1 ? scroll_bar.position() - 1 : min_position;
        }
        else
        {
            assert(virtual_key == virtual_key_type::down() || virtual_key == virtual_key_type::right());

            return scroll_bar.position() + 1 < max_position ? scroll_bar.position() + 1 : max_position;
        }
    }


    template <typename ViewTraits>
    paint_paint<ViewTraits>::paint_paint(const picture_box_type& picture_box, view_type& view)
    : m_picture_box{ picture_box }, m_view{ view }
    {}

    template <typename ViewTraits>
    void paint_paint<ViewTraits>::operator()(canvas_type& canvas) const
    {
        assert(m_picture_box.has_vertical_scroll_bar());
        assert(m_picture_box.has_horizontal_scroll_bar());

        const auto client_dimension = m_picture_box.client_dimension();

        canvas.begin_transaction(client_dimension);

        m_view.draw_on(
            canvas,
            client_dimension,
            to_position(
                m_picture_box.horizontal_scroll_bar().tracking_position(),
                m_picture_box.vertical_scroll_bar().tracking_position()));

        canvas.end_transaction();
    }

    template <typename ViewTraits>
    typename paint_paint<ViewTraits>::position_type
    paint_paint<ViewTraits>::to_position(const scroll_bar_size_type left, const scroll_bar_size_type top)
    {
        return { static_cast<position_unit_type>(left), static_cast<position_unit_type>(top) };
    }


    template <typename ViewTraits>
    scroll_bar_scrolled<ViewTraits>::scroll_bar_scrolled(const picture_box_type& picture_box, view_type& view)
    : m_picture_box{ picture_box }, m_view{ view }
    {}

    template <typename ViewTraits>
    void scroll_bar_scrolled<ViewTraits>::operator()(const size_type /*new_position*/) const
    {
        // m_view.update_dimension();
        // m_picture_box.repaint();
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
    template class mouse_pressed<typename application::traits_type_list_type::timetable_view_type>;

    template class mouse_released<typename application::traits_type_list_type::timetable_view_type>;

    template class mouse_moved<typename application::traits_type_list_type::timetable_view_type>;

    template class mouse_wheeled<typename application::traits_type_list_type::timetable_view_type>;

    template class paint_paint<typename application::traits_type_list_type::timetable_view_type>;

    template class scroll_bar_scrolled<typename application::traits_type_list_type::timetable_view_type>;
#endif

    template class mouse_pressed<typename test::traits_type_list_type::timetable_view_type>;

    template class mouse_released<typename test::traits_type_list_type::timetable_view_type>;

    template class mouse_moved<typename test::traits_type_list_type::timetable_view_type>;

    template class mouse_wheeled<typename test::traits_type_list_type::timetable_view_type>;

    template class paint_paint<typename test::traits_type_list_type::timetable_view_type>;

    template class scroll_bar_scrolled<typename test::traits_type_list_type::timetable_view_type>;
}