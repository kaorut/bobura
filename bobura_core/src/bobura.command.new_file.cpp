/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/command/new_file.h>
#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename LoadSaveTraits>
    class new_file<Traits, LoadSaveTraits>::impl
    {
    public:
        // types

        using abstract_window_type = typename new_file::abstract_window_type;

        using model_type = typename new_file::model_type;

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
    noexcept
    {}
    
    template <typename Traits, typename LoadSaveTraits>
    void new_file<Traits, LoadSaveTraits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class new_file<
        typename application::traits_type_list_type::command_type,
        typename application::traits_type_list_type::load_save_type
    >;
#endif

    template class new_file<
        typename test::traits_type_list_type::command_type, typename test::traits_type_list_type::load_save_type
    >;


}}
