/*! \file
    \brief The definition of bobura::model::station_info::grade.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADE_H)
#define BOBURA_MODEL_STATIONINFO_GRADE_H

#include <boost/core/noncopyable.hpp>

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
        const string_type& name() const;


    protected:
        // constructors and destructor

        /*!
            \brief Creates a station grade.
        */
        grade();

        /*!
            \brief Destroys the station grade.
        */
        virtual ~grade();


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
        static const local& instance();


        // constructors and destructor

        /*!
            \brief Destroys the local station grade.
        */
        virtual ~local();


    private:
        // constructors

        local();


        // virtual functions

        virtual const typename local::string_type& name_impl() const override;
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
        static const principal& instance();


        // constructors and destructor

        /*!
            \brief Destroys the principal station grade.
        */
        virtual ~principal();


    private:
        // constructors

        principal();


        // virtual functions

        virtual const typename principal::string_type& name_impl() const override;
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
        static const local_terminal& instance();


        // constructors and destructor

        /*!
            \brief Destroys the local terminal station grade.
        */
        virtual ~local_terminal();


    private:
        // constructors

        local_terminal();


        // virtual functions

        virtual const typename local_terminal::string_type& name_impl() const override;
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
        static const principal_terminal& instance();


        // constructors and destructor

        /*!
            \brief Destroys the principal terminal station grade.
        */
        virtual ~principal_terminal();


    private:
        // constructors

        principal_terminal();


        // virtual functions

        virtual const typename principal_terminal::string_type& name_impl() const override;
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
