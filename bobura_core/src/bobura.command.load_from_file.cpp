/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/command/load_from_file.h>
#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>

namespace bobura { namespace command {
    class parameter_base;
}}


namespace bobura::command {
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

        explicit impl(const load_from_file_type& load_from_file) : m_load_from_file{ load_from_file } {}


        // functions

        bool enabled(const model_type& model) const
        {
            return m_load_from_file.reloadable(model, TETENGO2_STDALT_NULLOPT);
        }

        void execute(model_type& model, abstract_window_type& parent) const
        {
            m_load_from_file(model, TETENGO2_STDALT_NULLOPT, parent);
        }

        void execute(model_type& model, abstract_window_type& parent, const parameter_base& parameter) const
        {
            m_load_from_file(
                model,
                tetengo2::stdalt::make_optional(
                    tetengo2::stdalt::filesystem::path{ parameter.as<parameter_type>().path() }),
                parent);
        }


    private:
        // variables

        const load_from_file_type& m_load_from_file;
    };


    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::parameter_type::parameter_type(tetengo2::stdalt::filesystem::path path)
    : m_path{ std::move(path) }
    {}

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::parameter_type::~parameter_type() noexcept
    {}

    template <typename Traits, typename LoadSaveTraits>
    const tetengo2::stdalt::filesystem::path& load_from_file<Traits, LoadSaveTraits>::parameter_type::path() const
    {
        return m_path;
    }

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::load_from_file(const load_from_file_type& load_from_file)
    : m_p_impl{ std::make_unique<impl>(load_from_file) }
    {}

    template <typename Traits, typename LoadSaveTraits>
    load_from_file<Traits, LoadSaveTraits>::~load_from_file() noexcept
    {}

    template <typename Traits, typename LoadSaveTraits>
    bool load_from_file<Traits, LoadSaveTraits>::enabled_impl(const model_type& model) const
    {
        return m_p_impl->enabled(model);
    }

    template <typename Traits, typename LoadSaveTraits>
    void load_from_file<Traits, LoadSaveTraits>::execute_impl(model_type& model, abstract_window_type& parent) const
    {
        m_p_impl->execute(model, parent);
    }

    template <typename Traits, typename LoadSaveTraits>
    void load_from_file<Traits, LoadSaveTraits>::execute_impl(
        model_type&           model,
        abstract_window_type& parent,
        const parameter_base& parameter) const
    {
        m_p_impl->execute(model, parent, parameter);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class load_from_file<
        typename application::traits_type_list_type::command_type,
        typename application::traits_type_list_type::load_save_type>;
#endif

    template class load_from_file<
        typename test::traits_type_list_type::command_type,
        typename test::traits_type_list_type::load_save_type>;
}
