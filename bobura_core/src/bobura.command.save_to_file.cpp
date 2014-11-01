/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/save_to_file.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename LoadSaveTraits>
    class save_to_file<Traits, LoadSaveTraits>::impl
    {
    public:
        // types

        using model_type = typename save_to_file::model_type;

        using abstract_window_type = typename save_to_file::abstract_window_type;

        using save_to_file_type = typename save_to_file::save_to_file_type;


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


    template <typename Traits, typename LoadSaveTraits>
    save_to_file<Traits, LoadSaveTraits>::save_to_file(const save_to_file_type& save_to_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(save_to_file))
    {}

    template <typename Traits, typename LoadSaveTraits>
    save_to_file<Traits, LoadSaveTraits>::~save_to_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename LoadSaveTraits>
    void save_to_file<Traits, LoadSaveTraits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
        using detail_type_list_type = detail_type_list;

        using traits_type_list_type = traits_type_list<detail_type_list_type>;

    }

    template class save_to_file<
        typename boost::mpl::at<traits_type_list_type, type::traits::command>::type,
        typename boost::mpl::at<traits_type_list_type, type::traits::load_save>::type
    >;


}}
