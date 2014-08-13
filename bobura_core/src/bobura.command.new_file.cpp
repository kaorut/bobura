/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <tetengo2.h>

#include <bobura/command/new_file.h>


namespace bobura { namespace command
{
    class new_file::impl
    {
    public:
        // types

        using model_type = new_file::model_type;

        using abstract_window_type = new_file::abstract_window_type;

        using new_file_type = new_file::new_file_type;


        // constructors and destructor

        explicit impl(const new_file_type& new_file)
        :
        m_new_file(new_file)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            m_new_file(model, parent);
        }


    private:
        // variables

        const new_file_type& m_new_file;


    };


    new_file::new_file(const new_file_type& new_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(new_file))
    {}

    new_file::~new_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void new_file::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
