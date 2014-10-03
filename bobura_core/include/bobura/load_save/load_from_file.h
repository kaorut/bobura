/*! \file
    \brief The definition of bobura::load_save::load_from_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_LOADFROMFILE_H)
#define BOBURA_LOADSAVE_LOADFROMFILE_H

#include <cassert>
#include <ios>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>

#include <bobura/load_save/confirm_file_save.h>
#include <bobura/model/serializer/reader_selector.h>
#include <bobura/model/serializer/reader_set.h>
#include <bobura/model/serializer/select_oudia_diagram.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file loading.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class load_from_file
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The iterator type.
        using iterator = typename traits_type::iterator;

        //! The output stream type.
        using output_stream_type = typename traits_type::output_stream_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The font type.
        using font_type = typename traits_type::font_type;

        //! The abstract window type.
        using abstract_window_type = typename traits_type::abstract_window_type;

        //! The message box type.
        using message_box_type = typename traits_type::message_box_type;

        //! The file open dialog type.
        using file_open_dialog_type = typename traits_type::file_open_dialog_type;

        //! The file save dialog type.
        using file_save_dialog_type = typename traits_type::file_save_dialog_type;

        //! The OuDia diagram dialog type.
        using oudia_diagram_dialog_type = typename traits_type::oudia_diagram_dialog_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The timetable file encoder type.
        using timetable_file_encoder_type = typename traits_type::timetable_file_encoder_type;

        //! The WinDIA file encoder type.
        using windia_file_encoder_type = typename traits_type::windia_file_encoder_type;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The file save confirmation type.
        using confirm_file_save_type =
            confirm_file_save<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                font_type,
                abstract_window_type,
                message_box_type,
                file_save_dialog_type,
                message_catalog_type,
                timetable_file_encoder_type
            >;

        //! The reader selector type.
        using reader_selector_type =
            model::serializer::reader_selector<
                size_type, difference_type, string_type, iterator, operating_distance_type, speed_type, font_type
            >;

        //! The OuDia diagram selector type.
        using select_oudia_diagram_type = model::serializer::select_oudia_diagram<oudia_diagram_dialog_type>;

        //! The reader set type.
        using reader_set_type =
            model::serializer::reader_set<
                size_type,
                difference_type,
                string_type,
                iterator,
                operating_distance_type,
                speed_type,
                select_oudia_diagram_type,
                font_type,
                timetable_file_encoder_type,
                windia_file_encoder_type
            >;


        // constructors and destructor

        /*!
            \brief Creates a file loading.

            \param ask_file_path     Set true to show a file selection dialog.
            \param confirm_file_save A file save confirmation.
            \param message_catalog   A message catalog.
        */
        load_from_file(
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

        /*!
            \brief Return whether the model is reloadable.

            \param model      A model.
            \param given_path A given path.

            \retval true  When the model is reloadable.
            \retval false Otherwise.
        */
        bool reloadable(const model_type& model, const boost::optional<boost::filesystem::path>& given_path)
        const
        {
            return m_ask_file_path || model.has_path() || given_path;
        }

        /*!
            \brief Executes the load_save.

            \param model      A model.
            \param given_path A given path.
            \param parent     A parent window.
        */
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
            auto error = reader_error_type::none;
            auto p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );
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

        using reader_error_type = typename reader_selector_type::error_type;


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


}}


#endif
