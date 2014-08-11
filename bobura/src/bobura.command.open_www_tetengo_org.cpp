/*! \file
    \brief The definition of bobura::command::open_www_tetengo_org.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/open_www_tetengo_org.h>


namespace bobura { namespace command
{
    class open_www_tetengo_org::impl
    {
    public:
        // types

        using model_type = open_www_tetengo_org::model_type;

        using abstract_window_type = open_www_tetengo_org::abstract_window_type;

        using shell_type = boost::mpl::at<ui_type_list, type::ui::shell>::type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model, parent);

            shell_type::instance().execute(string_type{ TETENGO2_TEXT("http://www.tetengo.org/") });
        }


    private:
        // types

        using string_type = shell_type::string_type;


    };


    open_www_tetengo_org::open_www_tetengo_org()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    open_www_tetengo_org::~open_www_tetengo_org()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void open_www_tetengo_org::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
