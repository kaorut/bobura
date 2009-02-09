/*! \file
    \brief The definition of concept_tetengo2::gui::Window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_WINDOW_H)
#define CONCEPTTETENGO2_GUI_WINDOW_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Widget.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a window.

        \tparam Type A type.
    */
    template <typename Type>
    class Window : private Widget<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::main_menu_type main_menu_type;

        typedef typename Type::window_observer_type window_observer_type;

        typename Type::style_type m_style;


        // usage checks

        BOOST_CONCEPT_USAGE(Window)
        {
            m_object.activate();

            main_menu_type& main_menu = m_object.main_menu();
            boost::ignore_unused_variable_warning(main_menu);

            std::auto_ptr<main_menu_type> p_main_menu;
            m_object.set_main_menu(p_main_menu);

            std::auto_ptr<window_observer_type> p_window_observer;
            m_object.add_window_observer(p_window_observer);

            m_object.close();

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const bool has_main_menu = object.has_main_menu();
            boost::ignore_unused_variable_warning(has_main_menu);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
