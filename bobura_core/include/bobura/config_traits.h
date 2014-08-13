/*! \file
    \brief The definition of bobura::config_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_CONFIGTRAITS_H)
#define BOBURA_CONFIGTRAITS_H

#include <tetengo2.h>


namespace bobura
{
   /*!
        \brief The class template for a configuration traits.

        \tparam String        A string type.
        \tparam UInt          An unsigned integer type.
        \tparam Encoder       An encoder type.
        \tparam ConfigDetails A detail implementation type of a configuration.
    */
    template <typename String, typename UInt, typename Encoder, typename ConfigDetails>
    class config_traits
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The unsigned integer type.
        using uint_type = UInt;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The detail implementation type of the configuration.
        using config_details_type = ConfigDetails;

        //! The configuration base type.
        using config_base_type = tetengo2::config::config_base<string_type, uint_type>;

        //! The configuration list type.
        using config_list_type = tetengo2::config::config_list<string_type, uint_type>;

        //! The cached configuration type.
        using cached_config_type = tetengo2::config::cached_config<string_type, uint_type>;

        //! The temporary configuration type.
        using temporary_config_type = tetengo2::config::temporary_config<string_type, uint_type>;

        //! The persistent configuration type.
        using persistent_config_type =
            tetengo2::config::persistent_config<string_type, uint_type, encoder_type, config_details_type>;


    };


}


#endif
