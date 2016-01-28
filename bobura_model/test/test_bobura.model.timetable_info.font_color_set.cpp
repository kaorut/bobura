/*! \file
    \brief Test of class bobura::model::timetable_info::font_color_set.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/timetable_info/font_color_set.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using font_type = ui_type_list_type::font_type;

    using color_type = ui_type_list_type::color_type;

    using font_color_set_type = bobura::model::timetable_info::font_color_set<font_type>;

    using font_color_type = font_color_set_type::font_color_type;


    // functions

    font_color_set_type make_font_color_set1()
    {
        font_color_type background_font_color{ boost::none, boost::make_optional(color_type{ 12, 34, 56 }) };
        font_color_type company_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type line_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("def") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type note_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("ghi") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type time_line_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("jkl") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type local_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("mno") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type principal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("pqr") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type local_terminal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("stu") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type principal_terminal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("vwx") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type train_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("yza") }, 42, false, true, false, true }),
            boost::none
        };

        return
            font_color_set_type{
                std::move(background_font_color),
                std::move(company_name_font_color),
                std::move(line_name_font_color),
                std::move(note_font_color),
                std::move(time_line_font_color),
                std::move(local_station_font_color),
                std::move(principal_station_font_color),
                std::move(local_terminal_station_font_color),
                std::move(principal_terminal_station_font_color),
                std::move(train_name_font_color)
            };
    }

    font_color_set_type make_font_color_set2()
    {
        font_color_type background_font_color{ boost::none, boost::make_optional(color_type{ 12, 34, 56 }) };
        font_color_type company_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type line_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("def") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type note_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("ghi") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type time_line_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("jkl") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type local_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("mno") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type principal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("pqr") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type local_terminal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("stu") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type principal_terminal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("vwx") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type train_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("yza") }, 42, false, true, false, true }),
            boost::none
        };

        return
            font_color_set_type{
                std::move(background_font_color),
                std::move(company_name_font_color),
                std::move(line_name_font_color),
                std::move(note_font_color),
                std::move(time_line_font_color),
                std::move(local_station_font_color),
                std::move(principal_station_font_color),
                std::move(local_terminal_station_font_color),
                std::move(principal_terminal_station_font_color),
                std::move(train_name_font_color)
            };
    }

    font_color_set_type make_font_color_set3()
    {
        font_color_type background_font_color{ boost::none, boost::make_optional(color_type{ 12, 34, 56 }) };
        font_color_type company_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("ABC") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type line_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("DEF") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type note_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("GHI") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type time_line_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("JKL") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type local_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("MNO") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type principal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("PQR") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type local_terminal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("STU") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type principal_terminal_station_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("VWX") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
        font_color_type train_name_font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("YZA") }, 42, false, true, false, true }),
            boost::none
        };

        return
            font_color_set_type{
                std::move(background_font_color),
                std::move(company_name_font_color),
                std::move(line_name_font_color),
                std::move(note_font_color),
                std::move(time_line_font_color),
                std::move(local_station_font_color),
                std::move(principal_station_font_color),
                std::move(local_terminal_station_font_color),
                std::move(principal_terminal_station_font_color),
                std::move(train_name_font_color)
            };
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable_info)
BOOST_AUTO_TEST_SUITE(font_color)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const font_color_type font_color1{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            };
            const font_color_type font_color2{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            };

            BOOST_CHECK(font_color1 == font_color2);
        }
        {
            const font_color_type font_color1{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            };
            const font_color_type font_color2{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("ABC") }, 24, true, true, false, false }),
                boost::make_optional(color_type{ 21, 43, 65 })
            };

            BOOST_CHECK(font_color1 != font_color2);
        }
    }

    BOOST_AUTO_TEST_CASE(diagram_font)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };

        const auto expected =
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true });
        BOOST_CHECK(font_color.diagram_font() == expected);
    }

    BOOST_AUTO_TEST_CASE(diagram_color)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color{
            boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
            boost::make_optional(color_type{ 12, 34, 56 })
        };

        BOOST_CHECK((font_color.diagram_color() == boost::make_optional(color_type{ 12, 34, 56 })));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(font_color_set)
    // test cases

    BOOST_AUTO_TEST_CASE(default_)
    {
        BOOST_TEST_PASSPOINT();

        font_color_set_type::default_();
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        make_font_color_set1();
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const font_color_set_type font_color_set1 = make_font_color_set1();
            const font_color_set_type font_color_set2 = make_font_color_set2();


            BOOST_CHECK(font_color_set1 == font_color_set2);
        }
        {
            const font_color_set_type font_color_set1 = make_font_color_set1();
            const font_color_set_type font_color_set3 = make_font_color_set3();

            BOOST_CHECK(font_color_set1 != font_color_set3);
        }
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.background() ==
            font_color_type{ boost::none, boost::make_optional(color_type{ 12, 34, 56 }) }
        ));
    }

    BOOST_AUTO_TEST_CASE(company_name)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.company_name() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("abc") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(line_name)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.line_name() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("def") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.note() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("ghi") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(time_line)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.time_line() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("jkl") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(local_station)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.local_station() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("mno") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(principal_station)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.principal_station() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("pqr") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(local_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.local_terminal_station() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("stu") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(principal_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.principal_terminal_station() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("vwx") }, 42, false, true, false, true }),
                boost::make_optional(color_type{ 12, 34, 56 })
            }
        ));
    }

    BOOST_AUTO_TEST_CASE(train_name)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_set_type font_color_set = make_font_color_set1();

        BOOST_CHECK((
            font_color_set.train_name() ==
            font_color_type{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("yza") }, 42, false, true, false, true }),
                boost::none
            }
        ));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
