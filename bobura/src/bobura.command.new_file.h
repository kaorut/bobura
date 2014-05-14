/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NEWFILE_H)
#define BOBURA_COMMAND_NEWFILE_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2/stdalt.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a new-file command.
    */
    class new_file : public command_base
    {
    public:
        // types

        //! The base type.
        using base_type = command_base;

        //! The file initialization type.
        using new_file_type = boost::mpl::at<load_save_type_list, type::load_save::new_file>::type;


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
