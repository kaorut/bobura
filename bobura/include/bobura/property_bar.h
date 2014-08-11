/*! \file
    \brief The definition of bobura::property_bar.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_PROPERTYBAR_H)
#define BOBURA_PROPERTYBAR_H

#include <cassert>
#include <memory>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/message/property_bar.h>
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
        \tparam ConfigTraits    A configuration traits type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename ConfigTraits,
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

        //! The config traits type.
        using config_traits_type = ConfigTraits;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type, config_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a property bar.

            \param parent          A parent.
            \param settings        Settings.
            \param message_catalog A message catalog.
        */
        property_bar(
            abstract_window_type&       parent,
            settings_type&              settings,
            const message_catalog_type& message_catalog
        )
        :
        base_type(parent),
        m_settings(settings),
        m_message_catalog(message_catalog),
        m_p_map_box()
        {
            initialize_property_bar();
        }

        /*!
            \brief Destroys the property bar.
        */
        virtual ~property_bar()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Returns the map box.

            \return The map box.
        */
        const map_box_type& map_box()
        const
        {
            assert(m_p_map_box);
            return *m_p_map_box;
        }

        /*!
            \brief Returns the map box.

            \return The map box.
        */
        map_box_type& map_box()
        {
            assert(m_p_map_box);
            return *m_p_map_box;
        }

        /*!
            \brief Saves the settings.
        */
        void save_settings()
        {
            m_settings.set_property_bar_width(this->normal_preferred_width());
            m_settings.set_property_bar_minimized(this->minimized());
            m_settings.set_property_bar_splitter_position(m_p_map_box->splitter_position());
        }


    private:
        // types

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using resized_type = message::property_bar::resized<base_type, map_box_type>;

        using mouse_pressed_type = message::property_bar::mouse_pressed<map_box_type>;

        // variables

        settings_type& m_settings;

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<map_box_type> m_p_map_box;


        // functions

        void initialize_property_bar()
        {
            this->set_text(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Properties")));

            m_p_map_box = tetengo2::stdalt::make_unique<map_box_type>(*this);

            this->size_observer_set().resized().connect(resized_type{ *this, *m_p_map_box });

            m_p_map_box->mouse_observer_set().pressed().connect(mouse_pressed_type{ *m_p_map_box });

            load_settings();
        }

        void load_settings()
        {
            const auto width = m_settings.property_bar_width();
            if (width)
                this->set_width(*width);
            else
                this->set_width(width_type{ 32 });

            this->size_observer_set().resized()();

            const auto minimized = m_settings.property_bar_minimized();
            if (minimized)
                this->set_minimized(*minimized);
            else
                this->set_minimized(false);

            const auto splitter_position = m_settings.property_bar_splitter_position();
            if (splitter_position)
                m_p_map_box->set_splitter_position(*splitter_position);
            else
                m_p_map_box->set_splitter_position(left_type{ 16 });
        }


    };


}

#endif
