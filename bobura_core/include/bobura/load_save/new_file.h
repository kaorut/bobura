/*! \file
    \brief The definition of bobura::load_save::new_file.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_NEWFILE_H)
#define BOBURA_LOADSAVE_NEWFILE_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/load_save/confirm_file_save.h>
#include <bobura/timetable_model.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file initialization.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class new_file : private boost::noncopyable
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

        //! The model type.
        using model_type =
            timetable_model<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The file save confirmation type.
        using confirm_file_save_type = confirm_file_save<traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a file initialization.

            \param confirm_file_save A file save confirmation.
        */
        explicit new_file(const confirm_file_save_type& confirm_file_save);

        /*!
            \brief Destroys the file initialization.
        */
        ~new_file()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Executes the load_save.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
