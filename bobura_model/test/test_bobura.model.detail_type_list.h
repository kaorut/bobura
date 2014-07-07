/*! \file
    \brief The definition of test_bobura::model::detail_type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_DETAILTYPELIST_H)
#define TESTBOBURA_MODEL_DETAILTYPELIST_H

#include <boost/mpl/pair.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2/detail/stub/drawing.h>
#if BOOST_COMP_MSVC
#   include <tetengo2/detail/windows/config.h>
#   include <tetengo2/detail/windows/encoding.h>
#else
#   include <tetengo2/detail/unixos/config.h>
#   include <tetengo2/detail/unixos/encoding.h>
#endif


namespace test_bobura { namespace model
{
    /**** Detail Implementation *********************************************/

    namespace type { namespace detail
    {
        struct config;   //!< The configuration type.
        struct drawing;  //!< The drawing type.
        struct encoding; //!< The encoding type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
        using drawing_details_type = tetengo2::detail::stub::drawing;
#if BOOST_COMP_MSVC
        using config_details_type = tetengo2::detail::windows::config;
        using encoding_details_type = tetengo2::detail::windows::encoding;
#else
        using config_details_type = tetengo2::detail::unixos::config;
        using encoding_details_type = tetengo2::detail::unixos::encoding;
#endif
    }}
#endif

    //! The detail type list.
    using detail_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::config, detail::detail::config_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::drawing, detail::detail::drawing_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::encoding, detail::detail::encoding_details_type>,
        tetengo2::meta::assoc_list_end
        >>>;


}}


#endif
