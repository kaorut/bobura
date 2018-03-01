/*! \file
    \brief The definition of bobura::model::serializer::reader.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/serializer/oudia_diagram_dialog.h>
#include <bobura/model/serializer/select_oudia_diagram.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer {
    template <typename OuDiaDiagramDialog>
    class select_oudia_diagram<OuDiaDiagramDialog>::impl : private boost::noncopyable
    {
    public:
        // types

        using oudia_diagram_dialog_type = OuDiaDiagramDialog;

        using abstract_window_type = typename select_oudia_diagram::abstract_window_type;

        using string_type = typename select_oudia_diagram::string_type;

        using iterator = typename select_oudia_diagram::iterator;

        using message_catalog_type = typename select_oudia_diagram::message_catalog_type;


        // constructors and destructor

        impl(abstract_window_type& parent, string_type file_name, const message_catalog_type& message_catalog)
        : m_parent(parent), m_file_name(std::move(file_name)), m_message_catalog(message_catalog)
        {}


        // functions

        iterator operator()(const iterator first, const iterator last) const
        {
            if (std::distance(first, last) < 2)
                return first;

            oudia_diagram_dialog_type dialog{ m_parent, m_message_catalog };

            dialog.set_file_name(m_file_name);
            dialog.set_names(std::vector<string_type>(first, last));
            dialog.set_selected_index(0);

            dialog.do_modal();
            if (dialog.result() != oudia_diagram_dialog_type::result_type::accepted)
                return last;

            const auto selected_index = dialog.selected_index();
            if (selected_index)
            {
                assert(*selected_index < static_cast<selected_index_type>(std::distance(first, last)));
                return std::next(first, *selected_index);
            }
            else
            {
                return last;
            }
        }


    private:
        // types

        using selected_index_type = typename oudia_diagram_dialog_type::size_type;


        // variables

        abstract_window_type& m_parent;

        const string_type m_file_name;

        const message_catalog_type& m_message_catalog;
    };


    template <typename OuDiaDiagramDialog>
    select_oudia_diagram<OuDiaDiagramDialog>::select_oudia_diagram(
        abstract_window_type&       parent,
        string_type                 file_name,
        const message_catalog_type& message_catalog)
    : m_p_impl(tetengo2::stdalt::make_unique<impl>(parent, std::move(file_name), message_catalog))
    {}

    template <typename OuDiaDiagramDialog>
    select_oudia_diagram<OuDiaDiagramDialog>::~select_oudia_diagram() noexcept
    {}

    template <typename OuDiaDiagramDialog>
    typename select_oudia_diagram<OuDiaDiagramDialog>::iterator select_oudia_diagram<OuDiaDiagramDialog>::
                                                                operator()(const iterator first, const iterator last) const
    {
        return (*m_p_impl)(first, last);
    }


    template <typename String>
    class select_oudia_diagram_for_test<String>::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = String;

        using iterator = typename select_oudia_diagram_for_test<String>::iterator;


        // constructors and destructor

        explicit impl(string_type name) : m_name(std::move(name)) {}


        // functions

        iterator operator()(const iterator first, const iterator last) const
        {
            return std::find(first, last, m_name);
        }


    private:
        // variables

        const string_type m_name;
    };


    template <typename String>
    select_oudia_diagram_for_test<String>::select_oudia_diagram_for_test(string_type name)
    : m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(name)))
    {}

    template <typename String>
    select_oudia_diagram_for_test<String>::~select_oudia_diagram_for_test() noexcept
    {}

    template <typename String>
    typename select_oudia_diagram_for_test<String>::iterator select_oudia_diagram_for_test<String>::
                                                             operator()(const iterator first, const iterator last) const
    {
        return (*m_p_impl)(first, last);
    }


    namespace {
#if BOOST_COMP_MSVC
        namespace application {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using oudia_diagram_dialog_type = oudia_diagram_dialog<
                typename type_list::traits<detail_type_list_type>::dialog_type,
                typename type_list::common::size_type>;
        }
#endif

        namespace test {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using oudia_diagram_dialog_type = oudia_diagram_dialog<
                typename type_list::traits<detail_type_list_type>::dialog_type,
                typename type_list::common::size_type>;
        }
    }

#if BOOST_COMP_MSVC
    template class select_oudia_diagram<application::oudia_diagram_dialog_type>;

    template class select_oudia_diagram_for_test<typename application::common_type_list_type::string_type>;
#endif

    template class select_oudia_diagram<test::oudia_diagram_dialog_type>;

    template class select_oudia_diagram_for_test<typename test::common_type_list_type::string_type>;


}}}
