/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/format.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/about_dialog.h>
#include <bobura/dialog_traits.h>
#include <bobura/message/type_list_impl.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <typename Traits, typename ConfigTraits>
    class about_dialog<Traits, ConfigTraits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename about_dialog::traits_type;

        using string_type = typename about_dialog::string_type;

        using position_type = typename about_dialog::position_type;

        using dimension_type = typename about_dialog::dimension_type;

        using base_type = typename about_dialog::base_type;

        using message_catalog_type = typename about_dialog::message_catalog_type;

        using settings_type = typename about_dialog::settings_type;


        // constructors and destructor

        impl(base_type& base, const message_catalog_type& message_catalog, const settings_type& settings)
        :
        m_base(base),
        m_message_catalog(message_catalog),
        m_settings(settings),
        m_p_application_image(),
        m_p_title_label(),
        m_p_copyright_label(),
        m_p_link_label(),
        m_p_ok_button()
        {
            initialize_dialog();
        }


    private:
        // types

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using label_type = typename traits_type::label_type;

        using color_type = typename label_type::color_type;

        using link_label_type = typename traits_type::link_label_type;

        using image_type = typename traits_type::image_type;

        using icon_type = typename image_type::icon_type;

        using button_type = typename traits_type::button_type;

        using transparent_background_type = typename traits_type::transparent_background_type;

        using about_dialog_message_type_list_type = message::about_dialog::type_list<base_type>;


        // variables

        base_type& m_base;

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;

        std::unique_ptr<image_type> m_p_application_image;

        std::unique_ptr<label_type> m_p_title_label;

        std::unique_ptr<label_type> m_p_copyright_label;

        std::unique_ptr<link_label_type> m_p_link_label;

        std::unique_ptr<button_type> m_p_ok_button;


        // functions

        void initialize_dialog()
        {
            m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:About:About")));

            m_p_application_image = create_application_image();
            m_p_title_label = create_title_label();
            m_p_copyright_label = create_copyright_label();
            m_p_link_label = create_link_label();
            m_p_ok_button = create_ok_button();

            locate_controls();
        }

        std::unique_ptr<image_type> create_application_image()
        {
            auto p_image = tetengo2::stdalt::make_unique<image_type>(m_base);

            auto p_icon =
                tetengo2::stdalt::make_unique<icon_type>(
                    m_settings.image_directory_path() / string_type{ TETENGO2_TEXT("bobura_app.ico") },
                    dimension_type{ width_type{ 4 }, height_type{ 4 } }
                );
            p_image->set_icon(std::move(p_icon));

            return std::move(p_image);
        }

        std::unique_ptr<label_type> create_title_label()
        {
            using char_type = typename string_type::value_type;
            std::basic_ostringstream<char_type> title{};
            title <<
                boost::basic_format<char_type>(TETENGO2_TEXT("%s  %s %s")) %
                m_message_catalog.get(TETENGO2_TEXT("App:Bobura")) %
                m_message_catalog.get(TETENGO2_TEXT("Dialog:About:version")) %
                string_type{ TETENGO2_TEXT("0.0.0") };

            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(title.str());
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<label_type> create_copyright_label()
        {
            auto p_label = tetengo2::stdalt::make_unique<label_type>(m_base);

            p_label->set_text(string_type{ TETENGO2_TEXT("Copyright (C) 2007-2014 kaoru") });
            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<link_label_type> create_link_label()
        {
            auto p_label =tetengo2::stdalt::make_unique<link_label_type>(m_base);

            p_label->set_text(string_type{ TETENGO2_TEXT("http://www.tetengo.org/") });
            p_label->set_target(p_label->text());

            return std::move(p_label);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            auto p_button = tetengo2::stdalt::make_unique<button_type>(m_base, button_type::style_type::default_);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    about_dialog_message_type_list_type, message::about_dialog::type::ok_button_mouse_clicked
                >::type{ m_base }
            );

            return std::move(p_button);
        }

        void locate_controls()
        {
            m_base.set_client_dimension(dimension_type{ width_type{ 36 }, height_type{ 10 } });

            m_p_application_image->fit_to_content();
            m_p_application_image->set_position(position_type{ left_type{ 2 }, top_type{ 1 } });
            
            const auto label_left =
                left_type{ 2 } +
                tetengo2::gui::dimension<dimension_type>::width(m_p_application_image->dimension()) +
                left_type{ 1 };

            m_p_title_label->fit_to_content();
            m_p_title_label->set_position(position_type{ label_left, top_type{ 1 } });

            m_p_copyright_label->fit_to_content();
            m_p_copyright_label->set_position(position_type{ label_left, top_type{ 3 } });

            m_p_link_label->fit_to_content();
            m_p_link_label->set_position(position_type{ label_left, top_type{ 5 } });

            m_p_ok_button->set_dimension(dimension_type{ width_type{ 8 }, height_type{ 2 } });
            m_p_ok_button->set_position(position_type{ left_type{ 26 }, top_type{ 7 } });
        }


    };


    template <typename Traits, typename ConfigTraits>
    about_dialog<Traits, ConfigTraits>::about_dialog(
        abstract_window_type&       parent,
        const message_catalog_type& message_catalog,
        const settings_type&        settings
    )
    :
    base_type(parent),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(*this, message_catalog, settings))
    {}

    template <typename Traits, typename ConfigTraits>
    about_dialog<Traits, ConfigTraits>::~about_dialog()
    TETENGO2_STDALT_NOEXCEPT
    {}


    namespace
    {
        namespace application
        {
            using detail_type_list_type = detail_type_list_for_application;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }

        namespace test
        {
            using detail_type_list_type = detail_type_list_for_test;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }

    }

    template class about_dialog<
        typename boost::mpl::at<application::traits_type_list_type, type::traits::dialog>::type,
        typename boost::mpl::at<application::traits_type_list_type, type::traits::config>::type
    >;

    template class about_dialog<
        typename boost::mpl::at<test::traits_type_list_type, type::traits::dialog>::type,
        typename boost::mpl::at<test::traits_type_list_type, type::traits::config>::type
    >;


}
