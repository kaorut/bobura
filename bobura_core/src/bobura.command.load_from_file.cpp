/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/command/load_from_file.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    template <typename Traits, typename LoadSaveTraits>
    class load_from_file<Traits, LoadSaveTraits>::impl
    {
    public:
        // types

        using abstract_window_type = typename load_from_file::abstract_window_type;

        using model_type = typename load_from_file::model_type;

        using load_from_file_type = typename load_from_file::load_from_file_type;

        using parameter_type = typename load_from_file::parameter_type;


        // constructors and destructor

        explicit impl(const load_from_file_type& load_from_file)
        :
        m_load_from_file(load_from_file)
        {}


        // functions

        bool enabled(const model_type& model)
        const
        {
            return m_load_from_file.reloadable(model, boost::none);
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            m_load_from_file(model, boost::none, parent);
        }

        void execute(model_type& model, abstract_window_type& parent, const parameter_base& parameter)
        const
        {
            m_load_from_file(model, boost::make_optional(parameter.as<parameter_type>().path()), parent);
        }


    private:
        // variables

        const load_from_file_type& m_load_from_file;


    };


    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::parameter_type::parameter_type(boost::filesystem::path path)
    :
    m_path(std::move(path))
    {}

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::parameter_type::~parameter_type()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits, typename LoadSaveTraits>
    const boost::filesystem::path& load_from_file<Traits, LoadSaveTraits>::parameter_type::path()
    const
    {
        return m_path;
    }

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::load_from_file(const load_from_file_type& load_from_file)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(load_from_file))
    {}

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::~load_from_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename LoadSaveTraits>
    bool load_from_file<Traits, LoadSaveTraits>::enabled_impl(const model_type& model)
    const
    {
        return m_p_impl->enabled(model);
    }

    template <typename Traits, typename LoadSaveTraits>
    void load_from_file<Traits, LoadSaveTraits>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }

    template <typename Traits, typename LoadSaveTraits>
    void load_from_file<Traits, LoadSaveTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent,
        const parameter_base& parameter
    )
    const
    {
        m_p_impl->execute(model, parent, parameter);
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = detail_type_list_for_application;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = detail_type_list_for_test;

            using traits_type_list_type = traits_type_list<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class load_from_file<
        typename boost::mpl::at<application::traits_type_list_type, type::traits::command>::type,
        typename boost::mpl::at<application::traits_type_list_type, type::traits::load_save>::type
    >;
#endif

    template class load_from_file<
        typename boost::mpl::at<test::traits_type_list_type, type::traits::command>::type,
        typename boost::mpl::at<test::traits_type_list_type, type::traits::load_save>::type
    >;
#endif


}}
