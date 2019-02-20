/*! \file
    \brief The definition of bobura::message::view_picture_box::diagram.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_VIEWPICTUREBOX_DIAGRAM_H)
#define BOBURA_MESSAGE_VIEWPICTUREBOX_DIAGRAM_H

#include <functional>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/widget/picture_box.h>

#include <bobura/diagram_view.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura::message::view_picture_box::diagram {
    /*!
        \brief The class template for a mouse pressed observer of the picture box.

        \tparam ViewTraits A view traits type.
    */
    template <typename ViewTraits>
    class mouse_pressed
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = tetengo2::gui::widget::picture_box;

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
        mouse_pressed(picture_box_type& picture_box, const set_mouse_capture_type& set_mouse_capture, view_type& view);


        // functions

        /*!
            \brief Called when the mouse button is pressed.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void
        operator()(mouse_button_type button, const position_type& position, bool shift, bool control, bool meta) const;


    private:
        // variables

        picture_box_type& m_picture_box;

        set_mouse_capture_type m_set_mouse_capture;

        view_type& m_view;
    };


    /*!
        \brief The class template for a mouse released observer of the picture box.

        \tparam ViewTraits A view traits type.
    */
    template <typename ViewTraits>
    class mouse_released
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = tetengo2::gui::widget::picture_box;

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
        mouse_released(const release_mouse_capture_type& release_mouse_capture, view_type& view);


        // functions

        /*!
            \brief Called when the mouse button is released.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void
        operator()(mouse_button_type button, const position_type& position, bool shift, bool control, bool meta) const;


    private:
        // variables

        release_mouse_capture_type m_release_mouse_capture;

        view_type& m_view;
    };


    /*!
        \brief The class template for a mouse moved observer of the picture box.

        \tparam ViewTraits A view traits type.
    */
    template <typename ViewTraits>
    class mouse_moved
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = tetengo2::gui::widget::picture_box;

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

            \param picture_box A picture box.
            \param view        A view.
        */
        mouse_moved(picture_box_type& picture_box, const view_type& view);


        // functions

        /*!
            \brief Called when the mouse is moved.

            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void operator()(const position_type& position, bool shift, bool control, bool meta) const;


    private:
        // types

        using cursor_type = typename picture_box_type::cursor_type;

        using system_cursor_type = tetengo2::gui::cursor::system;


        // variables

        picture_box_type& m_picture_box;

        const view_type& m_view;
    };


    /*!
        \brief The class template for a mouse wheel observer of the picture box.

        \tparam Zoom       A zoom type.
        \tparam ViewTraits A view traits type.
    */
    template <typename ViewTraits>
    class mouse_wheeled
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = tetengo2::gui::widget::picture_box;

        //! The position type.
        using position_type = typename picture_box_type::position_type;

        //! The button kind type.
        using mouse_button_type = typename picture_box_type::mouse_observer_set_type::mouse_button_type;

        //! The delta type.
        using delta_type = typename picture_box_type::mouse_observer_set_type::delta_type;

        //! The direction type.
        using direction_type = typename picture_box_type::mouse_observer_set_type::direction_type;

        //! The view traits type.
        using view_traits_type = ViewTraits;

        //! The view type.
        using view_type = bobura::diagram_view<view_traits_type>;

        //! The view zoom type.
        using view_zoom_type = view::diagram::zoom<view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a mouse wheel observer of the picture box.

            \param picture_box A picture box.
            \param view        A view.
        */
        mouse_wheeled(picture_box_type& picture_box, view_type& view);


        // functions

        /*!
            \brief Called when the mouse wheel is wheeled.

            \param delta     A delta.
            \param direction A direction.
            \param shift     True when shift key is pressed.
            \param control   True when control key is pressed.
            \param meta      True when meta key is pressed.
        */
        void operator()(const delta_type& delta, direction_type direction, bool shift, bool control, bool meta) const;


    private:
        // types

        using scroll_bar_size_type = typename picture_box_type::scroll_bar_type::size_type;


        // variables

        picture_box_type& m_picture_box;

        view_type& m_view;


        // functions

        bool is_vertical(direction_type direction, bool shift) const;

        void scroll(const delta_type& delta, bool vertical) const;

        scroll_bar_size_type calculate_new_position(
            const typename picture_box_type::scroll_bar_type& scroll_bar,
            const delta_type&                                 delta) const;

        void zoom(const delta_type& delta, bool vertical) const;
    };


    /*!
        \brief The class for a key down observer of the picture box.
    */
    class keyboard_key_down
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = tetengo2::gui::widget::picture_box;

        //! The virtual key type.
        using virtual_key_type = typename picture_box_type::keyboard_observer_set_type::virtual_key_type;


        // constructors and destructor

        /*!
            \brief Creates a key down observer of the picture box.

            \param picture_box A picture box.
        */
        explicit keyboard_key_down(picture_box_type& picture_box);


        // functions

        /*!
            \brief Called when a key is pressed down.

            \param virtual_key A virtual key.
            \param shift       True when shift key is pressed.
            \param control     True when control key is pressed.
            \param meta        True when meta key is pressed.
        */
        void operator()(const virtual_key_type& virtual_key, bool shift, bool control, bool meta) const;


    private:
        // types

        using scroll_bar_size_type = typename picture_box_type::scroll_bar_type::size_type;


        // variables

        picture_box_type& m_picture_box;


        // functions

        void scroll(const virtual_key_type& virtual_key, bool shift) const;

        bool is_vertical(const virtual_key_type& virtual_key, bool shift) const;

        scroll_bar_size_type calculate_new_position(
            const typename picture_box_type::scroll_bar_type& scroll_bar,
            const virtual_key_type&                           virtual_key) const;
    };


    /*!
        \brief The class template for a paint observer of the picture box.

        \tparam ViewTraits A view traits type.
    */
    template <typename ViewTraits>
    class paint_paint
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = tetengo2::gui::widget::picture_box;

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
        paint_paint(const picture_box_type& picture_box, view_type& view);


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas) const;


    private:
        // types

        using position_type = typename picture_box_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using scroll_bar_size_type = typename picture_box_type::scroll_bar_type::size_type;


        // static functions

        static position_type to_position(scroll_bar_size_type left, scroll_bar_size_type top);


        // variables

        const picture_box_type& m_picture_box;

        view_type& m_view;
    };


    /*!
        \brief The class template for a scroll bar observer of the picture box.

        \tparam ViewTraits A view traits type.
    */
    template <typename ViewTraits>
    class scroll_bar_scrolled
    {
    public:
        // types

        //! The picture box type.
        using picture_box_type = tetengo2::gui::widget::picture_box;

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
        scroll_bar_scrolled(const picture_box_type& picture_box, view_type& view);


        // functions

        /*!
            \brief Called when the scroll bar is scrolled.

            \param new_position A new position.
        */
        void operator()(size_type new_position) const;


    private:
        // variables

        const picture_box_type& m_picture_box;

        view_type& m_view;
    };
}


#endif
