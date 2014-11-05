/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/new_file.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename LoadSaveTraits>
    class new_file<Traits, LoadSaveTraits>::impl
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


    template <typename Traits, typename LoadSaveTraits>
    new_file<Traits, LoadSaveTraits>::new_file(const new_file_type& new_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(new_file))
    {}

    template <typename Traits, typename LoadSaveTraits>
    new_file<Traits, LoadSaveTraits>::~new_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename LoadSaveTraits>
    void new_file<Traits, LoadSaveTraits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
        namespace application
        {
            using detail_type_list_type = detail_type_list_for_application;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }

        namespace test
        {
            using detail_type_list_type = detail_type_list_for_test;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }

    }

    template class new_file<
        typename boost::mpl::at<application::traits_type_list_type, type::traits::command>::type,
        typename boost::mpl::at<application::traits_type_list_type, type::traits::load_save>::type
    >;


}}
