/*! \file
    \brief The definition of bobura::load_save::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_SAVETOFILE_H)
#define BOBURA_LOADSAVE_SAVETOFILE_H

#include <ios>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
#include <boost/system/system_error.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/writer_selector.h>
#include <bobura/model/serializer/writer_set.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file saving.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam OutputStream      An output stream type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
        \tparam AbstractWindow    An abstract window type.
        \tparam MessageBox        A message box type.
        \tparam FileSaveDialog    A file save dialog type.
        \tparam MessageCatalog    A message catalog type.
        \tparam Encoder           An encoder type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font,
        typename AbstractWindow,
        typename MessageBox,
        typename FileSaveDialog,
        typename MessageCatalog,
        typename Encoder
    >
    class save_to_file
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The output stream type.
        using output_stream_type = OutputStream;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The message box type.
        using message_box_type = MessageBox;

        //! The file save dialog type.
        using file_save_dialog_type = FileSaveDialog;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The writer selector type.
        using writer_selector_type =
            model::serializer::writer_selector<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                font_type
            >;

        //! The writer set type.
        using writer_set_type =
            model::serializer::writer_set<
                size_type,
                difference_type,
                string_type,
                output_stream_type,
                operating_distance_type,
                speed_type,
                font_type,
                encoder_type
            >;


        // constructors and destructor

        /*!
            \brief Creates a file saving.

            \param ask_file_path     Set true to show a file selection dialog.
                                     When the model does not have a path, a file selection dialog is always shown.
            \param message_catalog   A message catalog.
        */
        save_to_file(const bool ask_file_path, const message_catalog_type& message_catalog)
        :
        m_ask_file_path(ask_file_path),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Saves the model to a file.

            \param model  A model.
            \param parent A parent window.

            \retval true   When the model has been saved.
            \retval false  Otherwise.
        */
        bool operator()(model_type& model, abstract_window_type& parent)
        const
        {
            boost::filesystem::path path{};
            if (!model.has_path() || m_ask_file_path)
            {
                file_save_dialog_type dialog{
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:SaveAs")),
                    model.has_path() ? boost::make_optional(model.path()) : boost::none,
                    make_file_filters(),
                    parent
                };
                const auto ok = dialog.do_modal();
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

            const auto temporary_path = path.parent_path() / boost::filesystem::unique_path();
            {
                writer_selector_type writer{ writer_set_type::create_writers(), path };
                if (!writer.selects(path))
                {
                    if (m_ask_file_path)
                        return false;
                    else
                        return save_to_file(true, m_message_catalog)(model, parent);
                }

                boost::filesystem::ofstream output_stream{ temporary_path, std::ios_base::binary };
                if (!output_stream)
                {
                    create_cant_create_temporary_file_message_box(temporary_path, parent)->do_modal();
                    return false;
                }

                writer.write(model.timetable(), output_stream);
            }

            {
                boost::system::error_code error_code{};
                boost::filesystem::rename(temporary_path, path, error_code);
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
        // variables

        const bool m_ask_file_path;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_cant_create_temporary_file_message_box(
            const boost::filesystem::path& path,
            abstract_window_type&          parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't create a temporary file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        std::unique_ptr<message_box_type> create_cant_write_to_file_message_box(
            const boost::filesystem::path& path,
            abstract_window_type&          parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't write to the file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        typename file_save_dialog_type::file_filters_type make_file_filters()
        const
        {
            return
                {
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files")),
                        string_type{ TETENGO2_TEXT("btt") }
                    },
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files (Compressed)")),
                        string_type{ TETENGO2_TEXT("btt_bz2") }
                    },
                    {
                        m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:All Files")),
                        string_type{ TETENGO2_TEXT("*") }
                    }
                };
        }


    };


}}


#endif
