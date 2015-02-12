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

        \tparam String         A string type.
        \tparam Dialog         A progress dialog type.
        \tparam Timer          A timer type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename String, typename Dialog, typename Timer, typename MessageCatalog>
    class exec_json_reading_task
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The dialog type.
        using dialog_type = Dialog;

        //! The abstract window type.
        using abstract_window_type = typename dialog_type::base_type;

        //! The timer type.
        using timer_type = Timer;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;


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
