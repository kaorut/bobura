/*! \file
    \brief Test of class bobura::model::message::oudia_diagram_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/detail_type_list.h>
#include <bobura/model/message/oudia_diagram_dialog.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using dialog_type = ui_type_list_type::dialog_type;

    using window_type = ui_type_list_type::window_type;

    class concrete_dialog : public dialog_type
    {
    public:
        explicit concrete_dialog(window_type::base_type& parent) : dialog_type{ parent } {}
    };
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(model)
        BOOST_AUTO_TEST_SUITE(message)
            BOOST_AUTO_TEST_SUITE(oudia_diagram_dialog)
                BOOST_AUTO_TEST_SUITE(ok_button_mouse_clicked)
                    // test cases

                    BOOST_AUTO_TEST_CASE(construction)
                    {
                        BOOST_TEST_PASSPOINT();

                        window_type     parent{};
                        concrete_dialog dialog{ parent };
                        const bobura::model::message::oudia_diagram_dialog::ok_button_mouse_clicked<dialog_type>
                            observer{ dialog };
                    }

                    BOOST_AUTO_TEST_CASE(operator_paren)
                    {
                        BOOST_TEST_PASSPOINT();

                        window_type     parent{};
                        concrete_dialog dialog{ parent };
                        const bobura::model::message::oudia_diagram_dialog::ok_button_mouse_clicked<dialog_type>
                            observer{ dialog };

                        observer();
                    }


                BOOST_AUTO_TEST_SUITE_END()
                BOOST_AUTO_TEST_SUITE(cancel_button_mouse_clicked)
                    // test cases

                    BOOST_AUTO_TEST_CASE(construction)
                    {
                        BOOST_TEST_PASSPOINT();

                        window_type     parent{};
                        concrete_dialog dialog{ parent };
                        const bobura::model::message::oudia_diagram_dialog::cancel_button_mouse_clicked<dialog_type>
                            observer{ dialog };
                    }

                    BOOST_AUTO_TEST_CASE(operator_paren)
                    {
                        BOOST_TEST_PASSPOINT();

                        window_type     parent{};
                        concrete_dialog dialog{ parent };
                        const bobura::model::message::oudia_diagram_dialog::cancel_button_mouse_clicked<dialog_type>
                            observer{ dialog };

                        observer();
                    }


                BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
