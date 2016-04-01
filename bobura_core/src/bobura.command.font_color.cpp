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
            dialog.set_background(to_dialog_font_color(font_color_set.background()));
            dialog.set_company_name(to_dialog_font_color(font_color_set.company_name()));
            dialog.set_line_name(to_dialog_font_color(font_color_set.line_name()));
            dialog.set_note(to_dialog_font_color(font_color_set.note()));
            dialog.set_time_line(to_dialog_font_color(font_color_set.time_line()));
            dialog.set_ruled_line(to_dialog_font_color(font_color_set.ruled_line()));
            dialog.set_local_station(to_dialog_font_color(font_color_set.local_station()));
            dialog.set_principal_station(to_dialog_font_color(font_color_set.principal_station()));
            dialog.set_local_terminal_station(to_dialog_font_color(font_color_set.local_terminal_station()));
            dialog.set_principal_terminal_station(to_dialog_font_color(font_color_set.principal_terminal_station()));

            dialog.do_modal();
            if (dialog.result() != dialog_type::result_type::accepted)
                return;
        
            font_color_set_type new_font_color_set{
                to_model_font_color(dialog.background()),
                to_model_font_color(dialog.company_name()),
                to_model_font_color(dialog.line_name()),
                to_model_font_color(dialog.note()),
                to_model_font_color(dialog.time_line()),
                to_model_font_color(dialog.ruled_line()),
                to_model_font_color(dialog.local_station()),
                to_model_font_color(dialog.principal_station()),
                to_model_font_color(dialog.local_terminal_station()),
                to_model_font_color(dialog.principal_terminal_station())
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


        // static functions

        static typename font_color_dialog_type::font_color_type to_dialog_font_color(
            const font_color_type& model_font_color
        )
        {
            return
                typename font_color_dialog_type::font_color_type{
                    model_font_color.diagram_font(),
                    model_font_color.diagram_color(),
                    model_font_color.timetable_font(),
                    model_font_color.timetable_color()
                };
        }

        static font_color_type to_model_font_color(
            const typename font_color_dialog_type::font_color_type& dialog_font_color
        )
        {
            return
                font_color_type{
                    dialog_font_color.diagram_font(),
                    dialog_font_color.diagram_color(),
                    dialog_font_color.timetable_font(),
                    dialog_font_color.timetable_color()
                };
        }


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
