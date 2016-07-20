/*! \file
    \brief The definition of bobura::load_save::load_from_file.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <cassert>
#include <ios>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>

#include <bobura/load_save/load_from_file.h>
#include <bobura/model/serializer/exec_json_reading_task.h>
#include <bobura/model/serializer/reader_selector.h>
#include <bobura/model/serializer/reader_set.h>
#include <bobura/model/serializer/select_oudia_diagram.h>
#include <bobura/type_list.h>


namespace bobura { namespace load_save
{
    template <typename Traits>
    class load_from_file<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using abstract_window_type = typename traits_type::abstract_window_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename load_from_file::model_type;

        using confirm_file_save_type = typename load_from_file::confirm_file_save_type;


        // constructors and destructor

        impl(
            const bool                    ask_file_path,
            const confirm_file_save_type& confirm_file_save,
            const message_catalog_type&   message_catalog
        )
        :
        m_ask_file_path(ask_file_path),
        m_confirm_file_save(confirm_file_save),
        m_message_catalog(message_catalog)
        {}


        // functions

        bool reloadable(const model_type& model, const boost::optional<boost::filesystem::path>& given_path)
        const
        {
            return m_ask_file_path || model.has_path() || given_path;
        }

        void operator()(
            model_type&                                     model,
            const boost::optional<boost::filesystem::path>& given_path,
            abstract_window_type&                           parent
        )
        const
        {
            if (!m_ask_file_path && !model.has_path() && !given_path)
                return;

            if (!m_confirm_file_save(parent))
                return;

            boost::filesystem::path path{};
            if (given_path)
            {
                path = *given_path;
            }
            else if (m_ask_file_path)
            {
                file_open_dialog_type dialog{
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Open")), make_file_filters(), parent
                };
                const auto ok = dialog.do_modal();
                if (!ok)
                    return;

                path = dialog.result();
            }
            else
            {
                assert(model.has_path());
                path = model.path();
            }

            boost::filesystem::ifstream input_stream{ path, std::ios_base::binary };
            if (!input_stream)
            {
                create_cant_open_file_message_box(path, parent)->do_modal();
                return;
            }

            reader_selector_type reader_selector{
                reader_set_type::create_readers(parent, path.template string<string_type>(), m_message_catalog)
            };
            const auto first =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input_stream })
                );
            const auto last =
                tetengo2::iterator::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            auto error = reader_error_type::none;
            auto p_timetable = reader_selector.read(first, last, error);
            if (!p_timetable)
            {
                switch (error)
                {
                case reader_error_type::canceled:
                    break; // Do nothing.
                case reader_error_type::corrupted:
                    create_file_broken_message_box(path, parent)->do_modal();
                    break;
                case reader_error_type::unsupported:
                    create_unsupported_format_file_message_box(path, parent)->do_modal();
                    break;
                default:
                    assert(false);
                    BOOST_THROW_EXCEPTION(std::logic_error("Unknown reader error."));
                }
                return;
            }

            model.reset_timetable(std::move(p_timetable), path);
        }


    private:
        // types

        using size_type = typename traits_type::size_type;

        using difference_type = typename traits_type::difference_type;

        using string_type = typename traits_type::string_type;

        using iterator = typename traits_type::iterator;

        using operating_distance_type = typename traits_type::operating_distance_type;

        using speed_type = typename traits_type::speed_type;

        using font_type = typename traits_type::font_type;

        using output_stream_type = typename traits_type::output_stream_type;

        using message_box_type = typename traits_type::message_box_type;

        using file_open_dialog_type = typename traits_type::file_open_dialog_type;

        using file_save_dialog_type = typename traits_type::file_save_dialog_type;

        using dialog_type = typename traits_type::dialog_type;

        using timer_type = typename traits_type::timer_type;

        using system_color_set_type = typename traits_type::system_color_set_type;

        using oudia_diagram_dialog_type = typename traits_type::oudia_diagram_dialog_type;

        using timetable_file_encoder_type = typename traits_type::timetable_file_encoder_type;

        using windia_file_encoder_type = typename traits_type::windia_file_encoder_type;

        using reader_selector_type =
            model::serializer::reader_selector<
                size_type, difference_type, string_type, iterator, operating_distance_type, speed_type, font_type
            >;

        using reader_error_type = typename reader_selector_type::error_type;

        using exec_json_reading_task_type =
            model::serializer::exec_json_reading_task<
                size_type,
                difference_type,
                string_type,
                operating_distance_type,
                speed_type,
                font_type,
                dialog_type,
                timer_type,
                system_color_set_type,
                message_catalog_type
            >;

        using select_oudia_diagram_type = model::serializer::select_oudia_diagram<oudia_diagram_dialog_type>;

        using reader_set_type =
            model::serializer::reader_set<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                exec_json_reading_task_type,
                select_oudia_diagram_type,
                font_type,
                timetable_file_encoder_type,
                windia_file_encoder_type
            >;


        // variables

        const bool m_ask_file_path;

        const confirm_file_save_type& m_confirm_file_save;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_cant_open_file_message_box(
            const boost::filesystem::path& path,
            abstract_window_type&          parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't open the file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        std::unique_ptr<message_box_type> create_file_broken_message_box(
            const boost::filesystem::path& path,
            abstract_window_type&          parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:The timetable file is corrupted.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        std::unique_ptr<message_box_type> create_unsupported_format_file_message_box(
            const boost::filesystem::path& path,
            abstract_window_type&          parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Unsupported format file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        typename file_open_dialog_type::file_filters_type make_file_filters()
        const
        {
            return
                {
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:All Timetable Files")),
                        string_type{ TETENGO2_TEXT("btt;*.btt_bz2;*.oud;*.dia") }
                    },
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files")),
                        string_type{ TETENGO2_TEXT("btt") }
                    },
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files (Compressed)")),
                        string_type{ TETENGO2_TEXT("btt_bz2") }
                    },
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:OuDia Files")),
                        string_type{ TETENGO2_TEXT("oud") }
                    },
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:WinDIA Files")),
                        string_type{ TETENGO2_TEXT("dia") }
                    },
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:All Files")),
                        string_type{ TETENGO2_TEXT("*") }
                    },
                };
        }


    };


    template <typename Traits>
    load_from_file<Traits>::load_from_file(
        const bool                    ask_file_path,
        const confirm_file_save_type& confirm_file_save,
        const message_catalog_type&   message_catalog
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(ask_file_path, confirm_file_save, message_catalog))
    {}

    template <typename Traits>
    load_from_file<Traits>::~load_from_file()
    noexcept
    {}

    template <typename Traits>
    bool load_from_file<Traits>::reloadable(
        const model_type&                               model,
        const boost::optional<boost::filesystem::path>& given_path
    )
    const
    {
        return m_p_impl->reloadable(model, given_path);
    }

    template <typename Traits>
    void load_from_file<Traits>::operator()(
        model_type&                                     model,
        const boost::optional<boost::filesystem::path>& given_path,
        abstract_window_type&                           parent
    )
    const
    {
        (*m_p_impl)(model, given_path, parent);
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class load_from_file<application::traits_type_list_type::load_save_type>;
#endif

    template class load_from_file<test::traits_type_list_type::load_save_type>;


}}
