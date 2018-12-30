/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <string>

#include <bobura/model/train_info/stop.h>
#include <bobura/model/train_info/time.h>


namespace bobura::model::train_info {
    class stop::impl
    {
    public:
        // types

        using time_type = stop::time_type;

        using string_type = stop::string_type;


        // constructors and destructor

        impl(time_type arrival, time_type departure, const bool operational, string_type platform)
        : m_arrival{ std::move(arrival) }, m_departure{ std::move(departure) }, m_operational{ operational },
          m_platform{ std::move(platform) }
        {}

        impl(const impl& another)
        : m_arrival{ another.m_arrival }, m_departure{ another.m_departure }, m_operational{ another.m_operational },
          m_platform{ another.m_platform } {};

        impl(impl&& another)
        : m_arrival{ std::move(another.m_arrival) }, m_departure{ std::move(another.m_departure) },
          m_operational{ another.m_operational }, m_platform{ std::move(another.m_platform) } {};


        // functions

        friend bool operator_equal(const impl& one, const impl& another)
        {
            return one.m_arrival == another.m_arrival && one.m_departure == another.m_departure &&
                   one.m_operational == another.m_operational && one.m_platform == another.m_platform;
        }

        void operator_assign(const impl& another)
        {
            impl temp{ another };
            std::swap(m_arrival, temp.m_arrival);
            std::swap(m_departure, temp.m_departure);
            std::swap(m_operational, temp.m_operational);
            std::swap(m_platform, temp.m_platform);
        }

        void operator=(impl&& another)
        {
            impl temp{ std::move(another) };
            std::swap(m_arrival, temp.m_arrival);
            std::swap(m_departure, temp.m_departure);
            std::swap(m_operational, temp.m_operational);
            std::swap(m_platform, temp.m_platform);
        }

        const time_type& arrival() const
        {
            return m_arrival;
        }

        const time_type& departure() const
        {
            return m_departure;
        }

        bool passing() const
        {
            return !m_arrival.initialized() && !m_departure.initialized();
        }

        bool operational() const
        {
            return m_operational;
        }

        const string_type& platform() const
        {
            return m_platform;
        }


    private:
        // variables

        time_type m_arrival;

        time_type m_departure;

        bool m_operational;

        string_type m_platform;
    };


    stop::stop(time_type arrival, time_type departure, const bool operational, string_type platform)
    : m_p_impl{ std::make_unique<impl>(std::move(arrival), std::move(departure), operational, std::move(platform)) }
    {}

    stop::stop(const stop& another) : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) } {}

    stop::stop(stop&& another) : m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) } {}

    stop::~stop() = default;

    bool operator==(const stop& one, const stop& another)
    {
        return operator_equal(*one.m_p_impl, *another.m_p_impl);
    }

    stop& stop::operator=(const stop& another)
    {
        m_p_impl->operator_assign(*another.m_p_impl);
        return *this;
    }

    stop& stop::operator=(stop&& another)
    {
        m_p_impl->operator_assign(std::move(*another.m_p_impl));
        return *this;
    }

    const stop::time_type& stop::arrival() const
    {
        return m_p_impl->arrival();
    }

    const stop::time_type& stop::departure() const
    {
        return m_p_impl->departure();
    }

    bool stop::passing() const
    {
        return m_p_impl->passing();
    }

    bool stop::operational() const
    {
        return m_p_impl->operational();
    }

    const stop::string_type& stop::platform() const
    {
        return m_p_impl->platform();
    }
}
