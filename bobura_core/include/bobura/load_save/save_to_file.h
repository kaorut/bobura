/*! \file
    \brief The definition of bobura::load_save::save_to_file.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_SAVETOFILE_H)
#define BOBURA_LOADSAVE_SAVETOFILE_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/timetable_model.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file saving.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class save_to_file : private boost::noncopyable
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


        // constructors and destructor

        /*!
            \brief Creates a file saving.

            \param ask_file_path     Set true to show a file selection dialog.
                                     When the model does not have a path, a file selection dialog is always shown.
            \param message_catalog   A message catalog.
        */
        save_to_file(bool ask_file_path, const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the file saving.
        */
        ~save_to_file()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Saves the model to a file.

            \param model  A model.
            \param parent A parent window.

            \retval true   When the model has been saved.
            \retval false  Otherwise.
        */
        bool operator()(model_type& model, abstract_window_type& parent)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
