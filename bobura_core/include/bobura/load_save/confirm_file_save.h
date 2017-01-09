/*! \file
    \brief The definition of bobura::load_save::confirm_file_save.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_CONFIRMFILESAVE_H)
#define BOBURA_LOADSAVE_CONFIRMFILESAVE_H

#include <memory>

#include <boost/core/noncopyable.hpp>

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
    class confirm_file_save : private boost::noncopyable
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

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The speed type.
        using speed_type = typename traits_type::speed_type;

        //! The font type.
        using font_type = typename traits_type::font_type;

        //! The abstract window type.
        using abstract_window_type = typename traits_type::abstract_window_type;

        //! The message catalog type.
        using message_catalog_type = typename traits_type::message_catalog_type;

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
        );

        /*!
            \brief Destroys the file save confirmation.
        */
        ~confirm_file_save()
        noexcept;


        // functions

        /*!
            \brief Confirms file save, and if necessary, save the model.

            \param parent A parent window.

            \retval true  When the model is saved or there is no need to save it.
            \retval false Otherwise.
        */
        bool operator()(abstract_window_type& parent)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
