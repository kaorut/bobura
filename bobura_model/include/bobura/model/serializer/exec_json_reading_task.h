/*! \file
    \brief The definition of bobura::model::serializer::exec_json_reading_task.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H)
#define BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H

#include <functional>
#include <memory>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/timetable.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reading task execution.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
        \tparam Dialog            A progress dialog type.
        \tparam Timer             A timer type.
        \tparam SystemColorSet    A system color set type.
        \tparam MessageCatalog    A message catalog type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename Dialog,
        typename Timer,
        typename SystemColorSet,
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

        //! The system color set type.
        using system_color_set_type = SystemColorSet;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The progress dialog type.
        using progress_dialog_type =
            tetengo2::gui::widget::progress_dialog<
                typename dialog_type::traits_type,
                std::unique_ptr<timetable_type>,
                message_catalog_type,
                typename dialog_type::details_traits_type,
                typename dialog_type::menu_details_type,
                typename dialog_type::message_loop_details_type,
                typename timer_type::timer_details_type,
                typename system_color_set_type::system_color_details_type
            >;

        //! The promise type.
        using promise_type = typename progress_dialog_type::promise_type;

        //! The timetable reading type.
        using read_timetable_type = std::function<std::unique_ptr<timetable_type> (promise_type& promise)>;


        // constructors and destructor

        /*!
            \brief Creates a JSON reading task execution.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        exec_json_reading_task(abstract_window_type& parent, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the JSON reading task execution.
        */
        ~exec_json_reading_task()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Execute a JSON reading task.

            \param read_timetable A timetable reading.

            \return A unique pointer to a timetable.
        */
        std::unique_ptr<timetable_type> operator()(read_timetable_type read_timetable)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
