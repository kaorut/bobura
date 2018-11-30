/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/text.h>

#include <bobura/model/station_info/grade.h>


namespace bobura::model::station_info {
    const grade::string_type& grade::name() const
    {
        return name_impl();
    }

    grade::grade() = default;

    grade::~grade() = default;


    const local& local::instance()
    {
        static const local singleton{};

        return singleton;
    }

    local::~local() = default;

    local::local() = default;

    const local::string_type& local::name_impl() const
    {
        static const typename local::string_type singleton{ TETENGO2_TEXT("local") };
        return singleton;
    }


    const principal& principal::instance()
    {
        static const principal singleton{};

        return singleton;
    }

    principal::~principal() = default;

    principal::principal() = default;

    const principal::string_type& principal::name_impl() const
    {
        static const typename principal::string_type singleton{ TETENGO2_TEXT("principal") };
        return singleton;
    }


    const local_terminal& local_terminal::instance()
    {
        static const local_terminal singleton{};

        return singleton;
    }

    local_terminal::~local_terminal() = default;

    local_terminal::local_terminal() = default;

    const local_terminal::string_type& local_terminal::name_impl() const
    {
        static const typename local_terminal::string_type singleton{ TETENGO2_TEXT("local terminal") };
        return singleton;
    }


    const principal_terminal& principal_terminal::instance()
    {
        static const principal_terminal singleton{};

        return singleton;
    }

    principal_terminal::~principal_terminal() = default;

    principal_terminal::principal_terminal() = default;

    const principal_terminal::string_type& principal_terminal::name_impl() const
    {
        static const typename principal_terminal::string_type singleton{ TETENGO2_TEXT("principal terminal") };
        return singleton;
    }
}
