/*! \file
    \brief The master test suite for bobura.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <boost/predef.h>
#define BOOST_TEST_MODULE test_bobura
#include <boost/test/unit_test.hpp> // IWYU pragma: keep

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/detail/stub/gui_impl_set.h>
#if BOOST_OS_WINDOWS
#include <tetengo2/detail/windows/impl_set.h>
#elif BOOST_OS_LINUX
#include <tetengo2/detail/unixos/impl_set.h>
#else
#error Unsupported platform.
#endif


namespace {
    struct set_detail_impl
    {
        set_detail_impl()
        {
#if BOOST_OS_WINDOWS
            tetengo2::detail::set_detail_impl_set(tetengo2::detail::windows::impl_set::instance());
#elif BOOST_OS_LINUX
            tetengo2::detail::set_detail_impl_set(tetengo2::detail::unixos::impl_set::instance());
#else
#error Unsupported platform.
#endif
            tetengo2::detail::set_gui_detail_impl_set(tetengo2::detail::stub::gui_impl_set::instance());
        }
    };
}


BOOST_GLOBAL_FIXTURE(set_detail_impl);
