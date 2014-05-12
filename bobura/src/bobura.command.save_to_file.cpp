/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <tetengo2.stdalt.h>

#include "bobura.command.save_to_file.h"


namespace bobura { namespace command
{
    class save_to_file::impl
    {
    public:
        // types

        using model_type = save_to_file::model_type;

        using abstract_window_type = save_to_file::abstract_window_type;

        using save_to_file_type = save_to_file::save_to_file_type;


        // constructors and destructor

        explicit impl(const save_to_file_type& save_to_file)
        :
        m_save_to_file(save_to_file)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            m_save_to_file(model, parent);
        }


    private:
        // variables

        const save_to_file_type& m_save_to_file;


    };


    save_to_file::save_to_file(const save_to_file_type& save_to_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(save_to_file))
    {}

    save_to_file::~save_to_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void save_to_file::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
