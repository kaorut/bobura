/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/about_dialog.h>
#include <bobura/basic_type_list.h>
#include <bobura/command/about.h>
#include <bobura/command/traits.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Label,
        typename LinkLabel,
        typename Image,
        typename Button,
        typename TransparentBackground,
        typename MessageCatalog,
        typename ConfigTraits
    >
    class about<
        Traits,
        Position,
        Dimension,
        Dialog,
        Label,
        LinkLabel,
        Image,
        Button,
        TransparentBackground,
        MessageCatalog,
        ConfigTraits
    >::impl
    {
    public:
        // types

        using model_type = typename about::model_type;

        using abstract_window_type = typename about::abstract_window_type;

        using dialog_type = typename about::dialog_type;

        using label_type = typename about::label_type;

        using link_label_type = typename about::link_label_type;

        using image_type = typename about::image_type;

        using button_type = typename about::button_type;

        using transparent_background_type = typename about::transparent_background_type;

        using message_catalog_type = typename about::message_catalog_type;

        using config_traits_type = typename about::config_traits_type;

        using settings_type = typename about::settings_type;


        // constructors and destructor

        impl(const message_catalog_type& message_catalog, const settings_type& settings)
        :
        m_message_catalog(message_catalog),
        m_settings(settings)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            about_dialog_type{ parent, m_message_catalog, m_settings }.do_modal();
        }


    private:
        // types

        using about_dialog_type =
            about_dialog<
                string_type,
                position_type,
                dimension_type,
                dialog_type,
                label_type,
                link_label_type,
                image_type,
                button_type,
                transparent_background_type,
                message_catalog_type,
                config_traits_type
            >;


        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


    };


    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Label,
        typename LinkLabel,
        typename Image,
        typename Button,
        typename TransparentBackground,
        typename MessageCatalog,
        typename ConfigTraits
    >
    about<
        Traits,
        Position,
        Dimension,
        Dialog,
        Label,
        LinkLabel,
        Image,
        Button,
        TransparentBackground,
        MessageCatalog,
        ConfigTraits
    >::about(
        const message_catalog_type& message_catalog,
        const settings_type&        settings
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog, settings))
    {}

    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Label,
        typename LinkLabel,
        typename Image,
        typename Button,
        typename TransparentBackground,
        typename MessageCatalog,
        typename ConfigTraits
    >
    about<
        Traits,
        Position,
        Dimension,
        Dialog,
        Label,
        LinkLabel,
        Image,
        Button,
        TransparentBackground,
        MessageCatalog,
        ConfigTraits
    >::~about()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename Label,
        typename LinkLabel,
        typename Image,
        typename Button,
        typename TransparentBackground,
        typename MessageCatalog,
        typename ConfigTraits
    >
    void about<
        Traits,
        Position,
        Dimension,
        Dialog,
        Label,
        LinkLabel,
        Image,
        Button,
        TransparentBackground,
        MessageCatalog,
        ConfigTraits
    >::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class about<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
            typename boost::mpl::at<ui_type_list, type::ui::mouse_capture>::type
        >,
        typename boost::mpl::at<ui_type_list, type::ui::position>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dimension>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<ui_type_list, type::ui::label>::type,
        typename boost::mpl::at<ui_type_list, type::ui::link_label>::type,
        typename boost::mpl::at<ui_type_list, type::ui::image>::type,
        typename boost::mpl::at<ui_type_list, type::ui::button>::type,
        typename boost::mpl::at<ui_type_list, type::ui::transparent_background>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<bobura::setting_type_list, bobura::type::setting::config_traits>::type
    >;


}}
