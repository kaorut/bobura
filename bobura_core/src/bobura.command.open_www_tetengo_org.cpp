/*! \file
    \brief The definition of bobura::command::open_www_tetengo_org.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/open_www_tetengo_org.h>
#include <bobura/command/traits.h>


namespace bobura { namespace command
{
    template <typename Traits>
    class open_www_tetengo_org<Traits>::impl
    {
    public:
        // types

        using model_type = typename open_www_tetengo_org::model_type;

        using abstract_window_type = typename open_www_tetengo_org::abstract_window_type;

        using shell_type =
            tetengo2::gui::shell<
                typename boost::mpl::at<common_type_list, type::string>::type,
                typename boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                typename boost::mpl::at<detail_type_list, type::detail::shell>::type
            >;


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


    template <typename Traits>
    open_www_tetengo_org<Traits>::open_www_tetengo_org()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits>
    open_www_tetengo_org<Traits>::~open_www_tetengo_org()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits>
    void open_www_tetengo_org<Traits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class open_www_tetengo_org<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type
        >
    >;


}}
