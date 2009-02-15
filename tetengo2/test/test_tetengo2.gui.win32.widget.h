/*! \file
    \brief Test of class tetengo2::gui::win32::widget.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_WIDGET_H)
#define TESTTETENGO2_GUI_WIN32_WIDGET_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui { namespace win32
{
    class widget
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void has_parent();

        static void parent();

        static void set_enabled();

        static void enabled();

        static void set_visible();

        static void visible();

        static void set_position();

        static void position();

        static void set_dimension();

        static void dimension();

        static void set_text();

        static void text();

        static void add_paint_observer();

        static void destroyed();

        static void p_static_window_procedure();

        static void associate_to_native_window_system();

        static void window_procedure();


    };


}}}

#endif
