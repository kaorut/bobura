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

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class new_file
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

        //! The file save confirmation type.
        using confirm_file_save_type = confirm_file_save<traits_type>;


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
