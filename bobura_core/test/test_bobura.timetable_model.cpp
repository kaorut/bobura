/*! \file
    \brief Test of class bobura::timetable_model.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include <bobura/detail_type_list.h>
#include <bobura/model/timetable.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace {
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using model_type = bobura::timetable_model<
        common_type_list_type::size_type,
        common_type_list_type::difference_type,
        string_type,
        common_type_list_type::operating_distance_type,
        common_type_list_type::speed_type,
        ui_type_list_type::fast_font_type>;

    using timetable_type = model_type::timetable_type;
}


BOOST_AUTO_TEST_SUITE(test_bobura)
    BOOST_AUTO_TEST_SUITE(timetable_model)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            const model_type model{};
        }

        BOOST_AUTO_TEST_CASE(timetable)
        {
            BOOST_TEST_PASSPOINT();

            const model_type model{};

            const auto& timetable = model.timetable();

            BOOST_TEST(timetable.line_name().empty());
        }

        BOOST_AUTO_TEST_CASE(reset_timetable)
        {
            BOOST_TEST_PASSPOINT();

            {
                model_type model{};

                model.reset_timetable();
            }
            {
                model_type model{};

                model.reset_timetable(std::make_unique<timetable_type>());
            }
            {
                model_type model{};

                model.reset_timetable(
                    std::make_unique<timetable_type>(),
                    tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("hoge") } });
            }
            {
                model_type model{};

                BOOST_CHECK_THROW(
                    model.reset_timetable(
                        std::unique_ptr<timetable_type>{},
                        tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("hoge") } }),
                    std::invalid_argument);
            }
        }

        BOOST_AUTO_TEST_CASE(has_path)
        {
            BOOST_TEST_PASSPOINT();

            {
                const model_type model{};

                BOOST_TEST(!model.has_path());
            }
            {
                model_type model{};
                auto       p_timetable = std::make_unique<timetable_type>();
                model.reset_timetable(std::move(p_timetable), string_type{ TETENGO2_TEXT("hoge") });

                BOOST_TEST(model.has_path());
            }
        }

        BOOST_AUTO_TEST_CASE(path)
        {
            BOOST_TEST_PASSPOINT();

            {
                const model_type model{};

                BOOST_CHECK_THROW(model.path(), std::logic_error);
            }
            {
                model_type model{};
                auto       p_timetable = std::make_unique<timetable_type>();
                model.reset_timetable(std::move(p_timetable), string_type{ TETENGO2_TEXT("hoge") });

                BOOST_CHECK(model.path() == tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("hoge") } });
            }
        }

        BOOST_AUTO_TEST_CASE(set_path)
        {
            BOOST_TEST_PASSPOINT();

            model_type model{};
            model.set_path(tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("hoge") } });

            BOOST_CHECK(model.path() == tetengo2::stdalt::filesystem::path{ string_type{ TETENGO2_TEXT("hoge") } });
        }

        BOOST_AUTO_TEST_CASE(changed)
        {
            BOOST_TEST_PASSPOINT();

            const model_type model{};

            BOOST_TEST(!model.changed());
        }

        BOOST_AUTO_TEST_CASE(set_changed)
        {
            BOOST_TEST_PASSPOINT();

            {
                model_type model{};

                model.set_changed(false);

                BOOST_TEST(!model.changed());
            }
            {
                model_type model{};

                model.set_changed(true);

                BOOST_TEST(model.changed());
            }
        }

        BOOST_AUTO_TEST_CASE(observer_set)
        {
            BOOST_TEST_PASSPOINT();

            {
                const model_type model{};

                model.observer_set();
            }
            {
                model_type model{};

                model.observer_set();
            }
        }


    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
