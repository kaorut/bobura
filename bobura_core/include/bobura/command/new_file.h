/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NEWFILE_H)
#define BOBURA_COMMAND_NEWFILE_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/load_save/new_file.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a new-file command.

        \tparam Traits         A traits type.
        \tparam LoadSaveTraits A loading and saving processing traits type.
    */
    template <typename Traits, typename LoadSaveTraits>
    class new_file : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The loading and saving processing traits type.
        using load_save_traits_type = LoadSaveTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The file initialization type.
        using new_file_type = load_save::new_file<load_save_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a new-file command.

            \param new_file A file initialization type.
        */
        explicit new_file(const new_file_type& new_file);

        /*!
            \brief Destroys the new-file command.
        */
        virtual ~new_file()
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
