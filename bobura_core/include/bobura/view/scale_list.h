/*! \file
    \brief The definition of bobura::view::scale_list.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_SCALELIST_H)
#define BOBURA_VIEW_SCALELIST_H

#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>


namespace bobura { namespace view
{
    /*!
        \brief The class template for a view scale list.

        \tparam Size   A size type.
        \tparam String A string type.
        \tparam Scale  A scale type.
    */
    template <typename Size, typename String, typename Scale>
    class scale_list : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The string type.
        using string_type = String;

        //! The scale type.
        using scale_type = Scale;


        // constructors and destructor

        /*!
            \brief Creates a view scale list.
        */
        scale_list();

        /*!
            \brief Destroys the view scale list.
        */
        ~scale_list();


        // functions

        /*!
            \brief Returns the scale count.

            \return The scale count.
        */
        size_type size()
        const;

        /*!
            \brief Returns the scale at the specified index.

            \param index An index.

            \return The scale.

            \throw std::out_of_range When index is out of range.
        */
        const scale_type& at(size_type index)
        const;

        /*!
            \brief Returns the scale label at the specified index.

            \param index An index.

            \return The scale label.

            \throw std::out_of_range When index is out of range.
        */
        const string_type& label_at(size_type index)
        const;

        /*!
            \brief Returns the same scale index.

            \param scale A scale.

            \return The same scale index.
        */
        boost::optional<size_type> index_of(const scale_type& scale)
        const;

        /*!
            \brief Returns the nearest larger scale.
        
            \param scale A scale.

            \return The nearest larger scale.
        */
        const scale_type& larger(const scale_type& scale)
        const;

        /*!
            \brief Returns the nearest smaller scale.
        
            \param scale A scale.

            \return The nearest smaller scale.
        */
        const scale_type& smaller(const scale_type& scale)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
