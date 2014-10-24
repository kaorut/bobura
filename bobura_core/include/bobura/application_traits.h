/*! \file
    \brief The definition of bobura::application_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_APPLICATIONTRAITS_H)
#define BOBURA_APPLICATIONTRAITS_H


namespace bobura
{
   /*!
        \brief The class template for an application traits.

        \tparam String       A string type.
        \tparam Position     A position type.
        \tparam Dimension    A dimension type.
        \tparam ConfigTraits A configuration traits type.
    */
    template <typename String, typename Position, typename Dimension, typename ConfigTraits>
    class application_traits
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The configuration traits type.
        using config_traits_type = ConfigTraits;


    };


}


#endif
