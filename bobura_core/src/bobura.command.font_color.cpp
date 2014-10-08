/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/font_color.h>
#include <bobura/command/traits.h>
#include <bobura/font_color_dialog.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
        typename MessageCatalog,
        typename DialogTraits
    >
    class font_color<Traits, Dialog, PointUnitSize, Color, MessageCatalog, DialogTraits>::impl
    {
    public:
        // types

        using traits_type = typename font_color::traits_type;

        using model_type = typename font_color::model_type;

        using abstract_window_type = typename font_color::abstract_window_type;

        using dialog_type = typename font_color::dialog_type;

        using point_unit_size_type = typename font_color::point_unit_size_type;

        using color_type = typename font_color::color_type;

        using message_catalog_type = typename font_color::message_catalog_type;

        using dialog_traits_type = typename font_color::dialog_traits_type;


        // constructors and destructor

        explicit impl(const message_catalog_type& message_catalog)
        :
        m_message_catalog(message_catalog)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            font_color_dialog_type dialog{ parent, m_message_catalog };

            const auto& font_color_set = model.timetable().font_color_set();
            dialog.set_background(font_color_set.background());
            dialog.set_company_line_name(
                font_color_set.company_line_name().font(), font_color_set.company_line_name().color()
            );
            dialog.set_note(font_color_set.note().font(), font_color_set.note().color());
            dialog.set_time_line(font_color_set.time_line().font(), font_color_set.time_line().color());
            dialog.set_local_station(font_color_set.local_station().font(), font_color_set.local_station().color());
            dialog.set_principal_station(
                font_color_set.principal_station().font(), font_color_set.principal_station().color()
            );
            dialog.set_local_terminal_station(
                font_color_set.local_terminal_station().font(), font_color_set.local_terminal_station().color()
            );
            dialog.set_principal_terminal_station(
                font_color_set.principal_terminal_station().font(),
                font_color_set.principal_terminal_station().color()
            );
            dialog.set_train_name(font_color_set.train_name());

            dialog.do_modal();
            if (dialog.result() != dialog_type::result_type::accepted)
                return;
        
            font_color_set_type new_font_color_set{
                dialog.background(),
                font_color_type{ dialog.company_line_name().first, dialog.company_line_name().second },
                font_color_type{ dialog.note().first, dialog.note().second },
                font_color_type{ dialog.time_line().first, dialog.time_line().second },
                font_color_type{ dialog.local_station().first, dialog.local_station().second },
                font_color_type{ dialog.principal_station().first, dialog.principal_station().second },
                font_color_type{ dialog.local_terminal_station().first, dialog.local_terminal_station().second },
                font_color_type{
                    dialog.principal_terminal_station().first, dialog.principal_terminal_station().second
                },
                dialog.train_name()
            };
            model.timetable().set_font_color_set(std::move(new_font_color_set));
        }


    private:
        // types

        using size_type = typename traits_type::size_type;

        using font_type = typename traits_type::font_type;

        using font_color_set_type = typename model_type::timetable_type::font_color_set_type;

        using font_color_type = typename font_color_set_type::font_color_type;

        using font_color_dialog_type =
            font_color_dialog<dialog_traits_type, size_type, font_type, point_unit_size_type, color_type>;


        // variables

        const message_catalog_type& m_message_catalog;


    };


    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
        typename MessageCatalog,
        typename DialogTraits
    >
    font_color<Traits, Dialog, PointUnitSize, Color, MessageCatalog, DialogTraits>::font_color(
        const message_catalog_type& message_catalog
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog))
    {}

    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
        typename MessageCatalog,
        typename DialogTraits
    >
    font_color<Traits, Dialog, PointUnitSize, Color, MessageCatalog, DialogTraits>::~font_color()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
        typename MessageCatalog,
        typename DialogTraits
    >
    void font_color<Traits, Dialog, PointUnitSize, Color, MessageCatalog, DialogTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class font_color<
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
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
        typename boost::mpl::at<ui_type_list, type::ui::color>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<main_window_type_list, type::main_window::dialog_traits>::type
    >;


}}
