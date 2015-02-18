/*! \file
    \brief The definition of bobura::model::serializer::exec_json_reading_task.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H)
#define BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H

#include <exception>
#include <functional>
#include <memory>
#include <utility>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/timetable.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reading task execution.

        \tparam Timetable      A timetable type.
        \tparam Dialog         A progress dialog type.
        \tparam Timer          A timer type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Dialog,
        typename Timer,
        typename MessageCatalog
    >
    class exec_json_reading_task
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The timetable type.
        using timetable_type =
            timetable<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename dialog_type::base_type;

        //! The timer type.
        using timer_type = Timer;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The progress dialog type.
        using progress_dialog_type =
            tetengo2::gui::widget::progress_dialog<
                typename dialog_type::traits_type,
                std::unique_ptr<timetable_type>,
                typename dialog_type::details_traits_type,
                typename dialog_type::menu_details_type,
                typename dialog_type::message_loop_details_type,
                typename timer_type::timer_details_type
            >;

        //! The promise type.
        using promise_type = typename progress_dialog_type::promise_type;

        //! The task type.
        using task_type = typename progress_dialog_type::task_type;

        //! The timetable reading type.
        using read_timetable_type = std::function<std::unique_ptr<timetable_type> (promise_type& promise)>;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        exec_json_reading_task(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        m_parent(parent),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Execute a JSON reading task.

            \param read_timetable A timetable reading.

            \return A unique pointer to a timetable.
        */
        std::unique_ptr<timetable_type> operator()(read_timetable_type read_timetable)
        const
        {
            string_type title{ m_message_catalog.get(TETENGO2_TEXT("App:Bobura")) };
            auto task =
                [&read_timetable](promise_type& promise)
                {
                    try
                    {
                        auto p_timetable = read_timetable(promise);
                        promise.set_value(std::move(p_timetable));
                    }
                    catch (std::exception& e)
                    {
                        promise.set_exception(std::make_exception_ptr(e));
                    }
                };
            progress_dialog_type dialog{ m_parent, std::move(title), std::move(task) };
            dialog.do_modal();

            return dialog.task_future().get();
        }


    private:
        // variables

        abstract_window_type& m_parent;

        const message_catalog_type& m_message_catalog;


    };


}}}


#endif
