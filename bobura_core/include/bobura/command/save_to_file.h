/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SAVETOFILE_H)
#define BOBURA_COMMAND_SAVETOFILE_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/load_save/save_to_file.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a save-to-file command.

        \tparam Traits         A traits type.
        \tparam LoadSaveTraits A loading and saving processing traits type.
    */
    template <typename Traits, typename LoadSaveTraits>
    class save_to_file : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The loading and saving processing traits type.
        using load_save_traits_type = LoadSaveTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The file saving type.
        using save_to_file_type = load_save::save_to_file<load_save_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a save-to-file command.

            \param save_to_file A file saving.
        */
        explicit save_to_file(const save_to_file_type& save_to_file);

        /*!
            \brief Destroys the save-to-file command.
        */
        virtual ~save_to_file()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
