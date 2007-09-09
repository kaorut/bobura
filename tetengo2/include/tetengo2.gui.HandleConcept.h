/*! \file
    \brief The definition of tetengo2::HandleConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_HANDLECONCEPT_H)
#define TETENGO2_HANDLECONCEPT_H

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class for handles.

        \param Handle A handle type.
    */
    template <typename Handle>
    class HandleConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a handle.
        */
        void constraints()
        {
            boost::function_requires<
                boost::CopyConstructibleConcept<Handle>
            >();
            boost::function_requires<boost::AssignableConcept<Handle> >();
            boost::function_requires<
                boost::EqualityComparableConcept<Handle>
            >();
        }

    };

}}

#endif
