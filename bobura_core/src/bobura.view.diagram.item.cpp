/*! \file
    \brief The definition of bobura::view::diagram::item.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>

#include <bobura/detail_type_list.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/item.h>


namespace bobura { namespace view { namespace diagram
{
    template <typename Traits>
    class item<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using position_type = typename canvas_type::position_type;

        using selection_type = typename item::selection_type;


        // constructors and destructor

        explicit impl(selection_type& selection)
        :
        m_p_selection(&selection)
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_selection = another.m_p_selection;

            return *this;
        }

        const selection_type& get_selection()
        const
        {
            return *m_p_selection;
        }

        selection_type& get_selection()
        {
            return *m_p_selection;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            boost::ignore_unused(canvas);
        }

        item* p_item_by_position_impl(const position_type& position)
        {
            boost::ignore_unused(position);

            return nullptr;
        }

        bool selected_impl()
        const
        {
            return false;
        }

        void select_impl(const bool switch_selection_style)
        {
            boost::ignore_unused(switch_selection_style);
        }


    private:
        // variables

        selection_type* m_p_selection;


    };


    template <typename Traits>
    item<Traits>::item(selection_type& selection)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(selection))
    {}

    template <typename Traits>
    item<Traits>::~item()
    noexcept
    {}

    template <typename Traits>
    item<Traits>& item<Traits>::operator=(item&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);

        return *this;
    }

    template <typename Traits>
    void item<Traits>::draw_on(canvas_type& canvas)
    const
    {
        draw_on_impl(canvas);
    }

    template <typename Traits>
    item<Traits>* item<Traits>::p_item_by_position(const position_type& position)
    {
        return p_item_by_position_impl(position);
    }

    template <typename Traits>
    const item<Traits>* item<Traits>::p_item_by_position(const position_type& position)
    const
    {
        return const_cast<item*>(this)->p_item_by_position_impl(position);
    }

    template <typename Traits>
    const typename item<Traits>::selection_type& item<Traits>::get_selection()
    const
    {
        return m_p_impl->get_selection();
    }

    template <typename Traits>
    typename item<Traits>::selection_type& item<Traits>::get_selection()
    {
        return m_p_impl->get_selection();
    }

    template <typename Traits>
    bool item<Traits>::selected()
    const
    {
        return selected_impl();
    }

    template <typename Traits>
    void item<Traits>::select(const bool switch_selection_style)
    {
        select_impl(switch_selection_style);
    }

    template <typename Traits>
    void item<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }

    template <typename Traits>
    item<Traits>* item<Traits>::p_item_by_position_impl(const position_type& position)
    {
        return m_p_impl->p_item_by_position_impl(position);
    }

    template <typename Traits>
    bool item<Traits>::selected_impl()
    const
    {
        return m_p_impl->selected_impl();
    }

    template <typename Traits>
    void item<Traits>::select_impl(const bool switch_selection_style)
    {
        m_p_impl->select_impl(switch_selection_style);
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
    template class item<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class item<typename test::traits_type_list_type::diagram_view_type>;


}}}
