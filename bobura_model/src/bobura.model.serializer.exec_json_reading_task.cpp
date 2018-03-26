/*! \file
    \brief The definition of bobura::model::serializer::exec_json_reading_task.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <exception>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/exec_json_reading_task.h>
#include <bobura/type_list.h>


namespace bobura::model::serializer {
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
        typename MessageCatalog>
    class exec_json_reading_task<
        Size,
        Difference,
        String,
        OperatingDistance,
        Speed,
        Font,
        Dialog,
        Timer,
        SystemColorSet,
        MessageCatalog>::impl : private boost::noncopyable
    {
    public:
        // types

        using timetable_type = typename exec_json_reading_task::timetable_type;

        using dialog_type = Dialog;

        using abstract_window_type = typename dialog_type::base_type;

        using message_catalog_type = MessageCatalog;

        using read_timetable_type = typename exec_json_reading_task::read_timetable_type;


        // constructors and destructor

        impl(abstract_window_type& parent, const message_catalog_type& message_catalog)
        : m_parent{ parent }, m_message_catalog{ message_catalog }
        {}


        // functions

        std::unique_ptr<timetable_type> operator()(read_timetable_type read_timetable) const
        {
            string_type title{ m_message_catalog.get(TETENGO2_TEXT("App:Bobura")) };
            string_type waiting_message{ m_message_catalog.get(
                TETENGO2_TEXT("Dialog:JsonReading:Opening the timetable file...")) };
            string_type canceling_message{ m_message_catalog.get(
                TETENGO2_TEXT("Dialog:JsonReading:Canceling opening the timetable file...")) };
            auto        task = [&read_timetable](promise_type& promise) {
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
            progress_dialog_type dialog{
                m_parent,        std::move(title), std::move(waiting_message), std::move(canceling_message),
                std::move(task), m_message_catalog
            };
            dialog.do_modal();

            return dialog.task_future().get();
        }


    private:
        // types

        using string_type = String;

        using progress_dialog_type = typename exec_json_reading_task::progress_dialog_type;

        using promise_type = typename exec_json_reading_task::promise_type;


        // variables

        abstract_window_type& m_parent;

        const message_catalog_type& m_message_catalog;
    };


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
        typename MessageCatalog>
    exec_json_reading_task<
        Size,
        Difference,
        String,
        OperatingDistance,
        Speed,
        Font,
        Dialog,
        Timer,
        SystemColorSet,
        MessageCatalog>::
        exec_json_reading_task(abstract_window_type& parent, const message_catalog_type& message_catalog)
    : m_p_impl{ tetengo2::stdalt::make_unique<impl>(parent, message_catalog) }
    {}

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
        typename MessageCatalog>
    exec_json_reading_task<
        Size,
        Difference,
        String,
        OperatingDistance,
        Speed,
        Font,
        Dialog,
        Timer,
        SystemColorSet,
        MessageCatalog>::~exec_json_reading_task() noexcept
    {}

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
        typename MessageCatalog>
    std::unique_ptr<typename exec_json_reading_task<
        Size,
        Difference,
        String,
        OperatingDistance,
        Speed,
        Font,
        Dialog,
        Timer,
        SystemColorSet,
        MessageCatalog>::timetable_type>
                         exec_json_reading_task<
                             Size,
                             Difference,
                             String,
                             OperatingDistance,
                             Speed,
                             Font,
                             Dialog,
                             Timer,
                             SystemColorSet,
                             MessageCatalog>::operator()(read_timetable_type read_timetable) const
    {
        return (*m_p_impl)(std::move(read_timetable));
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class exec_json_reading_task<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::ui_type_list_type::dialog_type,
        typename application::ui_type_list_type::timer_type,
        typename application::ui_type_list_type::system_color_set_type,
        typename application::locale_type_list_type::message_catalog_type>;
#endif

    template class exec_json_reading_task<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type,
        typename test::ui_type_list_type::dialog_type,
        typename test::ui_type_list_type::timer_type,
        typename test::ui_type_list_type::system_color_set_type,
        typename test::locale_type_list_type::message_catalog_type>;
}
