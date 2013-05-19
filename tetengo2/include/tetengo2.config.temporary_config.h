/*! \file
    \brief The definition of tetengo2::config::temporary_config.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_TEMPORARYCONFIG_H)
#define TETENGO2_CONFIG_TEMPORARYCONFIG_H

#include <unordered_map>
//#include <utility>

//#include <boost/optional.hpp>

#include "tetengo2.config.config_base.h"
#include "tetengo2.cpp11.h"


namespace tetengo2 { namespace config
{
    /*!
        \brief The class template for a temporary configuration.

        \tparam String A string type.
        \tparam UInt   An unsigned integer type.
    */
    template <typename String, typename UInt>
    class temporary_config : public config_base<String, UInt>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The unsigned integer type.
        typedef UInt uint_type;

        //! The base type.
        typedef config_base<string_type, uint_type> base_type;

        //! The value type.
        typedef typename base_type::value_type value_type;


        // constructors and destructor

        /*!
            \brief Creates a temporary configuration.
        */
        temporary_config()
        :
        m_values()
        {}

        /*!
            \brief Creates a temporary configuration.

            \tparam InputIterator An input iterator type.

            \param first The first position of values.
            \param last  The last position of values.
        */
        template <typename InputIterator>
        temporary_config(const InputIterator first, const InputIterator last)
        :
        m_values(first, last)
        {}

        /*!
            \brief Destroys the temporary configuration.
        */
        virtual ~temporary_config()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef std::unordered_map<string_type, value_type> key_value_type;


        // variables

        key_value_type m_values;


        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key)
        const override
        {
            const typename key_value_type::const_iterator found = m_values.find(key);
            return found != m_values.end() ? boost::make_optional<value_type>(found->second) : boost::none;
        }

        virtual void set_impl(const string_type& key, value_type value)
        override
        {
            m_values[key] = std::move(value);
        }


    };


}}


#endif