/*! \file
    \brief The definition of tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_MAPBOX_H)
#define TETENGO2_GUI_WIDGET_MAPBOX_H

//#include <memory>
//#include <utility>

//#include <boost/noncopyable.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.custom_control.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a map box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class map_box : public custom_control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The solid background type.
        typedef typename traits_type::solid_background_type solid_background_type;

        //! The system color set type.
        typedef typename traits_type::system_color_set_type system_color_set_type;

        //! The mouse capture type.
        typedef typename traits_type::mouse_capture_type mouse_capture_type;

        //! The system cursor type.
        typedef typename traits_type::system_cursor_type system_cursor_type;

        //! The cursor type.
        typedef typename system_cursor_type::base_type cursor_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            custom_control<typename traits_type::base_type, widget_details_type, message_handler_details_type>
            base_type;

        //! The widget type.
        typedef typename base_type::base_type::base_type widget_type;

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;


        // constructors and destructor

        /*!
            \brief Creates a map box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        map_box(widget_type& parent, const scroll_bar_style_type scroll_bar_style)
        :
        base_type(parent, true, scroll_bar_style),
        m_splitter_position(left_type(8)),
        m_p_splitter(),
        m_p_mouse_capture(),
        m_p_mouse_captured_item(nullptr)
        {
            initialize_map_box(*this);
        }

        /*!
            \brief Destroys the map box.
        */
        virtual ~map_box()
        TETENGO2_STDALT_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        typedef typename mouse_observer_set_type::mouse_button_type mouse_button_type;

        typedef typename base_type::canvas_type canvas_type;

        typedef typename base_type::position_type position_type;

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;

        typedef typename base_type::dimension_type dimension_type;

        typedef typename gui::dimension<dimension_type>::width_type width_type;

        typedef typename gui::dimension<dimension_type>::height_type height_type;

        class item : boost::noncopyable
        {
        public:
            // functions

            const position_type& position()
            const
            {
                return m_position;
            }

            void set_position(position_type position)
            {
                m_position = std::move(position);
            }

            const dimension_type& dimension()
            const
            {
                return m_dimension;
            }

            void set_dimension(dimension_type dimension)
            {
                m_dimension = std::move(dimension);
            }

            void resized()
            {
                resized_impl();
            }

            void paint(canvas_type& canvas)
            const
            {
                paint_impl(canvas);
            }

            void mouse_pressed(const position_type& cursor_position)
            {
                if (!inside(cursor_position))
                    return;

                mouse_pressed_impl(cursor_position);
            }

            void mouse_released(const position_type& cursor_position)
            {
                if (!this->map_box_().mouse_captured(this) && !inside(cursor_position))
                    return;

                mouse_released_impl(cursor_position);
            }

            void mouse_moved(const position_type& cursor_position)
            {

                if (this->map_box_().mouse_captured(this) || inside(cursor_position))
                {
                    mouse_moved_impl(cursor_position);
                    if (!m_mouse_inside)
                    {
                        mouse_entered_impl();
                        m_mouse_inside = true;
                    }
                }
                else
                {
                    if (m_mouse_inside)
                    {
                        mouse_left_impl();
                        m_mouse_inside = false;
                    }
                }
            }


        protected:
            // constructors

            explicit item(map_box& map_box_)
            :
            m_map_box(map_box_),
            m_position(left_type(0), top_type(0)),
            m_dimension(width_type(0), height_type(0)),
            m_mouse_inside(false)
            {}


            // functions

            const map_box& map_box_()
            const
            {
                return m_map_box;
            }

            map_box& map_box_()
            {
                return m_map_box;
            }


        private:
            // variables

            map_box& m_map_box;

            position_type m_position;

            dimension_type m_dimension;

            bool m_mouse_inside;


            // virtual functions

            virtual void resized_impl()
            = 0;

            virtual void paint_impl(canvas_type& canvas)
            const = 0;

            virtual void mouse_pressed_impl(const position_type& cursor_position)
            {
                suppress_unused_variable_warning(cursor_position);
            }

            virtual void mouse_released_impl(const position_type& cursor_position)
            {
                suppress_unused_variable_warning(cursor_position);
            }

            virtual void mouse_moved_impl(const position_type& cursor_position)
            {
                suppress_unused_variable_warning(cursor_position);
            }

            virtual void mouse_entered_impl()
            {}

            virtual void mouse_left_impl()
            {}


            // functions

            bool inside(const position_type& position)
            const
            {
                const auto& left = gui::position<position_type>::left(m_position);
                const auto right = left + left_type::from(gui::dimension<dimension_type>::width(m_dimension));
                const auto& top = gui::position<position_type>::top(m_position);
                const auto bottom = top + top_type::from(gui::dimension<dimension_type>::height(m_dimension));

                const auto& cursor_left = gui::position<position_type>::left(position);
                const auto& cursor_top = gui::position<position_type>::top(position);

                return (left <= cursor_left && cursor_left < right) && (top <= cursor_top && cursor_top < bottom);
            }


        };

        class splitter : public item
        {
        public:
            // constructors and destructor

            explicit splitter(map_box& map_box_)
            :
            item(map_box_)
            {}


        private:
            // static functions

            static const width_type& width()
            {
                static const width_type singleton(width_type(1) / 2);
                return singleton;
            }


            // virtual functions

            virtual void resized_impl()
            override
            {
                static const width_type splitter_width(width_type(1) / 2);

                this->set_position(position_type(this->map_box_().m_splitter_position - width() / 2, top_type(0)));

                const dimension_type map_box_client_dimension = this->map_box_().client_dimension();
                this->set_dimension(
                    dimension_type(width(), gui::dimension<dimension_type>::height(map_box_client_dimension))
                );
            }

            virtual void paint_impl(canvas_type& canvas)
            const override
            {
                std::unique_ptr<solid_background_type> p_background =
                    stdalt::make_unique<solid_background_type>(system_color_set_type::dialog_background());
                canvas.set_background(std::move(p_background));
                canvas.fill_rectangle(this->position(), this->dimension());
            }


        };


        // static functions

        static void initialize_map_box(map_box& map_box_)
        {
            map_box_.m_p_splitter = stdalt::make_unique<splitter>(map_box_);

            map_box_.size_observer_set().resized().connect(
                [&map_box_]()
                {
                    map_box_.m_p_splitter->resized();
                }
            );

            map_box_.set_background(
                stdalt::make_unique<solid_background_type>(system_color_set_type::control_background())
            );

            map_box_.paint_observer_set().paint_background().disconnect_all_slots();
            map_box_.paint_observer_set().paint_background().connect(
                [&map_box_](canvas_type& canvas)
                {
                    return map_box_.paint_background(canvas);
                }
            );
            map_box_.paint_observer_set().paint().connect(
                [&map_box_](canvas_type& canvas) {
                    map_box_.m_p_splitter->paint(canvas);
                }
            );

            map_box_.mouse_observer_set().pressed().connect(
                [&map_box_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    if (button != mouse_button_type::left)
                        return;

                    map_box_.m_p_splitter->mouse_pressed(position);
                }
            );
            map_box_.mouse_observer_set().released().connect(
                [&map_box_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    if (button != mouse_button_type::left)
                        return;

                    map_box_.m_p_splitter->mouse_released(position);
                }
            );
            map_box_.mouse_observer_set().moved().connect(
                [&map_box_](const position_type& position, bool, bool, bool)
                {
                    map_box_.m_p_splitter->mouse_moved(position);
                }
            );
        }


        // variables

        left_type m_splitter_position;

        std::unique_ptr<item> m_p_splitter;

        std::unique_ptr<mouse_capture_type> m_p_mouse_capture;

        const item* m_p_mouse_captured_item;


        // functions

        bool paint_background(canvas_type& canvas)
        const
        {
            if (!this->background())
                return false;

            canvas.set_background(this->background()->clone());
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), this->client_dimension());

            return true;
        }

        bool mouse_captured(const item* const p_item)
        const
        {
            return static_cast<bool>(m_p_mouse_capture) && m_p_mouse_captured_item == p_item;
        }

        void set_mouse_capture(const item* const p_item)
        {
            m_p_mouse_capture = stdalt::make_unique<mouse_capture_type>(*this);
            m_p_mouse_captured_item = p_item;
        }

        void release_mouse_capture()
        {
            m_p_mouse_captured_item = nullptr;
            m_p_mouse_capture.reset();
        }


    };


}}}


#endif
