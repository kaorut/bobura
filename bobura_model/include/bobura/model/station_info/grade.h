/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADE_H)
#define BOBURA_MODEL_STATIONINFO_GRADE_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2/text.h>

#include <bobura/type_list.h>


namespace bobura::model::station_info {
    /*!
        \brief The class for a station grade.
    */
    class grade : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::common::string_type;


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name() const
        {
            return name_impl();
        }


    protected:
        // constructors and destructor

        /*!
            \brief Destroys the grade.
        */
        virtual ~grade() = default;


    private:
        // virtual functions

        virtual const string_type& name_impl() const = 0;
    };


    /*!
        \brief The class for a local station grade.
    */
    class local : public grade
    {
    public:
        // types

        //! The base type.
        using base_type = grade;


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

        virtual ~local() = default;


        // virtual functions

        virtual const typename local::string_type& name_impl() const override
        {
            static const typename local::string_type singleton{ TETENGO2_TEXT("local") };
            return singleton;
        }
    };

    /*!
        \brief The class for a principal station grade.
   */
    class principal : public grade
    {
    public:
        // types

        //! The base type.
        using base_type = grade;


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

        virtual ~principal() = default;


        // virtual functions

        virtual const typename principal::string_type& name_impl() const override
        {
            static const typename principal::string_type singleton{ TETENGO2_TEXT("principal") };
            return singleton;
        }
    };

    /*!
        \brief The class for a local terminal station grade.
    */
    class local_terminal : public grade
    {
    public:
        // types

        //! The base type.
        using base_type = grade;


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

        virtual ~local_terminal() = default;


        // virtual functions

        virtual const typename local_terminal::string_type& name_impl() const override
        {
            static const typename local_terminal::string_type singleton{ TETENGO2_TEXT("local terminal") };
            return singleton;
        }
    };

    /*!
        \brief The class for a principal terminal station grade.
    */
    class principal_terminal : public grade
    {
    public:
        // types

        //! The base type.
        using base_type = grade;


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

        virtual ~principal_terminal() = default;


        // virtual functions

        virtual const typename principal_terminal::string_type& name_impl() const override
        {
            static const typename principal_terminal::string_type singleton{ TETENGO2_TEXT("principal terminal") };
            return singleton;
        }
    };


    /*!
        \brief The class for a grade type set.
    */
    class grade_type_set : private boost::noncopyable
    {
    public:
        // types

        //! The grade type.
        using grade_type = grade;

        //! The local type.
        using local_type = local;

        //! The principal type.
        using principal_type = principal;

        //! The local terminal type.
        using local_terminal_type = local_terminal;

        //! The principal terminal type.
        using principal_terminal_type = principal_terminal;


    private:
        // forbidden operations

        grade_type_set() = delete;
    };
}

#endif
