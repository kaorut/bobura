/*! \file
    \brief The definition of bobura::command::vertically_zoom_out.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/vertically_zoom_out.h>
#include <bobura/command/traits.h>
#include <bobura/main_window.h>
#include <bobura/main_window_traits.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace command
{
    template <typename Traits, typename ViewTraits>
    class vertically_zoom_out<Traits, ViewTraits>::impl
    {
    public:
        // types

        using model_type = typename vertically_zoom_out::model_type;

        using abstract_window_type = typename vertically_zoom_out::abstract_window_type;

        using diagram_view_type = typename vertically_zoom_out::diagram_view_type;


        // constructors and destructor

        explicit impl(diagram_view_type& diagram_view)
        :
        m_diagram_view(diagram_view)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom{ p_main_window->get_diagram_picture_box(), m_diagram_view };

            zoom.vertically_zoom_out(true);
        }


    private:
        // types

        using picture_box_type = typename boost::mpl::at<ui_type_list, type::ui::picture_box>::type;

        using main_window_traits_type =
            main_window_traits<
                typename boost::mpl::at<common_type_list, type::size>::type,
                typename boost::mpl::at<common_type_list, type::difference>::type,
                typename boost::mpl::at<common_type_list, type::string>::type,
                typename boost::mpl::at<ui_type_list, type::ui::position>::type,
                typename boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                typename boost::mpl::at<common_type_list, type::output_stream>::type,
                typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                typename boost::mpl::at<model_type_list, type::model::speed>::type,
                typename boost::mpl::at<ui_type_list, type::ui::window>::type,
                picture_box_type,
                typename boost::mpl::at<ui_type_list, type::ui::map_box>::type,
                typename boost::mpl::at<ui_type_list, type::ui::side_bar>::type,
                typename boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                typename boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
                typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                typename boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type,
                typename boost::mpl::at<setting_type_list, type::setting::config_traits>::type,
                typename boost::mpl::at<load_save_type_list, type::load_save::traits>::type,
                message::diagram_picture_box::type_list<
                    typename boost::mpl::at<view_type_list, type::view::traits>::type, picture_box_type
                >,
                typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                typename boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type
            >;

        using main_window_type = main_window<main_window_traits_type>;

        using traits_type = typename boost::mpl::at<view_type_list, type::view::traits>::type;

        using zoom_type = typename view::diagram::zoom<traits_type, picture_box_type>;


        // variables

        diagram_view_type& m_diagram_view;


    };


    template <typename Traits, typename ViewTraits>
    vertically_zoom_out<Traits, ViewTraits>::vertically_zoom_out(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view))
    {}

    template <typename Traits, typename ViewTraits>
    vertically_zoom_out<Traits, ViewTraits>::~vertically_zoom_out()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename ViewTraits>
    void vertically_zoom_out<Traits, ViewTraits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class vertically_zoom_out<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type
        >,
        typename boost::mpl::at<view_type_list, type::view::traits>::type
    >;


}}
