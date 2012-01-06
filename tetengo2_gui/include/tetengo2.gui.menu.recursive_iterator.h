/*! \file
    \brief The definition of tetengo2::gui::menu::recursive_iterator.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_RECURSIVEITERATOR_H)
#define TETENGO2_GUI_MENU_RECURSIVEITERATOR_H

#include <cassert>
#include <cstddef>
#include <iterator>
#include <stack>
#include <utility>

#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility.hpp>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a recursive iterator.

        \tparam MenuBase A menu base type.
    */
    template <typename MenuBase>
    class recursive_iterator :
        public boost::iterator_facade<
            recursive_iterator<MenuBase>,
            MenuBase,
            boost::forward_traversal_tag
        >
    {
    public:
        // types

        //! The menu base type.
        typedef MenuBase menu_base_type;


        // constructors and destructor

        /*!
            \brief Creates a recursive iterator.
        */
        recursive_iterator()
        :
        m_p_menu(NULL),
        m_parents()
        {
            m_parents.push(
                parent_and_index_type(static_cast<menu_base_type*>(NULL), 0)
            );
        }

        /*!
            \brief Creates a recursive iterator.

            \param p_menu A pointer to a menu.
        */
        explicit recursive_iterator(menu_base_type* const p_menu)
        :
        m_p_menu(p_menu),
        m_parents()
        {
            m_parents.push(
                parent_and_index_type(static_cast<menu_base_type*>(NULL), 0)
            );
        }


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The value.
        */
        menu_base_type& dereference()
        const
        {
            return *m_p_menu;
        }

        /*!
            \brief Returns whether this iterator is equal to another.

            \param another Another recursive iterator.

            \retval true  When this iterator is equal to another.
            \retval false Otherwise.
        */
        bool equal(const recursive_iterator& another)
        const
        {
            return m_p_menu == another.m_p_menu;
        }

        /*!
            \brief Increments the iterator.
        */
        void increment()
        {
            assert(m_p_menu);

            if (
                m_parents.top().second <
                std::distance(m_p_menu->begin(), m_p_menu->end())
            )
            {
                const menu_difference_type index = m_parents.top().second;
                m_parents.push(parent_and_index_type(m_p_menu, 0));
                m_p_menu = &*boost::next(m_p_menu->begin(), index);
                return;
            }

            if (!m_parents.top().first)
            {
                m_p_menu = NULL;
                return;
            }

            m_p_menu = m_parents.top().first;
            m_parents.pop();
            ++m_parents.top().second;
            increment();
        }


    private:
        // types

        typedef
            typename menu_base_type::const_iterator::difference_type
            menu_difference_type;

        typedef
            std::pair<menu_base_type*, menu_difference_type>
            parent_and_index_type;


        // variables

        menu_base_type* m_p_menu;

        std::stack<parent_and_index_type> m_parents;


    };


}}}


#endif