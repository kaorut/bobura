/*! \file
    \brief The definition of bobura::model::serializer::reader.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <bobura/model/serializer/bzip2_reader.h>
#include <bobura/model/serializer/exec_json_reading_task.h>
#include <bobura/model/serializer/json_reader.h>
#include <bobura/model/serializer/oudia_diagram_dialog.h>
#include <bobura/model/serializer/oudia_reader.h>
#include <bobura/model/serializer/reader_selector.h>
#include <bobura/model/serializer/reader_set.h>
#include <bobura/model/serializer/select_oudia_diagram.h>
#include <bobura/model/serializer/windia_reader.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer
{
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename ExecJsonReadingTask,
        typename SelectOuDiaDiagram,
        typename Font,
        typename Utf8Encoder,
        typename Cp932Encoder
    >
    class reader_set<
        Size,
        Difference,
        String,
        ForwardIterator,
        OperatingDistance,
        Speed,
        ExecJsonReadingTask,
        SelectOuDiaDiagram,
        Font,
        Utf8Encoder,
        Cp932Encoder
    >::impl :
        private boost::noncopyable
    {
    public:
        // types

        using size_type = Size;

        using difference_type = Difference;

        using string_type = String;

        using iterator = ForwardIterator;

        using operating_distance_type = OperatingDistance;

        using speed_type = Speed;

        using exec_json_reading_task_type = ExecJsonReadingTask;

        using select_oudia_diagram_type = SelectOuDiaDiagram;

        using abstract_window_type = typename select_oudia_diagram_type::abstract_window_type;

        using message_catalog_type = typename select_oudia_diagram_type::message_catalog_type;

        using font_type = Font;

        using utf8_encoder_type = Utf8Encoder;

        using cp932_encoder_type = Cp932Encoder;

        using reader_type = typename reader_set::reader_type;

        using json_reader_type =
            json_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                int,
                double,
                operating_distance_type,
                speed_type,
                exec_json_reading_task_type,
                font_type,
                utf8_encoder_type
            >;

        using bzip2_reader_type =
            bzip2_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                font_type
            >;

        using oudia_reader_type =
            oudia_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                select_oudia_diagram_type,
                font_type,
                cp932_encoder_type
            >;

        using windia_reader_type =
            windia_reader<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                font_type,
                cp932_encoder_type
            >;


        // static functions

        /*!
            \brief Creates readers.

            \param parent          A parent window.
            \param file_name       A file name.
            \param message_catalog A message catalog.

            \return Unique pointers to readers.
        */
        static std::vector<std::unique_ptr<reader_type>> create_readers(
            abstract_window_type&       parent,
            string_type                 file_name,
            const message_catalog_type& message_catalog
        )
        {
            std::vector<std::unique_ptr<reader_type>> readers{};

            readers.push_back(create_json_reader(parent, message_catalog));
            readers.push_back(
                tetengo2::stdalt::make_unique<bzip2_reader_type>(create_json_reader(parent, message_catalog))
            );
            readers.push_back(create_oudia_reader(parent, std::move(file_name), message_catalog));
            readers.push_back(tetengo2::stdalt::make_unique<windia_reader_type>());

            return std::move(readers);
        }


    private:
        // static functions

        static std::unique_ptr<reader_type> create_json_reader(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog
        )
        {
            auto p_exec_json_reading_task =
                tetengo2::stdalt::make_unique<exec_json_reading_task_type>(parent, message_catalog);
            return tetengo2::stdalt::make_unique<json_reader_type>(std::move(p_exec_json_reading_task));
        }

        static std::unique_ptr<reader_type> create_oudia_reader(
            abstract_window_type&       parent,
            string_type                 file_name,
            const message_catalog_type& message_catalog
        )
        {
            auto p_select_oudia_diagram =
                tetengo2::stdalt::make_unique<select_oudia_diagram_type>(
                    parent, std::move(file_name), message_catalog
                );
            return tetengo2::stdalt::make_unique<oudia_reader_type>(std::move(p_select_oudia_diagram));
        }


        // forbidden operations

        impl()
        = delete;


    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename ExecJsonReadingTask,
        typename SelectOuDiaDiagram,
        typename Font,
        typename Utf8Encoder,
        typename Cp932Encoder
    >
    std::vector<
        std::unique_ptr<
            typename reader_set<
                Size,
                Difference,
                String,
                ForwardIterator,
                OperatingDistance,
                Speed,
                ExecJsonReadingTask,
                SelectOuDiaDiagram,
                Font,
                Utf8Encoder,
                Cp932Encoder
            >::reader_type
        >
    >
    reader_set<
        Size,
        Difference,
        String,
        ForwardIterator,
        OperatingDistance,
        Speed,
        ExecJsonReadingTask,
        SelectOuDiaDiagram,
        Font,
        Utf8Encoder,
        Cp932Encoder
    >::create_readers(
        abstract_window_type&       parent,
        string_type                 file_name,
        const message_catalog_type& message_catalog
    )
    {
        return impl::create_readers(parent, std::move(file_name), message_catalog);
    }


    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using exec_json_reading_task_type =
                exec_json_reading_task<
                    typename application::common_type_list_type::size_type,
                    typename application::common_type_list_type::difference_type,
                    typename application::common_type_list_type::string_type,
                    typename application::common_type_list_type::operating_distance_type,
                    typename application::common_type_list_type::speed_type,
                    typename application::ui_type_list_type::fast_font_type,
                    typename application::ui_type_list_type::dialog_type,
                    typename application::ui_type_list_type::timer_type,
                    typename application::ui_type_list_type::system_color_set_type,
                    typename application::locale_type_list_type::message_catalog_type
                >;

            using select_oudia_diagram_type =
                select_oudia_diagram<
                    oudia_diagram_dialog<
                        typename type_list::traits<detail_type_list_type>::dialog_type,
                        typename type_list::common::size_type
                    >
                >;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using exec_json_reading_task_type =
                exec_json_reading_task<
                    typename test::common_type_list_type::size_type,
                    typename test::common_type_list_type::difference_type,
                    typename test::common_type_list_type::string_type,
                    typename test::common_type_list_type::operating_distance_type,
                    typename test::common_type_list_type::speed_type,
                    typename test::ui_type_list_type::font_type,
                    typename test::ui_type_list_type::dialog_type,
                    typename test::ui_type_list_type::timer_type,
                    typename test::ui_type_list_type::system_color_set_type,
                    typename test::locale_type_list_type::message_catalog_type
                >;

            using select_oudia_diagram_type =
                select_oudia_diagram<
                    oudia_diagram_dialog<
                        typename type_list::traits<detail_type_list_type>::dialog_type,
                        typename type_list::common::size_type
                    >
                >;

        }

    }

#if BOOST_COMP_MSVC
    template class reader_set<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::input_stream_iterator_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        application::exec_json_reading_task_type,
        application::select_oudia_diagram_type,
        typename application::ui_type_list_type::fast_font_type,
        typename application::locale_type_list_type::timetable_file_encoder_type,
        typename application::locale_type_list_type::windia_file_encoder_type
    >;
#endif

    template class reader_set<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::input_stream_iterator_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        test::exec_json_reading_task_type,
        test::select_oudia_diagram_type,
        typename test::ui_type_list_type::font_type,
        typename test::locale_type_list_type::timetable_file_encoder_type,
        typename test::locale_type_list_type::windia_file_encoder_type
    >;


}}}
