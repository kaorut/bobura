/*! \file
    \brief The definition of bobura::view_picture_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2/stdalt.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view_picture_box.h>


namespace bobura
{
    template <typename PictureBox, typename MouseCapture>
    class view_picture_box<PictureBox, MouseCapture>::impl : private boost::noncopyable
    {
    public:
        // types

        using widget_type = typename view_picture_box::widget_type;

        using dimension_type = typename view_picture_box::dimension_type;

        using mouse_button_type = typename view_picture_box::mouse_button_type;


        // constructors and destructor

        explicit impl(widget_type&)
        :
        m_p_mouse_capture()
        {}


        // functions

        void set_mouse_capture(view_picture_box& self, const mouse_button_type mouse_button)
        {
            assert(!m_p_mouse_capture);
            m_p_mouse_capture = tetengo2::stdalt::make_unique<mouse_capture_type>(self, mouse_button);
        }

        bool release_mouse_capture(const mouse_button_type mouse_button)
        {
            if (m_p_mouse_capture && m_p_mouse_capture->button() == mouse_button)
            {
                m_p_mouse_capture.reset();
                return true;
            }
            else
            {
                return false;
            }
        }

        void update_scroll_bars(
            view_picture_box&     self,
            const dimension_type& view_dimension,
            const dimension_type& page_dimension
        )
        {
            assert(self.has_vertical_scroll_bar());
            assert(self.has_horizontal_scroll_bar());
            
            update_scroll_bar(
                self.vertical_scroll_bar(),
                view_dimension.height(),
                boost::rational_cast<scroll_bar_size_type>(page_dimension.height().value())
            );
            update_scroll_bar(
                self.horizontal_scroll_bar(),
                view_dimension.width(),
                boost::rational_cast<scroll_bar_size_type>(page_dimension.width().value())
            );
        }


    private:
        // types

        using base_type = PictureBox;

        using mouse_capture_type = MouseCapture;
        
        using scroll_bar_type = typename base_type::scroll_bar_type;

        using scroll_bar_size_type = typename scroll_bar_type::size_type;


        // variables

        std::unique_ptr<mouse_capture_type> m_p_mouse_capture;


        // functions

        template <typename Size>
        void update_scroll_bar(
            scroll_bar_type&           scroll_bar,
            const Size&                view_size,
            const scroll_bar_size_type page_size

        )
        {
            const auto size =
                view_size.value() > 0 ? boost::rational_cast<scroll_bar_size_type>(view_size.value()) - 1 : 0;
            const auto previous_size = scroll_bar.range().second;

            if (view_size > Size{ 0 } && page_size > scroll_bar_size_type{ 0 } && page_size <= size)
            {
                scroll_bar.set_enabled(true);
                scroll_bar.set_range(std::make_pair(0U, size));
                scroll_bar.set_page_size(page_size);

                if (scroll_bar.position() + page_size > size)
                {
                    const auto new_position = size - page_size + 1;
                    scroll_bar.set_position(new_position);
                    scroll_bar.scroll_bar_observer_set().scrolled()(new_position);
                }
                else if (previous_size > 0 && previous_size != view_size.value())
                {
                    const auto new_position =
                        calculate_scroll_bar_position(
                            scroll_bar, view_size, previous_size, page_size, size - page_size + 1
                        );
                    if (new_position != scroll_bar.position())
                    {
                        scroll_bar.set_position(new_position);
                        scroll_bar.scroll_bar_observer_set().scrolled()(new_position);
                    }
                }
            }
            else
            {
                if (view_size <= page_size)
                {
                    const scroll_bar_size_type new_position = 0;
                    if (new_position != scroll_bar.position())
                    {
                        scroll_bar.set_position(new_position);
                        scroll_bar.scroll_bar_observer_set().scrolled()(new_position);
                    }
                }

                scroll_bar.set_enabled(false);
            }
        }

        template <typename ViewSize>
        scroll_bar_size_type calculate_scroll_bar_position(
            const scroll_bar_type&     scroll_bar,
            const ViewSize&            view_size,
            const scroll_bar_size_type previous_size,
            const scroll_bar_size_type page_size,
            const scroll_bar_size_type max
        )
        const
        {
            const boost::rational<scroll_bar_size_type> change_rate{ view_size.value() / previous_size };
            const boost::rational<scroll_bar_size_type> half_page_size{ page_size, 2 };
            if ((scroll_bar.position() + half_page_size) * change_rate < half_page_size)
                return 0;
            const boost::rational<scroll_bar_size_type> new_position{
                (scroll_bar.position() + half_page_size) * change_rate - half_page_size
            };
            if (new_position > boost::rational<scroll_bar_size_type>(max))
                return max;
            return boost::rational_cast<scroll_bar_size_type>(new_position);
        }


    };


    template <typename PictureBox, typename MouseCapture>
    view_picture_box<PictureBox, MouseCapture>::view_picture_box(widget_type& parent)
    :
    base_type(parent, base_type::scroll_bar_style_type::both),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(parent))
    {}

    template <typename PictureBox, typename MouseCapture>
    view_picture_box<PictureBox, MouseCapture>::~view_picture_box()
    noexcept
    {}

    template <typename PictureBox, typename MouseCapture>
    void view_picture_box<PictureBox, MouseCapture>::set_mouse_capture(const mouse_button_type mouse_button)
    {
        m_p_impl->set_mouse_capture(*this, mouse_button);
    }

    template <typename PictureBox, typename MouseCapture>
    bool view_picture_box<PictureBox, MouseCapture>::release_mouse_capture(const mouse_button_type mouse_button)
    {
        return m_p_impl->release_mouse_capture(mouse_button);
    }

    template <typename PictureBox, typename MouseCapture>
    void view_picture_box<PictureBox, MouseCapture>::update_scroll_bars(
        const dimension_type& view_dimension,
        const dimension_type& page_dimension
    )
    {
        m_p_impl->update_scroll_bars(*this, view_dimension, page_dimension);
    }


    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class view_picture_box<
        typename application::ui_type_list_type::picture_box_type,
        typename application::ui_type_list_type::mouse_capture_type
    >;
#endif

    template class view_picture_box<
        typename test::ui_type_list_type::picture_box_type,
        typename test::ui_type_list_type::mouse_capture_type
    >;


}
