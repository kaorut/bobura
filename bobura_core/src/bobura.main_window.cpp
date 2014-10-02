/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/command/command_base.h>
#include <bobura/command/set.h>
#include <bobura/command/traits.h>
#include <bobura/main_window.h>
#include <bobura/main_window_traits.h>
#include <bobura/message/type_list.h>
#include <bobura/basic_type_list.h>


namespace bobura
{
    template <typename Traits>
    class main_window<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = typename main_window::size_type;

        using difference_type = typename main_window::difference_type;

        using string_type = typename main_window::string_type;

        using position_type = typename main_window::position_type;

        using dimension_type = typename main_window::dimension_type;

        using operating_distance_type = typename main_window::operating_distance_type;

        using speed_type = typename main_window::speed_type;

        using base_type = typename main_window::base_type;

        using abstract_window_type = typename main_window::abstract_window_type;

        using font_type = typename main_window::font_type;

        using config_traits_type = typename main_window::config_traits_type;

        using message_catalog_type = typename main_window::message_catalog_type;

        using diagram_picture_box_type = typename main_window::diagram_picture_box_type;

        using property_bar_type = typename main_window::property_bar_type;
        
        using settings_type = typename main_window::settings_type;

        using confirm_file_save_type = typename main_window::confirm_file_save_type;


        // constructors and destructor

        impl(
            base_type&                    base,
            const message_catalog_type&   message_catalog,
            settings_type&                settings,
            const confirm_file_save_type& confirm_file_save
        )
        :
        m_base(base),
        m_message_catalog(message_catalog),
        m_p_diagram_picture_box(),
        m_p_property_bar(),
        m_settings(settings),
        m_confirm_file_save(confirm_file_save)
        {
            initialize_window();
        }


        // functions

        void set_title(const boost::optional<string_type>& document_name, const bool changed)
        {
            auto title = document_name ? *document_name : m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));
            if (changed)
                title += string_type{ TETENGO2_TEXT(" *") };
            title += string_type{ TETENGO2_TEXT(" - ") };
            title += m_message_catalog.get(TETENGO2_TEXT("App:Bobura"));

            m_base.set_text(title);
        }

        const diagram_picture_box_type& get_diagram_picture_box()
        const
        {
            assert(m_p_diagram_picture_box);
            return *m_p_diagram_picture_box;
        }

        diagram_picture_box_type& get_diagram_picture_box()
        {
            assert(m_p_diagram_picture_box);
            return *m_p_diagram_picture_box;
        }

        const property_bar_type& get_property_bar()
        const
        {
            assert(m_p_property_bar);
            return *m_p_property_bar;
        }

        property_bar_type& get_property_bar()
        {
            assert(m_p_property_bar);
            return *m_p_property_bar;
        }


    private:
        // types

        using message_loop_break_type =
            tetengo2::gui::message::message_loop_break<
                typename boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >;

        using command_traits_type =
            command::traits<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                font_type,
                abstract_window_type
            >;

        using message_type_list_type =
            message::main_window::type_list<
                typename boost::mpl::at<ui_type_list, type::ui::popup_menu>::type,
                command::set<
                    command_traits_type,
                    typename boost::mpl::at<view_type_list, type::view::traits>::type,
                    position_type,
                    dimension_type,
                    typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    typename boost::mpl::at<ui_type_list, type::ui::color>::type,
                    typename boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
                    config_traits_type,
                    message_catalog_type
                >,
                command::command_base<command_traits_type>,
                timetable_model<
                    size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
                >,
                diagram_view<boost::mpl::at<view_type_list, type::view::traits>::type>,
                abstract_window_type,
                diagram_picture_box_type,
                property_bar_type,
                confirm_file_save_type
            >;


        // variables

        base_type& m_base;

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<diagram_picture_box_type> m_p_diagram_picture_box;

        std::unique_ptr<property_bar_type> m_p_property_bar;

        settings_type& m_settings;

        const confirm_file_save_type& m_confirm_file_save;


        // functions

        void initialize_window()
        {
            m_p_diagram_picture_box = tetengo2::stdalt::make_unique<diagram_picture_box_type>(m_base);
            m_p_property_bar = tetengo2::stdalt::make_unique<property_bar_type>(m_base, m_settings, m_message_catalog);

            set_message_observers();

            set_window_icon();
            set_title(boost::none, false);
                
            auto dimension = m_settings.main_window_dimension();
            if (dimension)
                m_base.set_dimension(std::move(*dimension));
            const auto maximized = m_settings.main_window_maximized();
            if (maximized && *maximized)
                m_base.set_window_state(window_state_type::maximized);
            else
                m_base.set_window_state(window_state_type::normal);
        }

        void set_message_observers()
        {
            m_base.focus_observer_set().got_focus().connect(
                [this]() { this->m_p_diagram_picture_box->set_focus(); }
            );
            m_base.paint_observer_set().paint_background().connect(
                [](base_type::canvas_type&) { return true; }
            );
            m_base.window_observer_set().closing().connect(
                typename boost::mpl::at<message_type_list_type, message::main_window::type::window_closing>::type(
                    m_base, m_confirm_file_save, [this]() { this->save_settings(); }
                )
            );
            m_base.window_observer_set().destroyed().connect([](){ return message_loop_break_type{}(0); });
        }

        void set_window_icon()
        {
            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(
                    m_settings.image_directory_path() / string_type{ TETENGO2_TEXT("bobura_app.ico") }
                );
            m_base.set_icon(std::move(p_icon));
        }

        void save_settings()
        {
            m_settings.set_main_window_dimension(m_base.normal_dimension());
            m_settings.set_main_window_maximized(m_base.window_state() == window_state_type::maximized);

            m_p_property_bar->save_settings();
        }


    };


    template <typename Traits>
    main_window<Traits>::main_window(
        const message_catalog_type&   message_catalog,
        settings_type&                settings,
        const confirm_file_save_type& confirm_file_save
    )
    :
    base_type(base_type::scroll_bar_style_type::none, true),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(*this, message_catalog, settings, confirm_file_save))
    {}

    template <typename Traits>
    main_window<Traits>::~main_window()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits>
    void main_window<Traits>::set_title(const boost::optional<string_type>& document_name, const bool changed)
    {
        m_p_impl->set_title(document_name, changed);
    }

    template <typename Traits>
    const typename main_window<Traits>::diagram_picture_box_type& main_window<Traits>::get_diagram_picture_box()
    const
    {
        return m_p_impl->get_diagram_picture_box();
    }

    template <typename Traits>
    typename main_window<Traits>::diagram_picture_box_type& main_window<Traits>::get_diagram_picture_box()
    {
        return m_p_impl->get_diagram_picture_box();
    }

    template <typename Traits>
    const typename main_window<Traits>::property_bar_type& main_window<Traits>::get_property_bar()
    const
    {
        return m_p_impl->get_property_bar();
    }

    template <typename Traits>
    typename main_window<Traits>::property_bar_type& main_window<Traits>::get_property_bar()
    {
        return m_p_impl->get_property_bar();
    }


    template class main_window<
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
            typename boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
            typename boost::mpl::at<ui_type_list, type::ui::map_box>::type,
            typename boost::mpl::at<ui_type_list, type::ui::side_bar>::type,
            typename boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
            typename boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type,
            typename boost::mpl::at<setting_type_list, type::setting::config_traits>::type,
            message::diagram_picture_box::type_list<
                typename boost::mpl::at<view_type_list, type::view::traits>::type,
                typename boost::mpl::at<ui_type_list, type::ui::picture_box>::type
            >,
            typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
            typename boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type
        >
    >;


}
