/*! \file
    \brief The definition of bobura::command::horizontally_zoom_out.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/horizontally_zoom_out.h>
#include <bobura/main_window.h>
#include <bobura/main_window_traits.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace command
{
    class horizontally_zoom_out::impl
    {
    public:
        // types

        using model_type = horizontally_zoom_out::model_type;

        using abstract_window_type = horizontally_zoom_out::abstract_window_type;

        using diagram_view_type = horizontally_zoom_out::diagram_view_type;


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

            zoom.horizontally_zoom_out(true);
        }


    private:
        // types

        using picture_box_type = boost::mpl::at<ui_type_list, type::ui::picture_box>::type;

        using main_window_traits_type =
            main_window_traits<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<ui_type_list, type::ui::position>::type,
                boost::mpl::at<ui_type_list, type::ui::dimension>::type,
                boost::mpl::at<common_type_list, type::output_stream>::type,
                boost::mpl::at<model_type_list, type::model::operating_distance>::type,
                boost::mpl::at<model_type_list, type::model::speed>::type,
                boost::mpl::at<ui_type_list, type::ui::window>::type,
                picture_box_type,
                boost::mpl::at<ui_type_list, type::ui::map_box>::type,
                boost::mpl::at<ui_type_list, type::ui::side_bar>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type,
                boost::mpl::at<setting_type_list, type::setting::config_traits>::type,
                message::diagram_picture_box::type_list<
                    boost::mpl::at<view_type_list, type::view::traits>::type, picture_box_type
                >,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type
            >;

        using main_window_type = main_window<main_window_traits_type>;

        using traits_type = boost::mpl::at<view_type_list, type::view::traits>::type;

        using zoom_type = view::diagram::zoom<traits_type, picture_box_type>;


        // variables

        diagram_view_type& m_diagram_view;


    };


    horizontally_zoom_out::horizontally_zoom_out(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view))
    {}

    horizontally_zoom_out::~horizontally_zoom_out()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void horizontally_zoom_out::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
