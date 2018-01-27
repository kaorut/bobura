/*! \file
    \brief The definition of bobura::property_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_PROPERTYBAR_H)
#define BOBURA_PROPERTYBAR_H

#include <memory>

#include <tetengo2/detail/base/impl_set.h>

#include <bobura/settings.h>


namespace bobura
{
    /*!
        \brief The class template for the property bar.

        \tparam String          A string type.
        \tparam Position        A position type.
        \tparam Dimension       A dimension type.
        \tparam AbstractWindow  An abstract window type.
        \tparam SideBar         A side bar type.
        \tparam MapBox          A map box type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename MessageCatalog
    >
    class property_bar : public SideBar
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The base type.
        using base_type = SideBar;

        //! The map box type.
        using map_box_type = MapBox;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type>;

        //! The detail implementation set type.
        using detail_impl_set_type = tetengo2::detail::base::impl_set;


        // constructors and destructor

        /*!
            \brief Creates a property bar.

            \param parent          A parent.
            \param settings        Settings.
            \param message_catalog A message catalog.
            \param detail_impl_set A detail implementation set.
        */
        property_bar(
            abstract_window_type&       parent,
            settings_type&              settings,
            const message_catalog_type& message_catalog,
            const detail_impl_set_type& detail_impl_set
        );

        /*!
            \brief Destroys the property bar.
        */
        virtual ~property_bar()
        noexcept;


        // functions

        /*!
            \brief Returns the map box.

            \return The map box.
        */
        const map_box_type& map_box()
        const;

        /*!
            \brief Returns the map box.

            \return The map box.
        */
        map_box_type& map_box();

        /*!
            \brief Saves the settings.
        */
        void save_settings();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}

#endif
