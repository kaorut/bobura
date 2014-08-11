/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADE_H)
#define BOBURA_MODEL_STATIONINFO_GRADE_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The class template for a station grade.

        \tparam String A string type.
    */
    template <typename String>
    class grade : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name()
        const
        {
            return name_impl();
        }


    protected:
        // constructors and destructor

        /*!
            \brief Destroys the grade.
        */
        virtual ~grade()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // virtual functions

        virtual const string_type& name_impl()
        const = 0;


    };


    /*!
        \brief The class template for a local station grade.

        \tparam String A string type.
    */
    template <typename String>
    class local : public grade<String>
    {
    public:
        // types

        //! The base type.
        using base_type = grade<String>;


        // static functions

        /*!
            \brief Returns the instance of the local.

            \return The instance of the local.
        */
        static const local& instance()
        {
            static const local singleton{};

            return singleton;
        }


    private:
        // constructors and destructor

        virtual ~local()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // virtual functions

        virtual const typename local::string_type& name_impl()
        const override
        {
            static const typename local::string_type singleton{ TETENGO2_TEXT("local") };
            return singleton;
        }


    };

    /*!
        \brief The class template for a principal station grade.

        \tparam String A string type.
   */
    template <typename String>
    class principal : public grade<String>
    {
    public:
        // types

        //! The base type.
        using base_type = grade<String>;


        // static functions

        /*!
            \brief Returns the instance of the principal.

            \return The instance of the principal.
        */
        static const principal& instance()
        {
            static const principal singleton{};

            return singleton;
        }


    private:
        // constructors and destructor

        virtual ~principal()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // virtual functions

        virtual const typename principal::string_type& name_impl()
        const override
        {
            static const typename principal::string_type singleton{ TETENGO2_TEXT("principal") };
            return singleton;
        }


    };

    /*!
        \brief The class template for a local terminal station grade.

        \tparam String A string type.
    */
    template <typename String>
    class local_terminal : public grade<String>
    {
    public:
        // types

        //! The base type.
        using base_type = grade<String>;


        // static functions

        /*!
            \brief Returns the instance of the local terminal.

            \return The instance of the local terminal.
        */
        static const local_terminal& instance()
        {
            static const local_terminal singleton{};

            return singleton;
        }


    private:
        // constructors and destructor

        virtual ~local_terminal()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // virtual functions

        virtual const typename local_terminal::string_type& name_impl()
        const override
        {
            static const typename local_terminal::string_type singleton{ TETENGO2_TEXT("local terminal") };
            return singleton;
        }


   };

    /*!
        \brief The class template for a principal terminal station grade.

        \tparam String A string type.
    */
    template <typename String>
    class principal_terminal : public grade<String>
    {
    public:
        // types

        //! The base type.
        using base_type = grade<String>;


        // static functions

        /*!
            \brief Returns the instance of the principal terminal.

            \return The instance of the principal terminal.
        */
        static const principal_terminal& instance()
        {
            static const principal_terminal singleton{};

            return singleton;
        }


    private:
        // constructors and destructor

        virtual ~principal_terminal()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // virtual functions

        virtual const typename principal_terminal::string_type& name_impl()
        const override
        {
            static const typename principal_terminal::string_type singleton{ TETENGO2_TEXT("principal terminal") };
            return singleton;
        }


    };


    /*!
        \brief The class template for a grade type set.

        \tparam String A string type.
    */
    template <typename String>
    class grade_type_set : boost::noncopyable
    {
    public:
        // types

        //! The grade type.
        using grade_type = grade<String>;

        //! The local type.
        using local_type = local<String>;

        //! The principal type.
        using principal_type = principal<String>;

        //! The local terminal type.
        using local_terminal_type = local_terminal<String>;

        //! The principal terminal type.
        using principal_terminal_type = principal_terminal<String>;


    private:
        // forbidden operations

        grade_type_set()
        = delete;


    };


}}}

#endif
