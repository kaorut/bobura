/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/noncopyable.hpp>

#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/command/font_color.h>
#include <bobura/font_color_dialog.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    class font_color<
        Traits, Dialog, PointUnitSize, Color, Canvas, FontDialog, ColorDialog, MessageCatalog, DialogTraits
    >::impl :
        private boost::noncopyable
    {
    public:
        // types

        using traits_type = typename font_color::traits_type;

        using dialog_type = typename font_color::dialog_type;

        using point_unit_size_type = typename font_color::point_unit_size_type;

        using color_type = typename font_color::color_type;

        using canvas_type = typename font_color::canvas_type;

        using font_dialog_type = typename font_color::font_dialog_type;

        using color_dialog_type = typename font_color::color_dialog_type;

        using message_catalog_type = typename font_color::message_catalog_type;

        using dialog_traits_type = typename font_color::dialog_traits_type;

        using abstract_window_type = typename font_color::abstract_window_type;

        using model_type = typename font_color::model_type;


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
            font_color_dialog<
                dialog_traits_type,
                size_type,
                font_type,
                point_unit_size_type,
                color_type,
                canvas_type,
                font_dialog_type,
                color_dialog_type
            >;


        // variables

        const message_catalog_type& m_message_catalog;


    };


    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    font_color<
        Traits, Dialog, PointUnitSize, Color, Canvas, FontDialog, ColorDialog, MessageCatalog, DialogTraits
    >::font_color(
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
        typename Canvas,
        typename FontDialog,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    font_color<
        Traits, Dialog, PointUnitSize, Color, Canvas, FontDialog, ColorDialog, MessageCatalog, DialogTraits
    >::~font_color()
    noexcept
    {}
    
    template <
        typename Traits,
        typename Dialog,
        typename PointUnitSize,
        typename Color,
        typename Canvas,
        typename FontDialog,
        typename ColorDialog,
        typename MessageCatalog,
        typename DialogTraits
    >
    void font_color<
        Traits, Dialog, PointUnitSize, Color, Canvas, FontDialog, ColorDialog, MessageCatalog, DialogTraits
    >::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;
    
            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using common_dialog_type_list_type = type_list::common_dialog<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;
    
            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using common_dialog_type_list_type = type_list::common_dialog<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class font_color<
        typename application::traits_type_list_type::command_type,
        typename application::ui_type_list_type::dialog_type,
        typename application::ui_type_list_type::point_unit_size_type,
        typename application::ui_type_list_type::color_type,
        typename application::ui_type_list_type::fast_canvas_type,
        typename application::common_dialog_type_list_type::font_type,
        typename application::common_dialog_type_list_type::color_type,
        typename application::locale_type_list_type::message_catalog_type,
        typename application::traits_type_list_type::dialog_type
    >;
#endif

    template class font_color<
        typename test::traits_type_list_type::command_type,
        typename test::ui_type_list_type::dialog_type,
        typename test::ui_type_list_type::point_unit_size_type,
        typename test::ui_type_list_type::color_type,
        typename test::ui_type_list_type::fast_canvas_type,
        typename test::common_dialog_type_list_type::font_type,
        typename test::common_dialog_type_list_type::color_type,
        typename test::locale_type_list_type::message_catalog_type,
        typename test::traits_type_list_type::dialog_type
    >;


}}
