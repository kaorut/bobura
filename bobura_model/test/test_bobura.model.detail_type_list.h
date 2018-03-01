/*! \file
    \brief The definition of test_bobura::model::detail_type_list.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_DETAILTYPELIST_H)
#define TESTBOBURA_MODEL_DETAILTYPELIST_H

#include <tetengo2/detail/stub/drawing.h>


namespace test_bobura { namespace model {
    namespace type_list {
    /**** Detail Implementation **************************************************************************************/

#if !defined(DOCUMENTATION)
        namespace detail { namespace detail { namespace test {
            using drawing_details_type = tetengo2::detail::stub::drawing;

        }}}
#endif

        /*!
            \brief The detail type list for the testing.
        */
        struct detail_for_test
        {
            //! The drawing type.
            using drawing_type = detail::detail::test::drawing_details_type;
        };
    }
}}


#endif
