/*! \file
    \brief The definition of bobura::message::view_picture_box::diagram.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_VIEWPICTUREBOX_DIAGRAM_H)
#define BOBURA_MESSAGE_VIEWPICTUREBOX_DIAGRAM_H

#include <cassert>
#include <functional>
#include <memory>

#include <boost/rational.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/stdalt.h>

#include <bobura/diagram_view.h>


namespace bobura::message::view_picture_box::diagram {
    /*!
        \brief The class template for a mouse pressed observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam ViewTraits A view traits type.
    */
    template <typename PictureBox, typename ViewTraits>
    class mouse_pressed
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The position type.
        using position_type = typename picture_box_type::position_type;

        //! The button kind type.
        using mouse_button_type = typename picture_box_type::mouse_observer_set_type::mouse_button_type;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The view type.
        using view_type = bobura::diagram_view<view_traits_type>;

        //! The set-mouse-capture function type.
        using set_mouse_capture_type = std::function<void(mouse_button_type)>;


        // constructors and destructor

        /*!
            \brief Creates a mouse pressed observer of the picture box.

            \param picture_box       A picture box.
            \param set_mouse_capture A set-mouse-capture function.
            \param view              A view.
        */
        mouse_pressed(picture_box_type& picture_box, const set_mouse_capture_type& set_mouse_capture, view_type& view)
        : m_picture_box{ picture_box }, m_set_mouse_capture{ set_mouse_capture }, m_view{ view }
        {}


        // functions

        /*!
            \brief Called when the mouse button is pressed.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void operator()(
            const mouse_button_type                 button,
            const position_type&                    position,
            TETENGO2_STDALT_MAYBE_UNUSED const bool shift,
            TETENGO2_STDALT_MAYBE_UNUSED const bool control,
            TETENGO2_STDALT_MAYBE_UNUSED const bool meta) const
        {
            m_picture_box.set_focus();

            m_set_mouse_capture(button);

            auto* const p_item = m_view.p_item_by_position(position);
            if (p_item)
                p_item->select(button != mouse_button_type::right);
            else
                m_view.unselect_all_items();

            m_picture_box.repaint();
        }


    private:
        // variables

        picture_box_type& m_picture_box;

        set_mouse_capture_type m_set_mouse_capture;

        view_type& m_view;
    };


    /*!
        \brief The class template for a mouse released observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam ViewTraits A view traits type.
    */
    template <typename PictureBox, typename ViewTraits>
    class mouse_released
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The position type.
        using position_type = typename picture_box_type::position_type;

        //! The button kind type.
        using mouse_button_type = typename picture_box_type::mouse_observer_set_type::mouse_button_type;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The view type.
        using view_type = bobura::diagram_view<view_traits_type>;

        //! The release-mouse-capture function type.
        using release_mouse_capture_type = std::function<bool(mouse_button_type)>;


        // constructors and destructor

        /*!
            \brief Creates a mouse released observer of the picture box.

            \param release_mouse_capture A set-mouse-capture function.
            \param view                  A view.
        */
        mouse_released(const release_mouse_capture_type& release_mouse_capture, view_type& view)
        : m_release_mouse_capture{ release_mouse_capture }, m_view{ view }
        {}


        // functions

        /*!
            \brief Called when the mouse button is released.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void operator()(
            const mouse_button_type            button,
            TETENGO2_STDALT_MAYBE_UNUSED const position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const bool           shift,
            TETENGO2_STDALT_MAYBE_UNUSED const bool           control,
            TETENGO2_STDALT_MAYBE_UNUSED const bool           meta) const
        {
            m_release_mouse_capture(button);
        }


    private:
        // variables

        release_mouse_capture_type m_release_mouse_capture;

        view_type& m_view;
    };


    /*!
        \brief The class template for a mouse moved observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam ViewTraits A view traits type.
    */
    template <typename PictureBox, typename ViewTraits>
    class mouse_moved
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The position type.
        using position_type = typename picture_box_type::position_type;

        //! The button kind type.
        using mouse_button_type = typename picture_box_type::mouse_observer_set_type::mouse_button_type;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The view type.
        using view_type = bobura::diagram_view<view_traits_type>;

        //! The detail implementation set type.
        using detail_impl_set_type = tetengo2::detail::base::gui_impl_set;


        // constructors and destructor

        /*!
            \brief Creates a mouse moved observer of the picture box.

            \param picture_box     A picture box.
            \param view            A view.
            \param detail_impl_set A detail implementation set.
        */
        mouse_moved(picture_box_type& picture_box, const view_type& view, const detail_impl_set_type& detail_impl_set)
        : m_picture_box{ picture_box }, m_view{ view }, m_detail_impl_set{ detail_impl_set }
        {}


        // functions

        /*!
            \brief Called when the mouse is moved.

            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void operator()(
            const position_type&                    position,
            TETENGO2_STDALT_MAYBE_UNUSED const bool shift,
            TETENGO2_STDALT_MAYBE_UNUSED const bool control,
            TETENGO2_STDALT_MAYBE_UNUSED const bool meta) const
        {
            const auto* const p_item = m_view.p_item_by_position(position);
            const auto        p_cursor = m_picture_box.p_cursor();
            const auto* const p_system_cursor = p_cursor ? dynamic_cast<const system_cursor_type*>(p_cursor) : nullptr;
            if (p_item)
            {
                if (!p_system_cursor || p_system_cursor->style() != system_cursor_type::style_type::hand)
                {
                    m_picture_box.set_cursor(std::make_unique<system_cursor_type>(
                        system_cursor_type::style_type::hand, m_detail_impl_set.cursor_()));
                }
            }
            else
            {
                if (p_system_cursor)
                {
                    m_picture_box.set_cursor(std::unique_ptr<cursor_type>{});
                }
            }
        }


    private:
        // types

        using cursor_type = typename picture_box_type::cursor_type;

        using system_cursor_type = typename picture_box_type::system_cursor_type;


        // variables

        picture_box_type& m_picture_box;

        const view_type& m_view;

        const detail_impl_set_type& m_detail_impl_set;
    };


    /*!
        \brief The class template for a mouse wheel observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam Zoom       A zoom type.
        \tparam ViewTraits A view traits type.
    */
    template <typename PictureBox, typename Zoom, typename ViewTraits>
    class mouse_wheeled
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The position type.
        using position_type = typename picture_box_type::position_type;

        //! The button kind type.
        using mouse_button_type = typename picture_box_type::mouse_observer_set_type::mouse_button_type;

        //! The delta type.
        using delta_type = typename picture_box_type::mouse_observer_set_type::delta_type;

        //! The direction type.
        using direction_type = typename picture_box_type::mouse_observer_set_type::direction_type;

        //! The view zoom type.
        using view_zoom_type = Zoom;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The view type.
        using view_type = bobura::diagram_view<view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a mouse wheel observer of the picture box.

            \param picture_box A picture box.
            \param view        A view.
        */
        mouse_wheeled(picture_box_type& picture_box, view_type& view) : m_picture_box{ picture_box }, m_view{ view } {}


        // functions

        /*!
            \brief Called when the mouse wheel is wheeled.

            \param delta     A delta.
            \param direction A direction.
            \param shift     True when shift key is pressed.
            \param control   True when control key is pressed.
            \param meta      True when meta key is pressed.
        */
        void operator()(
            const delta_type&    delta,
            const direction_type direction,
            const bool           shift,
            const bool           control,
            const bool           meta) const
        {
            const auto adjusted_delta =
                direction == picture_box_type::mouse_observer_set_type::direction_type::horizontal ? delta : -delta;

            if (!control && !meta)
                scroll(adjusted_delta, is_vertical(direction, shift));
            else if (control && !meta)
                zoom(adjusted_delta, is_vertical(direction, shift));
        }


    private:
        // types

        using scroll_bar_size_type = typename picture_box_type::scroll_bar_type::size_type;


        // variables

        picture_box_type& m_picture_box;

        view_type& m_view;


        // functions

        bool is_vertical(const direction_type direction, const bool shift) const
        {
            return (!shift && direction == picture_box_type::mouse_observer_set_type::direction_type::vertical) ||
                   (shift && direction == picture_box_type::mouse_observer_set_type::direction_type::horizontal);
        }

        void scroll(const delta_type& delta, const bool vertical) const
        {
            if (vertical)
            {
                assert(m_picture_box.has_vertical_scroll_bar());
                if (!m_picture_box.vertical_scroll_bar().enabled())
                    return;

                const auto new_position = calculate_new_position(m_picture_box.vertical_scroll_bar(), delta);
                m_picture_box.vertical_scroll_bar().set_position(new_position);
                m_picture_box.vertical_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
            }
            else
            {
                assert(m_picture_box.has_horizontal_scroll_bar());
                if (!m_picture_box.horizontal_scroll_bar().enabled())
                    return;

                const auto new_position = calculate_new_position(m_picture_box.horizontal_scroll_bar(), delta);
                m_picture_box.horizontal_scroll_bar().set_position(new_position);
                m_picture_box.horizontal_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
            }
        }

        scroll_bar_size_type calculate_new_position(
            const typename picture_box_type::scroll_bar_type& scroll_bar,
            const delta_type&                                 delta) const
        {
            using delta_int_type = typename delta_type::int_type;
            auto int_delta = boost::rational_cast<delta_int_type>(delta * 3);
            if (int_delta == 0)
            {
                if (delta > 0)
                    ++int_delta;
                else
                    --int_delta;
            }
            const delta_int_type new_position = scroll_bar.position() + int_delta;

            if (new_position < static_cast<delta_int_type>(scroll_bar.range().first))
                return scroll_bar.range().first;
            if (new_position > static_cast<delta_int_type>(scroll_bar.range().second - scroll_bar.page_size() + 1))
                return scroll_bar.range().second - scroll_bar.page_size() + 1;

            return new_position;
        }

        void zoom(const delta_type delta, const bool vertical) const
        {
            view_zoom_type zoom{ m_picture_box, m_view };

            if (vertical)
            {
                if (delta > 0)
                    zoom.vertically_zoom_in(false);
                else
                    zoom.vertically_zoom_out(false);
            }
            else
            {
                if (delta > 0)
                    zoom.horizontally_zoom_in(false);
                else
                    zoom.horizontally_zoom_out(false);
            }
        }
    };


    /*!
        \brief The class template for a key down observer of the picture box.

        \tparam PictureBox A picture box type.
    */
    template <typename PictureBox>
    class keyboard_key_down
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The virtual key type.
        using virtual_key_type = typename picture_box_type::keyboard_observer_set_type::virtual_key_type;


        // constructors and destructor

        /*!
            \brief Creates a key down observer of the picture box.

            \param picture_box A picture box.
        */
        explicit keyboard_key_down(picture_box_type& picture_box) : m_picture_box{ picture_box } {}


        // functions

        /*!
            \brief Called when a key is pressed down.

            \param virtual_key A virtual key.
            \param shift       True when shift key is pressed.
            \param control     True when control key is pressed.
            \param meta        True when meta key is pressed.
        */
        void
        operator()(const virtual_key_type& virtual_key, const bool shift, const bool control, const bool meta) const
        {
            if (virtual_key == virtual_key_type::left() || virtual_key == virtual_key_type::right() ||
                virtual_key == virtual_key_type::up() || virtual_key == virtual_key_type::down() ||
                virtual_key == virtual_key_type::page_up() || virtual_key == virtual_key_type::page_down() ||
                virtual_key == virtual_key_type::home() || virtual_key == virtual_key_type::end())
            {
                if (!control && !meta)
                    scroll(virtual_key, shift);
            }
        }


    private:
        // types

        using scroll_bar_size_type = typename picture_box_type::scroll_bar_type::size_type;


        // variables

        picture_box_type& m_picture_box;


        // functions

        void scroll(const virtual_key_type& virtual_key, const bool shift) const
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

        bool is_vertical(const virtual_key_type& virtual_key, const bool shift) const
        {
            if (virtual_key == virtual_key_type::up() || virtual_key == virtual_key_type::down())
            {
                return true;
            }
            else if (
                !shift && (virtual_key == virtual_key_type::page_up() || virtual_key == virtual_key_type::page_down()))
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

        scroll_bar_size_type calculate_new_position(
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
    };


    /*!
        \brief The class template for a paint observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam ViewTraits A view traits type.
    */
    template <typename PictureBox, typename ViewTraits>
    class paint_paint
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The canvas type.
        using canvas_type = typename view_traits_type::canvas_type;

        //! The view type.
        using view_type = bobura::diagram_view<view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the picture box.

            \param picture_box A picture box.
            \param view        A view.
        */
        paint_paint(const picture_box_type& picture_box, view_type& view) : m_picture_box{ picture_box }, m_view{ view }
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas) const
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


    private:
        // types

        using position_type = typename picture_box_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using scroll_bar_size_type = typename picture_box_type::scroll_bar_type::size_type;


        // static functions

        static position_type to_position(const scroll_bar_size_type left, const scroll_bar_size_type top)
        {
            return { static_cast<position_unit_type>(left), static_cast<position_unit_type>(top) };
        }


        // variables

        const picture_box_type& m_picture_box;

        view_type& m_view;
    };


    /*!
        \brief The class template for a scroll bar observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam ViewTraits A view traits type.
    */
    template <typename PictureBox, typename ViewTraits>
    class scroll_bar_scrolled
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = PictureBox;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The size type.
        using size_type = typename view_traits_type::size_type;

        //! The view type.
        using view_type = bobura::diagram_view<view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a scroll bar observer of the picture box.

            \param picture_box A picture box.
            \param view        A view.
        */
        scroll_bar_scrolled(const picture_box_type& picture_box, view_type& view)
        : m_picture_box{ picture_box }, m_view{ view }
        {}


        // functions

        /*!
            \brief Called when the scroll bar is scrolled.

            \param new_position A new position.
        */
        void operator()(TETENGO2_STDALT_MAYBE_UNUSED const size_type new_position) const
        {
            m_view.update_dimension();
            m_picture_box.repaint();
        }


    private:
        // variables

        const picture_box_type& m_picture_box;

        view_type& m_view;
    };
}


#endif
