/*! \file
    \brief Test of class tetengo2::message::message_catalog_parser_j.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <istream>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.text.grammar.json.h"
#include "tetengo2.text.pull_parser.h"
#include "tetengo2.text.push_parser.h"
#include "tetengo2.unique.h"

#include "tetengo2.message.message_catalog_parser_j.h"


namespace
{
    // types

    typedef
        tetengo2::text::grammar::json<std::string::const_iterator>
        grammar_type;

    typedef
        tetengo2::text::push_parser<
            std::string::const_iterator,
            grammar_type,
            int,
            double
        >
        push_parser_type;

    typedef
        tetengo2::text::pull_parser<push_parser_type, std::size_t>
        pull_parser_type;

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        message_catalog_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, message_catalog_encoding_type
        >
        message_catalog_encoder_type;

    typedef
        tetengo2::message::message_catalog_parser_j<
            pull_parser_type, std::string, message_catalog_encoder_type
        >
        message_catalog_parser_type;

    typedef message_catalog_parser_type::entry_type entry_type;


    // data

    const std::string catalog0(
        ""
    );

    const std::string catalog1(
        "{\n"
        "    \"header\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\"\n"
        "    }\n"
        "}\n"
    );

    const std::string catalog2(
        "{\n"
        "    \"body\":\n"
        "    {\n"
        "    }\n"
        "}\n"
    );

    const std::string catalog3(
        "{\n"
        "    \"body\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\"\n"
        "    }\n"
        "}\n"
    );

    const std::string catalog4(
        "{\n"
        "    \"header\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\",\n"
        "        \"Key2\": [12, 34, 56]\n"
        "    },\n"
        "    \"body\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\",\n"
        "        \"Key2\": \"Value2\"\n"
        "    }\n"
        "}\n"
    );


    // functions

    std::unique_ptr<pull_parser_type> create_pull_parser(
        const std::string& input
    )
    {
        std::unique_ptr<grammar_type> p_grammar =
            tetengo2::make_unique<grammar_type>();

        std::unique_ptr<push_parser_type> p_push_parser =
            tetengo2::make_unique<push_parser_type>(
                input.begin(), input.end(), std::move(p_grammar)
            );

        return tetengo2::make_unique<pull_parser_type>(
            std::move(p_push_parser), 3
        );
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_catalog_parser_j)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const std::unique_ptr<message_catalog_parser_type> p_parser =
            tetengo2::make_unique<message_catalog_parser_type>(
                create_pull_parser(catalog0)
            );
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog0)
                );

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog1)
                );

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog2)
                );

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog3)
                );

            BOOST_CHECK(p_parser->has_next());
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog4)
                );

            BOOST_CHECK(p_parser->has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog0)
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog1)
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog2)
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog3)
                );

            {
                const entry_type entry = p_parser->next();
                BOOST_CHECK(entry.first == "Key1");
                BOOST_CHECK(entry.second == "Value1");
            }
            BOOST_CHECK(!p_parser->has_next());
        }
        {
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(catalog4)
                );

            {
                const entry_type entry = p_parser->next();
                BOOST_CHECK(entry.first == "Key1");
                BOOST_CHECK(entry.second == "Value1");
            }
            {
                const entry_type entry = p_parser->next();
                BOOST_CHECK(entry.first == "Key2");
                BOOST_CHECK(entry.second == "Value2");
            }
            BOOST_CHECK(!p_parser->has_next());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
