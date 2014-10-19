/*! \file
    \brief The definition of bobura::load_save::confirm_file_save.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_CONFIRMFILESAVE_H)
#define BOBURA_LOADSAVE_CONFIRMFILESAVE_H

#include <memory>

#include <tetengo2.h>

#include <bobura/load_save/save_to_file.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for the file save confirmation.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class confirm_file_save
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

        //! The file save dialog type.
        using file_save_dialog_type = typename traits_type::file_save_dialog_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

        //! The timetable file encoder type.
        using timetable_file_encoder_type = typename traits_type::timetable_file_encoder_type;

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The file saving type.
        using save_to_file_type = save_to_file<traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a file save confirmation.

            \param model           A model.
            \param save_to_file    A file saving.
            \param message_catalog A message catalog.
        */
        confirm_file_save(
            model_type&                 model,
            const save_to_file_type&    save_to_file,
            const message_catalog_type& message_catalog
        )
        :
        m_model(model),
        m_save_to_file(save_to_file),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Confirms file save, and if necessary, save the model.

            \param parent A parent window.

            \retval true  When the model is saved or there is no need to save it.
            \retval false Otherwise.
        */
        bool operator()(abstract_window_type& parent)
        const
        {
            if (!m_model.changed())
                return true;

            const auto selected_button = create_message_box(parent)->do_modal();
            if (selected_button == message_box_type::button_id_type::cancel)
                return false;
            if (selected_button == message_box_type::button_id_type::yes)
            {
                if (!m_save_to_file(m_model, parent))
                    return false;
            }

            return true;
        }


    private:
        // variables

        model_type& m_model;

        const save_to_file_type& m_save_to_file;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_message_box(abstract_window_type& parent)
        const
        {
            const auto file_path =
                m_model.has_path() ?
                m_model.path().template string<string_type>() :
                m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));

            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(
                        TETENGO2_TEXT("Message:File:The file has been changed. Do you want to save the changes?")
                    ),
                    file_path,
                    message_box_type::button_style_type::yes_no(
                        true,
                        m_message_catalog.get(TETENGO2_TEXT("Message:File:&Save")),
                        m_message_catalog.get(TETENGO2_TEXT("Message:File:&Don't save"))
                    ),
                    message_box_type::icon_style_type::warning
                );
        }


    };


}}


#endif
