/*! \file
    \brief The definition of bobura::load_save::new_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_NEWFILE_H)
#define BOBURA_LOADSAVE_NEWFILE_H

#include <tetengo2.h>

#include <bobura/load_save/confirm_file_save.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a new-file load_save.

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
    class new_file
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
                encoder_type
            >;


        // constructors and destructor

        /*!
            \brief Creates a new-file load_save.

            \param confirm_file_save A file save confirmation.
        */
        explicit new_file(const confirm_file_save_type& confirm_file_save)
        :
        m_confirm_file_save(confirm_file_save)
        {}


        // functions

        /*!
            \brief Executes the load_save.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        const
        {
            if (!m_confirm_file_save(parent))
                return;

            model.reset_timetable(tetengo2::stdalt::make_unique<timetable_type>());
        }


    private:
        // types

        using timetable_type = typename model_type::timetable_type;


        // variables

        const confirm_file_save_type& m_confirm_file_save;


    };


}}


#endif
