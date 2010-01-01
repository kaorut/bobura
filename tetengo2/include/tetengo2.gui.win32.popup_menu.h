/*! \file
    \brief The definition of tetengo2::gui::popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_POPUPMENU_H)
#define TETENGO2_GUI_WIN32_POPUPMENU_H

//#include <cstddef>
//#include <memory>
#include <stdexcept>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"
#include "concept_tetengo2.gui.MenuItemList.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a popup menu.

        \tparam MenuItem     A menu item type. It must conform to
                             concept_tetengo2::gui::MenuItem<MenuItem>
        \tparam MenuItemList A menu item list type. It must conform to
                             concept_tetengo2::gui::MenuItemList<MenuItemList>.
   */
    template <typename MenuItem, typename MenuItemList>
    class popup_menu : public MenuItem
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuItemList<MenuItemList>
        ));


    public:
        // types

        //! The menu item type.
        typedef MenuItem menu_item_type;

        //! \copydoc tetengo2::gui::win32::menu_item::id_type
        typedef typename menu_item_type::id_type id_type;

        //! \copydoc tetengo2::gui::win32::menu_item::handle_type
        typedef typename menu_item_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::menu_item::string_type
        typedef typename menu_item_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::menu_item::encode_from_native_type
        typedef
            typename menu_item_type::encode_from_native_type
            encode_from_native_type;

        //! \copydoc tetengo2::gui::win32::menu_item::encode_to_native_type
        typedef
            typename menu_item_type::encode_to_native_type
            encode_to_native_type;

        //! \copydoc tetengo2::gui::win32::menu_item::menu_observer_type
        typedef
            typename menu_item_type::menu_observer_type
            menu_observer_type;

        //! The menu items type.
        typedef MenuItemList menu_items_type;

        //! The menu item iterator type.
        typedef typename menu_items_type::iterator menu_item_iterator;

        //! The const menu item iterator type.
        typedef
            typename menu_items_type::const_iterator const_menu_item_iterator;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \param text A text.
        */
        popup_menu(const string_type& text)
        :
        menu_item(text),
        m_handle(create_menu()),
        m_menu_items(m_handle)
        {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup_menu()
        throw ()
        {
            if (::IsMenu(m_handle) != 0)
                ::DestroyMenu(m_handle);
        }


        // functions

        //! \copydoc tetengo2::gui::win32::menu_item::is_command
        virtual bool is_command()
        const
        {
            return false;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::is_popup
        virtual bool is_popup()
        const
        {
            return true;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::is_separator
        virtual bool is_separator()
        const
        {
            return false;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::handle
        virtual handle_type handle()
        const
        {
            return m_handle;
        }

        /*!
            \brief Returns the first immutable iterator to the menu items.

            \return The first immutable iterator.
        */
        const_menu_item_iterator menu_item_begin()
        const
        {
            return m_menu_items.begin();
        }

        /*!
            \brief Returns the first mutable iterator to the menu items.

            \return The first mutable iterator.
        */
        menu_item_iterator menu_item_begin()
        {
            return m_menu_items.begin();
        }

        /*!
            \brief Returns the last immutable iterator to the menu items.

            \return The last immutable iterator.
        */
        const_menu_item_iterator menu_item_end()
        const
        {
            return m_menu_items.end();
        }

        /*!
            \brief Returns the last mutable iterator to the menu items.

            \return The last mutable iterator.
        */
        menu_item_iterator menu_item_end()
        {
            return m_menu_items.end();
        }

        /*!
            \brief Inserts a menu item.

            \param offset      An offset where a menu item is inserted.
            \param p_menu_item An auto pointer to a menu item. It must not be
                               NULL.
        */
        void insert(
            menu_item_iterator            offset,
            std::auto_ptr<menu_item_type> p_menu_item
        )
        {
            m_menu_items.insert(offset, p_menu_item);
        }

        /*!
            \brief Erases the menu items.

            \param first The first iterator to the erased items.
            \param last  The last iterator to the eraed items.
        */
        void erase(menu_item_iterator first, menu_item_iterator last)
        {
            m_menu_items.erase(first, last);
        }

        /*!
            \brief Finds a menu item by the specified id.

            If the menu item does not exist, it returns NULL.

            \param id An id.

            \return The pointer to the menu item.
        */
        const menu_item_type* find_by_id(const id_type id)
        const
        {
            return m_menu_items.find_by_id<popup_menu>(id);
        }

        /*!
            \brief Finds a menu item by the specified id.

            If the menu item does not exist, it returns NULL.

            \param id An id.

            \return The pointer to the menu item.
        */
        menu_item_type* find_by_id(const id_type id)
        {
            return m_menu_items.find_by_id<popup_menu>(id);
        }

        /*!
            \brief Finds a menu item by the specified handle.

            If the menu item does not exist, it returns NULL.

            \param handle A handle.

            \return The pointer to the menu item.
        */
        const menu_item_type* find_by_handle(const handle_type handle)
        const
        {
            return m_menu_items.find_by_handle<popup_menu>(handle);
        }

        /*!
            \brief Finds a menu item by the specified handle.

            If the menu item does not exist, it returns NULL.

            \param handle A handle.

            \return The pointer to the menu item.
        */
        menu_item_type* find_by_handle(const handle_type handle)
        {
            return m_menu_items.find_by_handle<popup_menu>(handle);
        }


    private:
        // static functions

        handle_type create_menu()
        {
            const handle_type handle = ::CreatePopupMenu();

            if (handle == NULL)
                throw std::runtime_error("Can't create a main menu.");

            return handle;
        }


        // variables

        const handle_type m_handle;

        menu_items_type m_menu_items;


    };


}}}

#endif
