/*! \file
    \brief The definition of bobura::model::serializer::exec_json_reading_task.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H)
#define BOBURA_MODEL_SERIALIZER_EXECJSONREADINGTASK_H


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reading task execution.

        \tparam Dialog A progress dialog type.
        \tparam Timer  A timer type.
    */
    template <typename Dialog, typename Timer>
    class exec_json_reading_task
    {
    public:
        // types

        //! The dialog type.
        using dialog_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename dialog_type::abstract_window_type;

        //! The string type.
        using string_type = typename dialog_type::string_type;

        //! The message catalog type.
        using message_catalog_type = typename dialog_type::message_catalog_type;

        //! The timer type.
        using timer_type = Timer;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        exec_json_reading_task(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        m_parent(parent),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Execute a JSON reading task.
        */
        void operator()()
        const
        {

        }


    private:
        // variables

        abstract_window_type& m_parent;

        const message_catalog_type& m_message_catalog;


    };


}}}


#endif
