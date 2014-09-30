/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/new_file.h>
#include <bobura/command/traits.h>


namespace bobura { namespace command
{
    template <typename Traits>
    class new_file<Traits>::impl
    {
    public:
        // types

        using model_type = typename new_file::model_type;

        using abstract_window_type = typename new_file::abstract_window_type;

        using new_file_type = typename new_file::new_file_type;


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


    template <typename Traits>
    new_file<Traits>::new_file(const new_file_type& new_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(new_file))
    {}

    template <typename Traits>
    new_file<Traits>::~new_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits>
    void new_file<Traits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class new_file<
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
