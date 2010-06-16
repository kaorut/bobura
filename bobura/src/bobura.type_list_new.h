/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELISTNEW_H)
#define BOBURA_TYPELISTNEW_H

//#include <cstddef>
#include <string>

#include <boost/mpl/pair.hpp>

#include <tetengo2.encoder.h>
#include <tetengo2.messages.h>
#include <tetengo2.message_catalog_parser.h>
#include <tetengo2.encoding.locale.h>
#include <tetengo2.encoding.win32.utf8.h>
#include <tetengo2.gui.menu_observer.h>
#include <tetengo2.gui.mouse_observer.h>
#include <tetengo2.gui.paint_observer.h>
#include <tetengo2.gui.window_observer.h>
#include <tetengo2.gui.win32.abstract_popup_menu.h>
#include <tetengo2.gui.win32.abstract_window.h>
#include <tetengo2.gui.win32.alert.h>
#include <tetengo2.gui.win32.button.h>
#include <tetengo2.gui.win32.canvas.h>
#include <tetengo2.gui.win32.dialog.h>
#include <tetengo2.gui.win32.dialog_message_loop.h>
#include <tetengo2.gui.win32.font.h>
#include <tetengo2.gui.win32.gui_initializer_finalizer.h>
#include <tetengo2.gui.win32.main_menu.h>
#include <tetengo2.gui.win32.menu.h>
#include <tetengo2.gui.win32.menu_command.h>
#include <tetengo2.gui.win32.menu_separator.h>
#include <tetengo2.gui.win32.message_loop.h>
#include <tetengo2.gui.win32.popup_menu.h>
#include <tetengo2.gui.win32.quit_message_loop.h>
#include <tetengo2.gui.win32.widget.h>
#include <tetengo2.gui.win32.window.h>
#include <tetengo2.meta.assoc_list.h>


namespace bobura
{
    /**** Common ************************************************************/

    namespace type
    {
        struct difference;     //!< The difference type.
        struct size;           //!< The size type.
        struct string;         //!< The string type.
    }

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, std::wstring>,
        tetengo2::meta::assoc_list_end
        > > >
        common_type_list;


    /**** Locale ************************************************************/

    namespace type
    {
        struct ui_encoder;     //!< The encoder type for the user interface.
        struct exception_encoder; //!< The encoder type for exceptions.
        struct message_catalog_encoder; //!< The encoder type for the
                                        //!< message catalog.
        struct locale_name_encoder; //!< The encoder type for locale names.

        struct message_catalog_parser; //!< The message catalog parser type.
        struct messages_facet; //!< The messages facet type.
    }

    namespace detail { namespace locale
    {
        typedef
            tetengo2::encoding::locale<
                boost::mpl::at<common_type_list, type::string>::type
            >
            internal_encoding_type;
        typedef tetengo2::encoding::locale<std::wstring> ui_encoding_type;
        typedef tetengo2::encoding::win32::utf8 exception_encoding_type;
        typedef
            tetengo2::encoding::win32::utf8 message_catalog_encoding_type;
        typedef
            tetengo2::encoding::locale<std::string>
            locale_name_encoding_type;

        typedef
            tetengo2::encoder<
                internal_encoding_type, message_catalog_encoding_type
            >
            message_catalog_encoder_type;
        typedef
            tetengo2::message_catalog_parser<
                std::istream,
                boost::mpl::at<common_type_list, type::string>::type,
                message_catalog_encoder_type
            >
            message_catalog_parser_type;
        typedef
            tetengo2::encoder<
                internal_encoding_type, locale_name_encoding_type
            >
            locale_name_encoder_type;
    }}

    //! The type list for the locale.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui_encoder,
                tetengo2::encoder<
                    detail::locale::internal_encoding_type,
                    detail::locale::ui_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::exception_encoder,
                tetengo2::encoder<
                    detail::locale::internal_encoding_type,
                    detail::locale::exception_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog_encoder,
                detail::locale::message_catalog_encoder_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale_name_encoder,
                detail::locale::locale_name_encoder_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog_parser,
                detail::locale::message_catalog_parser_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::messages_facet,
                tetengo2::messages<
                    boost::filesystem::wpath,
                    detail::locale::message_catalog_parser_type,
                    detail::locale::locale_name_encoder_type
                >
            >,
        tetengo2::meta::assoc_list_end
        > > > > > >
        locale_type_list;


    /**** User Interface ****************************************************/

    namespace type
    {
        struct gui_initializer_finalizer; //!< The GUI initializer and
                                          //!< finalizer type.
        struct message_loop;   //!< The message loop type.
        struct quit_message_loop; //!< The quit-message-loop type.
        struct canvas;         //!< The canvas type.
        struct window;         //!< The window type.
        struct popup_menu;     //!< The popup menu type.
        struct menu_command;   //!< The menu command type.
        struct menu_separator; //!< The menu separator type;
        struct dialog;         //!< The dialog type.
        struct button;         //!< The button type.
    }

    namespace detail { namespace ui
    {

    }}

    //! The type list for the user interface.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::gui_initializer_finalizer,
                tetengo2::gui::win32::gui_initializer_finalizer
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_loop, tetengo2::gui::win32::message_loop
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::quit_message_loop,
                tetengo2::gui::win32::quit_message_loop
            >,
        tetengo2::meta::assoc_list_end
        > > >
        ui_type_list;



    /**** All ***************************************************************/

    //! The type list for Bobura.
    typedef
        boost::mpl::insert_range<
            common_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            locale_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            ui_type_list, tetengo2::meta::assoc_list_end,
        tetengo2::meta::assoc_list_end
        >::type>::type>::type
        bobura_type_list;


}


#endif
