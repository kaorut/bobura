/*! \file
    \brief The definition of bobura::application.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(BOBURA_APPLICATION_H)
#define BOBURA_APPLICATION_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>
#include <tetengo2.detail.h>

#include <bobura/settings.h>


namespace bobura
{
   /*!
        \brief The class template for a bobura application.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class application : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.

        using traits_type = Traits;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The position type.
        using position_type = typename traits_type::position_type;

        //! The dimension type.
        using dimension_type = typename traits_type::dimension_type;

        //! The settings type.
        using settings_type = settings<string_type, position_type, dimension_type>;

        //! The detail implementation set type.
        using detail_impl_set_type = tetengo2::detail::base::impl_set;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param settings        Settings of the bobura.
            \param detail_impl_set A detail implementation set.
        */
        application(settings_type& settings, const detail_impl_set_type& detail_impl_set);

        /*!
            \brief Destroys the bobura application.
        */
        ~application()
        noexcept;


        // functions

        /*!
            \brief Runs the main process of the application.

            \return The exit status code.
        */
        int run();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}

#endif
