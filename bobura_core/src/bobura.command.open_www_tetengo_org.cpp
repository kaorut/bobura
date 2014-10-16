/*! \file
    \brief The definition of bobura::command::open_www_tetengo_org.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/open_www_tetengo_org.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename Shell>
    class open_www_tetengo_org<Traits, Shell>::impl
    {
    public:
        // types

        using model_type = typename open_www_tetengo_org::model_type;

        using abstract_window_type = typename open_www_tetengo_org::abstract_window_type;

        using shell_type = typename open_www_tetengo_org::shell_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model, parent);

            shell_type::instance().execute(string_type{ TETENGO2_TEXT("http://www.tetengo.org/") });
        }


    private:
        // types

        using string_type = typename shell_type::string_type;


    };


    template <typename Traits, typename Shell>
    open_www_tetengo_org<Traits, Shell>::open_www_tetengo_org()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits, typename Shell>
    open_www_tetengo_org<Traits, Shell>::~open_www_tetengo_org()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename Shell>
    void open_www_tetengo_org<Traits, Shell>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class open_www_tetengo_org<
        typename boost::mpl::at<main_window_type_list, type::main_window::command_traits>::type,
        typename boost::mpl::at<ui_type_list, type::ui::shell>::type
    >;


}}
