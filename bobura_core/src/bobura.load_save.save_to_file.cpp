/*! \file
    \brief The definition of bobura::load_save::save_to_file.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <fstream>
#include <ios>
#include <memory>
#include <system_error>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/load_save/save_to_file.h>
#include <bobura/model/serializer/writer_selector.h>
#include <bobura/model/serializer/writer_set.h>
#include <bobura/type_list.h>


namespace bobura::load_save {
    template <typename Traits>
    class save_to_file<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using abstract_window_type = typename traits_type::abstract_window_type;

        using message_catalog_type = typename traits_type::message_catalog_type;

        using model_type = typename save_to_file::model_type;


        // constructors and destructor

        impl(const bool ask_file_path, const message_catalog_type& message_catalog)
        : m_ask_file_path{ ask_file_path }, m_message_catalog{ message_catalog }
        {}


        // functions

        bool operator()(model_type& model, abstract_window_type& parent) const
        {
            tetengo2::stdalt::filesystem::path path{};
            if (!model.has_path() || m_ask_file_path)
            {
                file_save_dialog_type dialog{ m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:SaveAs")),
                                              model.has_path() ?
                                                  tetengo2::stdalt::make_optional(
                                                      tetengo2::stdalt::filesystem::path{ model.path() }) :
                                                  TETENGO2_STDALT_NULLOPT,
                                              make_file_filters(),
                                              parent };
                const auto            ok = dialog.do_modal();
                if (!ok)
                    return false;

                path = dialog.result();
            }
            else
            {
                if (!model.changed())
                    return false;

                path = model.path();
            }

            auto temporary_path = path;
            temporary_path += tetengo2::stdalt::filesystem::path::string_type{ TETENGO2_TEXT(".tmp") };
            {
                writer_selector_type writer{ writer_set_type::create_writers(), path };
                if (!writer.selects(path))
                {
                    if (m_ask_file_path)
                        return false;
                    else
                        return save_to_file(true, m_message_catalog)(model, parent);
                }

                std::ofstream output_stream{ temporary_path, std::ios_base::binary };
                if (!output_stream)
                {
                    create_cant_create_temporary_file_message_box(temporary_path, parent)->do_modal();
                    return false;
                }

                writer.write(model.timetable(), output_stream);
            }

            {
                std::error_code error_code{};
                tetengo2::stdalt::filesystem::rename(temporary_path, path, error_code);
                if (error_code)
                {
                    create_cant_write_to_file_message_box(path, parent)->do_modal();
                    return false;
                }
            }

            model.set_path(path);

            return true;
        }


    private:
        // types

        using size_type = typename traits_type::size_type;

        using difference_type = typename traits_type::difference_type;

        using string_type = typename traits_type::string_type;

        using output_stream_type = typename traits_type::output_stream_type;

        using operating_distance_type = typename traits_type::operating_distance_type;

        using speed_type = typename traits_type::speed_type;

        using font_type = typename traits_type::font_type;

        using message_box_type = typename traits_type::message_box_type;

        using file_save_dialog_type = typename traits_type::file_save_dialog_type;

        using timetable_file_encoder_type = typename traits_type::timetable_file_encoder_type;

        using writer_selector_type = model::serializer::writer_selector<
            size_type,
            difference_type,
            string_type,
            output_stream_type,
            operating_distance_type,
            speed_type,
            font_type>;

        using writer_set_type = model::serializer::writer_set<
            size_type,
            difference_type,
            string_type,
            output_stream_type,
            operating_distance_type,
            speed_type,
            font_type,
            timetable_file_encoder_type>;


        // variables

        const bool m_ask_file_path;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_cant_create_temporary_file_message_box(
            const tetengo2::stdalt::filesystem::path& path,
            abstract_window_type&                     parent) const
        {
            return std::make_unique<message_box_type>(
                parent,
                m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't create a temporary file.")),
                path.template string<typename string_type::value_type>(),
                message_box_type::button_style_type::ok(false),
                message_box_type::icon_style_type::error);
        }

        std::unique_ptr<message_box_type> create_cant_write_to_file_message_box(
            const tetengo2::stdalt::filesystem::path& path,
            abstract_window_type&                     parent) const
        {
            return std::make_unique<message_box_type>(
                parent,
                m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't write to the file.")),
                path.template string<typename string_type::value_type>(),
                message_box_type::button_style_type::ok(false),
                message_box_type::icon_style_type::error);
        }

        typename file_save_dialog_type::file_filters_type make_file_filters() const
        {
            return { { m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files")),
                       string_type{ TETENGO2_TEXT("btt") } },
                     { m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files (Compressed)")),
                       string_type{ TETENGO2_TEXT("btt_bz2") } },
                     { m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:All Files")),
                       string_type{ TETENGO2_TEXT("*") } } };
        }
    };


    template <typename Traits>
    save_to_file<Traits>::save_to_file(const bool ask_file_path, const message_catalog_type& message_catalog)
    : m_p_impl{ std::make_unique<impl>(ask_file_path, message_catalog) }
    {}

    /*!
        \brief Destroys the file saving.
    */
    template <typename Traits>
    save_to_file<Traits>::~save_to_file() noexcept
    {}

    template <typename Traits>
    bool save_to_file<Traits>::operator()(model_type& model, abstract_window_type& parent) const
    {
        return (*m_p_impl)(model, parent);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class save_to_file<application::traits_type_list_type::load_save_type>;
#endif

    template class save_to_file<test::traits_type_list_type::load_save_type>;
}
