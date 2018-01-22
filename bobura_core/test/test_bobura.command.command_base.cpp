/*! \file
    \brief Test of class bobura::command::command_base.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <bobura/command/command_base.h>
#include <bobura/detail_type_list.h>
#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using window_type = ui_type_list_type::window_type;

    using model_type =
        bobura::timetable_model<
            common_type_list_type::size_type,
            common_type_list_type::difference_type,
            string_type,
            common_type_list_type::operating_distance_type,
            common_type_list_type::speed_type,
            ui_type_list_type::fast_font_type
        >;

    using parameter_base_type = bobura::command::parameter_base;

    class concrete_parameter_type : public parameter_base_type
    {
    public:
        concrete_parameter_type()
        {}

        virtual ~concrete_parameter_type()
        noexcept
        {}

    };

    using command_base_type = bobura::command::command_base<traits_type_list_type::command_type>;

    class concrete_command_type : public command_base_type
    {
    public:
        virtual ~concrete_command_type()
        noexcept
        {}

    private:
        virtual void execute_impl(model_type&, abstract_window_type&)
        const
        {}

    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(parameter_base)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_parameter_type parameter{};
    }

    BOOST_AUTO_TEST_CASE(as)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_parameter_type parameter{};
            const parameter_base_type& parameter_base = parameter;

            BOOST_TEST(&parameter_base.as<concrete_parameter_type>() == &parameter);
        }
        {
            concrete_parameter_type parameter{};
            parameter_base_type& parameter_base = parameter;

            BOOST_TEST(&parameter_base.as<concrete_parameter_type>() == &parameter);
        }
    }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(command_base)
    // test cases

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_command_type command{};

        const model_type model{};
        BOOST_TEST(command.enabled(model));
    }

    BOOST_AUTO_TEST_CASE(state)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_command_type command{};

        BOOST_CHECK(command.state() == command_base_type::state_type::default_);
    }

    BOOST_AUTO_TEST_CASE(execute)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_command_type command{};

        {
            model_type model{};
            window_type parent{};
            command.execute(model, parent);
        }
        {
            model_type model{};
            window_type parent{};
            const concrete_parameter_type parameter{};
            command.execute(model, parent, parameter);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
