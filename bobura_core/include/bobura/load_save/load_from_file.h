/*! \file
    \brief The definition of bobura::load_save::load_from_file.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_LOADFROMFILE_H)
#define BOBURA_LOADSAVE_LOADFROMFILE_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

#include <bobura/load_save/confirm_file_save.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file loading.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class load_from_file : private boost::noncopyable
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

        //! The file save confirmation type.
        using confirm_file_save_type = confirm_file_save<traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a file loading.

            \param ask_file_path     Set true to show a file selection dialog.
            \param confirm_file_save A file save confirmation.
            \param message_catalog   A message catalog.
        */
        load_from_file(
            bool                          ask_file_path,
            const confirm_file_save_type& confirm_file_save,
            const message_catalog_type&   message_catalog
        );

        /*!
            \brief Destroys the file loading.
        */
        ~load_from_file()
        noexcept;


        // functions

        /*!
            \brief Return whether the model is reloadable.

            \param model      A model.
            \param given_path A given path.

            \retval true  When the model is reloadable.
            \retval false Otherwise.
        */
        bool reloadable(const model_type& model, const boost::optional<boost::filesystem::path>& given_path)
        const;

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
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
