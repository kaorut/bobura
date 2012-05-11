/*! \file
    \brief The definition of tetengo2::gui::widget::widget.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WIDGET_H)
#define TETENGO2_GUI_WIDGET_WIDGET_H

#include <cassert>
//#include <cstddef>
//#include <memory>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The base class template for a GUI widget.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
    */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class widget : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The widget canvas type.
        typedef typename traits_type::widget_canvas_type widget_canvas_type;

        //! The canvas type.
        typedef typename traits_type::canvas_type canvas_type;

        //! The alert type.
        typedef typename traits_type::alert_type alert_type;

        //! The position type.
        typedef typename traits_type::position_type position_type;

        //! The dimension type.
        typedef typename traits_type::dimension_type dimension_type;

        //! The difference type.
        typedef typename traits_type::difference_type difference_type;

        //! The size type.
        typedef typename traits_type::size_type size_type;

        //! The string type.
        typedef typename traits_type::string_type string_type;

        //! The encoder type.
        typedef typename traits_type::encoder_type encoder_type;

        //! The background type.
        typedef typename traits_type::background_type background_type;

        //! The font type.
        typedef typename traits_type::font_type font_type;

        //! The system cursor type.
        typedef typename traits_type::system_cursor_type system_cursor_type;

        //! The cursor type.
        typedef typename system_cursor_type::base_type cursor_type;

        //! The focus observer set type.
        typedef typename traits_type::focus_observer_set_type focus_observer_set_type;

        //! The paint observer set type.
        typedef typename traits_type::paint_observer_set_type paint_observer_set_type;

        //! The keyboard observer set type.
        typedef typename traits_type::keyboard_observer_set_type keyboard_observer_set_type;

        //! The mouse observer set type.
        typedef typename traits_type::mouse_observer_set_type mouse_observer_set_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename widget_details_type::widget_details_ptr_type details_ptr_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The message handler type.
        typedef typename message_handler_details_type::message_handler_type message_handler_type;

        //! The message handler map type.
        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;

        //! The child type.
        typedef widget child_type;

        //! The scroll bar style type.
        enum scroll_bar_style_type
        {
            scroll_bar_style_none,       //!< The widget has no scroll bar.
            scroll_bar_style_horizontal, //!< The widget has a horizontal scroll bar.
            scroll_bar_style_vertical,   //!< The widget has a vertical scroll bar.
            scroll_bar_style_both,       //!< The widget has both horizontal and vertiacal scroll bars.
        };


        // constructors and destructor

        /*!
            \brief Destroys the widget.
        */
        virtual ~widget()
        {}


        // functions

        /*!
            \brief Returns whether the widget has a parent.

            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        bool has_parent()
        const
        {
            return widget_details_type::has_parent(*this);
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        const widget& parent()
        const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::logic_error("Has no parent."));

            return widget_details_type::parent(*this);
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        widget& parent()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::logic_error("Has no parent."));

            return widget_details_type::parent(*this);
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        const widget& root_ancestor()
        const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::logic_error("Has no parent."));

            return widget_details_type::root_ancestor(*this);
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        widget& root_ancestor()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::logic_error("Has no parent."));

            return widget_details_type::root_ancestor(*this);
        }

        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        bool enabled()
        const
        {
            return widget_details_type::enabled(*this);
        }

        /*!
            \brief Sets an enabled status.

            \param enabled An enabled status.
        */
        void set_enabled(const bool enabled)
        {
            widget_details_type::set_enabled(*this, enabled);
        }

        /*!
            \brief Returns the visible status.

            \return The visible status.
        */
        bool visible()
        const
        {
            return widget_details_type::visible(*this);
        }

        /*!
            \brief Sets a visible status.

            \param visible A visible status.
        */
        void set_visible(const bool visible)
        {
            widget_details_type::set_visible(*this, visible);
        }

        /*!
            \brief Returns the focused status.

            \return The focused status.
        */
        bool focused()
        const
        {
            return m_focused;
        }

        /*!
            \brief Returns the position.

            \return The position.
        */
        position_type position()
        const
        {
            return widget_details_type::template position<position_type>(*this);
        }

        /*!
            \brief Sets a position.

            \tparam P A position type.

            \param position A position.
        */
        template <typename P>
        void set_position(const P& position)
        {
            widget_details_type::move(*this, position, dimension());
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension()
        const
        {
            return widget_details_type::template dimension<dimension_type>(*this);
        }

        /*!
            \brief Sets a dimension.

            \tparam D A dimension type.

            \param dimension A dimension.
        */
        template <typename D>
        void set_dimension(const D& dimension)
        {
            widget_details_type::move(*this, position(), dimension);
        }

        /*!
            \brief Returns the client dimension.

            \return The client dimension.
        */
        dimension_type client_dimension()
        const
        {
            return widget_details_type::template client_dimension<dimension_type>(*this);
        }

        /*!
            \brief Sets a client dimension.

            \tparam D A dimension type.

            \param client_dimension A client dimension.

            \throw std::invalid_argument When either client_dimension.first or client_dimension.second is equal to 0.
        */
        template <typename D>
        void set_client_dimension(const D& client_dimension)
        {
            if (gui::dimension<D>::width(client_dimension) == 0 || gui::dimension<D>::height(client_dimension) == 0)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Client dimension has zero value."));

            widget_details_type::template set_client_dimension<position_type>(
                *this, client_dimension
            );
        }

        /*!
            \brief Sets a position and a dimension.

            \tparam P A position type.
            \tparam D A dimension type.

            \param position  A position.
            \param dimension A dimension.
        */
        template <typename P, typename D>
        void set_position_and_dimension(const P& position, const D& dimension)
        {
            widget_details_type::move(*this, position, dimension);
        }

        /*!
            \brief Retuns the text.

            \return The text.
        */
        string_type text()
        const
        {
            return widget_details_type::template text<string_type>(*this, encoder());
        }

        /*!
            \brief Sets a text.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        void set_text(S&& text)
        {
            widget_details_type::set_text(*this, std::forward<S>(text), encoder());
        }

        /*!
            \brief Returns the background.

            When the system default background is used, this function returns an uninitialized value.

            \return The background or an uninitialized value.
        */
        boost::optional<const background_type&> background()
        const
        {
            return boost::make_optional<const background_type&>(static_cast<bool>(m_p_background), *m_p_background);
        }

        /*!
            \brief Sets a background.

            When p_background points to NULL, the system default background is used.

            \param p_background A unique pointer to a background.
        */
        void set_background(std::unique_ptr<background_type> p_background)
        {
            m_p_background = std::move(p_background);
        }

        /*!
            \brief Retuns the font.

            \return The font.
        */
        font_type font()
        const
        {
            return widget_details_type::template font<font_type>(*this, encoder());
        }

        /*!
            \brief Sets a font.

            \param font A font.
        */
        void set_font(const font_type& font)
        {
            widget_details_type::set_font(*this, font, encoder());
        }

        /*!
            \brief Returns the cursor.

            \return The cursor.
        */
        boost::optional<const cursor_type&> cursor()
        const
        {
            if (!m_p_cursor)
                return boost::none;

            return *m_p_cursor;
        }

        /*!
            \brief Sets a cursor.

            \param p_cursor A unique pointer to a cursor.
        */
        void set_cursor(std::unique_ptr<cursor_type> p_cursor)
        {
            m_p_cursor = std::move(p_cursor);
        }

        /*!
            \brief Returns the constant children.

            \return The children.
        */
        std::vector<typename cpp11::reference_wrapper<const child_type>::type> children()
        const
        {
            return widget_details_type::template children<const child_type>(*this);
        }

        /*!
            \brief Returns the children.

            \return The children.
        */
        std::vector<typename cpp11::reference_wrapper<child_type>::type> children()
        {
            return widget_details_type::template children<child_type>(*this);
        }

        /*!
            \brief Repaints the widget.
        */
        void repaint()
        const
        {
            widget_details_type::repaint(*this);
        }

        /*!
            \brief Creates a canvas.

            \return The unique pointer to a canvas.
        */
        std::unique_ptr<canvas_type> create_canvas()
        const
        {
            return make_unique<widget_canvas_type>(*details());
        }

        /*!
            \brief Clicks this widget.
        */
        void click()
        const
        {
            m_mouse_observer_set.clicked()();
        }

        /*!
            \brief Clicks this widget.
        */
        void click()
        {
            m_mouse_observer_set.clicked()();
        }

        /*!
            \brief Returns the focus observer set.

            \return The focus observer set.
        */
        const focus_observer_set_type& focus_observer_set()
        const
        {
            return m_focus_observer_set;
        }

        /*!
            \brief Returns the focus observer set.

            \return The focus observer set.
        */
        focus_observer_set_type& focus_observer_set()
        {
            return m_focus_observer_set;
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        const paint_observer_set_type& paint_observer_set()
        const
        {
            return m_paint_observer_set;
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        paint_observer_set_type& paint_observer_set()
        {
            return m_paint_observer_set;
        }

         /*!
            \brief Returns the keyboard observer set.

            \return The keyboard observer set.
        */
        const keyboard_observer_set_type& keyboard_observer_set()
        const
        {
            return m_keyboard_observer_set;
        }

        /*!
            \brief Returns the keyboard observer set.

            \return The keyboard observer set.
        */
        keyboard_observer_set_type& keyboard_observer_set()
        {
            return m_keyboard_observer_set;
        }

       /*!
            \brief Returns the mouse observer set.

            \return The mouse observer set.
        */
        const mouse_observer_set_type& mouse_observer_set()
        const
        {
            return m_mouse_observer_set;
        }

        /*!
            \brief Returns the mouse observer set.

            \return The mouse observer set.
        */
        mouse_observer_set_type& mouse_observer_set()
        {
            return m_mouse_observer_set;
        }

        /*!
            \brief Returns wether the widget is destroyed.

            \retval true  When the widget is destroyed.
            \retval false Otherwise.
        */
        bool destroyed()
        const
        {
            return m_destroyed;
        }

        /*!
            \brief Sets the status of the widget that it is already destroyed.
        */
        void set_destroyed()
        {
            m_destroyed = true;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        boost::optional<const details_type&> details()
        const
        {
            if (m_destroyed)
                BOOST_THROW_EXCEPTION(std::runtime_error("This widget is destroyed."));

            return details_impl();
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        boost::optional<details_type&> details()
        {
            if (m_destroyed)
                BOOST_THROW_EXCEPTION(std::runtime_error("This widget is destroyed."));

            return details_impl();
        }

        /*!
            \brief Returns the message handler map.

            \return The message handler map.
        */
        const message_handler_map_type& message_handler_map()
        const
        {
            return m_message_handler_map;
        }


    protected:
        // static functions

        /*!
            \brief Returns the encoder.

            \return The encoder.
        */
        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        /*!
            \brief Initializes the widget.

            This function must be called in the constructor and only in the constructor.

            \param p_widget A pointer to a widget.
        */
        static void initialize(widget* const p_widget)
        {
            assert(p_widget);

            widget_details_type::associate_to_native_window_system(*p_widget);
            p_widget->set_font(font_type::dialog_font());
        }


        // constructors and destructor

        /*!
            \brief Creates a widget.

            \param scroll_bar_style    A scroll bar style.
            \param message_handler_map A message handler map.
        */
        widget(const scroll_bar_style_type scroll_bar_style, message_handler_map_type&& message_handler_map)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        m_message_handler_map(
            message_handler_details_type::make_widget_message_handler_map(
                *this, std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_focused(false),
        m_destroyed(false),
        m_p_background(),
        m_p_cursor(),
        m_focus_observer_set(),
        m_paint_observer_set(),
        m_keyboard_observer_set(),
        m_mouse_observer_set()
        {
            m_focus_observer_set.got_focus().connect(got_focus(*this));
            m_focus_observer_set.lost_focus().connect(lost_focus(*this));
            m_paint_observer_set.paint_background().connect(paint_background(*this));
        }


    private:
        // types

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;

        class got_focus
        {
        public:
            got_focus(widget& self)
            :
            m_self(self)
            {}

            void operator()()
            const
            {
                m_self.m_focused = true;
            }

        private:
            widget& m_self;

        };

        class lost_focus
        {
        public:
            lost_focus(widget& self)
            :
            m_self(self)
            {}

            void operator()()
            const
            {
                m_self.m_focused = false;
            }

        private:
            widget& m_self;

        };

        class paint_background
        {
        public:
            paint_background(widget& self)
            :
            m_self(self)
            {}

            bool operator()(canvas_type& canvas)
            const
            {
                if (!m_self.background()) return false;

                canvas.fill_rectangle(
                    position_type(left_type(0), top_type(0)), m_self.client_dimension(), *m_self.background()
                );

                return true;
            }

        private:
            widget& m_self;

        };


        // variables

        const message_handler_map_type m_message_handler_map;

        bool m_focused;

        bool m_destroyed;

        std::unique_ptr<background_type> m_p_background;

        std::unique_ptr<cursor_type> m_p_cursor;

        focus_observer_set_type m_focus_observer_set;

        paint_observer_set_type m_paint_observer_set;

        keyboard_observer_set_type m_keyboard_observer_set;

        mouse_observer_set_type m_mouse_observer_set;


        // virtual functions

        virtual boost::optional<const details_type&> details_impl()
        const
        = 0;

        virtual boost::optional<details_type&> details_impl()
        = 0;


    };


}}}


#endif
