/*! \file
    \brief The definition of bobura::message::timetable_model.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TIMETABLEMODEL_H)
#define BOBURA_MESSAGE_TIMETABLEMODEL_H

#include <cassert>
#include <utility>

#include <boost/optional.hpp>
#include <boost/rational.hpp>

#include <tetengo2.gui.h>


namespace bobura { namespace message { namespace timetable_model
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        template <typename TimetableModel, typename MainWindow>
        void set_main_window_title(const TimetableModel& timetable_model, MainWindow& main_window)
        {
            using string_type = typename MainWindow::string_type;

            const auto title =
                timetable_model.has_path() ?
                boost::make_optional(timetable_model.path().filename().template string<string_type>()) : boost::none;
            main_window.set_title(title, timetable_model.changed());
        }


    }
#endif


     /*!
        \brief The class template for a timetable model reset observer.

        \tparam TimetableModel A timetable model type.
        \tparam DiagramView    A diagram view type.
        \tparam MainWindow     A main window type.
    */
    template <typename TimetableModel, typename DiagramView, typename MainWindow>
    class reset
    {
    public:
        // types

        //! The timetable model type.
        using timetable_model_type = TimetableModel;

        //! The diagram view type.
        using diagram_view_type = DiagramView;

        //! The main window type.
        using main_window_type = MainWindow;


        // constructors and destructor

        /*!
            \brief Creates a timetable model reset observer.

            \param timetable_model A timetable model.
            \param diagram_view    A diagram view.
            \param main_window     A main window.
        */
        reset(
            const timetable_model_type& timetable_model,
            diagram_view_type&          diagram_view,
            main_window_type&           main_window
        )
        :
        m_timetable_model(timetable_model),
        m_diagram_view(diagram_view),
        m_main_window(main_window)
        {}


        // functions

        /*!
            \brief Called when the timetable model is reset.
        */
        void operator()()
        const
        {
            detail::set_main_window_title(m_timetable_model, m_main_window);
            m_diagram_view.update_dimension();
            m_diagram_view.unselect_all_items();
            reset_scroll_bars(m_main_window.get_diagram_picture_box(), m_diagram_view);
            m_main_window.get_diagram_picture_box().repaint(true);
            m_main_window.size_observer_set().resized()();
        }


    private:
        // types

        using dimension_type = typename diagram_view_type::dimension_type;

        using diagram_picture_box_type = typename main_window_type::diagram_picture_box_type;

        using scroll_bar_type = typename diagram_picture_box_type::scroll_bar_type;

        using scroll_bar_size_type = typename scroll_bar_type::size_type;


        // static functions

        static void reset_scroll_bars(diagram_picture_box_type& picture_box, const diagram_view_type& view)
        {
            assert(picture_box.has_vertical_scroll_bar());
            reset_scroll_bar(
                picture_box.vertical_scroll_bar(),
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::height(view.dimension()).value()
                )
            );

            assert(picture_box.has_horizontal_scroll_bar());
            reset_scroll_bar(
                picture_box.horizontal_scroll_bar(),
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::width(view.dimension()).value()
                )
            );

            picture_box.update_scroll_bars(view.dimension(), view.page_size(picture_box.client_dimension()));
        }

        static void reset_scroll_bar(scroll_bar_type& scroll_bar, const scroll_bar_size_type size)
        {
            scroll_bar.set_range(std::make_pair<scroll_bar_size_type>(0, size));
            scroll_bar.set_position(0);
            scroll_bar.scroll_bar_observer_set().scrolled()(0);
        }


        // variables

        const timetable_model_type& m_timetable_model;

        diagram_view_type& m_diagram_view;

        main_window_type& m_main_window;


    };


     /*!
        \brief The class template for a timetable model change observer.

        \tparam TimetableModel A timetable model type.
        \tparam DiagramView    A diagram view type.
        \tparam MainWindow     A main window type.
    */
    template <typename TimetableModel, typename DiagramView, typename MainWindow>
    class changed
    {
    public:
        // types

        //! The timetable model type.
        using timetable_model_type = TimetableModel;

        //! The diagram view type.
        using diagram_view_type = DiagramView;

        //! The main window type.
        using main_window_type = MainWindow;


        // constructors and destructor

        /*!
            \brief Creates a timetable model change observer.

            \param timetable_model A timetable model.
            \param diagram_view    A diagram view.
            \param main_window     A main window.
        */
        changed(
            const timetable_model_type& timetable_model,
            diagram_view_type&          diagram_view,
            main_window_type&           main_window
        )
        :
        m_timetable_model(timetable_model),
        m_diagram_view(diagram_view),
        m_main_window(main_window)
        {}


        // functions

        /*!
            \brief Called when the timetable model is changed.
        */
        void operator()()
        const
        {
            detail::set_main_window_title(m_timetable_model, m_main_window);
            m_diagram_view.update_dimension();
            m_main_window.get_diagram_picture_box().repaint(true);
            m_main_window.size_observer_set().resized()();
        }


    private:
        // variables

        const timetable_model_type& m_timetable_model;

        diagram_view_type& m_diagram_view;

        main_window_type& m_main_window;


    };


}}}


#endif
